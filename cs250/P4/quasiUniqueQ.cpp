//Kaleb Loo
//quasiUniqueQ.cpp Version 2.0
//CPSC 250
//4/29/13
//Implementation of the quasiUniqueQ.h header file

#include <iomanip>
#include <cassert>
#include "quasiUniqueQ.h"

quasiUniqueQ::quasiUniqueQ(unsigned s)
{
  size = s;
  array = new ListNode[size + 1];
  assert (array != NULL);
  index = 0;
}

quasiUniqueQ::quasiUniqueQ(const quasiUniqueQ& q)
{
  size = q.size;
  copyList(size, q.size, q.array);
  index = q.index;
}

quasiUniqueQ& quasiUniqueQ::operator=(const quasiUniqueQ& rhs)
{
  if (this != &rhs) {
	delete[] array;
	size = rhs.size;
	copyList(size, rhs.size, rhs.array);
	index = rhs.index;
  }
  return *this;
}

quasiUniqueQ::~quasiUniqueQ()
{
  delete[] array;
}

void quasiUniqueQ::enqueue(int num)
{
  if (filter(num)) {
	if (index == size)
	  resize();
	index++;
	int position = index;
	array[index].data = num;
	array[index].age = 0;
	while (position > 1 && array[position].data - array[position].age <=
		   array[position/2].data - array[position/2].age) {
	  swap(array[position], array[position/2]);
	  position = position/2;
	}
	age();
  }
}

int quasiUniqueQ::dequeue()
{
  int data = array[1].data;
  array[1] = array[index];
  int small;
  if (!isEmpty())
	index--;
  int position = 1;
  while ((2*position <= index &&
		  position != findMin(position, 2*position)) ||
		 (2*position + 1 <= index &&
		  position != findMin(position, 2*position + 1))) {
	if (2*position + 1 > index) {
	  swap(array[position], array[2*position]);
	  position++;
	}else {
	  small = findMin(2*position, 2*position + 1);
	  swap(array[position], array[small]);
	  position = small;
	}
  }
  return data;
}

bool quasiUniqueQ::isEmpty()
{
  return (index <= 0);
}

void quasiUniqueQ::copyList(int smallSize, int largeSize, ListNode *heapArray)
{
  ListNode *tmp = new ListNode[largeSize + 1];
  for (int i = 1; i <= smallSize; i++)
	tmp[i] = heapArray[i];
  if (smallSize != largeSize)
	delete[] array;
  array = tmp;  
}

void quasiUniqueQ::resize()
{
  const int SCALE = 2;
  copyList(size, size * SCALE, array);
  size *= SCALE;
}

void quasiUniqueQ::swap(ListNode& listA, ListNode& listB)
{
  ListNode tmp = listA;
  listA = listB;
  listB = tmp;
}

bool quasiUniqueQ::filter(int num)
{
  if (num % 2 != 0)
	return true;
  int i = 1;
  while (i <= index && array[i].data != num)
	i++;
  return (i > index);
}

void quasiUniqueQ::age()
{
  for (int i = 1; i <= index; i++)
	array[i].age++;
}

int quasiUniqueQ::findMin(int indexA, int indexB)
{
  //Must check several cases to determine what to do when the priorities
  //are the same
  //Index A is strictly smaller than Index B
  if (array[indexA].data - array[indexA].age
	  < array[indexB].data - array[indexB].age)
	return indexA;
  //Index B is strictly smaller than Index A
  else if (array[indexB].data - array[indexB].age
		   < array[indexA].data - array[indexA].age)
	return indexB;
  //Index A and Index B have the same priority
  //The data in Index A is smaller than the value in Index B
  else if (array[indexA].data < array[indexB].data)
	return indexA;
  //The data in Index B is smaller than the value in Index A
  return indexB;
}
