//Kaleb Loo
//P6.cpp Version 1.0
//CPSC 250
//6/3/13
//Purpose: This program is designed to populate a file with randomly generated
//         data. It does this using the STL list container and iterator
//         functionality. After the data is generated and loaded,
//         it is filtered and then outputted to a file called P6Output.txt.
//Input: The user has to press enter to run the program.
//Process: The program clears the screen and then displays a welcome message
//         that informs the user of the functionality of the program.
//         The program creates an instance of a list of size NUMELEMENTS.
//         It then randomly generates numbers between 0 and NUMELEMENTS/2
//         and stores them in the list. The program then creates three
//         list iterators that allow for traversal through the list. The
//         data in the list is analyzed in triplets using a filter.
//         The data is acquired through the use of the iterators, one used to
//         point to the first elements, one for the second, and one for the
//         third.  The filter works in the following way. If
//         the first two elements are of opposite parity and the third
//         element is a prime number, then the third element is written to the
//         output file. Each iterator is then incremented and the process
//         repeats until the third iterator falls off of the list. The
//         program then displays a goodbye message that informs the user that
//         the process is complete.
//Output: The program displays a welcome message.
//        The program outputs a text file.
//        The program displays a goodbye message.

using namespace std;

#include <iostream>
#include <iterator>
#include <list>
#include <fstream>
#include <cstring>
#include <ctime>
#include <cmath>

//Global Constants
const string OUTFILENAME = "P6Output.txt";
const int NUMELEMENTS = 2000;

void clearScreen();
//clears the screen

void welcome();
//displays a welcome message to the user

void generateNumbers(list<int>& container);
//generates NUMELEMENTS number of random integers and
//stores them in a container
//MODIFY: container

void fileWrite(list<int>& container);
//writes data from the container into a file
//IN: container
//OUT: OUTFILENAME data

bool filter(int first, int second, int third);
//returns true if first and second are opposite parity and
//third is a prime number and returns a false otherwise
//IN: first, second, third
//OUT: true/false

bool isPrime(int num);
//returns true if a number is prime and returns a false otherwise
//IN: num
//OUT: true/false

void goodbye();
//displays a goodbye message to the user

int main()
{
  //Enable use of random
  srand(time(0));
  //Instantiate container
  list<int> intList;
  clearScreen();
  welcome();
  generateNumbers(intList);
  cout << "Random number have been generated and stored in a container. \n"
	   << "The program will now filter and write the data to a file. \n";
  cout << "Press <Enter>";
  cin.get();
  fileWrite(intList);
  goodbye();
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
  cout << "Welcome!  This program will utilize list iterator \n"
	   << "functionality. Data will be generated randomly and stored\n"
	   << "in a list. \n";
  cout << "Press <Enter>";
  cin.get();
}

void generateNumbers(list<int>& container)
{
  for (int i = 0; i < NUMELEMENTS; i++)
	container.push_back(rand() % NUMELEMENTS/2);
}

void fileWrite(list<int>& container)
{
  //Create iterators
  list<int>::iterator first;
  list<int>::iterator second;
  list<int>::iterator third;
  first = container.begin();
  second = container.begin();
  second++;
  third = container.begin();
  third++;
  third++;

  ofstream outFile;
  //open file
  outFile.open(OUTFILENAME.c_str());
  if (!outFile.fail()) {
	//Write to file
	while (third != container.end()) {
	  //cout << *first << " " << *second << " " << *third << "\n";
	  if (filter(*first, *second, *third))
		outFile << *third << "\n";
	  first++;
	  second++;
	  third++;
	}
  }
  outFile.close();
}

bool filter(int first, int second, int third)
{
  if (!isPrime(third))
	return false;
  return (first % 2 != second % 2);
}

bool isPrime(int num)
{
  if (num <= 1)
	return false;
  else if (num == 2)
	return true;
  else if (num % 2 == 0)
	return false;
  //Data is a number not divisible by 2
  int divisor = 3;
  int threshhold = (int) sqrt(num);
  while (divisor <= threshhold && num % divisor != 0)
	divisor += 2;
  return (divisor > threshhold);
}

void goodbye()
{
  cout << "The data has been analyzed from the container and \n"
	   << "put into a file called " << OUTFILENAME << ". Goodbye! \n\n";
}
