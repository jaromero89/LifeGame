/*
  a. Full Name: James Romero
  b. Student ID: 2334232
  c. Chapman email: jaromero@chapman.edu
  d. Course number and section: 350
  e. Assignment Number: 01
  */

#include "LifeGame.h"
#include <iostream>
#include <cstring>
#include <string>
#include <fstream>
#include <cstdlib>
#include <cmath>

using namespace std;

LifeGame :: LifeGame() // Constructor
{
	density = 0;//If User chooses a random generation , they must input a density float value within the range of 0-1
	X_Counter = 0;// Count the X characters per generation
}
//Destructer will be used to close all open file streams, essentially freeing up memory
LifeGame :: ~LifeGame() //Destructs all open streams and all the dynamically allocated arrays
{
	if (outputFileStream.is_open())
	{
		outputFileStream.close();
	}
	if (inputFileStream.is_open())
	{
		inputFileStream.close();
	}

 }
 //Provides User with a Print Element in hopes to bring elegance to the Game of Life
 void LifeGame :: introduction()
 {
	 cout << "-------------------------------------------------------------------" ;
	 cout << "\n\t\t-x-x-x-x-x-Game of Life-x-x-x-x-x\n";
	 cout << "-------------------------------------------------------------------" << endl;
	 cout << "\t                       By: J.H. Conway\n" << endl;
	 cout << "-------------------------------------------------------------------" << endl;
	 cout << "\n Game of Life is a simulation that models \n";
	 cout << " the life cycle of bacteria, providing \n" ;
	 cout << " entertainment wrapped up in what some \n";
   cout << " would call mathematical elegance.\n" << endl;
	 cout << "-------------------------------------------------------------------" ;
 }
