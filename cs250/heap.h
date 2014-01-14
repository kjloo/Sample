//Kaleb Loo
//heap.h Version 1.0
//CPSC 250
//4/29/13
//Provide the functionality of a selective priority queue including creating
//a queue, selectively enqueueing onto the queue, dequeueing from the queue,
//and checking if the queue is empty. Also, the queue has an internal aging
//process that ages after an enqueue occurs.  The priority scheme is set to
//such that high priorities correspond to low numbers. If two elements have
//the same priority then age is not taken into account and the priority is
//based on the data only.

using namespace std;

#ifndef HEAP_H
#define HEAP_H

class heap
{
 public:
  heap(unsigned s = 10);
  //constructor

  heap(const heap& h);
  //copy constructor

  heap& operator=(const heap& rhs);
  //overloaded assignment operator      
  
  ~heap();
  //destructor

  void enqueue(int num);
  //selectively inserts a node into the queue based on priority
  //ages all elements upon a successful enqueue
  //IN: num
  //MODIFY: head
  //POSTCONDITION: the list should not be empty

  int dequeue();
  //returns the value at the front of the queue and deletes the node
  //OUT: data
  //MODIFY: head
  //PRECONDITION: the list should not be empty
  //POSTCONDITION: the list may be empty

  bool isEmpty();
  //returns true if the queue is empty and a false otherwise
  //OUT: true/false

 private:
  struct ListNode
  {
	//high priorities correspond to low numbers.
	int data;
	int age; //increments on enqueue
  };

  void copyList(int smallSize, int largeSize, ListNode* heapArray);
  //makes a copy of the array
  //IN: smallSize, largeSize, heapArray
  //MODIFY: array

  void resize();
  //doubles the size of the array

  void swap(ListNode& a, ListNode& b);
  //swaps the values of nodes
  //MODIFY: a, b
  
  bool filter(int num);
  //returns a true if the integer is odd or first instance of an even
  //number and returns a false otherwise
  //IN: num
  //OUT: true/false

  void age();
  //ages every element in the array
  //MODIFY: age

  int findMin(int a, int b);
  //returns the index that has the smaller priority
  //IN: a, b
  //OUT: a/b
  
  ListNode *array;
  int size;
  int index;
};

#endif
