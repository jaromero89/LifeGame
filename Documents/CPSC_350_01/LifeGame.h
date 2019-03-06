/*
  a. Full Name: James Romero
  b. Student ID: 2334232
  c. Chapman email: jaromero@chapman.edu
  d. Course number and section: 350-1
  e. Assignment Number: 02
  */

#include <iostream>
#include <cstring>
#include <string>
#include <fstream>

using namespace std;
//Variables X and Dash will be used in every matrix printed representing dead and alive cells
int const X = 1;
int const dash = 0;

class LifeGame{
public:
  LifeGame(); // constructor
  ~LifeGame(); // destructor
  ///////////////////////////////////////////////////////////////////////////////////////////////////////////
  //Setup
  //////////////////////////////////////////////////////////////////////////////////////////////////////////
  void introduction();//Gives the user a brief introduction of the "The Game of Life."
  void userchoice(); //asks questions to the user regarding input, mode, and output settings
  void createMatrix(); // creates the initial array based off either a .txt file or population density
  void baseSize(); // sets the sizes for array, with "original" being the original size of the grid, and "array" being +2
  void InitializebaseMatrix(int **arr); //SET UP: filling initially
  void pushMatrix(int **arr1, int **arr2); //SET UP: Pushes "InitializebaseMatrix" anothe matrix
  void checkIfEmpty(int **arr); //SET UP: checks to see if the grid has emptied
  void pauseEnterOrOutput(); //SET UP: checks to see if the program should pause, wait for enter, or just output to txt
  void Complete_System_Data(); //sets up the game using the set up methods above
  //////////////////////////////////////////////////////////////////////////////////////////////////////////
  //Game mode Initializer : works by filling outer boundaries of matrix which are dependent on mode type: Classic. Donut, and Mirror
  //////////////////////////////////////////////////////////////////////////////////////////////////////////
  void GameModeMatrix(int **arr); // This function will fillout  the outerbounds of the matrix in accorandance the game modes selected
  bool checkIfStable(int **arr1, int **arr2); //checks to see if stable
 //////////////////////////////////////////////////////////////////////////////////////////////////////////
 //Print and utility functions
 //////////////////////////////////////////////////////////////////////////////////////////////////////////
  void Display_Base_Array(int **arr); //Displays base matrix
  void fill_all_matrix(); // fill array with either dash or x value until completely filled
  void PrintMatrix_Per_Gen(); //utility function
  void Copy_to_File(int **arr); //prints the resulting grids to an output file
  //////////////////////////////////////////////////////////////////////////////////////////////////////////
  //Imperative to the makeup functionality of the program
  //////////////////////////////////////////////////////////////////////////////////////////////////////////
  void Game_of_Life(); //runs the game loop
  //////////////////////////////////////////////////////////////////////////////////////////////////////////
  //////////////////////////////////////////////////////////////////////////////////////////////////////////

  int **baseMatrix; // original array from file
  int baseMatrixRows; // original row size
  int baseMatrixColumns; //original column size
  int gameModeRows; //original row size + 2 for the outer grid
  int gameModeColumns;//original column size + 2 for the outer grid
  int **presentGen; //current array
  int **nextGen; //next array for copying purposes
  char modeChoice; // Current mode you are playing classic, doughnut, or mirror mode!
  char pause_or_output; //for checking if you will be using either pause, play, or output!
  float density; // for random generation of a grid based on the dimensions and density input
  std::string outputFileString; // output stream name
  std::ofstream outputFileStream; // output stream
  std::string inputFileString; // input string name
  std::ifstream inputFileStream; // input stream
  bool readFile; //checks to see if reading from a file.
  //bool oArrayExists; //checks to see if the original array exists.
  int trackGen; //keeps track of the generation
  int X_Counter; //Counts nuber of X's in the matrix, while making checks to stop program

};
