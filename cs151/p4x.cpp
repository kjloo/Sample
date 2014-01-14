//Kaleb Loo
//p4.cpp
//11/9/2011
//Purpose: This program plays a memory game with the user
//Input: The user decides if he/she wants to play.
//       The user decides a difficulty level.
//       The user inputs a file to play.
//       The user chooses a space on the board to reveal.
//       The user then chooses another space on the board
//       that they think matches. Input is (row, column)
//       The user decides if he/she wants to play again.
//Proccess: 
// First we must read in a file and input it into an array
// row by row. We must validate the user input, whether it
// falls in the array and whether it is not blank. We must
// then check to see if they made a match. If they made a match
// we must remove the spaces on the board. We must keep track of
// the number of turns and we must check if they matched all pairs
// by incrementing turns and pairs as the game progresses.
//Output: The program displays a board with face down cards.
//        The user picks a place on the board and the spot is
//        revealed. The user picks another spot and it is revealed
//        The program alerts the user if they made a match.
//        After a few seconds the cards are then put face down.
//        The program tells the user they won.
//        The program displays how many turns were taken.
//        The program asks if the user wants to play again.
//        The program displays cards removed with blanks spaces.
//Example:
//
//  0 1 2
//0 * * *
//1 * * *
//2 * * *
//3 * * *
//
// Where would you like to check? (row, column) 0 0
//
//  0 1 2
//0 A * *
//1 * * *
//2 * * *
//3 * * *
//
// Where would you like to check? (row, column) 0 2
//
//  0 1 2
//0 A * A
//1 * * *
//2 * * *
//3 * * *
//
// You found a pair!
//
//  0 1 2
//0 _ * _
//1 * * *
//2 * * *
//3 * * *
//
#include <iostream>
#include <iomanip>
#include <ctime>

using namespace std;

// use to determine array size
const int COLUMN = 4;
const int ROW = 6;
// use to determine menu choices
const int PLAY = 1;
const int QUIT = 2;
const char REPLAY = 'Y';
const int EASY = 5;
const int HARD = 2;
// use in displays
const char STAR = '*';
const char BLANK = '_';
const int SCREENCLEAR = 40;
const int MIN_NUM = 0;

int welcome();
// displays a welcome message

int difficulty(int& waitTime, int& rowSize, int& columnSize);
// determines time based on difficulty
// IN: call by reference, seconds, row dimension, column dimension

void print(char board[][COLUMN], int rowSize, int columnSize, int row1 = -1,
		   int column1 = -1, int row2 = -1, int column2 = -1);
// prints board displaying blank spaces, cards face up, and cards face down
// depending on situation
// IN: board array, dimensions, user input for coordinates

void takeTurn(char board[][COLUMN], int waitTime, int rowSize, int columnSize,
			  int& score, int& pairs);
// takes a turn
// IN: board array, seconds, dimensions, score and pair tally

void clearScreen();
// clears the screen

bool checkValid(char map[][COLUMN], int rowSize, int columnSize, int row,
				int column);
// checks to see if the move is valid
// IN: board array, dimensions, user input for coordinates

void wait(int seconds);
// pauses the program for seconds
// IN: seconds

int generate(int max);
// generates a random number

void goodbye();
// displays a goodbye message



int main ()
{ 
  // Create board
  char board[ROW][COLUMN];
  
  // charecter pool
  char pool[ROW*COLUMN];
  
  // use for random number
  int rand;
  
  // must use to produce different rand number each time
  srand(time(0));
  
  // Use to keep track of score
  int score = 0;
  int pairCount = 0;
  
  // Use for board size
  int rowSize;
  int columnSize;
  
  // Use to determine gameplay
  int menuChoice = 1;
  char play = REPLAY;
  
  // Use to determine difficulty
  int waitTime;
  
  // Welcome Message
  menuChoice = welcome();
  
  switch (menuChoice) {
  
  case (PLAY) :
    while (toupper(play) == 'Y') {
	  waitTime = difficulty(waitTime, rowSize, columnSize);
	  const int PAIRS = (rowSize*columnSize)/2;
      // Setup Board
	  for (int i = 0; i < ROW*COLUMN; i+=2) {
	    pool[i] = static_cast<char>(i);
		pool[i+1] = static_cast<char>(i);
	  }
      for (int r = 0; r < rowSize; r++)
        for (int c = 0; c < columnSize; c++) {
		  rand = generate(PAIRS);
		  if (pool[rand] != BLANK) {
            board[r][c] = pool[rand];
			pool[rand] = BLANK;
		  }else
		    c--;
		}
	  // Reset Variables
	  score = 0;
	  pairCount = 0;
	  while (pairCount < PAIRS) {
	    takeTurn(board, waitTime, rowSize, columnSize, score, pairCount);
	  }
	  cout << " Congratulations! You took " << score << " moves. \n";
      cout << " Would you like to play again? (y/n) ";
      cin >> play;
      cout << " \n ";
    }
  case (QUIT) :
     // Goodbye Message
    goodbye ();
  }
  
  return 0;
}

