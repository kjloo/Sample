//Kaleb Loo
//p2.cpp
//CPSC 152
//2/6/13
//Purpose: This program decodes a message from an input file.
//Input: The user inputs the name of the file that they would like to
//       decode.  The user must hit enter periodically.  The user decides
//       if he/she wants to execute the program again.
//Process: The program asks the user for the name of the file.  It then
//         reads the file in and checks if the file that was loaded was
//         valid and if it is non-empty.  If it is invalid or empty, it
//         displays a message and skips to the end without printing the
//         message.  Else, it loads the data from the file into a Linked
//         List in ascending numerical order.  It then deallocates the
//         memory and asks the user if he/she wants to repeat.
//Example:
//Welcome to Message Decoder!  Here you can decode a message from a file.
//
//Input a file name: p2.dat
//
//
//You have completed this assignment, only three(?) more to go
//
//  <Press Enter to Continue>
//
//
// Would you like to load another file? (Y/N): N
//
//
//Thank you for using our decoder!
//
//Output: The program displays a welcome message.
//        The program may display an error message.
//        The program displays the secret message.
//        The program displays a goodbye message.

using namespace std;

#include <iostream>
#include <iomanip>
#include <fstream>
#include <cstring>
#include <string>

struct ListNode
{
  int num;
  char letter;
  ListNode* next;
};

//Create constants for screen dimensions
const int HEIGHT = 25;
const int WIDTH = 80;
const char YES = 'Y';

void clearScreen ();
//Clears the screen

void welcome ();
//Displays a welcome message

int readFile (ListNode*& head);
//Asks the user for a file name and reads the file and puts the data
//in the Linked List
//MODIFY: head
//OUT: count

void insert (ListNode*& head, int numData, char letterData);
//Inserts data into Linked List in numerical ascending order.
//MODIFY: head
//IN: number, letter

void printList (ListNode* head);
//Prints the letters in the Linked List
//IN: head

void remove (ListNode*& head);
//Deallocates and deletes the Linked List
//MODIFY: head

void goodbye ();
//Displays a goodbye message

int main()
{
  //Allocate memory for pointer to head
  ListNode* head = NULL;
  //Variable for repitition
  char repeat = YES;
  //Variable to determine valid file read
  int count;

  //Clear the Screen
  clearScreen ();
  //Display Welcome Message
  welcome ();
  //Check if executing
  while (toupper(repeat) == YES) {
	//Read file and check if file read was successful
	count = readFile (head);
	if (count != 0)
	  printList (head);
	else
	  cout << "ERROR: Could not read file. \n\n";
	//Deallocate memory
	remove (head);
	//Ask user to repeat
	cout << "Would you like to load another file? (Y/N): ";
	cin >> repeat;
	cout << "\n\n";
  }
  //Display Goodbye Message
  goodbye ();
  return 0;
}

void clearScreen ()
{
  for (int i = 0; i < HEIGHT; i++)
	cout << "\n";
}

void welcome ()
{
  cout << "Welcome to Message Decoder!  Here you can decode a message "
	   << "from a file. \n\n";
}

int readFile(ListNode*& head)
{
  // use to read file
  ifstream inFile;
  string filename;
  int count = 0;
  // use to load data
  char letter;
  int position;

  //Ask user for file name
  cout << " Input a file name: ";
  cin >> filename;
  cin.get();

  //Open file and load data into Linked List
  inFile.open(filename.c_str());
  while (inFile.get(letter)) {
	inFile >> position;
	inFile.ignore();
	insert (head, position, letter);
	count++;
  }
  cout << "\n\n";
  return count;
}


void insert (ListNode*& head, int numData, char letterData)
{
  //Pointer to move nodes
  ListNode* ptr;
  //Temporary Variable for new node
  ListNode* temp = new ListNode;
  //Load data into new node
  temp -> num = numData;
  temp -> letter = letterData;
  //Check head case
  if (head == NULL || head -> num > numData) {
	temp -> next = head;
	head = temp;
  }else {
	ptr = head;
	while (ptr -> next != NULL && ptr -> next -> num < temp -> num)
	  ptr = ptr -> next;
	temp -> next = ptr -> next;
	ptr -> next = temp;
  }
}

void printList (ListNode* head)
{
  int spot = 0;
  ListNode* print;
  //Start at head
  print = head;
  //Print Values that exist
  while (print != NULL) {
	if (spot < WIDTH - 10 || print -> letter != ' ') {
	  cout << print -> letter;
	  print = print -> next;
	  spot++;
	}else {
	  spot = 0;
	  cout << "\n";
	}
  }
  cout << "\n\n";
  cout << "<Press Enter to Continue>";
  cin.get();
  cout << "\n\n";
}

void remove (ListNode*& head)
{
  ListNode* del;
  while (head != NULL) {
	del = head;
	head = head -> next;
	delete del;
	del = NULL;
  }
}

void goodbye ()
{
  cout << "Thank you for using our decoder! \n\n";
}
