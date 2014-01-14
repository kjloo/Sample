//Kaleb Loo
//p2.cpp
//10/17/11
//Purpose: This program will have the user guess a number from 1 to 100 and tell them
//         if there guess is too high or too low until they guess correctly.
//Input: The user must input a number from 1 to 100.
//Procedure: The program will receive an input and compare it to a random number.
//           It will then either tell the user the number is correct or it will
//           have the user guess again.
//Output: The program will either tell the user they inputted the correct answer,
//        or it will ask the user to guess again.

#include <iostream>
#include <cstdlib>
#include <ctime>

using namespace std;

//Set constants to determine the range that the computer generates a random number
const int MAX_NUM=101;
const int MIN_NUM=1;
const int PLAY=1;
const int SCORE=2;
const int QUIT=3;

int main ()
  {
    //Variables used for guessing game
    int num;
	int guess;
	
	//Variable used to determine score
	int high=100;
	int low=100;
	int mid=100;
	int score=0;
	
	//Variable used to determine if the game is won
	int verdict=0;
	
	//Variable used to determine menu choice
	int menuChoice=1;
	
	//Must use to generate a different number each time the program is run.
	srand(time(0));
	
	//This is to allow the user to choose whether or not he/she wants to play
	while (menuChoice==PLAY||menuChoice==SCORE) {
		//Welcome Message
		score=0;
		verdict=0;
		cout <<"\n\n";
		cout <<" Welcome to the Random Number Guessing Game.\n\n";
		//The user decides if he/she wants to play the game (again).
		cout <<" What would you like to do? \n";
		cout <<PLAY <<"  Start Game \n";
		cout <<SCORE <<"  See Scores \n";
		cout <<QUIT <<"  Exit Game \n";
		cout <<" Choose (1-3): ";
		cin >>menuChoice;
		cout <<"\n";
		
		switch (menuChoice) {
		  case (PLAY):
		    //Setting Random Number for game
		    num=rand()%(MAX_NUM-MIN_NUM)+MIN_NUM;
			//Game starts here
			while (verdict!=1) {
			  cout <<" Guess a number between 1 and 100: ";
			  cin >>guess;
			  score++;
			  if (guess==num) {
				cout <<"\n You guessed correctly!  The number was " <<num <<"\n\n";
				cout <<" You took " <<score <<" tries. \n\n";
				verdict=1;
				if (score < high) {
				low=mid;
				mid=high;
				high=score;
				}else if (score < mid) {
				low=mid;
				mid=score;			
				}else if (score < low)
				low=score;
			  }else if (guess>num) {
				cout <<" Your guess " <<guess <<" is too high.  Please guess lower\n";
			  }else if (guess<num) {
				cout <<" Your guess " <<guess <<" is too low.  Please guess higher\n";
			  }
			}
			break;
		  case (SCORE):
		    //Display Scores
			cout <<" Your high scores are: \n";
			cout <<"  1: " <<high <<"\n";
			cout <<"  2: " <<mid <<"\n";
			cout <<"  3: " <<low <<"\n";
			break;
		  case (QUIT):
			cout <<" Thank you for playing!\n\n";
            break;			
		}
	}	
    return 0;
  }
