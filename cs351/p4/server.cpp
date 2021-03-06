//Kaleb Loo
//server.cpp
//CPSC 351
//3/7/14
//
//Purpose: This program will act as the server in a client-server treasure
//         hunt game.  The server is responsible for connecting with clients,
//         creating a thread for each client, hiding the treasure, receiving
//         guesses, sending results such as distance or score, updating the
//         leader board, sending the leader board, and closing the connection.
//         The server should run indefinitely.
//Input: The user sends a command line input for the port to run the server on.
//Process: The program initializes all of the variables and then loads the
//         command line parameters in.  It then creates a socket for the server
//         and assigns the port from the command line to the socket.  It then
//         creates a listener on the socket to allow it to connect to clients.
//         The program then enters an infinite while loop and waits for client
//         connections.  When a client connects, the program creates a thread
//         that spawns a iteration of the game on the server.  It then randomly
//         generates a position for the treasure by setting an x and a y
//         between -100 and 100.  The server then asks the client for a name
//         and then waits for a guess.  When it receives a guess, the server
//         calculates the distance from the treasure.  If the distance is not
//         zero the game continues and the amount of turns increases.  If the
//         distance is zero then the game ends and the server sends the client
//         their score and the leaderboard.  The process of the game occurs
//         within a thread so while one instance of the game is running, the
//         server is waiting on requests from other clients.
//Example: ./server 109011
//         Waiting for client request
//         Connected with Client: 10.124.72.20 49203
//         Waiting for client request
//         The treasure is at: -6, 25
//         Connected with Client: 10.124.72.20 49211
//         Waiting for client request
//         The treasure is at: -78, 98
//         Connected with Client: 10.124.72.20 49219
//         Waiting for client request
//         The treasure is at: 38, -68
//         Connected with Client: 10.124.72.20 49220
//         Waiting for client request
//         The treasure is at: 7, -43
//         Connected with Client: 10.124.72.20 49221
//         Waiting for client request
//         The treasure is at: -79, -7
//Output: The program displays a connection to a client.
//        The program displays the location of the treasure (for testing).
//        

#include <iostream>
#include <cmath>
#include <time.h>
#include <pthread.h>
#include <errno.h>
#include "connection.h"

using namespace std;

struct SockData {
  int sock;
};

struct Score {
  string name;
  int turns;
};

//Global Constants
const int NUM_OF_PARAMETERS = 2;
const int BOARD_SIZE = 201;
const int MAX_DISTANCE = 100;
const int SCORE_BOARD_SIZE = 3;

//Global Variables
Score leaderboard[SCORE_BOARD_SIZE];
int size = 0;
pthread_mutex_t boardLock;

void initBoard();
//Initializes leaderboard to empty.
//MODIFY: leaderboard

void loadParameters(int argc, char* argv[],  int &port);
//Loads the parameters from the command line arguments into local variables.
//Checks to see if the arguments are valid.
//IN: argc, argv[]
//OUT: port

void createThread(int sock);
//Creates a thread for a client to play the game on.
//IN: sock

void *tfunc(void* args);
//Provides all the functionality for hosting the treasure hunt game.
//IN: args

float checkDistance(int x, int y, int xGuess, int yGuess);
//Checks the distance between player guess and treasure location.
//IN: x, y, xGuess, yGuess
//OUT: distance

void updateScoreboard(string name, int turns, int size);
//Updates the global leaderboard with most recent game.
//IN: name, turns, size
//MODIFY: leaderboard

void sendLeaderboard(int sock, int size);
//Sends the contents of the leaderboard to the client.
//IN: sock, size

int main(int argc, char* argv[])
{
  //Initialize leaderboard
  initBoard();

  //Initialize lock
  pthread_mutex_init(&boardLock, NULL);
  
  //Initialize random
  srand(time(NULL));
  
  //Command line variables
  int port;

  //Local Variables
  string message;
  int sock;
  int clientSock;
  
  //Check/Load in parameters
  try {
	loadParameters(argc, argv,  port);
  }catch(string e) {
	cerr << "Error: " << e << endl;
	exit(-1);
  }

  //Create Socket
  sock = createSocket();

  //Assign Port to Socket
  assignPort(port, sock);

  //Set socket to listen
  requestListener(sock);

  //Wait for Client Connection
  while(true) {
	clientSock = acceptConnection(sock);
	createThread(clientSock);
  }
  
  return 0;
}

