// Kaleb Loo
// p5.cpp
// 11/21/2011
// Purpose: This program sorts inventory and writes a report.
// Input: The user inputs a filename. The file must be formatted
//        with details in the following order, name, manufacturer, quantity,
//        minimum, cost each. Each detail is only one word long and separated
//        by a space.
//        There are no partial records
//        The user decides which type of report to view or quit.
// Process:
// For the inventory report, the program calculates the total value
// of the parts in storage, the amount of items in storage, and the
// number of different parts.  It also calculates the value for each
// set of parts.
// For the reorder report, the program calculates the amount of items
// that must be ordered to fulfill the minimum requirements, the total
// cost of ordering all the items, and the number of different parts that
// need to be ordered.  It also calculates the cost for each set of parts.
// Output: The program outputs a menu of choices
//         The program outputs an inventory report of users choice.
// Example:
//
//                          Inventory Report
// Item               Manufacturer      Quantity     Cost each    Total Value
// Capacitor          Ohmite                  70       $  0.73       $  51.10
// Ocilloscope        EBrand                   2       $100.00       $ 200.00
// Resistor           Ohmite                 100       $  0.05       $   5.00
//
// Number of different items: 3
// Total quantity: 172
// Total value of all items: $256.10
//
// Press enter to continue...
//
//                            Reorder Report
// Item               Manufacturer       Quantity  Minimum  Order  Cost
// Capacitor          Ohmite                70       80      10    $  7.30
// Resistor           Ohmite               100      250     150    $  7.50
//
// Number of different items to order: 2
// Total number to order: 160
// Total cost: $14.80
//
// Press enter to continue...

#include <iostream>
#include <iomanip>
#include <fstream>
#include <cstring>
#include <string>

using namespace std;

// needed type to store data
struct Parts {
  string name;
  string maker;
  int amount;
  int minimum;
  double cost;
};

void clearScreen();
// clears the screen

void welcome();
// prints a welcome message

int menu();
// allows the user to choose the form of display

int readFile(Parts list[], int numElements);
// reads in a file and writes to array
// MODIFY: adds data to list
// IN: numElements (size of list)

void selectionSort(Parts list[], int numElements);
// sorts the elements in the array by name
// MODIFY: sorts data in list
// IN: numElements

void swap(Parts& var1, Parts& var2);
// swaps the two parameters values
// MODIFY: two variables to be swapped

void printInventory(Parts list[], int numElements);
// prints a table of inventory information
// IN: inventory array, numElements

void printReorder(Parts list[], int numElements);
// prints a table of order information
// IN: inventory array, numElements

void goodbye();
// prints a goodbye message

// use for formatting to screen
const int SCREEN_HEIGHT = 40;
const int SCREEN_WIDTH = 80;
const char BLANK = ' ';
// use to build array
const int MAX = 150;
// use to determine menu choices
const int INVENTORY = 1;
const int REORDER = 2;
const int QUIT = 3;
// use to format values
const char* c_str();
const int DOLLAR_PRECISION = 2;
// use to format tables
const int NAME_COL = 20;
const int VAL_COL = 8;
const int INT_COL = 7;
const char DOLLAR = '$';

int main ()
{
  // use to determine printing
  int size;
  int display = 1;
  Parts inventory[MAX];
  
  // use to set dollars and cents
  cout.setf(ios::fixed);
  cout.setf(ios::showpoint);
  cout.precision(DOLLAR_PRECISION);
  
  // welcome message
  welcome();

  // read in file
  size = readFile(inventory, MAX);
  if (size != 0) {
	selectionSort(inventory, size);
  // begin process
    while(display == INVENTORY || display == REORDER) {
	  clearScreen();
	  display = menu();
	  switch (display) {
	    case (INVENTORY) :
		  clearScreen();
	      printInventory(inventory, size);
		  break;
	    case (REORDER) :
		  clearScreen();
		  printReorder(inventory, size);
		  break;
	    case (QUIT) :
		  goodbye();
		  return 0;
	  }
	  cout << "Press enter to continue...";
	  cin.get();
    }
  }else {
	cout << " ERROR: Could not read file. Exiting program. \n";
    goodbye();
	return 0;
  }
}


void clearScreen()
{
  for (int i = 0; i < SCREEN_HEIGHT; i++)
	cout << "\n";
}

void welcome()
{
  cout << "\n\n";
  cout << " Welcome to the Inventory Program. Here you can select \n"
	   << " to display an inventory report or a re-order report.\n\n";
}

