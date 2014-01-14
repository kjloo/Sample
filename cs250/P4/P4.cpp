//Kaleb Loo
//P4.cpp
//CPSC 250
//5/1/13
//Purpose: This program is designed to test the functionality of the
//         quasiUniqueQ class.  It will read integer data from a file, and use
//         the quasiUniqueQ functionality to store, filter,
//         and output the data. The input data comes from a file named
//         P4Input.txt and the output data goes into a file named P4Output.txt.
//Input: The user has to press enter to run the program.
//       The program uses data from a file named P4Input.txt
//Process: The program clears the screen.  The program displays a welcome
//         message that informs the user of the functionality of the program.
//         The program then assumes that the user has a file called
//         P4Input.txt and opens said file and then reads the
//         data integer by integer, and attempts to enqueue them onto the
//         queue. The data is successfully enqueued to the queue
//         when the integer is odd or the first instance of an even number.
//         The data is ordered in the queue by priority.
//         The program loads data until there is no more data to read.
//         The program then dequeues the data from the queue and writes
//         the data into a file called P4Output.txt.  It does this until
//         the queue is empty.  The program then displays a goodbye message
//         that informs the user that process is complete.  All methods
//         related to the selective priority queue are in the quasiUniqueQ.h
//         header file.
//Output: The program displays a welcome message.
//        The program outputs a text file
//        The program displays a goodybe message

using namespace std;

#include <iostream>
#include <cstring>
#include <iomanip>
#include <fstream>
#include "quasiUniqueQ.h"

//Global Constants
const string INFILENAME = "P4Input.txt";
const string OUTFILENAME = "P4Output.txt";

void clearScreen();
//clears the screen

void welcome();
//displays a welcome message to the user

bool fileRead(quasiUniqueQ& queue);
//reads data from a file and places it into the queue
//returns true if data is read and false if data is not read
//IN: INFILENAME data
//MODIFY: queue
//OUT: true/false

void fileWrite(quasiUniqueQ& queue);
//writes data from the queue into a file
//MODIFY: queue
//OUT: OUTFILENAME data

void goodbye();
//displays a goodbye message to the user

int main()
{
  //Variable Declaration
  quasiUniqueQ testData;

  //Function Execution
  clearScreen();
  welcome();
  if (fileRead(testData)) {
	cout << "The data has been read from the file. The program will \n"
		 << "now dequeue the data and write to an output file. \n";
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
  cout << "Welcome!  This program will test a selective priority queue \n"
	   << "by taking the data from a file named " << INFILENAME << " and \n"
	   << "attempting the enqueue the data onto a queue. \n";
  cout << "Press <Enter>";
  cin.get();
}

bool fileRead(quasiUniqueQ& queue)
{
  int count = 0;
  int data;
  ifstream inFile;
  //Open file
  inFile.open(INFILENAME.c_str());
  //Read from file
  while (inFile >> data) {
	queue.enqueue(data);
	count++;
  }
  inFile.close();
  return (count > 0);
}

void fileWrite(quasiUniqueQ& queue)
{
  ofstream outFile;
  //open file
  outFile.open (OUTFILENAME.c_str());
  //Write to file
  while (!queue.isEmpty())
	outFile << queue.dequeue() << "\n";
  outFile.close();
}

void goodbye()
{
  cout << "The data has been dequeued from the queue and put into a file \n"
	   << "called " << OUTFILENAME << ". Goodbye! \n\n";
}
