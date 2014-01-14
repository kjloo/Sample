//Kaleb Loo
//stack.cpp Version 2.0
//CPSC 250
//4/4/13
//Implementation of the stack.h header file

#include <iostream>
#include <iomanip>
#include <cassert>
#include <cmath>
#include "stack.h"

stack::stack()
{
  size = DEFAULT;
  array = new ListNode*[size];
  assert (array != NULL);
  top = -1;
}

stack::stack(unsigned int s)
{
  size = s;
  array = new ListNode*[size];
  assert (array != NULL);
  top = -1;
}

stack::stack(const stack& s)
{
  size = s.size;
  copyStack(size, s.size, s.array);
  top = s.top;
}

stack& stack::operator=(const stack& rhs)
{
  if (this != &rhs) {
	delete[] array;
	size = rhs.size;
	copyStack(size, rhs.size, rhs.array);
	top = rhs.top;
  }
  return *this;
}

stack::~stack()
{
  delete[] array;
}

void stack::push(ListNode *data)
{
  if (top == size - 1)
	resizeStack();
  top++;
  array[top] = data;
}

ListNode* stack::pop()
{
  ListNode *data = array[top];
  top--;
  return data;
}

bool stack::isEmpty()
{
  return (top < 0);
}

void stack::copyStack(int smallSize, int largeSize, ListNode **stackArray)
{
  ListNode **tmp = new ListNode*[largeSize];
  for (int i = 0; i < smallSize; i++)
	tmp[i] = stackArray[i];
  if (smallSize != largeSize)
    delete[] array;
  array = tmp;
}

void stack::resizeStack()
{
  const int SCALE = 2;
  copyStack(size, size * SCALE, array);
  size *= SCALE;
}
  
