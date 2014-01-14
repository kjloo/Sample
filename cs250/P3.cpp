//Kaleb Loo
//P3.cpp
//CPSC 250
//4/25/13
//Purpose: This program is designed to test the functionality of the
//         parityBST class.  It will read integer data from a file, and use
//         the parityBST functionality to store, sort, filter, transverse,
//         remove, and output the data. The input data comes from a file named
//         P3Input.txt and the output data goes into a file named P3Output.txt.
//Input: The user has to press enter to run the program.
//       The program uses data from a file named P3Input.txt
//Process: The program creates two instances of a parityBST object.
//         One tree is instantiated to store odd integers while the other
//         is instantiated to store even numbers. The ability to choose
//         the type of binary search tree can be seen in parityBST.h.
//         The program clears the screen.  The program displays a welcome
//         message that informs the user of the functionality of the program.
//         The program then assumes that the user has a file called
//         P3Input.txt and opens said file and then reads the
//         data integer by integer, and attempts to insert them into a
//         binary search tree. The data is successfully stored to the tree
//         if the integer is odd and is being inserted into a tree that
//         stores odd numbers or if the integer is even and is being inserted
//         into a tree that stores even integers. The type of integer that
//         a particular tree stores is determined on instantiation and
//         the details can be seen in the parityBST.h header file.
//         The data is ordered in the container following the structure of
//         a binary tree. Each particular integer an a tree can only occur
//         once so no duplicates are stored.
//         The program loads data until there is no more data to read.
//         The program removes multiples of NUM from NUM to MAX from each tree.
//         The program then traverses the data in the tree in order and writes
//         the data into a file called P3Output.txt.  It does this until
//         the entire tree has been traversed.  The program then displays a
//         goodbye message that informs the user that process is complete.
//         All methods related to the parity binary search tree are in the
//         parityBST.h header file.
//Output: The program displays a welcome message.
//        The program outputs a text file
//        The program displays a goodybe message

using namespace std;

#include <iostream>
#include <cstring>
#include <iomanip>
#include <fstream>
#include "parityBST.h"

//Global Constants
const string INFILENAME = "P3Input.txt";
const string OUTFILENAME = "P3Output.txt";
const int NUM = 3;
const int MAX = 100;

void clearScreen();
//clears the screen

void welcome();
//displays a welcome message to the user

bool fileRead(parityBST& oddBST, parityBST& evenBST);
//reads data from a file and places it into a tree
//returns true if data is read and false if data is not read
//IN: INFILENAME data
//MODIFY: oddBST, evenBST
//OUT: true/false

void removal(parityBST& oddBST, parityBST& evenBST);
//removes all multiples of 3 between 0 and 100 from each tree
//MODIFY: oddBST, evenBST

void fileWrite(parityBST& oddBST, parityBST& evenBST);
//writes data from the trees into a file
//IN: oddBST, evenBST
//OUT: OUTFILENAME data

void goodbye();
//displays a goodbye message to the user

int main()
{
  //Constants for class instantiation
  bool ODD = true;
  bool EVEN = false;
  //Variable Declaration
  parityBST testData1(ODD);
  parityBST testData2(EVEN);

  //Function Execution
  clearScreen();
  welcome();
  if (fileRead(testData1, testData2)) {
	cout << "The data has been read from the file. The program will \n"
		 << "now read the data from the tree and write to an output file. \n";
	cout << "Press <Enter>";
	cin.get();
	removal(testData1, testData2);
	fileWrite(testData1, testData2);
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
  cout << "Welcome!  This program will test a parity binary search tree \n"
	   << "by taking the data from a file named " << INFILENAME << " and \n"
	   << "attempting the insert the data into a binary search tree. \n";
  cout << "Press <Enter>";
  cin.get();
}

bool fileRead(parityBST& oddBST, parityBST& evenBST)
{
  int count = 0;
  int data;
  ifstream inFile;
  //Open file
  inFile.open(INFILENAME.c_str());
  //Read from file
  while (inFile >> data) {
	oddBST.insertNode(data);
	evenBST.insertNode(data);
	count++;
  }
  inFile.close();
  return (count > 0);
}

void removal(parityBST& oddBST, parityBST& evenBST)
{
  for (int i = NUM; i < MAX; i+=NUM) {
	oddBST.removeNode(i);
	evenBST.removeNode(i);
  }
}

void fileWrite(parityBST& oddBST, parityBST& evenBST)
{
  ofstream outFile;
  //open file
  outFile.open (OUTFILENAME.c_str());
  //write to file
  outFile << "First Set of Data\n";
  oddBST.outputList(outFile);
  outFile << "Second Set of Data\n";
  evenBST.outputList(outFile);
  
  //close file
  outFile.close();
}

void goodbye()
{
  cout << "The data has been dequeued from the queue and put into a file \n"
	   << "called " << OUTFILENAME << ". Goodbye! \n\n";
}
