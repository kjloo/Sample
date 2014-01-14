//Kaleb Loo
//queue.cpp
//CPSC 152
//2/24/13
//Implementation of the queue.h header file.

#include <iomanip>
#include <iostream>
#include <cassert>
#include "queue.h"

Queue::Queue ()
{
  front = NULL;
  tail = NULL;
}

Queue::Queue (const Queue& q)
{
  ListNode *qptr;
  ListNode *ptr;
  if (q.front == NULL) {
	front = NULL;
	tail = NULL;
  }else {
	if (q.front != NULL) {
	  front = new ListNode;
	  front -> num = q.front -> num;
	  qptr = q.front -> next;
	  tail = front;
	}
	while (qptr != NULL) {
	  ptr = new ListNode;
	  tail -> next = ptr;
	  tail = tail -> next;
	  tail -> num = qptr -> num;
	  qptr = qptr -> next;
	}
	tail -> next = NULL;
  }
}

Queue& Queue::operator= (const Queue& rhs)
{
  bool check = true;
  ListNode *rptr = rhs.front;
  ListNode *ptr = front;
  ListNode *del;
  if (rhs.front == NULL ^ front == NULL) {
	check = false;
  }else {
	while (check && (rptr != NULL && ptr != NULL)) {
	  if (rptr -> num != ptr -> num)
		check = false;
	  else {
		rptr = rptr -> next;
		ptr = ptr -> next;
	  }
	}
  }
  if (!check) {
	while (front != NULL) {
	  del = front;
	  front = front -> next;
	  delete del;
	  del = NULL;
	}
	if (rhs.front != NULL) {
	  front = new ListNode;
	  front -> num = rhs.front -> num;
	  rptr = rhs.front -> next;
	  tail = front;
	}
	while (rptr != NULL) {
	  ptr = new ListNode;
	  tail -> next = ptr;
	  tail = tail -> next;
	  tail -> num = rptr -> num;
	  rptr = rptr -> next;
	}
	tail -> next = NULL;
  }
  return *this;
}

Queue::~Queue ()
{
  cout << "DESTROY!\n";
  ListNode* del;
  while (front != NULL) {
	del = front;
	front = front -> next;
	delete del;
	del = NULL;
  }
}

bool Queue::enqueue (int data)
{
  ListNode *tmp = new ListNode;
  if (tmp == NULL)
	return false;
  tmp -> num = data;
  tmp -> next = NULL;
  if (isEmpty ()) {
	front = tmp;
	tail = tmp;
  }else {
	tail -> next = tmp;
	tail = tail -> next;
  }
  return true;
}

bool Queue::dequeue (int& data)
{
  if (isEmpty ())
	return false;
  ListNode *del;
  data = front -> num;
  del = front;
  front = front -> next;
  delete del;
  del = NULL;
  return true;
}

bool Queue::isEmpty ()
{
  return (front == NULL);
}

bool Queue::frontIs (int& data)
{
  if (isEmpty ())
	return false;
  data = front -> num;
  return true;
}
