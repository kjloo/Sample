//Kaleb Loo
//p3x.cpp
//10/21/2011
//Purpose: This program plays Chutes & Ladders with 2 players.
//Input: The user decides whether or not he/she wants to play.
//       The user inputs a name for player 1 and player 2.
//       The user must periodically press <Enter>.
//       The user decides if he/she wants to play again.
//       The user decides how many players.
//Process: The program asks the user if they would like to play
//         It then asks the players for their names.
//         The program spins a number between 1 and 6 and moves the
//         current player appropriately.  It then checks if the player
//         landed on a chute or ladder and moves the player appropriately.
//         It then checks if the player has won.  If so, the game ends.
//         If not, the next player takes a turn.
//Example: Welcome to Chutes & Ladders!
//         What would you like to to?
//         1. Play Chutes & Ladders
//         2. Leave the game
//         Enter your decision (1-2): 1
//
//         How many players: 3
//         Player enter your name: Player1
//         Player enter your name: Player2
//         Player enter your name: Player3
//
//         Player1's turn
//         Press <Enter> to spin.
//         You spun a 4.
//         You landed on space 4.
//
//         Player2's turn
//         Press <Enter> to spin.
//         You spun a 1.
//         You landed on space 1.
//
//         You climbed a ladder and landed at 38.
//
//         Player3's turn
//         Press <Enter> to spin.
//         You spun a 3
//         You landed on space 3.
//
//         Player1's turn 
//         Press <Enter> to spin.
//Output: The program declares who wins the game.
//        The program tells the user what space they are on.
//        The program tells the user if he/she hit a chute or ladder

#include <iostream>
#include <ctime>
#include <cstdlib>
#include <string>

using namespace std;

int welcome ();
//Displays a welcome message

void setup (int board[]);
//Sets up the board

bool takeTurn (int playerSpace[], string playerName[], 
  int board[], int spacesMove, int index);
//Takes a turn for current player.

int spin ();
//Determines the amount of spaces the player moves.

bool win (int playerSpace[], string playerName[], int index);
//Determines if the player won and ends the game.

void goodbye ();
//Displays a goodbye message

//Constants
const int MAX_NUM = 7;
const int MIN_NUM = 1;
const int PLAY = 1;
const int QUIT = 2;
const int WINNING_SPACE = 100;
const int MAX_PLAYER = 7;
const int BOARD_SPACES = 101;

int main ()
  {    
    //Set player array
    string playerName[MAX_PLAYER];
    int playerSpace[MAX_PLAYER];
    int playerAmount = 0;
    
    //Set Board Array
    int board[BOARD_SPACES];
    
    //Set Space Players are at
    for (int i = 1; i < MAX_PLAYER; i++) {
      playerSpace[i] = 0;
    }
    //Use to determine winner
    bool verdict = false;
    
    //Use to determine player turn
    int index = 1;
    //Set Menu Choice
    int menuChoice = 1;
    char play = 'Y';
    
    //Must use to produce different rand number each time
    srand(time(0));
    
    //Welcome Message
    menuChoice = welcome ();
    
    switch (menuChoice) {
    
    case (PLAY) :
      while (playerAmount < 2 || playerAmount > 6) {
        //Ask how many players
        cout << " How many players (2-6): ";
        cin >> playerAmount;
      }
      
      //Ask Players for names
      for (int i = 1; i <= playerAmount; i++) {
        cout << "Player enter your name: ";
        cin >> playerName[i];
      }
      cout << " \n\n";
      
      //Setup Board
      setup(board);
      
      while (toupper(play) == 'Y') {
      //Reset Variables
      for (int  i = 1; i < MAX_NUM; i++)
        playerSpace[i] = 0;
      index = 1;    
      verdict = false;
      cin.get();
        //Start Game
        while (!verdict) {
          //Take a turn
          verdict = takeTurn (playerSpace, playerName, board, spin(), index);
          index++;
          if (index > playerAmount)
            index = 1;
        }
      cout << " Would you like to play again? (y/n) ";
      cin >> play;
      cout << " \n ";
      }
    case (QUIT) :
    //Goodbye Message
    goodbye ();
    }
    
    return 0;
  }

int welcome ()
  {
    cout << "\n\n";
    //Allows player to make a choice to play
    int menuChoice = 1;
    cout << " Welcome to Chutes & Ladders! \n";
    cout << " What would you like to to? \n";
    cout << PLAY << ". Play Chutes & Ladders \n";
    cout << QUIT << ". Leave the game \n";
    cout << " Enter your decision (1-2): ";
    cin >> menuChoice;
    cout << "\n\n";
    return menuChoice;
  }
      
void setup (int boardSpace[])
  {
    for (int i = 0; i < BOARD_SPACES; i++)
        boardSpace[i] = 0;
    boardSpace[98] = -20;
    boardSpace[95] = -20;
    boardSpace[93] = -20;
    boardSpace[87] = -63;
    boardSpace[64] = -4;
    boardSpace[62] = -43;
    boardSpace[56] = -3;
    boardSpace[49] = -38;
    boardSpace[48] = -22;
    boardSpace[16] = -10;
    boardSpace[1] = 37;
    boardSpace[4] = 10;
    boardSpace[9] = 12;
    boardSpace[23] = 21;
    boardSpace[28] = 56;
    boardSpace[36] = 8;
    boardSpace[51] = 15;
    boardSpace[71] = 19;
    boardSpace[80] = 20;
  }        
    
bool takeTurn (int playerSpace[], string playerName[], 
  int board[], int spacesMove, int index)
  {
    bool verdict = false;
   //Player Presses Enter to spin
    cout << playerName[index] << "'s turn. \n";
    cout << " Press <Enter> to spin. \n";
    cin.get();
    //Spin
    spacesMove = spin();
    //Determine if player can move
    if (playerSpace[index] + spacesMove <= WINNING_SPACE) {
      //Calculate where the player moves
      playerSpace[index] = playerSpace[index] + spacesMove;
      
      //Display number of spaces moved
      cout << " You spun a " << spacesMove <<".\n";
      
      //Display what space player is on
      cout << " You landed on space " << playerSpace[index] <<".\n\n";
      
    }else {
      cout << " You spun too high. \n";
      cout << " You are on space " << playerSpace[index] <<".\n\n";
    }
    //Game checks the space for a chute or a ladder
    //and moves player appropriately
    if (board[playerSpace[index]] > 0) {
      cout << " You climbed up a ladder and landed at ";
      cout <<board[playerSpace[index]] + playerSpace[index] << "\n\n";
    }else if (board[playerSpace[index]] < 0) {
      cout << " You fell down a chute and landed at ";
      cout <<board[playerSpace[index]] + playerSpace[index] << "\n\n";
    }
    playerSpace[index] = board[playerSpace[index]] + playerSpace[index];
    
    //Game checks for a winner and displays message
    verdict = win (playerSpace, playerName, index);
    return verdict;
  }
    
int spin ()
  {
    return rand()%(MAX_NUM - MIN_NUM) + MIN_NUM;
  }
  
bool win (int playerSpace[], string playerName[], int index)
  {
    bool verdict = false;
    //Check if player has won and display victory message.
    if (playerSpace[index] == WINNING_SPACE) {
      cout << playerName[index] << " won Chutes & Ladders! \n";
      verdict = true;
      cout << " Press <Enter> to continue. \n";
      cin.get();
    }
    return verdict;
  }
  
void goodbye ()
  {
    cout << " Thank you for playing! \n\n";
  }
