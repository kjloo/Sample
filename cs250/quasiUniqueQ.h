//Kaleb Loo
//quasiUniqueQ.h Version 1.0
//CPSC 250
//4/11/13
//Provide the functionality of a selective priority queue including creating
//a queue, selectively enqueueing onto the queue, dequeueing from the queue,
//and checking if the queue is empty. Also, the queue has an internal aging
//process that ages after an enqueue occurs.  The priority scheme is set to
//such that high priorities correspond to low numbers. If two elements have
//the same priority then age is not taken into account and the priority is
//based on the data only.

using namespace std;

#ifndef QUASIUNIQUEQ_H
#define QUASIUNIQUEQ_H

struct ListNode
{
  //high priorities correspond to low numbers.
  int data;
  int age; //increments on enqueue
  ListNode *next;
};

class quasiUniqueQ
{
 public:
  quasiUniqueQ();
  //constructor

  quasiUniqueQ(const quasiUniqueQ& q);
  //copy constructor

  quasiUniqueQ& operator=(const quasiUniqueQ& rhs);
  //overloaded assignment operator      
  
  ~quasiUniqueQ();
  //destructor

  void enqueue(int num);
  //selectively inserts a node into the queue based on priority
  //ages all elements upon a successful enqueue
  //IN: num
  //MODIFY: head

  int dequeue();
  //returns the value at the front of the queue and deletes the node
  //OUT: data
  //MODIFY: head

  bool isEmpty();
  //returns true if the queue is empty and a false otherwise
  //OUT: true/false

  ListNode* traverse(int num);
  //returns the address of the node before the data location
  //IN: num
  //OUT: ptr

 private:
  void copyList(ListNode *rhead);
  //makes a copy of a Linked List
  //IN: rhead
  //MODIFY: head

  bool filter(int num);
  //returns a true if the integer is odd or first instance of an even
  //number and returns a false otherwise
  //IN: num
  //OUT: true/false

  void deleteList();
  //deletes entire queue
  //MODIFY: head
  
  ListNode *head;  
};

#endif
