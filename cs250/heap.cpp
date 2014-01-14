//Kaleb Loo
//heap.cpp Version 1.0
//CPSC 250
//4/29/13
//Implementation of the quasiUniqueQ.h header file

#include <iomanip>
#include <cassert>
#include "heap.h"

heap::heap(unsigned s)
{
  size = s;
  array = new ListNode[size + 1];
  assert (array != NULL);
  index = 0;
}

heap::heap(const heap& h)
{
  size = h.size;
  copyList(size, h.size, h.array);
  index = h.index;
}

heap& heap::operator=(const heap& rhs)
{
  if (this != &rhs) {
	delete[] array;
	size = rhs.size;
	copyList(size, rhs.size, rhs.array);
	index = rhs.index;
  }
  return *this;
}

heap::~heap()
{
  delete[] array;
}

void heap::enqueue(int num)
{
  if (filter(num)) {
	if (index == size)
	  resize();
	index++;
	int position = index;
	array[index].data = num;
	while (position > 1 && array[position].data - array[position].age <
		   array[position/2].data - array[position/2].age) {
	  swap(array[position], array[position/2]);
	  position = position/2;
	}
	age();
  }
}

int heap::dequeue()
{
  int data = array[1].data;
  array[1].data = array[index].data;
  int small;
  index--;
  int position = 1;
  while (2*position < index && array[position].data - array[position].age >
		 array[2*position].data - array[2*position].age ||
		 array[position].data - array[position].age >
		 array[2*position + 1].data - array[2*position + 1].age) {
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

bool heap::isEmpty()
{
  return (index <= 0);
}

void heap::copyList(int smallSize, int largeSize, ListNode *heapArray)
{
  ListNode *tmp = new ListNode[largeSize + 1];
  for (int i = 1; i <= smallSize; i++)
	tmp[i] = heapArray[i];
  if (smallSize != largeSize)
	delete[] array;
  array = tmp;  
}

void heap::resize()
{
  const int SCALE = 2;
  copyList(size, size * SCALE, array);
  size *= SCALE;
}

void heap::swap(ListNode& a, ListNode& b)
{
  ListNode tmp = a;
  a = b;
  b = tmp;
}

bool heap::filter(int num)
{
  return true;
}

void heap::age()
{
  for (int i = 1; i < size; i++)
	array[i].age++;
}

int heap::findMin(int a, int b)
{
  if (array[a].data - array[a].age < array[b].data - array[b].age)
	return a;
  return b;
}