void LifeGame :: userchoice() // User will have the option of providing a game file or choosing a random assignment
{
	string ynReadFile;
	while(ynReadFile != "file" && ynReadFile != "random")
	{
	cout << "\n Would you like to start with a random configuration, or a flatfile configuration? \n";
	cout << "Respond with 'file' or 'random': ";
	cin >> ynReadFile;

	if (ynReadFile == "file")
	{
		readFile = true;
		cout << "Please enter .txt file name: ";
		cin >> inputFileString;
		inputFileStream.open(inputFileString.c_str());
		//baseSize();
		string line;
		getline (inputFileStream, line);
		baseMatrixRows = atoi(line.c_str());
		getline (inputFileStream, line);
		baseMatrixColumns = atoi(line.c_str());

		gameModeRows = baseMatrixRows + 2;
		gameModeColumns = baseMatrixColumns + 2;
	}
	if(ynReadFile == "random")
	{
	//	baseSize();
	cout << "Please enter the height of your random grid: ";
	cin >> baseMatrixRows;
	cout << "Please enter the width of your random grid: ";
	cin >> baseMatrixColumns;

	gameModeRows = baseMatrixRows +2;
	gameModeColumns = baseMatrixColumns +2;

	cout << "Please enter the desired population density in the form of a decimal(between 0 and 1): ";
	cin >> density;
	}
}
	cout << "Now you will choose boundary conditions. \n" << endl;
	cout << "Boundary Modes and Conditions: \n" << endl;
	cout << "\nClassic Mode: All locations off the grid are considered to be empty "<< endl;
	cout << "Doughnut mode: The grid is wrapped around itself horizontally and vertically, " << endl;
	cout << "resulting in a torus (doughnut) shape." << endl;
	cout << "Mirror Mode: References off the grid are bounced back as though the wall were" << endl;
	cout << "a mirror. " << endl;

	cout << "Choose boundary mode: Classic, Doughnut, or Mirror? type C, D, or M: ";
	cin >> modeChoice;
	cout << "Do you wish to have the game Pause after each generation, hit 'enter' on keyboard to continue, or output results? Type P or O: ";
	cin >> pause_or_output;
	if ((pause_or_output == 'O') || (pause_or_output == 'o'))
	{
		cout << "Please enter the name of the file you would like to output to: ";
		cin >> outputFileString;
		outputFileStream.open(outputFileString.c_str(), ios::out | ios::app);
	}
}
//2D array help file: Used as a way to help me understand a 2d array
/*
// C++ Program to print the elements of a
// Two-Dimensional array
#include<iostream>
using namespace std;

int main()
{
    // an array with 3 rows and 2 columns.
    int x[3][2] = {{0,1}, {2,3}, {4,5}};

    // output each array element's value
    for (int i = 0; i < 3; i++)
    {
        for (int j = 0; j < 2; j++)
        {
            cout << "Element at x[" << i
                 << "][" << j << "]: ";
            cout << x[i][j]<<endl;
        }
    }

    return 0;
		Output:

Element at x[0][0]: 0
Element at x[0][1]: 1
Element at x[1][0]: 2
Element at x[1][1]: 3
Element at x[2][0]: 4
Element at x[2][1]: 5
} */
void LifeGame :: createMatrix() // CreATES MATRIX
{
	baseMatrix = new int*[gameModeRows];
	for (int i = 0; i < gameModeRows; ++i) //DESTRUCT BOTH LATER!!!!
	{
		baseMatrix[i] = new int[gameModeColumns];
	}
	presentGen = new int*[gameModeRows];
	for (int a = 0; a < gameModeRows; ++a) //DESTRUCT BOTH LATER!!!!
	{
		presentGen[a] = new int[gameModeColumns];
	}

	nextGen = new int*[gameModeRows];
	for (int b = 0; b < gameModeRows; ++b) //DESTRUCT BOTH LATER!!!!
	{
		nextGen[b] = new int[gameModeColumns];
	}
}
// Initializes a matrix based on the userchoice function, hence( Random || FILE )
void LifeGame :: InitializebaseMatrix(int **arr)
{
	string line;

	// Pulls data from file and fills the rows and colums of the mnatrix
	if (readFile)
	{
		for (int s = 1; s < gameModeRows -1; ++s)
		{
			getline (inputFileStream, line);
			for (int b = 1; b < gameModeColumns - 1; ++b)
			{
				if ((line[b-1] == 'X') || (line[b-1] == 'x'))//files rolls and colums with x values
				{
					arr[s][b] = X; //Ofcourse using a 2D array to properly store x and dash values
				}
				else if (line[b-1] == '-')
				{
					arr[s][b] = dash;
				}
			}
		}


	}
	//Initializes matrix based on density
	else if (density > 0)
	{
		int row = 0;
		int column = 0;
		int xPopulation=(baseMatrixRows*baseMatrixColumns)*(density); // gets the number of x's to put in grid

		for (int s = 1; s < gameModeRows -1; ++s) // fills grid with dashes first
		{
			for (int b = 1; b < gameModeColumns - 1; ++b)
			{
				arr[s][b] = dash;
			}
		}

		while (xPopulation > 0)//Rand used to fill matrix with x's in "random areas which will be based on the density"
		{
			row = rand() % baseMatrixRows + 1;
			column = rand() % baseMatrixColumns + 1;
			if (arr[row][column] != X)
			{
				arr[row][column] = X;
				--xPopulation;
			}

		}

	}
}
//Big O notation of O(1) used in the GameModeMatrix function.
//The outer boundaries will be filled based on the mode selected: Classic , Donut and mirror
void LifeGame :: GameModeMatrix(int **arr) // Fill sides of array based off of the mode selected
{
	//sets to empty the outside rows and columns.  baseMatrix as argument for initial, nextGen for game loop
	if((modeChoice == 'C') || (modeChoice == 'c'))
	{

		for (int a = 0; a < gameModeRows; ++a)
		{
			for (int b = 0; b < gameModeColumns; ++b)
			{
				if((a == 0) || (a == gameModeRows-1))
				{
					arr[a][b] = dash;
				}
				if ((b == 0) || (b == gameModeColumns-1))
				{
					arr[a][b] = dash;
				}
			}
		}
	}
	//sets to doughnut mode/mirror mode. baseMatrix as argument for initial, nextGen for game loop
	if( ((modeChoice == 'D') || (modeChoice == 'd')) || ((modeChoice == 'M') || (modeChoice == 'm')) )
	{																				///////////////////////////
		for (int a = 1; a < gameModeRows-1; ++a)//Big O notation: O(n^2)////
		{
			for (int b = 1; b < gameModeColumns-1; ++b) //^ ^ ^ ^ ^
			{																	//////////////////////////////
				if((a == 1) && (b == 1)) //left corner side of Matrix
				{
					if ((modeChoice == 'D') || (modeChoice == 'd'))
					{
						arr[a-1][b-1] = arr[gameModeRows-2][gameModeColumns-2];
					}																																		///////////
					if ((modeChoice == 'M') || (modeChoice == 'm'))									/////Algorithm//////
					{																													///////////Joshua Smith///////
						arr[a-1][b-1] = arr[a][b];																		///////////////////
						arr[a-1][b] = arr[a][b];
						arr[a][b-1] = arr[a][b];
					}
				}
				if( (a == 1) && ((b > 1) && (b < gameModeColumns -2)) )// top middle of Matrix
				{
					if ((modeChoice == 'D') || (modeChoice == 'd'))
					{
						arr[a-1][b-1] = arr[gameModeRows-2][b-1];
						arr[a-1][b] =  arr[gameModeRows -2][b];
						arr[a-1][b+1] = arr[gameModeRows -2][b+1];
					}
					if ((modeChoice == 'M') || (modeChoice == 'm'))
					{
						arr[a-1][b] = arr[a][b];

					}
				}
				if ((a == 1) && (b == gameModeColumns - 2)) // right corner of matrix
				{
					if ((modeChoice == 'D') || (modeChoice == 'd'))
					{
						arr[a-1][b+1] = arr[gameModeRows - 2][1];
					}
					if ((modeChoice == 'M') || (modeChoice == 'm'))
					{
						arr[a-1][b] = arr[a][b];
						arr[a-1][b+1] = arr[a][b];
						arr[a][b+1] = arr[a][b];
					}
				}
				if ( ((a > 1) && (a < gameModeRows - 2)) && (b == gameModeColumns - 2) ) // right middle of matrix
				{
					if ((modeChoice == 'D') || (modeChoice == 'd'))
					{
						arr[a-1][b+1] = arr[a-1][1];
						arr[a][b+1] = arr[a][1];
						arr[a+1][b+1] = arr[a+1][1];
					}
					if ((modeChoice == 'M') || (modeChoice == 'm'))
					{
						arr[a][b+1] = arr[a][b];
					}
				}
				if ( (a == gameModeRows -2) && (b == gameModeColumns - 2) ) // bottom right corner of matrix
				{
					if ((modeChoice == 'D') || (modeChoice == 'd'))
					{
						arr[a+1][b+1] = arr[1][1];
					}
					if ((modeChoice == 'M') || (modeChoice == 'm'))
					{
						arr[a][b+1] = arr[a][b];
						arr[a+1][b+1] = arr[a][b];
						arr[a+1][b] = arr[a][b];
					}
				}
				if ( (a == gameModeRows -2) && ((b < gameModeColumns - 2) && (b > 1)) ) // bottom of matrix
				{
					if ((modeChoice == 'D') || (modeChoice == 'd'))
					{
						arr[a+1][b+1] = arr[1][b+1];
						arr[a+1][b] = arr[1][b];
						arr[a+1][b-1] = arr[1][b-1];
					}
					if ((modeChoice == 'M') || (modeChoice == 'm'))
					{
						arr[a+1][b] = arr[a][b];
					}
				}
				if ((a == gameModeRows -2) && (b == 1)) // bottom left corner of matrix
				{
					if ((modeChoice == 'D') || (modeChoice == 'd'))
					{
						arr[a+1][b-1] = arr[1][gameModeColumns -2];
					}
					if ((modeChoice == 'M') || (modeChoice == 'm'))
					{
						arr[a+1][b] = arr[a][b];
						arr[a+1][b-1] = arr[a][b];
						arr[a][b-1] = arr[a][b];
					}
				}
				if ( ((a < gameModeRows - 2) && (a > 1)) && (b == 1) ) // left middle of matrix
				{
					if ((modeChoice == 'D') || (modeChoice == 'd'))
					{
						arr[a+1][b-1] = arr[a+1][gameModeColumns -2];
						arr[a][b-1] = arr[a][gameModeColumns - 2];
						arr[a-1][b-1] = arr[a-1][gameModeColumns - 2];
					}
					if ((modeChoice == 'M') || (modeChoice == 'm'))
					{
						arr[a][b-1] = arr[a][b];
					}
				}

			}
		}
	}

}
// Example of an algorithm found on GitHub
//Used another method because this way was to many lines of code and inefficent
//Big O of O(2n) and 2X
/*void DonutMode::checkNeighbors(int row, int col) //check neighbor of only one cell
{
	neighborCount = 0;
	if(checkBound(row-1,col))//top
	{
		if(checkFilled(row-1,col))
			neighborCount++;
	}
	else if(!checkBound(row-1,col)) //if top is out of bounds, go to bottom
	{
		if(checkFilled(modulo(row-1,rowCount),col))
			neighborCount++;
	}
	if(checkBound(row,col-1)) //left
	{
		if(checkFilled(row,col-1))
			neighborCount++;
	}
*/
void LifeGame :: checkIfEmpty(int **arr) // Check to see if array has emptied, so you can quit the game later
{
	int result = 0;
	for (int s = 0; s < gameModeRows; ++s)
	{

		for (int b = 0; b < gameModeColumns; ++b)
		{
			if (arr[s][b] == X)
			{
				result +=1;
			}

		}
	}
	 X_Counter = result;
}

