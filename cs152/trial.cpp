// trial.cpp
// Debugging exercise

#include <iostream>
#include <string>
#include <fstream>

using namespace std;

struct Node{
  string data;
  Node* next;
};

void addNode(Node*& h, string n);
// adds name to h in alphabetical order
// IN: n
// MODIFY: h

void printList(Node* h);
// prints list of names in a column
// IN: h

void deleteList(Node*& h);
// deletes all nodes on list
// MODIFY: h

int main()
{
  Node* head = NULL;
  ifstream inFile;
  string name;
  inFile.open("test.dat");

  cout << endl << endl << "This program reads in a list of names from the "
	   << "file 'test.dat' and " << endl
	   << "inserts them into a list in alphabetical order." << endl << endl;

  printList(head);

  while (getline(inFile, name)){
	addNode(head, name);
	printList(head);
  }

  printList(head);
  
  deleteList(head);
  return 0;
}
void addNode(Node*& h, string n)
{
  Node* temp = new Node;
  temp -> data = n;

  if (h == NULL || h -> data > temp -> data){
	temp -> next = h;
	h = temp;
  }else{
	Node* ptr = h;
	while (ptr -> next != NULL && ptr -> next -> data < temp -> data){
	  ptr = ptr -> next;
	}
	temp -> next = ptr -> next;
	ptr -> next = temp;
  }
}

void printList(Node* h)
{
  cout << "Printing list of names: " << endl;
  while (h != NULL){
	cout << h -> data << endl;
	h = h -> next;
  }

  cout << endl << endl;
}

void deleteList(Node*& h)
{
  Node* ptr = h;
  while (ptr -> next != NULL){
	ptr = h;
	h = h -> next;
	delete ptr;
  }
}
