// Kaleb Loo
// lab6.cpp
// 11/18/2011

#include <iostream>
#include <fstream>
#include <iomanip>
#include <string>

using namespace std;

int readFile(int arr[], int numElements);
// reads in file and inputs data into array

void print(int arr[], int numElements);
// prints data

void sort(int arr[], int numElements);
// sorts in accending order

void swap(int& x, int& y);
// swaps x and y values

const int MAX = 150;

int main ()
{
  int list[MAX];
  int size;
  for (int i = 0; i < MAX; i++)
	list[i] = 0;
  size = readFile(list, MAX);
  if (size != 0) {
    print(list, size);
    sort(list, size);
    print(list, size);
  }
  return 0;
}

int readFile(int arr[], int numElements)
{
  ifstream inFile;
  string filename;
  int size = 0;
  int data;
  cout << "Filename? ";
  cin >> filename;
  cin.ignore();
  inFile.open(filename.c_str());
  while (inFile >> data && size < numElements) {
	arr[size] = data;
	size++;
  }
  inFile.close();
  return size;
}

void print(int arr[], int numElements)
{
  const int INDEX_COL = 5;
  const int VAL_COL = 7;
  cout << "Index   Value \n";
  for (int i = 0; i < numElements; i++) {
	cout << setw(INDEX_COL) << i << setw(VAL_COL) << arr[i] << "\n";
  }
}

void sort(int arr[], int numElements)
{
  int smallest;
  for (int index = 0; index < numElements -1; index++) {
	smallest = index;
	for (int min = index + 1; min < numElements; min++) {
	  if (arr[min] < arr[smallest])
		smallest = min;
	}
	if (arr[index] != arr[smallest])
	  swap(arr[index], arr[smallest]);
  }
}

void swap(int& x, int& y)
{
  int temp;
  temp = y;
  y = x;
  x = temp;
}