void initBoard()
{
  for(int i = 0; i < SCORE_BOARD_SIZE; i++) {
	leaderboard[i].name = "";
	leaderboard[i].turns = 0;
  }
}

void loadParameters(int argc, char* argv[], int &port)
{
  //Check if number of parameters is correct
  if(argc == NUM_OF_PARAMETERS) {
	port = atoi(argv[1]);
  }else {
	throw string("Invalid Number of Parameters");
  }

  //Check if Parameters are valid
}

void createThread(int sock)
{
  int status;
  pthread_t tid;
  SockData* data = new SockData;
  data->sock = sock;
  status = pthread_create(&tid, NULL, tfunc, (void*) data);
  if(status != 0) {
	cerr << "Error creating thread: " << strerror(errno) << endl;
  }
}

void *tfunc(void* arg)
{
  //Variables
  int x;
  int y;
  int xGuess;
  int yGuess;
  float distance = 1;
  int turns = 0;
  string name;
  SockData* data = (SockData*) arg;
  int sock = data->sock;
  delete data;

  //Place treasure
  x = rand() % BOARD_SIZE - MAX_DISTANCE;
  y = rand() % BOARD_SIZE - MAX_DISTANCE;
  //Display treasure location
  cout << "The treasure is at: " << x << ", " << y << endl;
  //Ask player for name
  if(!recvMessage(name, sock)) {
	cerr << "Error, terminating thread" << endl;
	pthread_exit(NULL);
  }
  //Play Game
  while(distance) {
	//Wait for player guess
	if(!recvMessage(xGuess, sock) || !recvMessage(yGuess, sock)) {
	  cerr << "Error, terminating thread" << endl;
	  pthread_exit(NULL);
	}
	//Check guess
	distance = checkDistance(x, y, xGuess, yGuess);
	if(!sendMessage(distance, sock)) {
	  cerr << "Error, terminating thread" << endl;
	  pthread_exit(NULL);
	}
	turns++;
  }

  //Send Result
  if(!sendMessage(turns, sock)) {
	cerr << "Error, terminating thread" << endl;
	pthread_exit(NULL);
  }

  //Update Leaderboard
  pthread_mutex_lock(&boardLock);
  if(size < SCORE_BOARD_SIZE)
	size++;
  updateScoreboard(name, turns, size);
  pthread_mutex_unlock(&boardLock);
  
  //Send Leaderboard
  sendLeaderboard(sock, size);
    
  //Detach Thread
  pthread_detach(pthread_self());
  closeSocket(sock);
}

float checkDistance(int x, int y, int xGuess, int yGuess)
{
  return sqrt(pow((double) (xGuess - x), 2) + pow((double) (yGuess - y), 2));
}

void updateScoreboard(string name, int turns, int size)
{
  string tmp;
  int num;
  int i = 0;
  bool done = false;
  while(i < size && !done)  {
	if(leaderboard[i].turns == 0 || turns < leaderboard[i].turns) {
	  tmp = leaderboard[i].name;
	  num = leaderboard[i].turns;
	  leaderboard[i].name = name;
	  leaderboard[i].turns = turns;
	  name = tmp;
	  turns = num;
	  done = true;
	}
	i++;
  }
  for(int j = i; j < size; j++) {
	tmp = leaderboard[j].name;
	num = leaderboard[j].turns;
	leaderboard[j].name = name;
	leaderboard[j].turns = turns;
	name = tmp;
	turns = num;
  }
}

void sendLeaderboard(int sock, int size)
{
  sendMessage(size, sock);

  for(int i = 0; i < size; i++) {
	if(!sendMessage(leaderboard[i].name, sock) ||
	   !sendMessage(leaderboard[i].turns, sock)) {
		 cerr << "Error, terminating thread" << endl;
		 pthread_exit(NULL);
	}
  }
}
