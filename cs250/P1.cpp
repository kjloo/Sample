//Kaleb Loo
//P1.cpp
//CPSC 250
//4/4/13
//Purpose: This program is designed to test the functionality of the
//         sPS class.  It will read integer data from a file, and use
//         the sPS functionality to store, filter, and output the data.
//         The input data comes from a file named P1Input1.txt and the
//         output data goes into a file named P1Output.txt.
//Input: The user has to press enter to run the program.
//       The program uses data from a file named P1Input1.txt
//Process: The program clears the screen.  The program displays a welcome
//         message that informs the user of the functionality of the program.
//         The program then assumes that the user has a file called
//         P1Input1.txt and opens said file and then reads the
//         data integer by integer, and attempts to push them onto the stack.
//         The data is successfully pushed onto the stack when the integer
//         is a prime number that is one less than a multiple of three.
//         The program does this until there is no more data to read.
//         The program then pops the data off of the stack and writes
//         the data into a file called P1Output.txt.  It does this until
//         the stack is empty.  The program then displays a goodbye message
//         that informs the user that process is complete.
//Output: The program displays a welcome message.
//        The program outputs a text file
//        The program displays a goodybe message

using namespace std;

#include <iostream>
#include <cstring>
#include <iomanip>
#include <fstream>
#include "sPS.h"

//Global Constants
const string INFILENAME = "P1Input1.txt";
const string OUTFILENAME = "P1Output.txt";

void clearScreen();
//clears the screen

void welcome();
//displays a welcome message to the user

bool fileRead(sPS& stack);
//reads data from a file and places it onto the stack
//returns true if data is read and false if data is not read
//MODIFY: stack
//OUT: true/false

void fileWrite(sPS& stack);
//writes data from the stack into a file
//MODIFY: stack
//OUT: P1Output.txt

void goodbye();
//displays a goodbye message to the user

int main()
{
  //Variable Declaration
  sPS testData;

  //Function Execution
  clearScreen();
  welcome();
  if (fileRead(testData)) {
	cout << "The data has been read from the file. The program will \n"
		 << "now pop the data and write to an output file. \n";
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
  cout << "Welcome!  This program will test a selective prime stack \n"
	   << "by taking the data from a file named " << INFILENAME << " and \n"
	   << "attempting the push the data onto a stack. \n";
  cout << "Press <Enter>";
  cin.get();
}

bool fileRead(sPS& stack)
{
  int count = 0;
  int data;
  ifstream inFile;
  //Open file
  inFile.open(INFILENAME.c_str());
  //Read from file
  while (inFile >> data) {
	stack.push(data);
	count++;
  }
  inFile.close();
  return (count > 0);
}

void fileWrite(sPS& stack)
{
  ofstream outFile;
  //open file
  outFile.open (OUTFILENAME.c_str());
  //Write to file
  while (!stack.isEmpty())
	outFile << stack.pop() << "\n";
  outFile.close();
}

void goodbye()
{
  cout << "The data has been popped off the stack and put into a file \n"
	   << "called " << OUTFILENAME << ". Goodbye! \n\n";
}
