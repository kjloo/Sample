//Kaleb Loo
//stack.h Version 1.0
//CPSC 250
//4/24/13
//Provide the functionality of a selective prime stack including creating a
//stack, selectively pushing onto the stack, popping from the stack, checking
//if the stack is empty, and resizing the stack.

using namespace std;

struct ListNode
{
  ListNode *right;
  ListNode *left;
  int data;
};

#ifndef STACK_H
#define STACK_H

class stack
{
 public:
  stack();
  //default constructor

  stack(unsigned int s);
  //constructor

  stack(const stack& s);
  //copy constructor

  stack& operator=(const stack& rhs);
  //overloaded assignment operator

  ~stack();
  //destructor

  void push(ListNode *data);
  //pushes data onto the stack
  //IN: data

  ListNode* pop();
  //pops data off of the stack
  //OUT: data

  bool isEmpty();
  //returns a true if the stack is empty and a false otherwise
  //OUT: true/false

 private:
  void copyStack(int smallSize, int largeSize, ListNode **stackArray);
  //copies a stack to another instance of a stack
  //IN: smallSize, largeSize, stackArray
  //MODIFY: array
  
  void resizeStack();
  //changes the size of the stack when stack is full
  //MODIFY: size, array
  
  ListNode **array;
  static const int DEFAULT = 10;
  int size;
  int top;
};

#endif
