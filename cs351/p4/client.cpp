//Kaleb Loo
//client.cpp
//CPSC 351
//3/7/14
//
//Purpose: This program will act as the client in a client-server treasure
//         hunt game.
//Input: The user inputs the server IP and port in order in the command line.
//       The user inputs his/her name.
//       The user inputs a guess to the location of the treasure.
//Process: The program initiates the variables and loads in the parameters
//         from the command line.  It then creates a socket and attempts to
//         establish a connection to the server IP.  After establishing a
//         connection, the game starts and the user is prompted to enter their
//         name.  The user then enters a guess.  The program assumes that the
//         user properly enter a guess as two ints.  The program then sends the
//         guess to the server and waits for a response.  The program will
//         receive the distance from the treasure.  If the distance is not zero
//         then the game continues and the user is notified of the distance
//         and is prompted to guess again.  If the distance is zero then the
//         user is notified that they have won and the server sends the score.
//         The server also sends the leaderboard and the program prints the
//         leaderboard to the screen.  The program then closes the socket and
//         thanks the user for playing.
//Example: ./client 10.124.72.20 10911
//         Requesting Connection to Server
//         Connected to Server: 10.124.72.20 10911
//         Enter your name: Tiger
//         Enter your guess: 0 0
//         You did not find the treasure.
//         Distance to the treasure is: 79.3095
//         Enter your guess: 9 9
//         You did not find the treasure.
//         Distance to the treasure is: 89.4427
//         Enter your guess: -79 -7
//         You found the treasure!
//         Tiger took 3 turns.
//            Player    Score
//         1  Frank     2
//         2  Joe       3
//         3  Tiger     3 
//Output: The program tells the user if they found the treasure.
//        The program displays the current distance from the treasure.
//        The program displays a victory message with score.
//        The program displays a leader board.

#include <iostream>
#include <iomanip>
#include "connection.h"

using namespace std;

struct Score {
  string name;
  int turns;
};

//Global Constants
const int NUM_OF_PARAMETERS = 3;
const int MAX = 100;
const int MIN = -100;

void welcome();
//Displays a welcome message to the user.

void loadParameters(int argc, char* argv[], char*&address, int &port);
//Loads the parameters from the command line arguments into local variables.
//Checks to see if the arguments are valid.
//IN: argc, argv[]
//OUT: address, port

void playGame(int sock);
//Provides all of the functionality needed to play the treasure hunt game.
//IN: sock

void printLeaderboard(int sock);
//Receives leaderboard information from server and prints it to the screen.
//IN: sock

void goodbye();
//Displays a goodbye message to the user.

int main(int argc, char* argv[])
{
  //Command line variables
  char* address;
  int port;

  //Local Variables
  int sock;
    
  //Check/Load in parameters
  try {
	loadParameters(argc, argv, address, port);
  }catch(string e) {
	cerr << "Error: " << e << endl;
	exit(-1);
  }
  
  //Create Socket
  sock = createSocket();

  //Establish Connection
  establishConnection(address, port, sock);

  //Receive Message
  playGame(sock);
    
  //Close Connection
  closeSocket(sock);
  
  return 0;
}

void welcome()
{
  cout << "Welcome to Treasure Hunt!" << endl;
}

void loadParameters(int argc, char* argv[], char*&address, int &port)
{
  //Check if number of parameters is correct
  if(argc == NUM_OF_PARAMETERS) {
	address = argv[1];
	port = atoi(argv[2]);
  }else {
	throw string("Invalid Number of Parameters");
  }
}

void playGame(int sock)
{
  //Variables
  int turns;
  int size;
  string name;
  float distance = 1;
  int x, y;
  bool valid;

  welcome();
  cout << "Enter your name: ";
  getline(cin, name);

  //Send name to server
  if(!sendMessage(name, sock)) {
	cerr << "Error: Message did not Send" << endl;
	exit(-1);
  }
  //Play game
  while(distance) {
	valid = false;
	//Enter guess
	while(!valid) {
	  cout << "Enter your guess: ";
	  cin >> x >> y;
	  if(x > MAX || y > MAX || x < MIN || y < MIN)
		cerr << "Invalid guess, try again." << endl;
	  else
		valid = true;
	}
	//Send guess
	if(!sendMessage(x, sock) || !sendMessage(y, sock)) {
	  cerr << "Error: Message did not Send" << endl;
	  exit(-1);
	}
	//Wait for response
	if(!recvMessage(distance, sock)) {
	  cerr << "Error: Could not receive Message" << endl;
	  exit(-1);
	}
	if(distance) {
	  cout << "You did not find the treasure." << endl;
	  cout << "Distance to the treasure is: " << distance << endl << endl;
	}
  }

  //Receive Result
  if(!recvMessage(turns, sock)) {
	cerr << "Error: Could not receive Message" << endl;
	exit(-1);
  }
  cout << "You found the treasure!" << endl;
  cout << name << " took " << turns << " turns." << endl << endl;

  //Receive Leaderboard
  printLeaderboard(sock);

  //Print Goodbye Message
  goodbye();
}

void printLeaderboard(int sock)
{
  const int COL1 = 3;
  const int COL2 = 10;
  int size;
  string name;
  int turns;
  //Receive Size
  recvMessage(size, sock);
  cout << "TOP SCORES" << endl;
  cout << left << setw(COL1) << " " << setw(COL2) << "Player" << setw(COL2)
	   << "Score" << endl;
  //Receive Leaderboard
  for(int i = 0; i < size; i++) {
	if(!recvMessage(name, sock) || !recvMessage(turns, sock)) {
	  cerr << "Error: Could not receive Message" << endl;
	  exit(-1);
	}
	cout << left << setw(COL1) << i + 1 << setw(COL2)
		 << name << setw(COL2) << turns << endl;
  }
}
void goodbye()
{
  cout << "Thanks for playing! " << endl;
}
