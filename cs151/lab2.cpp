//Kaleb Loo
//Lab2.cpp
//10/7/11
//Purpose: This program asks the user for two integers and evaluates
//whether the first is a factor of the second
//Input: The user will input two integers
//Process: The program will use the % operator to evaluate if there is a remainder.
//If there is a remainder then the integers are not multiples of each other.
//If there is no remainder then the integers are multiples of each other.
//Output: The user will be told whether or not the integers are multiples of each other.
//Example: num1=20
//         num2=4
// 20 is a multiple of 4
// The other factor is 5

#include <iostream>

using namespace std;

int main ()
  {
    //Input Variables used in Calculations
    int num1;
	int num2;
	//Variables used to determine if statement
	int result;
	int factor;
	
	cout <<" Number 1: ";
	cin >>num1;
	cout <<" Number 2: ";
	cin >>num2;
	result=num1%num2;
	factor=num1/num2;
	
	//Checking for remainders
	if (result==0) {
	  cout <<num1 <<" is a multiple of " <<num2 <<". \n";
	  cout <<"The other factor is " <<factor <<". \n";
	}else
	  cout <<num1 <<" is not a multiple of " <<num2 <<". \n";
	
	return 0;
  }
