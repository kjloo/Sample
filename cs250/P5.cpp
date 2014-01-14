//Kaleb Loo
//P5.cpp
//CPSC 250
//5/21/13
//Purpose: This program is designed to test the functionality of the
//         hashTable class.  It will read text data from a file, and use
//         the hashTable functionality to store, count, filter, format,
//         process, and output the data. The input data comes from a file named
//         P5Input.txt and the output data goes into a file named P5Output.txt.
//         The output data will be a list of the top 50 most frequently used
//         words.
//Input: The user has to press enter to run the program.
//       The program uses data from a file named P5Input.txt
//       The program uses data from a file named filter.txt
//Process: The program clears the screen.  The program displays a welcome
//         message that informs the user of the functionality of the program.
//         The program then assumes that the user has a file called
//         P5Input.txt and opens said file and then reads the
//         data "word" by "word", and attempts to store them in the
//         hash table. The data is successfully stored to the hash table
//         when the word is not a commonly used word such as articles,
//         prepositions, and pronouns. The specific list of words can be found
//         in the filter.txt file, which the user should have.
//         When there is an attempt to insert a word that is already in the
//         hash table, the hashTable class will increment a count to
//         represent how frequently the word occured.
//         The program loads data until there is no more data to read.
//         The program then outputs the top 50 most frequently used words from
//         the hash table to a file called P5Output.txt using the hashTable.h
//         output functionality.
//         The program then displays a goodbye message
//         that informs the user that process is complete.  All methods
//         related to the hash table are in the hashTable.h
//         header file.
//Output: The program displays a welcome message.
//        The program outputs a text file
//        The program displays a goodybe message

using namespace std;

#include <iostream>
#include <cstring>
#include <iomanip>
#include <fstream>
#include "hashTable.h"

//Global Constants
const string INFILENAME = "P5Input.txt";
const string OUTFILENAME = "P5Output.txt";
const int LISTSIZE = 50;

void clearScreen();
//clears the screen

void welcome();
//displays a welcome message to the user

bool fileRead(hashTable& table);
//reads data from a file and places it into the hash table
//returns true if data is read and false if data is not read
//IN: INFILENAME data
//MODIFY: table
//OUT: true/false

void fileWrite(hashTable& table);
//writes data into a file
//IN: table
//OUT: OUTFILENAME data

void goodbye();
//displays a goodbye message to the user

int main()
{
  //Variable Declaration
  hashTable testData;
  
  //Function Execution
  clearScreen();
  welcome();
  if (fileRead(testData)) {
	cout << "The data has been read from the file. The program will \n"
		 << "now process the data and write the top 50 words\n"
		 << "to an output file. \n";
	cout << "Press <Enter>";
	cin.get();
	fileWrite(testData);
	goodbye();
  }else
	cout << "Error: No Data was Read! \n";
  return 0;
}

void clearScreen()
{
  const int SCREENHEIGHT = 25;
  for (int i = 0; i < SCREENHEIGHT; i++)
	cout << "\n";
}

void welcome()
{
  cout << "Welcome!  This program will test a hash table \n"
	   << "by taking the data from a file named " << INFILENAME << " and \n"
	   << "attempting to insert the data into the hash table. \n";
  cout << "Press <Enter>";
  cin.get();
}

bool fileRead(hashTable& table)
{
  int count = 0;
  string data;
  ifstream inFile;
  //Open file
  inFile.open(INFILENAME.c_str());
  //Read from file
  while (inFile >> data) {
	table.insert(data);
	count++;
  }
  inFile.close();
  return (count > 0);
}

void fileWrite(hashTable& table)
{
  ofstream outFile;
  //open file
  outFile.open (OUTFILENAME.c_str());
  //Write to file
  table.outputData(outFile, LISTSIZE);
  outFile.close();
}

void goodbye()
{
  cout << "The data has been analyzed and put into a file \n"
	   << "called " << OUTFILENAME << ". Goodbye! \n\n";
}
