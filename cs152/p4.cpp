//Kaleb Loo
//p4.cpp
//CPSC 152
//3/9/13
//Purpose: This program plays a card game with two players.
//Input: The user has to periodically press enter.  The user must decide
//       if he/she wants to play the game again.
//Process: The program shuffles numbers from 1 to 13 into a stack, which
//         represents the deck.  It then deals 7 cards into each player's
//         hands which are created using queues.  Players take turns until
//         one player runs out of cards.  The player who runs out of cards
//         wins.  A turn consists of playing the first card of the player's
//         hand, checking if the value is less than, equal to, or greater
//         than the value currently at the top of the discard.  The player
//         is then either dealt 0, 1, or 2 cards based on the result.  If
//         the deck is empty, the discard pile is flipped, saving the top
//         of the discard for continuity.  The cards in the deck, discard,
//         and the players' hands are then reset and user is asked if he/she
//         wants to play again.
//Example:
//
//Welcome to Silly Little Games Everlasting Card Game.
//Press <Enter>
//
//
//It is player1's turn.
//Press <Enter>
//You must beat a 9.
//Press <Enter>
//You played a 3 which is less than 9.
//Draw two cards.
//Press <Enter>
//You have 8 cards.
//
//
//It is player2's turn.
//Press <Enter>
//You must beat a 3.
//Press <Enter>
//You played a 2 which is less than 3.
//Draw two cards.
//Press <Enter>
//You have 8 cards.
//
//
//It is player1's turn.
//Press <Enter>
//
//.....
//Output: The program displays a welcome message.
//        The program may display an error message.
//        The program tells the player whose turn it it.
//        The program tells the player what card they need to beat.
//        The program tells the player the result of their turn.
//        The program displays a winner.
//        The program displays an error message.

using namespace std;

#include <iostream>
#include <ctime>
#include "stack.h"
#include "queue.h"

//Create constants
const int SCREENHEIGHT = 25;
const char YES = 'Y';
const int START = 7;
const int PLAYER1 = 1;
const int PLAYER2 = 2;
const int DECKSIZE = 52;
const int NUMCARDS = 4;

void clearScreen ();
//Clears the screen

void welcome ();
//Displays a welcome message for the user

void shuffle (Stack& deal);
//Shuffles a full deck of cards
//MODIFY: deal

bool dealCards (Stack& deck, Queue& player, int& numCards);
//Deals cards to a player.  If it cannot deal cards out, it returns a false.
//MODIFY: deal, player, numCards
//OUT: true/false

void takeTurn (Stack& deck, Stack& discard, Queue& player, int& numCards);
//Takes a turn
//MODIFY: deck, discard, player, numCards

void flipDeck (Stack& deck, Stack& discard);
//Flips the stack pile over into the deck
//MODIFY: deck, discard

bool checkWinner (Queue player);
//Checks if a player has won
//IN: player
//OUT: true/false

void resetCards (Stack& deck, Stack& discard, Queue& player1, Queue& player2);
//Removes all cards from play
//MODIFY: deck, discard, player1, player2

void goodbye ();
//Displays a goodbye message for the user

int main ()
{
  //Enable use of random
  srand(time(0));
  //Create player queues
  Queue player1;
  Queue player2;
  //Keep track of amount of cards
  int numCards1;
  int numCards2;
  int turn = PLAYER1;
  //Create deck
  Stack deck(DECKSIZE);
  Stack discard(DECKSIZE);
  int first;
  //Create repeat
  char repeat = YES;
  //Display Welcome Message and clear screen
  clearScreen ();
  welcome ();
  //Start Game
  while (toupper(repeat) == YES) {
	numCards1 = 0;
	numCards2 = 0;
	shuffle (deck);
	//Deal Hands
	for (int i = 0; i < START; i++) {
	  dealCards (deck, player1, numCards1);
	  dealCards (deck, player2, numCards2);
	}
	//Put one card into the discard
	if (deck.pop (first))
	  discard.push (first);
	//Take a turn
	while (!checkWinner (player1) && !checkWinner (player2)) {
	  if (turn == PLAYER1) {
		cout << "\n\nIt is player1's turn. \n";
		cout << "Press <Enter>";
		cin.get();
		takeTurn (deck, discard, player1, numCards1);
		cout << "You have " << numCards1 << " cards. \n";
		turn = PLAYER2;
	  }else {
		cout << "\n\nIt is player2's turn. \n";
		cout << "Press <Enter>";
		cin.get();
		takeTurn (deck, discard, player2, numCards2);
		cout << "You have " << numCards2 << " cards. \n";
		turn = PLAYER1;
	  }
	}
	//Put all cards back into deck
	resetCards (deck, discard, player1, player2);
	if (turn == PLAYER1)
	  cout << "Player 2 won! \n";
	else
	  cout << "Player 1 won! \n";
	//Ask for repeat
	cout << "Would you like to play again? (Y/N) ";
	cin >> repeat;
	cin.ignore();
  }
  goodbye ();
  return 0;
}

