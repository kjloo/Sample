//Kaleb Loo
//lab3.cpp
//CPSC 152
//2/1/13

using namespace std;

#include <iostream>
#include <iomanip>
#include <cstdlib>
#include <ctime>

struct ListNode
{
  int data;
  ListNode* next;
};

void insert (ListNode*& head, int d);
void printList (ListNode* head);
void deleteNode (ListNode*& head, int delNum);
void deleteAll (ListNode*& head, int delNum);
void remove (ListNode* head);

int main()
{
  srand(time(0));
  const int SIZE = 15;
  ListNode* head = NULL;
  int delNum;
  //Assign Values
  for (int i = 0; i < SIZE; i++)
	insert (head, (rand() % 10));
  //Print List
  printList (head);
  //Delete data
  cout << "What number would you like to delete? ";
  cin >> delNum;
  deleteNode (head, delNum);
  //Print List
  printList (head);
  //Pause
  cout << "<Press Enter to Continue>";
  cin.ignore();
  cin.get();
  //Add multiple values
  for (int i = 0; i < 2; i++)
	insert (head, 3);
  //Print List
  printList (head);
  //Delete Number
  cout << "What number would you like to delete? ";
  cin >> delNum;
  deleteAll (head, delNum);
  //Print List
  printList (head);
  //Deallocate memory
  remove (head);
  return 0;
}

void insert (ListNode*& head, int d)
{
  ListNode* ptr;
  ListNode* temp = new ListNode;
  temp -> data = d;
  if (head == NULL || head -> data > d) {
	temp -> next = head;
	head = temp;
  }else {
	ptr = head;
	while (ptr -> next != NULL && ptr -> next -> data < temp -> data)
	  ptr = ptr -> next;
	temp -> next = ptr -> next;
	ptr -> next = temp;
  }
}

void printList (ListNode* head)
{
  ListNode* print;
  //Start at head
  print = head;
  //Print Values that exist
  while (print != NULL) {
	cout << print -> data << "\n";
	print = print -> next;
  }
}

void deleteNode (ListNode*& head, int delData)
{
  ListNode* ptr;
  ListNode* del;
  //Delete Number
  ptr = head;
  if (head != NULL && head -> data == delData) {
	del = head;
	head = head -> next;
	delete del;
  }else {
	while (ptr -> next != NULL && ptr -> next -> data < delData)
	  ptr = ptr -> next;
	if (ptr -> next != NULL && ptr -> next -> data == delData) {
	  del = ptr -> next;
	  ptr -> next = ptr -> next -> next;
	  delete del;
	}
  }  
}

void deleteAll (ListNode*& head, int delData)
{
  ListNode* ptr;
  ListNode* del;
  //Delete Number
  ptr = head;
  if (head != NULL && head -> data == delData) {
	while (head != NULL && head -> data == delData) {
	  del = head;
	  head = head -> next;
	  delete del;
	}
  }else {
	while (ptr -> next != NULL && ptr -> next -> data < delData)
	  ptr = ptr -> next;
	while (ptr -> next != NULL && ptr -> next -> data == delData) {
	  del = ptr -> next;
	  ptr -> next = ptr -> next -> next;
	  delete del;
	}
  }
}

void remove (ListNode* head)
{
  ListNode* ptr;
  while (head != NULL) {
	ptr = head;
	head = head -> next;
	delete ptr;
	ptr = NULL;
  }
}
