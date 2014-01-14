// Kaleb Loo
// lab5.cpp

#include <iostream>
#include <fstream>
#include <string>
#include <iomanip>

using namespace std;

void print(const int list[], int numElements);
// prints contents of list neatly formatted
// IN: list, numElements

const int MAX = 30;

int main()
{
  ifstream inFile;
  string filename;

  // add needed variables here
  int oddNum[MAX];
  int evenNum[MAX];
  int negNum[MAX];
  int index = 0;
  int negIndex = 0;
  int oddIndex = 0;
  int evenIndex = 0;
  int num;

  cout << "Filename? ";
  cin >> filename;
  cin.ignore();
  inFile.open(filename.c_str());
  if (inFile.fail()){
	cout << "File problem.....press enter to exit program ";
	cin.get();
	return 0;
  }
  
  // read all values from file, putting integers into appropriate arrays
  // remember, 0 is not negative or positive and should not be stored
  // there may not be 30 values in the file....
  while (inFile >> num && index < MAX) {
    if (num < 0) {
    negNum[negIndex] = num;
	negIndex++;
    }else if (num %2 == 1) {
    oddNum[oddIndex] = num;
	oddIndex++;
    }else if (num != 0) {
	evenNum[evenIndex] = num;
	evenIndex++;
    }
	index++;
  }
  inFile.close();
  cout << "Printing NEGATIVE values" << endl;
  // call print function to print negative values
  // only print good values, not empty array cells
  print(negNum, negIndex);
  
  cout << endl << endl;
  cout << "Printing EVEN values" << endl;
  // call print function to print even values
  // only print good values, not empty array cells
  print(evenNum, evenIndex);
   
  cout << endl << endl;
  cout << "Printing ODD values" << endl;
  // call print function to print odd values
  // only print good values, not empty array cells
  print(oddNum, oddIndex);
  
  
  return 0;
}

void print(const int list[], int numElements)
{
  const int INDEX_COL = 5;
  const int VAL_COL = 7;
  
  cout << "Index  Value" << endl;
  for (int i = 0; i < numElements; i++){
	cout << setw(INDEX_COL) << i << setw(VAL_COL) << list[i] << endl;
  }
}

