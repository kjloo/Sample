//Kaleb Loo
//memory.cpp
//CPSC 351
//2/21/14
//
//
//Purpose: This program will simulate three different memory management
//         algorithms used to manage virtual memory mapping.  The included
//         algorithms are First Come First Serve (FCFS), Optimal (OPT),
//         and Least Recently Used (LRU).  
//Input: The user will input parameters into the UNIX command line.  The first
//       parameter is the name of the file where the virtual addresses are
//       listed.  The second is the abbreviated name of the algorithm they
//       wish to simulate.  The third is the page offset length for the
//       virtual addresses.  The forth is the number of physical pages in the
//       memory they wish to simulate.
//Process: The program will receive the inputs as command line inputs and will
//         then perform error checking in order to determine if the command was
//         given properly.  In particular, the program will check is the
//         correct number of parameters were given, if the name of the
//         algorithm is valid, if the page offset is valid, and if the number
//         of physical pages is valid.  The program will then store this
//         information along with the file name into local variables.  With
//         this information the program is then able to initialize the
//         physical memory as well as the page table.  The program then reads
//         the given input file, verifies that it can open, and puts the data
//         into a list.  With everything setup, the program will then simulate
//         the memory management algorithms.  For this process, the virtual
//         addresses will be read from the list.  Each address is then shifted
//         by the appropriate amount determined by the page offset.  The
//         program then checks the page table for whether or not a page fault
//         occurs.  If so, the program invokes the page replacement algorithm
//         determined by the user input.  After the entire list is read, the
//         program will disply what is in the physical memory and will also
//         show the hit rate of the algorithm.  The program will then exit.
//Example:
//1000 Page Fault
//2000 Page Fault
//3000 Page Fault
//40b0 Page Fault
//1001 Hit
//2001 Hit
//5002 Page Fault
//1002 Page Fault
//2001 Page Fault
//3000 Page Fault
//40a0 Page Fault
//5000 Page Fault

//Memory (final state) :
//Physical page 1:    4
//Physical page 2:    5
//Physical page 3:    2
//Physical page 4:    3
//
//Hit rate: 2 / 12 (16.6667%)
//
//
//Output: The program will output the virtual memory address that is being
//        analyzed followed by whether or not there was a page fault attempting
//        to access said address.
//        The program will output the final state of the physical memory.
//        The program will display the hit rate of the algorithm
//

#include <iostream>
#include <iomanip>
#include <string>
#include <fstream>
#include <cmath>
#include <list>

using namespace std;

//Global Constants
const int MAX_ADDRESS_SIZE = 16;
const int BASE = 2;
const int NUM_OF_PARAMETERS = 5;
const string FCFS = "FCFS";
const string OPT = "OPT";
const string LRU = "LRU";

//Create Table Entry Struct
struct PageEntry {
  int pageNumber;
  bool validBit;
  int frameNumber;
  int index;
};

//Functions
void loadParameters(int argc, char* argv[], char*&fileName, char*&algorithm,
					int &pageOffset, int &numOfPages);
//Loads the parameters from the command line arguments into local variables.
//Checks to see if arguments are valid.
//IN: argc, argv[]
//OUT: fileName, algorithm, pageOffset, numOfPages

void initMemory(int* memory, int numOfPages);
//Initilizes the data in memory to an invalid page -1.
//IN: numOfPages
//MODIFY: memory

void initTable(PageEntry* table, int virtualPageSize);
//Initializes the data in the page table to that of a new page table.
//IN: virtualPageSize
//MODIFY: table

void readFile(list<int> &data, char* fileName);
//Reads the input file and outputs the data into a list.
//IN: fileName
//MODIFY: data

void simulate(list<int> data, char* algorithm, int pageOffset,
			  int numOfPages, int* memory, PageEntry* table);
//Runs the virtual memory management algorithm and displays the results.
//IN: data, algorithm, pageOffset, numOfPages
//MODIFY: memory, table

void insertPage(int* memory, PageEntry* table, int index,
				int pageNumber, int count);
//Places the virtual page into memory and updates the page table using a
//given index.
//IN: index, pageNumber, count
//MODIFY: memory, table