bool LifeGame :: checkIfStable(int **arr1, int **arr2) // checks to see if the array has stablized, so you can quit later
{
	for (int s = 0; s < gameModeRows; ++s)
	{

		for (int b = 0; b < gameModeColumns; ++b)
		{
			if (arr1[s][b] != arr2[s][b])
			{
				return false;
			}

		}
	}

	return true;

}



void LifeGame :: pushMatrix(int **from, int **to) // Copies one array's contents to another array
{
	for (int s = 0; s < gameModeRows; ++s)
	{

		for (int b = 0; b < gameModeColumns; ++b)
		{
			if (from[s][b] == X)
			{
				to[s][b] = X;
			}
			else if (from[s][b] == dash)
			{
				to[s][b] = dash;
			}
		}
	}

}


void LifeGame :: Display_Base_Array(int ** arr) // print original array
{
	cout << trackGen << endl;
	for (int s = 1; s < gameModeRows - 1; ++s)
	{

		for (int b = 1; b < gameModeColumns - 1; ++b)
		{
			if (arr[s][b] == X)
			{
				cout << "X";
			}
			else if (arr[s][b] == dash)
			{
				cout << "-";
			}
		}
		cout << endl;
	}
	++trackGen;

}
void LifeGame :: fill_all_matrix() // UTIL PRINT
{
	cout << trackGen << endl;
	for (int s = 1; s < gameModeRows - 1; ++s)
	{

		for (int b = 1; b < gameModeColumns - 1; ++b)
		{
			if (presentGen[s][b] == X)
			{
				cout << "X";
			}
			else if (presentGen[s][b] == dash)
			{
				cout << "-";
			}
		}
		cout << endl;
	}

}

