//
// exceptionLab.cpp

#include <iostream>

using namespace std;

void memTest();
// allocates memory to try and get bad_alloc

int main()
{
  memTest();
  cout << "I Finished the Test \n";
  return 0;
}

void memTest()

{
  try {
	int* list = new int[9999999999];
	list[9999999998] = 100;
	cout << "list allocated" << endl;
  }
  catch (exception& ba) {
	cout << "Error: Bad Allocation: " << ba.what() << "\n";
  }  
}