void pageReplace(list<int> &data, list<int>::iterator i, char* algorithm,
				 int pageNumber, int pageOffset, int numOfPages, int count,
				 int* memory, PageEntry* table, int &index);
//Determines which index in physical memory to replace based on the algorithm.
//IN: data, i, algorithm, pageNumber, pageOffset, numOfPages, count
//MODIFY: memory, table, index

bool memFull(int* memory, int numOfPages);
//Determines whether or not the physical memory is full.
//IN: memory, numOfPages
//OUT: true/false

int findOPT(list<int> &data, list<int>::iterator i, int* memory,
			int pageOffset, int numOfPages);
//Finds the index to replace using the optimal algorithm.
//IN: data, i, memory, pageOffset, numOfPages
//OUT: index

int findLRU(int* memory, PageEntry* table, int numOfPages, int count);
//Finds the index to replace using the least recently used algorithm.
//IN: memory, table, numOfPages, count
//OUT: index

int findMax(int* arr, int numOfPages);
//Finds the maximum element in an array.
//IN: arr, numOfPages
//OUT: index

void printMemory(PageEntry* table, int* memory, int numOfPages);
//Prints the contents of memory.
//IN: table, memory, numOfPages

void printHitRate(int hitCount, int count); 
//Prints the hit rate of the algorithm.
//IN: hitCount, count

void deallocate(int* memory, PageEntry* table);
//Deallocates the dynamic memory used in the program.
//MODIFY: memory, table

int main(int argc, char* argv[])
{
  //List to store data
  list<int> data;

  //Command line variables
  char* fileName;
  char* algorithm;
  int pageOffset;
  int numOfPages;

  //Calculated values
  int virtualPageSize;
  
  //Data Structures
  int* memory;
  PageEntry* table;

  //Check/Load in parameters
  try {
	loadParameters(argc, argv, fileName, algorithm, pageOffset, numOfPages);
  }catch(string e) {
	cerr << "Error: " << e << endl;
	exit(-1);
  }

  //Calculate values
  virtualPageSize = (int) pow((double) BASE, MAX_ADDRESS_SIZE - pageOffset);
  
  //Create Table
  memory = new int[numOfPages];
  table = new PageEntry[virtualPageSize];

  //Initialize Data
  initMemory(memory, numOfPages);
  initTable(table, virtualPageSize);

  //Read File
  readFile(data, fileName);

  //Simulate Memory Management with the given file
  simulate(data, algorithm, pageOffset, numOfPages, memory, table);
  
  //Deallocate Memory
  deallocate(memory, table);
  return 0;
}

void loadParameters(int argc, char* argv[], char*&fileName, char*&algorithm,
					int &pageOffset, int &numOfPages)
{
  //Check if number of parameters is correct
  if(argc == NUM_OF_PARAMETERS) {
	fileName = argv[1];
	algorithm = argv[2];
	pageOffset = atoi(argv[3]);
	numOfPages = atoi(argv[4]);
  }else {
	throw string("Invalid Number of Parameters");
  }
  
  //Check if Parameters are valid
  if(algorithm != FCFS && algorithm != OPT && algorithm != LRU)
	throw string("Algorithm not recognized");
  if(pageOffset <= 0 || pageOffset >= MAX_ADDRESS_SIZE)
	throw string("Page offset is outside of allowable bounds");
  if(numOfPages <=0)
	throw string("Number of pages should be a positive integer");
}

void initMemory(int* memory, int numOfPages)
{
  for(int i = 0; i < numOfPages; i++) {
	memory[i] = -1;
  }
}

void initTable(PageEntry* table, int virtualPageSize)
{
  for(int i = 0; i < virtualPageSize; i++) {
	table[i].validBit = false;
	table[i].index = 0;
  }
}

void readFile(list<int> &data, char* fileName)
{
  ifstream inFile;
  int virtualAddress;
  
  inFile.open(fileName);
  if(!inFile.fail()) {
	while(inFile >> hex >> virtualAddress) {
	  //Load data into list
	  data.push_back(virtualAddress);
	}
  }else {
	cerr << "Error opening file: " << fileName << endl;
	exit(-1);
  }
  inFile.close();
}

