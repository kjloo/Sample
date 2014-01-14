using namespace std;
#include <iostream>
#include <cstring>
#include <fstream>

int main ()
{
  int data;
  ifstream inFile;
  ofstream outFile;
  inFile.open("P3Input.txt");
  outFile.open("P3Outputtest.txt");
  while (inFile >> data) {
	if (data % 3 != 0)
	  outFile << data << "\n";
  }
  inFile.close();
  outFile.close();
}
	
