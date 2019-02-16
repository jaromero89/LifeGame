/*
  a. Full Name: James Romero
  b. Student ID: 2334232
  c. Chapman email: jaromero@chapman.edu
  d. Course number and section: 350
  e. Assignment Number: 01
  */
#include <iostream>
#include <string>//for stings
#include <cstring>
#include <fstream>
#include <math.h>
#include <random>
#include <cstdlib>
#include <ctime>

using namespace std;
int a, t, c, g;
int aa, tt, cc, gg, at, ac, ag, ta, tc, tg, ct, ca, cg, ga, gt, gc;
int mean, sum, variance, listCount;
string z, p, dna;

void calcsum(int x, int sum);//Calculate some of dna strands
int calsum(int sum);//return calcsum
int getlistCounter(int listCount);//used to calculate total list
int calcmean(int mean, int sum, int listCount);//Mean
int getvariance(int variance, int mean, string word);
int thes_lenght(int s_lenght, int variance, int listCount);
void bigram(string z);
void checkNA(string p);
string probPrint();
string printBi;
//counts number of DNA strands within the line
void printtooutfile(ofstream& getFile, int& sum, int& mean, int& variance, int& s_lenght, string& prob_main, string& printBi);


int main(int argc, char* argv[])
{

  int x;
  int s_lenght;
  string prob_main;
  string reRun = "y";
  string filename;
  string word;
  string dNA;
  string nucleotide;
  ifstream inFile;
  ofstream getFile("JamesLRomeroz.txt", ios::app);
  //readFile(filename,inFile);
  cout << "Enter in text file: " << endl;
  cin >> filename;// function allows program to take in text file
  inFile.open(filename);

    if (inFile.fail())// Check the validaty of user input
    {
      cerr << "File not found." << endl;
      cout << "Would you like to enter another file: y or ctrl+z" << endl;
      cin >> reRun;
     while(reRun .compare("y") != 0 && reRun.compare("n") != 0)//User char choice
      {
        cout << "Please enter \"y\" to run the program again or \"n\" to exit." << endl;
        cin >> reRun;
      }
      //reRun = tolower(reRun);
      exit(1);
    }
    else//program continue to run its course once valid input is taken
      for(string line; getline(inFile, line);)//For loop used as a way to iterate through the text file to calculate sum, mean bigram, while doing a list count
      {
      cout << line << endl;
      calcsum(line.length(), sum);
      cout << calsum(sum) << endl;
      calsum( sum);
      bigram(line);
      checkNA(line);
      getlistCounter(listCount);
      calcmean(mean, sum,listCount);
      cout << sum << endl;
      cout << mean << endl;
      cout << listCount << endl;
      inFile.close();
      inFile.open("inFile.txt");
      for(string line2; getline(inFile, line2);) //for loop used to calculate variance
      {
        variance += ((word.length() - mean) * (word.length() - mean)); //Algoritm used to process variance count
      }
      cout <<"Variance: " << variance << endl;

      string printBi;

      printtooutfile(getFile, sum, mean, variance, s_lenght, prob_main, printBi);

      int counting = 0;

        while(counting < 1000)
        {
          //if(calc.gaussianDist() == calc.getMean())
          //{
            counting++;
            getFile << probPrint();
        //  }

        }
      getFile.close();
    }
    cin >> reRun;
    while(reRun .compare("y") != 0 && reRun.compare("n") != 0)
    {
      cout << "Please enter \"y\" to run the program again or \"n\" to exit." << endl;
      cin >> reRun;
    }
    return 0;
  }
}

  void calcsum(int x, int sum)
  {
    sum += x;
  }
  int calsum(int sum)
  {
    return sum;
  }

  int getlistCounter(int listCount)
  {
    listCount+=1;
    return listCount;
  }
  int calcmean(int mean, int sum, int listCount)
  {
    mean = sum/listCount;
    return mean;
  }
  int getvariance(int variance, int mean, string word)
  {
    variance += (word.length() - mean) * (word.length() - mean);
    return variance;
  }
  int thes_lenght(int s_lenght, int variance, int listCount)
  {
    s_lenght = sqrt((variance)/(listCount-1));
    return sqrt((variance));
  }

  void printtooutfile(ofstream& getFile, int& sum, int& mean, int& variance, int& s_lenght, string& prob_main, string& printBi)
  {
    getFile << "James Romero\n2280432\nAssignment 1"<< endl;
    getFile << "Sum: " << sum << endl;
    getFile << "Mean: " << mean << endl;
    getFile << "Variance: " << variance << endl;
    getFile << "Standard deviation of length: " << s_lenght << endl;
    getFile << prob_main << endl;
    getFile << "Bigram Probablitiy: \n" << printBi << endl;
  }
  //Function used to check for all bigrams, but if there is a letter that is not A, T, C, or G
  //it will break the loop but keep everything it read so far
  void bigram(string z)
  {
    string dna;
    string ck;

    for(int i = 0; i < dna.length()-1; i++)
    {

      ck = "";
      ck.append(dna,i,2);
      transform(ck.begin(), ck.end(), ck.begin(), ::toupper);
      //cout << ck << endl;
      //cout << ck.compare("AA") << endl;
      if(ck.compare("AA") == 0)
      {
        aa += 1;
      }
      else if(ck.compare("AT") == 0)
      {
        at +=1;
      }
      else if(ck.compare("AC") == 0)
      {
        ac +=1;
      }
      else if(ck.compare("AG") == 0)
      {
        ag +=1;
      }
      else if(ck.compare("TT") == 0)
      {
        tt +=1;
      }
      else if(ck.compare("TA") == 0)
      {
        ta +=1;
      }
      else if(ck.compare("TC") == 0)
      {
        tc +=1;
      }
      else if(ck.compare("TG") == 0)
      {
        tg +=1;
      }
      else if(ck.compare("CC") == 0)
      {
        cc +=1;
      }
      else if(ck.compare("CG") == 0)
      {
        cg +=1;
      }
      else if(ck.compare("CA") == 0)
      {
        ca +=1;
      }
      else if(ck.compare("CT") == 0)
      {
        ct +=1;
      }
      else if(ck.compare("GG") == 0)
      {
        gg +=1;
      }
      else if(ck.compare("GC") == 0)
      {
        gc +=1;
      }
      else if(ck.compare("GA") == 0)
      {
        at +=1;
      }
      else if(ck.compare("GT") == 0)
      {
        gt +=1;
      }
      else
      {
        cout << "Did not match the qualified letters of A, T, C, or G." << endl;
        break;
      }
    }
  }

  void checkNA(string p)
  {
    string check;
    for(int i = 0; i < dna.length(); i++)
    {
      check = (dna[i]);
      transform(check.begin(), check.end(), check.begin(), ::toupper);
      //cout << check << endl;
      if(check.compare("A") == 0)
      {
        a += 1;
      }
      else if(check.compare("T") == 0)
      {
        t +=1;
      }
      else if(check.compare("C") == 0)
      {
        c +=1;
      }
      else if(check.compare("G") == 0)
      {
        g +=1;
      }

      else
      {
        cout << "Did not match the qualified letters of A, T, C, or G." << endl;
        break;
      }
    }
  }

  string probPrint()
  {
    srand(time(NULL));
    int aA = (int)(((double)a/sum)*100);
    int tT = (int)(((double)t/sum)*100);
    int cC = (int)(((double)c/sum)*100);
    int ggg = (int)(((double)g/sum)*100);
    int r = (rand() % 100) + 1;
    cout << r << endl;
    cout << (int)(((double)a/sum)*100) << endl;
    if(r <= aA)
    {
      return "A";
    }
    else if(r <= (tT + aA))
    {
      return "T";
    }
    else if(r <= (cC + tT + aA))
    {
      return "C";
    }
    else
    {
      return "G";
    }
  }