void LifeGame :: PrintMatrix_Per_Gen() //utility purposes , prints presentGen array
{
	cout << trackGen << endl;
	for (int s = 0; s < gameModeRows; ++s)
	{

		for (int b = 0; b < gameModeColumns; ++b)
		{
			if (presentGen[s][b] == X)
			{
				cout << "X";
			}
			else if (presentGen[s][b] == dash)
			{
				cout << "-";
			}
		}
		cout << endl;
	}
	++trackGen;

}
void LifeGame :: Copy_to_File(int **arr) // print to a file (stream is closed in the destructor)
{
	outputFileStream << trackGen << endl;
	if(outputFileStream.is_open())
	{
		for (int s = 1; s < gameModeRows - 1; ++s)
		{
			for (int b = 1; b < gameModeColumns - 1; ++b)
			{
				if (arr[s][b] == X)
				{
					outputFileStream << "X";
				}
				else if (arr[s][b] == dash)
				{
					outputFileStream << "-";
				}
			}
			outputFileStream << endl;
		}
	}
	++trackGen;
}

void LifeGame:: Complete_System_Data() // set up the game intially
{
	//by creating the arrays, filling in the array inside based off file/density
	//filling in the outer part of the array
	//copying the original setup to the presentGen array
  introduction();
	userchoice();
	createMatrix();
	InitializebaseMatrix(baseMatrix);
	GameModeMatrix(baseMatrix);
	pushMatrix(baseMatrix, presentGen);
	checkIfEmpty(presentGen);
	pauseEnterOrOutput();

}

