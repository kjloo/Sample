//Kaleb Loo
//tictactoe.h
//CPSC 152
//1/18/13
//Provide the functionality of a TicTacToe board including placing
//pieces, displaying the board, and checking for a winner

using namespace std;

#ifndef TICTACTOE_H
#define TICTACTOE_H

class TicTacToe
{
 public:
  TicTacToe ();
  //constructor
  
  TicTacToe (const TicTacToe& ttt);
  //copy constructor
  
  TicTacToe& operator= (const TicTacToe& rhs);
  //overloaded assignment operator
  
  ~TicTacToe ();
  //destructor
  
  void printBoard ();
  //shows current board on screen
  
  bool placeMark (int row, int col, char piece);
  //places a mark based on user input
  //returns false if spot is occupied
  //IN: row, column, piece
  //MODIFY: board
  
  bool checkWinner (char piece);
  //checks if a player has won
  //if so returns true and piece
  //IN: piece
  
  void resetBoard ();
  //clears the board for the next game
  
 private:
  char **board;
  static const int SIZE = 3;
  static const char SPACE = ' '; 
};

#endif
