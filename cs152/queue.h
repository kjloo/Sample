//Kaleb Loo
//queue.h
//CPSC 152
//2/24/13
//Provides the functionality of a queue including creating a queue,
//enqueuing, and dequeuing, and returning the front of the queue.

using namespace std;

#ifndef QUEUE_H
#define QUEUE_H

class Queue
{
 public:
  Queue ();
  //default constructor

  Queue (const Queue& q);
  //copy contructor

  Queue& operator= (const Queue& rhs);
  //overloaded assignment operator

  ~Queue ();
  //destructor

  bool enqueue (int data);
  //adds data to the end of the queue
  //IN: data
  //OUT: true/false

  bool dequeue (int& data);
  //takes data from the front of the queue
  //MODIFY: data
  //OUT: true/false

  bool isEmpty ();
  //returns a bool that indicates if the queue is empty.
  //OUT: true/false

  bool frontIs (int& data);
  //looks at the data in the front of the queue
  //MODIFY: data
  //OUT: true/false

 private:
  struct ListNode
  {
	int num;
	ListNode * next;
  };
  ListNode *front;
  ListNode *tail;
};

#endif
