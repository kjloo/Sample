//Kaleb Loo
//tictactoe.cpp
//CPSC 152
//1/18/13
//This is an implementation of TicTacToe from TicTacToe.h

#include <iostream>
#include <cassert>
#include "tictactoe.h"

TicTacToe::TicTacToe ()
{
  board = new char*[SIZE];
  assert(board != NULL);
  for (int i = 0; i < SIZE; i++) {
	board[i] = new char[SIZE];
	assert(board[i] != NULL);
  }
  for (int r = 0; r < SIZE; r++)
	for (int c = 0; c < SIZE; c++)
	  board[r][c] = SPACE;
}

TicTacToe::TicTacToe (const TicTacToe& ttt)
{
  board = new char*[ttt.SIZE];
  assert(board != NULL);
  for (int i = 0; i < SIZE; i++) {
	board[i] = new char[ttt.SIZE];
	assert(board[i] != NULL);
  }
  for (int r = 0; r < SIZE; r++)
	for(int c = 0; c < SIZE; c++)
	  board[r][c] = ttt.board[r][c];
}

TicTacToe& TicTacToe::operator= (const TicTacToe& rhs)
{
  if (this != &rhs) {
	for (int r = 0; r < SIZE; r++)
	  for (int c = 0; c < SIZE; c++)
		board[r][c] = rhs.board[r][c];
  }
  return *this;
}

TicTacToe::~TicTacToe ()
{
  for (int i = 0; i < SIZE; i++)
	delete [] board[i];
  delete [] board;
}

void TicTacToe::printBoard ()
{
  cout << SPACE;
  for (int i = 0; i < SIZE; i++)
	cout << SPACE << i;
  cout << "\n";
  for (int r = 0; r < SIZE; r++) {
	cout << r;
	for (int c = 0; c < SIZE; c++)
	  cout << SPACE << board[r][c];
	cout << "\n";
  }
}

bool TicTacToe::placeMark (int row, int col, char piece)
{
  //Check valid piece placement
  if (row < SIZE && col < SIZE && board[row][col] == SPACE) {
	board[row][col] = piece;
	return true;
  }else
	return false;
}

bool TicTacToe::checkWinner (char piece)
{
  bool won = false;
  int row = 0;
  int col = 0;
  bool check = true;
  //Check rows for winner
  while (!won & row < SIZE) {
	col = 0;
	check = true;
	while (check & col < SIZE) {
	  if (board[row][col] != piece)
		check = false;
	  else
		col++;
	}
	if (check) {
	  won = true;
	}else
	  row++;
  }
  //Check columns for winner
  col = 0;
  while (!won & col < SIZE) {
	row = 0;
	check = true;
	while (check & row < SIZE) {
	  if (board[row][col] != piece)
		check = false;
	  else
		row++;
	}
	if (check) {
	  won = true;
	}else
	  col++;
  }
  //Check diagonals for winner
  check = true;
  row = 0;
  col = 0;
  while (check & row < SIZE) {
    if (board[row][col] != piece) {
  	  check = false;
    }else {
  	  row++;
  	  col++;
    }
  }
  if (check)
    won = true;
  check = true;
  row = 0;
  col = SIZE - 1;
  while (check & row < SIZE) {
    if (board[row][col] != piece) {
  	  check = false;
    }else {
	  row++;
	  col--;
	}
  }
  if (check)
    won = true;
  return won;  
}

void TicTacToe::resetBoard ()
{
  for (int r = 0; r < SIZE; r++)
	for (int c = 0; c < SIZE; c++)
	  board[r][c] = SPACE;
}
