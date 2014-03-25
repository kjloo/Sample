//Kaleb Loo
//states.cpp
//CPSC 351
//1/25/14
//
//Purpose: This program is designed to parse through several files for
//         population data.  It will then display the information in a table.
//         The information displayed is a tally of population sizes of cities,
//         towns, villages, etc. in the given files.  This program will
//         demonstrate programming with threading synchronization.
//Input: The user will tell the program how many threads they want to use.
//       It is assumed that the number of threads will not exceed the amount
//       of files.
//Process: This program will create one or more threads, based on user input,
//         that will parse through a given list of files, which will be found
//         in states.txt.  It is assumed that states.txt is in the current
//         directory and all of the files referenced are also in the current
//         directory.  It is also assumed that states.txt is not empty.  The
//         threads will extract the various population numbers from the files
//         and tally the information within a census struct.  The population
//         numbers are extracted by parsing the input data for integers.
//         The program then checks how large the given population number is
//         and appropriately increments the count in the corresponding range.
//         The main thread will wait for all of the threads to finish and will
//         consolidate the information from each threads tally.  The program
//         will then output the results.  
//Example:
//        Input number of threads: 2
//        1-999:              9204
//        1,000 - 9,999:      7318
//        10,000 - 99,999:    2702
//        100,000 - 999,999:  279
//        1,000,000+:         9
//Output: The program will output a table of the final tally of the population
//        sizes.
//        The program will output any error messages involving creating and
//        joining threads.
//

#include <iostream>
#include <iomanip>
#include <cmath>
#include <fstream>
#include <pthread.h>
#include <errno.h>

using namespace std;

//Global Constants
const string INFILENAME = "states.txt";
const int SIZE = 50;
const char COMMA = ',';

//Create Ranges
const int BORDER1 = 1000;
const int BORDER2 = 10000;
const int BORDER3 = 100000;
const int BORDER4 = 1000000;

//Create Data Struc
struct Census {
  int sec1;
  int sec2;
  int sec3;
  int sec4;
  int sec5;
};

void createList(int threadCount, char ***list);
//Allocates memory for the lists based on the number of threads and
//number of files.
//IN: threadCount
//MODIFY: ***list

int getCount();
//Gets the number of files referenced in states.txt
//OUT: count;

void readFile(int threadCount, char ***list);
//Reads the states.txt file and distributes the referenced files into
//the various lists.
//IN: threadCount
//MODIFY: ***list

void createThread(char **list, pthread_t& tid);
//Creates a thread to parse the census data in the given list
//IN: **list
//MODIFY: tid

Census joinThread(pthread_t tid);
//Waits for a thread to complete and receives the parsed census data.
//IN: tid
//OUT: info

void *tfunc(void *args);
//Reads the given files and tallies the population data into a census struct.
//IN: **list
//OUT: info

void setToZero(Census& info);
//Initializes the census struct to have all tallies at zero.
//MODIFY: info

void tally(int num, Census &info);
//Adds the given population number to the census tally.
//IN: num
//MODIFY: info

void collectData(Census& info, Census data);
//Consolidates various census structs into one.
//IN: data
//MODIFY: info

void print(Census info);
//Prints the census info in the required format.
//IN: info

void deleteList(int threadCount, char ***list);
//Deallocates the list memory
//IN: threadCount
//MODIFY: ***list

int main()
{
  //Initialize Variables
  char ***list;
  int threadCount;
  Census info;
  pthread_t *tid;
  setToZero(info);
  
  //Get User Input
  cout << "Input number of threads: ";
  cin >> threadCount;
  //Create lists/Allocate memory
  list = new char**[threadCount];
  tid = new pthread_t[threadCount];
  createList(threadCount, list);
  
  //Read From File
  readFile(threadCount, list);
  //Create Threads
  for(int i = 0; i < threadCount; i++) {
	createThread(list[i], tid[i]);
  }
  //Join Threads
  for(int i = 0; i < threadCount; i++) {
	collectData(info, joinThread(tid[i]));
  }
  print(info);
  //Deallocate memory
  deleteList(threadCount, list);
  delete[] tid;
  return 0;
}