int welcome()
{
  int menuChoice = 0;
  while (menuChoice < PLAY || menuChoice > QUIT) {
    cout << "\n\n";
    //Allows player to make a choice to play
    cout << " Welcome to Memory! \n";
    cout << " What would you like to to? \n";
    cout << PLAY << ". Play Memory \n";
    cout << QUIT << ". Leave the game \n";
    cout << " Enter your decision (1-2): ";
    cin >> menuChoice;
    cout << "\n\n";
  }
  return menuChoice;
}

int difficulty(int& waitTime, int&rowSize, int& columnSize)
{
  const int BEGINNER = 1;
  const int EXPERT = 2;
  int level = 0;
  while (level < BEGINNER || level > EXPERT) {
    cout << "Would you like to play on Beginner or Expert? \n";
    cout << BEGINNER << ". Beginner \n";
    cout << EXPERT << ". Expert \n";
    cout << " Enter your decision (1-2): ";
    cin >> level;
	cout << "\n\n";
  }
  switch (level) {
  case (BEGINNER) :
    waitTime = EASY;
	rowSize = 4;
	columnSize = 3;
	break;
  case (EXPERT) :
    waitTime = HARD;
	rowSize = ROW;
	columnSize = COLUMN;
	break;
  }
  return waitTime;
} 
  
void print(char board[][COLUMN], int rowSize, int columnSize, int row1,
		   int column1, int row2, int column2)
{
  const int WIDTH = 2;
  cout << "\n\n " << setw(WIDTH);
  // print column headers
  for (int c = 0; c < columnSize; c++)
    cout << c << setw(WIDTH);
  cout << "\n";
  for (int r = 0; r < rowSize; r++) {
    // print row headers
	cout << r << setw(WIDTH);
    for (int c = 0; c < columnSize; c++) {
	  if (r == row1 && c == column1 || r == row2 && c == column2)
        cout << static_cast<int>(board[r][c]) << setw(WIDTH);
	  else if (board[r][c] != BLANK)
	    cout << STAR << setw(WIDTH);
	  else
	    cout << BLANK << setw(WIDTH);
	}
	cout << "\n";
  } 
  cout << "\n\n";
}

void takeTurn(char board[][COLUMN], int waitTime, int rowSize, int columnSize,
			  int& score, int& pairs)
{
  score++;
  int row1, row2, column1, column2;
  print(board, rowSize, columnSize);
  // ask for input
  do {
    cout << " Where would you like to check? (row, column) ";
    cin >> row1 >> column1;
  }while (!checkValid(board, rowSize, columnSize, row1, column1));
  print(board, rowSize, columnSize, row1, column1);
  do {
    cout << " Where would you like to check? (row, column) ";
    cin >> row2 >> column2;
  }while (!checkValid(board, rowSize, columnSize, row2, column2) ||
		  (row1 == row2 && column1 == column2));
  print(board, rowSize, columnSize, row1, column1, row2, column2);
  // check for matches
  if (board[row1][column1] == board[row2][column2]) {
    board[row1][column1] = BLANK;
	board[row2][column2] = BLANK;
	cout << " You found a pair! \n";
	pairs++;
  }
  wait(waitTime);

  // clear screen
  clearScreen();
}

void clearScreen()
{
  for (int i = 0; i < SCREENCLEAR; i++)
    cout << "\n";
}

bool checkValid(char board[][COLUMN], int rowSize, int columnSize, int row,
				int column)
{
  bool valid = false;
  if (board[row][column] == BLANK)
    cout << " Card already removed. \n";
  else if (row < 0 || row > rowSize-1 || column < 0 || column > columnSize-1)
    cout << " You chose an invalid space. \n";
  else
    valid = true;
  return valid;
}

void wait(int seconds)
{
  clock_t endwait;
  endwait = clock() + seconds * CLOCKS_PER_SEC;
  while (clock() < endwait){}
}

int generate(int max)
{
  return rand()%(max*2 - MIN_NUM) + MIN_NUM;
}

void goodbye()
{
  cout << " Thank you for playing! \n\n";
}
