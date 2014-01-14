//Kaleb Loo
//LL.cpp
//CPSC 250
//4/8/13
//Implementation of the LL.h header file

#include <iomanip>
#include <iostream>
#include "LL.h"

LL::LL()
{
  head = NULL;
}

LL::~LL()
{
  ListNode *del;
  while(head != NULL) {
	del = head;
	head = head -> next;
	delete del;
	del = NULL;
  }
}

void LL::insertNode(int num)
{
  ListNode *tmp = new ListNode;
  tmp -> data = num;
  if (head == NULL || head -> data > num) {
	tmp -> next = head;
	head = tmp;
  }else {
	ListNode *ptr = traverse(num);
	tmp -> next = ptr -> next;
	ptr -> next = tmp;
  }
}

void LL::deleteNode(int num)
{
  ListNode *del;
  if (head != NULL && head -> data == num) {
	del = head;
	head = head -> next;
	delete del;
  }else {
	ListNode *ptr = traverse(num);
	if (ptr -> next != NULL && ptr -> next -> data == num) {
	  del = ptr -> next;
	  ptr -> next = ptr -> next -> next;
	  delete del;
	}
  }
}

void LL::printList()
{
  ListNode *ptr = head;
  while (ptr != NULL) {
	cout << ptr -> data << "\n";
	ptr = ptr -> next;
  }
}

ListNode* LL::traverse(int num)
{
  ListNode *ptr = head;
  while (ptr -> next != NULL && ptr -> next -> data < num)
	ptr = ptr -> next;
  return ptr;
}
