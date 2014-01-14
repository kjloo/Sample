//Kaleb Loo
//stack.cpp
//CPSC 152
//2/23/13
//Implementation of the stack.h header file

#include <iomanip>
#include <cassert>
#include "stack.h"

Stack::Stack ()
{
  size = DEFAULT;
  stackArr = new int[size];
  assert (stackArr != NULL);
  top = -1;
}

Stack::Stack (int num)
{
  size = num;
  stackArr = new int[size];
  assert (stackArr != NULL);
  top = -1;
}

Stack::Stack (const Stack& s)
{
  if (s.size > 0) {
	stackArr = new int[s.size];
  }else
	stackArr = NULL;
  size = s.size;
  for (int i = 0; i < size; i++) {
	stackArr[i] = s.stackArr[i];
  }
  top = s.top;
}

Stack& Stack::operator= (const Stack& rhs)
{
  bool check = true;
  if (size != rhs.size) {
	size = rhs.size;
	stackArr = new int[size];
	for (int i = 0; i < size; i++)
	  stackArr[i] = rhs.stackArr[i];
	top = rhs.top;
  }else {
	for (int i = 0; i < size; i++)
	  if (stackArr[i] != rhs.stackArr[i])
		check = false;
	if (!check) {
	  for (int i = 0; i < size; i++)
		stackArr[i] = rhs.stackArr[i];
	  top = rhs.top;
	}
  }
  return *this;
}

Stack::~Stack ()
{
  delete [] stackArr;
}

bool Stack::push (int data)
{
  if (!resizeStack ())
	return false;
  top++;
  stackArr[top] = data;
  return true;
}

bool Stack::pop (int& data)
{
  if (isEmpty ())
	return false;
  data = stackArr[top];
  top--;
  return true;
}

bool Stack::isEmpty ()
{
  return (top < 0);
}

bool Stack::topIs (int& data)
{
  if (top < 0) {
	return false;
  }else {
	data = stackArr[top];
	return true;
  }
}

bool Stack::resizeStack ()
{
  const double SCALE = 1.5;
  if (top == size - 1) {
	size = (int)(size * SCALE);
	int *tmp = new int[size];
	if (tmp == NULL)
	  return false;
	for (int i = 0; i < size; i++)
	  tmp[i] = stackArr[i];
	delete [] stackArr;
	stackArr = tmp;
  }
  return true;
}