void simulate(list<int> data, char* algorithm, int pageOffset,
			  int numOfPages, int* memory, PageEntry* table)
{
  //Create Counts
  int hitCount;
  int count;
  
  //Create Local Variables
  int pageNumber;
  int virtualAddress;
  int index;

  //Initialize Counts
  hitCount = 0;
  count = 0;
  index = -1;
  
  //Iterate through data
  for(list<int>::iterator i = data.begin(); i != data.end(); i++) {
	//Convert to Page Number
	virtualAddress = *i;
	pageNumber = virtualAddress >> pageOffset;
	cout << hex << virtualAddress << " ";
	//Check for a page fault
	if(!table[pageNumber].validBit) {
	  cout << "Page Fault" << endl;
	  //Load Data into Memory
	  pageReplace(data, i, algorithm, pageNumber, pageOffset, numOfPages,
				  count, memory, table, index);
	}else {
	  //Increment Hit and Update table for historical data
	  cout << "Hit" << endl;
	  table[pageNumber].index = count;
	  hitCount++;
	}
	count++;
  }
  cout << endl;
  
  //Print Results
  printMemory(table, memory, numOfPages);
  printHitRate(hitCount, count);
}

void insertPage(int* memory, PageEntry* table, int index,
				int pageNumber, int count)
{
  //Set the valid bit for the page being replaced to 0
  table[memory[index]].validBit = false;
  //Update memory and page table with new data
  memory[index] = pageNumber;
  table[pageNumber].frameNumber = index;
  table[pageNumber].validBit = true;
  table[pageNumber].index = count;
}

void pageReplace(list<int> &data, list<int>::iterator i, char* algorithm,
				 int pageNumber, int pageOffset, int numOfPages, int count,
				 int* memory, PageEntry* table, int &index)
{
  //Check if memory is full
  if(!memFull(memory, numOfPages)) {
	index++;
  }else {
	if(algorithm == FCFS) {
	  index++;
	  if(index >= numOfPages)
		index = 0;
	}else if(algorithm == OPT) {
	  index = findOPT(data, i, memory, pageOffset, numOfPages);
	}else {
	  index = findLRU(memory, table, numOfPages, count);
	}
  }
  insertPage(memory, table, index, pageNumber, count);
}

bool memFull(int* memory, int numOfPages)
{
  int i = 0;
  while(i < numOfPages && memory[i] >=0)
	i++;
  return i >= numOfPages;
}

int findOPT(list<int> &data, list<int>::iterator i, int* memory,
			int pageOffset, int numOfPages)
{
  int index;
  int* opt = new int[numOfPages];
  list<int>::iterator j;
  for(int k = 0; k < numOfPages; k++) {
	j = i;
	while(j != data.end() && (*j >> pageOffset) != memory[k]) {
	  j++;
	}
	opt[k] = distance(i, j);
  }
  index = findMax(opt, numOfPages);
  delete[] opt;
  return index;
  
}

int findLRU(int* memory, PageEntry* table, int numOfPages, int count)
{
  int index;
  int* lru = new int[numOfPages];
  for(int i = 0; i < numOfPages; i++) {
	lru[i] = count - table[memory[i]].index;
  }
  index = findMax(lru, numOfPages);
  delete[] lru;
  return index;
}

int findMax(int* arr, int numOfPages)
{
  int max;
  int index = 0;
  max = arr[index];
  for(int i = 1; i < numOfPages; i++) {
	if(arr[i] > max) {
	  max = arr[i];
	  index = i;
	}
  }
  return index;
}

void printMemory(PageEntry* table, int* memory, int numOfPages)
{;
  cout << dec;
  cout << "Memory (final state) :" << endl;
  for(int i = 0; i < numOfPages; i++) {
	if(table[memory[i]].validBit)
	cout << "Physical page " << i + 1 << ": " << memory[i]<< endl;
  }
  cout << endl;
}

void printHitRate(int hitCount, int count)
{
  const double PERCENT = 100;
  double rate = ((double) hitCount / (double) count) * PERCENT;
  cout << dec;
  cout << "Hit rate: " << hitCount << " / " << count
	   << " (" << rate << "%)" << endl;
}

void deallocate(int* memory, PageEntry* table)
{
  delete[] memory;
  delete[] table;
}
