//Kaleb Loo
//p1.cpp
//CPSC 152
//1/19/13
//Purpose: This program plays Tic-Tac-Toe with the user
//Input: The user decides if he/she wants to play.
//       The user chooses what space on the board he/she wants to place
//       his/her piece.
//       The user must hit <Enter> after scoreboard is displayed.
//Process: The program asks the user if they would like to play
//         It then asks the first player to choose a coordinate on the board.
//         The game checks if the space indicated is valid and if so, places
//         the current player's piece in that spot.  Else, the game reports
//         an error and asks for a different coordinate.  After each turn,
//         the game checks the board for any winners.  If there is a winner,
//         the game ends and the winner is declared and the scoreboard is
//         updated and displayed.  If there is not winner, the next player
//         takes a turn.  At the end of the game, the program updates the
//         scoreboard and clears the gameboard.
//Example: Welcome to Tic-Tac-Toe!
//         What would you like to do?
//         1. Start Game
//         2. See Scoreboard
//         3. Quit Game
//         Choose (1-3): 1
//
//
//         X: Where would you like to go? (Row Column): 1 1
//           0 1 2
//         0
//         1   X
//         2
//
//
//         0: Where would you like to go? (Row, Column):0 0
//           0 1 2
//         0 O
//         1   X
//         2
//Output: The program displays a welcome message.
//        The program declares who wins the game or if there was a tie.
//        The program shows a running tally of the score.
//        The program tells the user if the chosen space is invalid.
//        The program displays the current board.
//        The program displays a goodbye message.

using namespace std;

#include <iostream>
#include <iomanip>
#include "tictactoe.h"

//Create constants for screen size
const int SCREENSIZE = 25;
//Create constants for pieces
const char PLAYER1 = 'X';
const char PLAYER2 = 'O';
//Create constant for board
const int SIZE = 3;
//Create constants for menu
const int PLAY = 1;
const int SCORE = 2;
const int QUIT = 3;

void clearScreen ();
//clears a full screen of 25 lines

int welcome ();
//displays a menu for the user
//OUT: menuChoice

void takeTurn(TicTacToe& game, char turn);
//takes a turn by placing a piece and checking if it is valid
//MODIFY: game
//IN: turn

void changeTurns (char& turn);
//switches whose turn it is
//MODIFY: turn

void scoreUpdate (char turn, int totalTurns,
				  int& xWin, int& oWin, int& tie);
//updates the score after the game
//MODIFY: number of X wins, number of O wins, number of ties
//IN: turn, totalTurns

void displayScore (int xWin, int oWin, int tie);
//displays the scoreboard for the game
//IN: the amount of X wins, O wins, and ties

void goodbye ();
//displays a goodbye message

int main ()
{
  //Create menu variable
  int menuChoice = PLAY;
  //Create turn variables
  TicTacToe game;
  char turn = PLAYER1;
  int totalTurns = 0;
  //Scoreboard tally
  int xWin = 0;
  int oWin = 0;
  int tie = 0;

  //Clear the Screen
  clearScreen ();

  while (menuChoice < QUIT && menuChoice >= PLAY) {
	//Display Welcome Message
	menuChoice = welcome ();
	switch (menuChoice) {
	case (PLAY):
	  totalTurns = 0;
	  while (!game.checkWinner (PLAYER1) & !game.checkWinner (PLAYER2)
			 & (totalTurns < SIZE * SIZE)) {
		//Display Board
		game.printBoard ();
		//Take a Turn
		takeTurn (game, turn);
		totalTurns++;
		//Switch turns
		changeTurns (turn);
	  }
	  
	  //Update Scoreboard and Display Victory Message
	  scoreUpdate (turn, totalTurns, xWin, oWin, tie);
	  //Clear the board for new game
	  game.resetBoard ();
	case (SCORE):
	  displayScore (xWin, oWin, tie); 
	  break;
	case (QUIT):
	  goodbye ();
	}
  }
  return 0;
}

void clearScreen ()
{
  //Clear the Screen
  for (int i = 0; i < SCREENSIZE; i++)
	cout << "\n";
}

int welcome ()
{
  int menuChoice = 0;
  while (menuChoice > QUIT ||  menuChoice <  PLAY) {
	//Welcome Message
	cout << "\n\n";
	cout << " Welcome to Tic-Tac-Toe! \n\n";
	//The user decides what action to take
	cout << " What would you like to do? \n";
	cout << PLAY << ".  Start Game \n";
	cout << SCORE << ".  See Scoreboard \n";
	cout << QUIT << ".  Exit Game \n";
	cout << " Choose (1-3): ";
	cin >> menuChoice;
	cout << "\n";
  }
  return menuChoice;
}

void takeTurn (TicTacToe& game, char turn)
{
  bool mark = false;
  int row;
  int col;
  //Ask player to make a move and check if they can go there
  while (!mark) {
	cout << "\n\n";
	cout << turn  << ": Where would you like to go? (Row Column): ";
	cin >> row >> col;
	if (game.placeMark (row, col, turn))
	  mark = true;
	else
	  cout << "That is an invalid move, try again please. \n";
  }
}

void changeTurns (char& turn)
{
  //Switch turns
  if (turn == PLAYER1)
	turn = PLAYER2;
  else
	turn = PLAYER1;
}

void scoreUpdate (char turn, int totalTurns,
				  int& xWin, int& oWin, int& tie)
{
  if (totalTurns == (SIZE * SIZE)) {
	tie++;
	cout << "\n It was a tie. \n";
  }else if (turn == PLAYER1) {
	oWin++;
    cout << "\n Congradulations! " << PLAYER2 << " won! \n";
  }else {
	xWin++;
	cout << "\n Congradulations! " << PLAYER1 << " won! \n";
  }
}

void displayScore (int xWin, int oWin, int tie)
{
  cout << "Player 1 has won " << xWin << " games. \n";
  cout << "Player 2 has won " << oWin << " games. \n";
  cout << "There have been " << tie << " ties. \n";
  cout << "<Press Enter to Continue>";
  cin.ignore();
  cin.get();
}

void goodbye ()
{
  cout << "Thank you for playing! \n";
}
