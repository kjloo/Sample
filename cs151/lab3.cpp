//Kaleb Loo
//lab3.cpp
//10/14/2011

#include <iostream>

using namespace std;

int main () 
  {
    int x;
	
	cout <<" Input an integer: ";
	cin >>x;
	
	//1
	for (int i=1; i<=x; i++) {
	  cout <<x;
	}
	cout <<"\n\n";
	
	//2
	for (int i=1; i<=x; i++) {
	  cout <<"1 \n";
	}
	cout <<"\n";
	
	//3
	cout <<" ";
	for (int i=1; i<=x; i++) {
	  cout <<" " <<i;
	}
	cout <<"\n";
	for (int i=1; i<=x; i++) {
	  cout <<i <<" ";
	  for (int j=1; j<=x; j++) {
	    cout <<j*i <<" ";
	  }
	  cout <<"\n";
	}
	cout <<"\n";
	
    //4
	for (int i=1; i<=x; i++) {
	  for (int j=1; j<=i; j++) {
	    cout <<i <<" ";
	  }
	  cout <<"\n";
	}
	cout <<"\n";
	
	//5
	for (int i=1; i<=x; i++) {
	  for (int j=1; j<=i; j++) {
	    cout <<" ";
	  }
	  cout <<i;
	  cout <<"\n";
	}
	for (int i=x-1; i>0; i--) {
	  for (int j=i; j>0; j--) {
	    cout <<" ";
	  }
	  cout <<i;
	  cout <<"\n";
	}
	cout <<"\n";
	return 0;
  }
  