int menu()
{
  int choice = 0;
  while(choice < INVENTORY || choice > QUIT) {
	cout << "\n\n";
	cout << " Here are your display options.\n";
    cout << INVENTORY << " Inventory report. \n";
    cout << REORDER << " Reorder report. \n";
	cout << QUIT << " Leave program. \n";
    cout << " What would you like to do? ";
	cin >> choice;
	cin.get();
	cout << "\n\n";
  }
  return choice;
}

int readFile(Parts list[], int numElements)
{
  // use to read file
  ifstream inFile;
  string filename;
  int size = 0;
  // use to load data
  string pname;
  string pmaker;
  int pamount;
  int pminimum;
  double pcost;
  
  cout << " Input a file name: ";
  cin >> filename;
  cin.get();
  inFile.open(filename.c_str());
  while (size < numElements && inFile >> pname) {
	list[size].name = pname;
	inFile >> pmaker;
	list[size].maker = pmaker;
	inFile >> pamount;
	list[size].amount = pamount;
	inFile >> pminimum;
	list[size].minimum = pminimum;
	inFile >> pcost;
	list[size].cost = pcost;
	size++;
  }
  cout << "\n\n";
  return size;
}

void selectionSort(Parts list[], int numElements)
{
  int smallest;
  for (int index = 0; index < numElements - 1; index++) {
	smallest = index;
	for (int min = index + 1; min < numElements; min++)
	  if (list[min].name < list[smallest].name)
		smallest = min;
	if (smallest != index)
	  swap(list[smallest], list[index]);
  }
}

void swap(Parts& var1, Parts& var2)
{
  Parts temp = var1;
  var1 = var2;
  var2 = temp;
}

void printInventory(Parts list[], int numElements)
{
  const string TITLE = "Inventory Report";
  int items = 0;
  int stock = 0;
  double value = 0;
  for (unsigned i = 0; i < (SCREEN_WIDTH - TITLE.length())/2; i++)
	cout << BLANK;
  cout << TITLE << "\n";
  cout << "Item                Manufacturer         ";
  cout << "Quantity     Cost Each     Total Value\n";
  for (int r = 0; r < numElements; r++) {
	cout << left << setw(NAME_COL) << list[r].name.c_str() << setw(NAME_COL)
		 << list[r].maker.c_str();
    cout << right << setw(INT_COL) << list[r].amount
		 << setw(VAL_COL) << DOLLAR << setw(VAL_COL) << list[r].cost
		 << setw(VAL_COL) << DOLLAR << setw(VAL_COL)
		 << list[r].cost * list[r].amount;
	cout << "\n";
	items++;
	stock += list[r].amount;
	value += list[r].amount*list[r].cost;
  }
  cout << "\n";
  cout << "Number of different items: " << items << "\n";
  cout << "Total quantity: " << stock << "\n";
  cout << "Total value of all items: " << DOLLAR << value << "\n\n";
}

void printReorder(Parts list[], int numElements)
{
  const string TITLE = "Reorder Report";
  int order = 0;
  int totalOrder = 0;
  double  totalCost = 0;
  for (unsigned i = 0; i < (SCREEN_WIDTH - TITLE.length())/2; i++)
	cout << BLANK;
  cout << TITLE << "\n";
  cout << "Item                Manufacturer       ";
  cout << "Quantity  Minimum Order      Cost\n";
  for (int r = 0; r < numElements; r++) {
	if (list[r].amount < list[r].minimum) {
	  cout << left << setw(NAME_COL) << list[r].name.c_str() << setw(NAME_COL)
		   << list[r].maker.c_str();
	  cout << right << setw(INT_COL) << list[r].amount << setw(INT_COL)
		   << list[r].minimum << setw(INT_COL)
		   << list[r].minimum - list[r].amount << setw(VAL_COL) << DOLLAR
		   << setw(VAL_COL)
		   << list[r].cost * (list[r].minimum - list[r].amount);
	  cout << "\n";
	  order++;
	  totalOrder += list[r].minimum - list[r].amount;
	  totalCost += list[r].cost * (list[r].minimum - list[r].amount);
	}
  }
  cout << "\n";
  cout << "Number of different items to order: " << order << "\n";
  cout << "Total number to order: " << totalOrder << "\n";
  cout << "Total cost: " << DOLLAR << totalCost << "\n\n";
}

void goodbye()
{
  cout << " Thank you for participating. \n\n";
}
