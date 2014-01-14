//Kaleb Loo
//quasiUniqueQ.cpp Version 1.0
//CPSC 250
//4/8/13
//Implementation of the quasiUniqueQ.h header file

#include <iomanip>
#include "quasiUniqueQ.h"

quasiUniqueQ::quasiUniqueQ()
{
  head = NULL;
}

quasiUniqueQ::quasiUniqueQ(const quasiUniqueQ& q)
{
  copyList(q.head);
}

quasiUniqueQ& quasiUniqueQ::operator=(const quasiUniqueQ& rhs)
{
  if (this != &rhs) {
	deleteList();
	copyList(rhs.head);
  }
  return *this;
}

quasiUniqueQ::~quasiUniqueQ()
{
  deleteList();
}

void quasiUniqueQ::enqueue(int num)
{
  if (filter(num)) {
	ListNode *tmp = new ListNode;
	tmp -> data = num;
	tmp -> age = 0;
	if (head == NULL || head -> data - head -> age >= num) {
	  tmp -> next = head;
	  head = tmp;
	}else {
	  ListNode *ptr = traverse(num);
	  tmp -> next = ptr -> next;
	  ptr -> next = tmp;
	}
	tmp = head;
	while (tmp != NULL) {
	  tmp -> age++;
	  tmp = tmp -> next;
	}
  }
}

int quasiUniqueQ::dequeue()
{
  int num = head -> data;
  ListNode *del = head;
  head = head -> next;
  delete del;
  del = NULL;
  return num;
}

bool quasiUniqueQ::isEmpty()
{
  return (head == NULL);
}

ListNode* quasiUniqueQ::traverse(int num)
{
  ListNode *ptr = head;
  while (ptr -> next != NULL && ptr -> next -> data - ptr -> next -> age < num)
	ptr = ptr -> next;
  return ptr;
}

void quasiUniqueQ::copyList(ListNode *rhead)
{
  if (rhead == NULL)
	head = NULL;
  else {
	//Auxillary Pointers
	ListNode *aux1;
	ListNode *aux2;
	ListNode *tmp;
	head = new ListNode;
	head -> data = rhead -> data;
	head -> age = rhead -> age;
	aux1 = rhead -> next;
	aux2 = head;
	while (aux1 != NULL) {
	  tmp = new ListNode;
	  aux2 -> next = tmp;
	  aux2 = aux2 -> next;
	  aux2 -> data = aux1 -> data;
	  aux2 -> age = aux1 -> age;
	  aux1 = aux1 -> next;
	}
	aux2 -> next = NULL;
  }
}

void quasiUniqueQ::deleteList()
{
  ListNode *del = head;
  while (head != NULL) {
	head = head -> next;
	delete del;
	del = head;
  }
}


bool quasiUniqueQ::filter(int num)
{
  if (num % 2 != 0)
	return true;
  ListNode *ptr = head;
  while (ptr != NULL && ptr -> data != num)
	ptr = ptr -> next;
  return (ptr == NULL);
}
