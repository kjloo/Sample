///////////
//Kaleb Loo
//lab1.cpp
//1/11/13
//CPSC 152

#include <iostream>

using namespace std;

int main()
{
  int var1;
  int *pnt1;
  int size;

  //ask user for a number
  cout << "Input a integer: ";
  cin >> var1;
  pnt1 = &var1;
  //print value variable
  cout << "Value using variable: " << var1 << "\n";
  //print address variable
  cout << "Address using variable: " << &var1 << "\n";
  //print value pointer
  cout << "Value using pointer: " << *pnt1 << "\n";
  //print address pointer
  cout << "Address using pointer: " << pnt1 << "\n";

  //allocate memory
  pnt1 = new int;
  *pnt1 = 25;

  //check allocation
  if (pnt1 == NULL)
	  cout << "Memory Allocation Error! \n";

  //print value variable
  cout << "Value using variable: " << var1 << "\n";
  //print address variable
  cout << "Address using varaible: " << &var1 << "\n";
  //print value pointer
  cout << "Value using pointer: " << *pnt1 << "\n";
  //print address pointer
  cout << "Address using pointer: " << pnt1 << "\n";

  //deallocate memory
  delete pnt1;
  pnt1 = NULL;
  
  //determine array size
  cout << "Input a size less than 50: ";
  cin >> size;
  pnt1 = new int[size];

  //check memory allocation
  if (pnt1 == NULL)
	cout << "Memory Allocation Error \n";
  //set values of array
  for (int i = 0; i < size; i++)
	  pnt1[i] = i;
  //display values of array
  for (int i = 0; i < size; i++)
	  cout << "pnt1[" << i << "]: " << pnt1[i] << "\n";
  
  //deallocate memory
  delete [] pnt1;
  pnt1 = NULL;
  
  return 0;
}

