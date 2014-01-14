//Kaleb Loo
//sPS.h Version 1.0
//CPSC 250
//4/4/13
//Provide the functionality of a selective prime stack including creating a
//stack, selectively pushing onto the stack, popping from the stack, checking
//if the stack is empty, and resizing the stack.

using namespace std;

#ifndef SPS_H
#define SPS_H

class sPS
{
 public:
  sPS();
  //default constructor

  sPS(unsigned int s);
  //constructor

  sPS(const sPS& s);
  //copy constructor

  sPS& operator=(const sPS& rhs);
  //overloaded assignment operator

  ~sPS();
  //destructor

  void push(int data);
  //pushes data onto the stack
  //IN: data

  int pop();
  //pops data off of the stack
  //OUT: data

  bool isEmpty();
  //returns a true if the stack is empty and a false otherwise
  //OUT: true/false

 private:
  void copyStack(int smallSize, int largeSize, int *stackArray);
  //copies a stack to another instance of a stack
  //IN: smallSize, largeSize, stackArray
  //MODIFY: array
  
  void resizeStack();
  //changes the size of the stack when stack is full
  //MODIFY: size, array
  
  bool filter(int data);
  //filters out data according to certain parameters
  //FILTER: returns a true if the data is a prime and 1 less than a multiple
  //of 3 and reutrns a false otherwise.
  //IN: data
  //OUT: true/false

  bool isPrime(int num);
  //returns a true if a number is prime and a false otherwise
  //IN: num
  //OUT: true/false
  
  int *array;
  static const int DEFAULT = 10;
  int size;
  int top;
};

#endif
