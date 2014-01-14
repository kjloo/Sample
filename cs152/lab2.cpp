//Kaleb Loo
//lab2.cpp
//CPSC 152
//1/25/13

using namespace std;
#include <iostream>
#include <cstdlib>

struct ListNode
{
  int data;
  ListNode* next;
};

int main ()
{
  const int SIZE = 15;
  ListNode* head;
  ListNode* ptr;
  head = new ListNode;
  ptr = head;
  //Assign Values
  for (int i = 0; i < SIZE; i++) {
	ptr -> data = i;
	ptr -> next = new ListNode;
	ptr = ptr -> next;
  }
  //Start at head
  ptr = head;
  //Print Values that exist
  while (ptr -> next != NULL) {
	cout << ptr -> data << "\n";
	ptr = ptr -> next;
  }
  //Start at head
  ptr = head;
  //Deallocate memory
  while (head != NULL) {
	ptr = head;
	head = head -> next;
	delete ptr;
	ptr = NULL;
  }
  return 0;
}