void createList(int threadCount, char ***list)
{
  //Get total number of files
  int count = getCount();
  //Calculate the distribution of files with room for null terminator
  int listCount = (int) ceil((double) count/threadCount) + 1;
  for(int i = 0; i < threadCount; i++) {
	list[i] = new char*[listCount];
	for(int j = 0; j < listCount; j++) {
	  //Allocate memory if in the correct range
	  if((i + 1) + threadCount * j <= count && j < listCount - 1) 
		list[i][j] = new char;
	  //Set null terminator so program can stop
	  else
		list[i][j] = NULL;
	}
  }
}

int getCount()
{
  int count = 0;
  string data;
  ifstream inFile;
  inFile.open(INFILENAME.c_str());
  if(!inFile.fail()) {
	while(inFile >> data)
	  count++;
	inFile.close();
  }else {
	cerr << "Error opening file: " << INFILENAME << endl;
	exit(-1);
  }
  return count;
}

void readFile(int threadCount, char ***list)
{
  int count = 0;
  int index = 0;
  ifstream inFile;
  //Open File
  inFile.open(INFILENAME.c_str());
  //Read From File
  if(!inFile.fail()) {
	while(inFile >> list[index][count]) {
	  index++;
	  if(index == threadCount) {
		index = 0;
		count++;
	  }
	}
	inFile.close();
  }else {
	cerr << "Error opening file: " << INFILENAME << endl;
  }
}

void createThread(char **list, pthread_t& tid)
{
  int status;
  status = pthread_create(&tid, NULL, tfunc, (void *) list);
  if(status != 0) {
	cerr << "Error creating thread: " << strerror(errno) << endl;
  }
}

Census joinThread(pthread_t tid)
{
  Census data;
  Census *info;
  Census **infop = &info;
  int status;
  status = pthread_join(tid, (void **) infop);
  if(status != 0) {
	cerr << "Error joining thread: " << strerror(errno) << endl;
	exit(-1);
  }
  data = **infop;
  delete info;
  return data;
}

void *tfunc(void *arg)
{
  //Variables
  Census *info = new Census;
  ifstream inFile;
  bool check = false;
  string data;
  int num;
  char **list = (char **) arg;
  int i = 0;

  //Initialize info
  setToZero(*info);
  //Go through given list
  while(list[i]) {
	inFile.open(list[i]);
	if(!inFile.fail()) {
	  while(inFile >> data) {
		//Check if preceding data had a comma
		if(check) {
		  //Convert to integer
		  num = atoi(data.c_str());
		  if(num > 0)
			tally(num, *info);
		  check = false;
		}else { //Check if current data has a comma
		  num = data.length();
		  check = (data[num - 1] == COMMA);
		}
	  }
	  inFile.close();
	}else {
	  cerr << "Error opening file: " << list[i] << endl;
	}
	i++;
  }
  return (void *) info;
}

void setToZero(Census& info)
{
  info.sec1 = 0;
  info.sec2 = 0;
  info.sec3 = 0;
  info.sec4 = 0;
  info.sec5 = 0;
}

void tally(int num, Census& info)
{
  if(num <= 0);
  //do nothing
  else if(num < BORDER1)
	info.sec1++;
  else if(num < BORDER2)
	info.sec2++;
  else if(num < BORDER3)
	info.sec3++;
  else if(num < BORDER4)
	info.sec4++;
  else
	info.sec5++;
}

void collectData(Census& info, Census data)
{
  info.sec1+=data.sec1;
  info.sec2+=data.sec2;
  info.sec3+=data.sec3;
  info.sec4+=data.sec4;
  info.sec5+=data.sec5;
}

void print(Census info)
{
  const int COL1 = 20;
  cout << left << setw(COL1) << "1-999: " << info.sec1 << endl;
  cout << left << setw(COL1) << "1,000 - 9,999: " << info.sec2 << endl;
  cout << left << setw(COL1) << "10,000 - 99,999: " << info.sec3 << endl;
  cout << left << setw(COL1) << "100,000 - 999,999: " << info.sec4 << endl;
  cout << left << setw(COL1) << "1,000,000+: " << info.sec5 << endl;
}

void deleteList(int threadCount, char ***list)
{
  int count = getCount();
  int listCount = (int) ceil((double) count/threadCount);
  for(int i = 0; i < threadCount; i++) {
	for(int j = 0; j < listCount; j++) {
	  if(list[i][j])
		delete list[i][j];
	}
	delete[] list[i];
  }
  delete[] list;
}
