//Kaleb Loo
//p1.cpp
//9/28/2011
//Purpose: The program plays a word game with the user that is somewhat related to MadLib.
//Input: The user will be asked to input various words for certain catagories, including: name, state, age, month,
//teacher, subject, feeling, number, exercise.
//Process: No Process
//Output: The program will print a paragraph containing words inputted by user. 
//The user is unaware of the contents of the paragraph

#include <iostream>
#include <string>
#include <fstream>

using namespace std;

int main ()
  {
    string name;
	string state;
	string age;
	string month;
	string teacher;
	string subject;
	string feeling;
	string number;
	string exercise;
	
	//Open File
	ifstream myfile;
    myfile.open ("input.dat", ifstream::in);
    name = getline (myfile,name);
	getline (myfile,age);
	getline (myfile,state);
	getline (myfile,month);
	getline (myfile,teacher);
	getline (myfile,subject);
	getline (myfile,feeling);
	getline (myfile,number);
	getline (myfile,exercise);

	//Welcome Message
    cout <<"Welcome to the best word game ever! My name is Wheatley and I shall be your \nguide. ";
	cout <<"Before we begin I would like to ask you if you could refrain from \nusing more than one word at a time. ";
	cout <<"I'm afraid that if you do, I will die. \n";
	cout <<"I hope these questions aren't too personal. Alright, shall we begin?\n \n";
	cout <<"Press Enter to Continue\n";
    cin.get();	
	//Output Paragraph
    cout <<"\nDear " <<name << ",\n Remember at the age of " << age << ", when we took that trip to " << state<< "?\n ";
	cout <<"I went there in " <<month <<" for my birthday and I saw " <<teacher << " our " <<subject <<" teacher. \n";
    cout <<" I remember in the 5th grade I felt so " <<feeling << " when you had to do \n ";
	cout <<number <<" " <<exercise <<" in front of the entire class. \n ";
	cout <<"Well it is about time I wrap this letter up. \n";
	cout <<" From, \n Your Best Friend\n\n";
	
	//Pause
    cout <<"Press Enter to Continue\n";
	cin.get();
	
	//Exit Message
	cout <<"Thank you for participating in our experiment, I mean game.\n";
	cout <<"We do not take any responsibility if you experience any headache, \n";
    cout <<"vomitting, lose of appetite, or death, after participating in our experiment.\n";
	cout <<"Hope you have a nice day!\n";
	
	//Close File
	myfile.close();
	
    return 0;
  }