void LifeGame :: pauseEnterOrOutput() //Either prompts for a continue key, or prints everything to a file based on your preference
{
	if ((pause_or_output == 'P') || (pause_or_output == 'p'))
	{
		Display_Base_Array(presentGen);
		cout << "Please press enter to continue simulation: " << endl;
		cin.get();
	}
	if ((pause_or_output == 'O') || (pause_or_output == 'o'))
	{
		Copy_to_File(presentGen);
	}
}
// Guide referenced from "chasetoyo" on how to use the pause feature
/*
cout << "\n---------------------------------------------------\n\n";
    cout << "Enter '1' for a brief pause" << endl;
    cout << "Enter '2' to press 'enter' to advance" << endl;
    cout << "Enter '3' to output to a file" << endl;
    cin >> proceedChoice;
    while(proceedChoice != 1 && proceedChoice != 2 && proceedChoice != 3) //error checking for bad input
    {
        cout << "Error. Please enter '1' or '2' or '3'" << endl;
        cin >> proceedChoice;
*/

void LifeGame ::Game_of_Life()
{
	// At this point, the arrays have been set up initially, the
	//boundary mode has been set, and the printer functionality
	//should already be set up too.

	////////////////////////////////////////////////////////////////////
	// Checks array and fills it in according to the Game of LifeGame rules
	////////////////////////////////////////////////////////////////////
	while ( X_Counter != 0)
	{

		for (int s = 1; s < gameModeRows -1; ++s)
		{
			for (int b = 1; b < gameModeColumns -1; ++b)
			{
				//case 1: One or Fewer Neighbors
				if ((presentGen[s-1][b]) + (presentGen[s-1][b+1]) + (presentGen[s][b+1]) + (presentGen[s+1][b+1]) + (presentGen[s+1][b]) +
					(presentGen[s+1][b-1]) + (presentGen[s][b-1]) + (presentGen[s-1][b-1]) <= 1)
				{
					nextGen[s][b] = dash;
				}
				//case 2: 2 Neighbors
				if ((presentGen[s-1][b]) + (presentGen[s-1][b+1]) + (presentGen[s][b+1]) + (presentGen[s+1][b+1]) + (presentGen[s+1][b]) +
					(presentGen[s+1][b-1]) + (presentGen[s][b-1]) + (presentGen[s-1][b-1]) == 2)
				{
					nextGen[s][b] = presentGen[s][b];
				}
				//case 3 : 3 Neighbors
				if ((presentGen[s-1][b]) + (presentGen[s-1][b+1]) + (presentGen[s][b+1]) + (presentGen[s+1][b+1]) + (presentGen[s+1][b]) +
					(presentGen[s+1][b-1]) + (presentGen[s][b-1]) + (presentGen[s-1][b-1]) == 3)
				{
					nextGen[s][b] = X;
				}
				//case 4: 4 or More Neighbors
				if ((presentGen[s-1][b]) + (presentGen[s-1][b+1]) + (presentGen[s][b+1]) + (presentGen[s+1][b+1]) + (presentGen[s+1][b]) +
					(presentGen[s+1][b-1]) + (presentGen[s][b-1]) + (presentGen[s-1][b-1]) >= 4)
				{
					nextGen[s][b] = dash;
				}

			}
		}
		// Fill the sides of the array depending on the mode
		GameModeMatrix(nextGen);
		// Exit game if it becomes stable
		if (checkIfStable(presentGen, nextGen))
		{
			if ((pause_or_output == 'O') || (pause_or_output == 'o'))
			{
				if(outputFileStream.is_open())
				{
					outputFileStream << "The grid is stable. Program end. " << endl;
				}
			}
			else
			{
				cout << "The grid is stable. Program end. " << endl;
			}
			break;

		}

		// copy to presentGen, nextGen remains the same
		pushMatrix(nextGen, presentGen);
		// It's here where you want to run a method to check if the array is empty
		checkIfEmpty(presentGen);

		pauseEnterOrOutput();//User will choose to use pause or print to a file

	}

}
