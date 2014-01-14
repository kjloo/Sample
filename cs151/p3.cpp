//Kaleb Loo
//p3.cpp
//10/21/2011
//Purpose: This program plays Chutes & Ladders with 2 players.
//Input: The user decides whether or not he/she wants to play.
//       The user inputs a name for player 1 and player 2.
//       The user must periodically press <Enter>.
//       The user decides if he/she wants to play again.
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
//         Player 1 enter your name: Player 1
//         Player 2 enter your name: Player 2
//
//         Player 1's turn
//         Press <Enter> to spin.
//         Player 1 spun a 4.
//         You landed on space 4.
//
//         Player 2's turn
//         Press <Enter> to spin.
//         Player 2 spun a 1.
//         You landed on space 1.
//
//         You climbed a ladder and landed at 38.
//
//         Player 1's turn 
//         Press <Enter> to spin.
//Output: The program declares who wins the game.
//        The program tells the user if they spun too high.
//        The program tells the user what space they are on.
//        The program tells the user if he/she hit a chute or ladder

#include <iostream>
#include <ctime>
#include <cstdlib>
#include <string>

using namespace std;

int welcome ();
//Displays a welcome message

int takeTurn (int space, string player, int spacesMove);
//Takes a turn for current player.

int spin ();
//Determines the amount of spaces the player moves.

int position (int space);
//Determines whether the player landed
//on a chute or ladder and moves the player.

void win (int space, string player);
//Determines if the player won and displays a message.

void goodbye ();
//Displays a goodbye message

//Use to determine spin range
const int MAX_NUM = 7;
const int MIN_NUM = 1;
//Use to determine menu choices
const int PLAY = 1;
const int QUIT = 2;
//Use to determine board size
const int WINNING_SPACE = 100;

int main ()
  {    
    //Set Space Players are at
    int space1 = 0;
    int space2 = 0;
    
    //Use to determine players turn
    bool playerTurn = true;
    
    //Set Menu Choice
    int menuChoice = 1;
    char play = 'Y';
    
    //Initialize Player names
    string player1;
    string player2;
    
    //Must use to produce different rand number each time
    srand(time(0));
    
    //Welcome Message
    menuChoice = welcome ();
    
    switch (menuChoice) {
    
    case (PLAY) :
      //Ask Players for names
      cout << " Player 1 enter your name: ";
      cin >> player1;
      cout << " Player 2 enter your name: ";
      cin >> player2;
      cout << "\n";
      
      while (toupper(play) == 'Y') {
      //Reset Variables
      space1 = 0;
      space2 = 0;
      cin.get();
        //Start Game
        while (space1 != WINNING_SPACE && space2 != WINNING_SPACE) {
          if (playerTurn) {//Player 1's turn
            //Take a turn
            space1 = takeTurn (space1, player1, spin());
            //Switch turns
            playerTurn = false;
          }else { //Player 2's turn
            //Take a turn
            space2 = takeTurn (space2, player2, spin());
            //Switch turns
            playerTurn = true;
          }
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
      
int takeTurn (int space, string player, int spacesMove)
  {
    //Player Presses Enter to Spin.
    cout << player << "'s turn. \n";
    cout << " Press <Enter> to spin. \n";
    cin.get();
    //Determine if player can move
    if (space + spacesMove <= WINNING_SPACE) {
      //Calculate where the player moves
      space = space + spacesMove;     
      //Display number of spaces moved
      cout << " You spun a " << spacesMove << ".\n";    
      //Display what space player is on
      cout << " You landed on space " << space << ".\n\n";
    }else {
      cout << " You spun too high. \n";
      cout << " You are on space " << space << ".\n\n";
    }
    //Game checks the space for a chute or a ladder
    //and moves player appropriately
    space = position (space);
    //Game checks for a winner and displays message
    win (space, player);
    return space;
  }
    
int spin ()
  {
    return rand()%(MAX_NUM - MIN_NUM) + MIN_NUM;
  }
  
int position (int space)
  {
    int space1 = space;
    //Checks for Chutes or Ladders
    if (space == 98 || space == 95 || space == 93) 
      space1 = space - 20;
    else if (space == 87) 
      space1 = space - 63;
    else if (space == 64) 
      space1 = space - 4;
    else if (space == 62) 
      space1 = space - 43;
    else if (space == 56) 
      space1 = space - 3;
    else if (space == 49) 
      space1 = space - 38;
    else if (space == 48) 
      space1 = space - 22;
    else if (space == 16) 
      space1 = space - 10;
    else if (space == 1) 
      space1 = space + 37;
    else if (space == 4) 
      space1 = space + 10;
    else if (space == 9) 
      space1 = space + 12;
    else if (space == 23) 
      space1 = space + 21;
    else if (space == 28) 
      space1 = space + 56;
    else if (space == 36) 
      space1 = space + 8;
    else if (space == 51) 
      space1 = space + 15;
    else if (space == 71) 
      space1 = space + 19;
    else if (space == 80) 
      space1 = space + 20;  
    //Determine whether they fell down a chute,
    //climbed a ladder, or neither.
    if (space1 < space) {
      cout << " You fell down a chute and landed at ";
      cout << space1 << " \n\n";
    }else if (space1 > space) {
      cout << " You climbed a ladder and landed at ";
      cout << space1 << " \n\n";
    }
    return space1;
  }
  
void win (int space, string player)
  {
    //Check if player has won and display victory message.
    if (space == WINNING_SPACE) {
      cout << player << " won Chutes & Ladders! \n";
      cout << " Press <Enter> to continue. \n";
      cin.get();
    }
  }
  
void goodbye ()
  {
    cout << " Thank you for playing! \n\n";
  }