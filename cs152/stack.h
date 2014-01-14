//Kaleb Loo
//stack.h
//CPSC 152
//2/23/13
//Provides the functionality of a stack including creating a stack,
//pushing onto the stack, popping from the stack, and returning the
//top of the stack.

using namespace std;

#ifndef STACK_H
#define STACK_H

class Stack
{
 public:
  Stack ();
  //default constructor

  Stack (int num);
  //constructor
  
  Stack (const Stack& s);
  //copy constructor

  Stack& operator= (const Stack& rhs);
  //overloaded assignment operator

  ~Stack ();
  //destructor

  bool push (int data);
  //pushes data onto the stack
  //IN: data
  //OUT: true/false
  
  bool pop (int& data);
  //pops data off of the stack
  //MODIFY: data
  //OUT: true/false

  bool isEmpty ();
  //returns a bool that indicates if the stack is empty.
  //OUT: true/false
  
  bool topIs (int& data);
  //looks at the data on the top of the stack
  //MODIFY: data
  //OUT: true/false

 private:
  bool resizeStack ();
  //changes the size of the stack array if necessary
  //MODIFY: stackArr
  //OUT: true/false
  int *stackArr;
  static const int DEFAULT = 10;
  int size;
  int top;
};

#endif
  

