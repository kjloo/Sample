//Kaleb Loo
//sPS.cpp Version 1.0
//CPSC 250
//4/4/13
//Implementation of the sPS.h header file

#include <iostream>
#include <iomanip>
#include <cassert>
#include <cmath>
#include "sPS.h"

sPS::sPS()
{
  size = DEFAULT;
  array = new int[size];
  assert (array != NULL);
  top = -1;
}

sPS::sPS(unsigned int s)
{
  size = s;
  array = new int[size];
  assert (array != NULL);
  top = -1;
}

sPS::sPS(const sPS& s)
{
  size = s.size;
  copyStack(size, s.size, s.array);
  top = s.top;
}

sPS& sPS::operator=(const sPS& rhs)
{
  if (this != &rhs) {
	delete[] array;
	size = rhs.size;
	copyStack(size, rhs.size, rhs.array);
	top = rhs.top;
  }
  return *this;
}

sPS::~sPS()
{
  delete[] array;
}

void sPS::push(int data)
{
  if (filter(data)) {
	if (top == size - 1)
	  resizeStack();
	top++;
	array[top] = data;
  }
}

int sPS::pop()
{
  int data = array[top];
  top--;
  return data;
}

bool sPS::isEmpty()
{
  return (top < 0);
}

void sPS::copyStack(int smallSize, int largeSize, int *stackArray)
{
  int *tmp = new int[largeSize];
  for (int i = 0; i < smallSize; i++)
	tmp[i] = stackArray[i];
  if (smallSize != largeSize)
    delete[] array;
  array = tmp;
}

void sPS::resizeStack()
{
  const int SCALE = 2;
  copyStack(size, size * SCALE, array);
  size *= SCALE;
}

bool sPS::filter(int data)
{
  const int DIVISOR = 3;
  const int ADDITIVE = 1;
  if (isPrime(data))
	return ((data + ADDITIVE) % DIVISOR == 0);
  //Data is not prime
  return false;
}

bool sPS::isPrime(int num)
{
  if (num <= 1)
	return false;
  else if (num == 2)
	return true;
  else if (num % 2 == 0)
	return false;
  //Data is a number not divisible by 2
  int divisor = 3;
  int threshhold = (int) sqrt(num);
  while (divisor <= threshhold && num % divisor != 0)
	divisor += 2;
  return (divisor > threshhold);
}
  