void clearScreen ()
{
  for (int i = 0; i < SCREENHEIGHT; i++)
	cout << "\n";
}

void welcome ()
{
  //Display Welcome Message
  cout << "Welcome to Silly Little Games Everlasting Card Game. \n";
  cout << "The rules for the game are simple.  If you play a card that\n"
	   << "is lower than the value in the discard, you must draw 2 cards.\n"
	   << "If you play a card that is equal to the value of the discard,\n"
	   << "you must draw 1 card. If you play a card that is greater than \n"
	   << "the discard then you draw no cards.  The player to get rid of \n"
	   << "all their cards first WINS!!!!\n";
  cout << "Press <Enter>";
  cin.get();
}

void shuffle (Stack& deck)
{
  //Create array to count cards
  int cards[DECKSIZE];
  //Create variable to store card value
  int number;
  int i = 0;
  //Display message
  cout << "\n\nShuffling Deck...\n";
  cout << "Press <Enter>";
  cin.get();
  //Initiate to 0
  for (int i = 0; i < DECKSIZE; i++)
	cards[i] = 0;
  //Shuffle cards into deck stack
  while (i < DECKSIZE) {
	number = (rand() % DECKSIZE/NUMCARDS);
	if (cards[number] < NUMCARDS) {
	  if (deck.push (number + 1)) {
		cards[number]++;
		i++;
	  }else
		cout << "ERROR: Could not push onto deck! \n";
	}
  }
}

bool dealCards (Stack& deck, Queue& player, int& numCards)
{
  //Store value of top of deck
  int num;
  if (deck.pop (num)) {
	//Put value into hand
	player.enqueue (num);
	numCards++;
	return true;
  }else {
	cout << "Deck is Empty! \n";
	return false;
  }
}

void takeTurn (Stack& deck, Stack& discard, Queue& player, int& numCards)
{
  //Store value of top of discard
  int num;
  int card;
  discard.topIs (num);
  player.dequeue (card);
  discard.push (card);
  numCards--;
  cout << "You must beat a " << num << ".\n";
  cout << "Press <Enter>";
  cin.get();
  //Check rules
  if (card < num) {
	cout << "You played a " << card << " which is less than " << num
		 << ".\n";
	cout << "Draw two cards. \n";
	cout << "Press <Enter>";
	cin.get();
	for (int i = 0; i < 2; i++) {
	  while (!dealCards (deck, player, numCards))
		flipDeck (deck, discard);
	}
  }else if (card == num) {
	cout << "You played a " << card << " which is equal to " << num
		 << ".\n";
	cout << "Draw one card. \n";
	cout << "Press <Enter>";
	cin.get();
	while (!dealCards (deck, player, numCards))
	  flipDeck (deck, discard);
  }else {
	cout << "You played a " << card << " which is greater than " << num
		 << ".\n";
	cout << "Draw zero cards. \n";
	cout << "Press <Enter>";
	cin.get();
  }
}

void flipDeck (Stack& deck, Stack& discard)
{
  //Create transfer variable
  int tmp;
  int num;
  //Display message
  cout << "Flipping Deck...\n";
  cout << "Press <Enter>";
  cin.get();
  //Put top of discard aside
  if (!discard.pop (tmp))
	cout << "Error: could not pop from discard! \n";
  while (discard.pop (num))
	deck.push (num);
  //Put one card onto discard
  discard.push (tmp);
}

bool checkWinner (Queue player)
{
  return player.isEmpty ();
}

void resetCards (Stack& deck, Stack& discard, Queue& player1, Queue& player2)
{
  //Temp variable
  int tmp;
  while (deck.pop (tmp));
  while (discard.pop (tmp));
  while (player1.dequeue (tmp));
  while (player2.dequeue (tmp));
}

void goodbye ()
{
  //Goodbye message
  cout << "\n\nThank you for playing with us! \n\n";
}
