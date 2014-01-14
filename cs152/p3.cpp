//Kaleb Loo
//p3.cpp
//CPSC 152
//2/27/13
//Purpose: This program tests the functionality of the Stack class and the
//         Queue class.  For the Stack class, this includes, creating the stack
//         pushing onto the stack, popping from the stack, resizing the stack,
//         and returning the top of the stack.  For the Queue class, this
//         includes, creating the queue, enqueing, dequeing, and returning
//         the front of the queue.  Also, the copy and overloaded assignment
//         operators for each class must be tested.
//Input: The user presses <Enter> periodically.
//Process: The program creates to instances for each class.  The program will
//         then add various data onto the stacks and queues.
//         It will then print the data to show correct functionality.
//         The program will then use equivalent statements
//         to test the copy constructor and the overloaded assignment operator.
//Output: The program will show the results of different test cases.

using namespace std;
#include <iostream>
#include "stack.h"
#include "queue.h"

const int  HEIGHT = 25;

void clearScreen ();
//Clears the screen of height 25

int main ()
{
  //Create two instances of each class
  Stack stack1, stack2(12);
  Queue queue1, queue2;
  //Create variable to read and write data
  int num;
  clearScreen();
  
  //Welcome Message
  cout << "Hello, this program will test all the features \n"
	   << "of stack.h and queue.h. \n";
  cout << "Press <Enter>";
  cin.get();
  clearScreen();
  
  //Test Ability to push 8 digits onto a stack of size 10
  cout << "Pushing 8 digits onto a stack of size 10. \n";
  for (int i = 0; i < 8; i++)
	if (stack1.push(i * i))
	  cout << i * i << " was successfully pushed onto stack1. \n";
	else
	  cout << "ERROR: Could not push onto stack1! \n";
  cout << "Press <Enter>";
  cin.get();
  cout << "\n";
  
  //Test Ability to push 14 digits onto a stack of size 12
  cout << "Pushing 14 digits onto a stack of size 12. \n";
  for (int i = 0; i < 14; i++)
	if (stack2.push(i + 4))
	  cout << i + 4 << " was successfully pushed onto stack2. \n";
	else
	  cout << "ERROR: Could not push onto stack2. \n";
  cout << "Press <Enter>";
  cin.get();
  clearScreen();

  //Test topIs function
  cout << "Testing the topIs function. \n";
  if (stack1.topIs(num))
	cout << "The top of stack1 is " << num << ". \n";
  else
	cout << "Stack1 is empty! \n";
  if (stack2.topIs(num))
	cout << "The top of stack2 is " << num << ". \n";
  else
	cout << "Stack2 is empty! \n";
  cout << "Press <Enter>";
  cin.get();
  clearScreen();
  
  //Test Copy Constructor
  cout << "Testing the copy constructor by loading \n"
	   << "stack2 into a new instance called stack3. \n";
  Stack stack3 = stack2;
  cout << "Press <Enter>";
  cin.get();
  cout << "\n";
  
  cout << "Pushing 4 numbers onto stack2. \n";
  for (int i = 0; i < 4; i++)
	if (stack2.push(i))
	  cout << i << " was successfully pushed onto stack2. \n";
	else
	  cout << "ERROR: could not push onto stack2! \n";
  cout << "Press <Enter>";
  cin.get();
  cout << "\n";
  
  cout << "Pushing 2 numbers onto stack3. \n";
  for (int i = 0; i < 2; i++)
	if (stack3.push(i + i))
	  cout << i + i << " was successfully pushed onto stack3. \n";
	else
	  cout << "ERROR: could not push onto stack3! \n";
  cout << "Press <Enter>";
  cin.get();
  cout << "\n";
  
  //Check popping function
  cout << "Popping everything from stack2. \n";
  while (stack2.pop(num))
	cout << num << " was successfully popped from stack2. \n";
  cout << "Stack2 is empty! \n";
  cout << "Press <Enter>";
  cin.get();
  cout << "\n";
  
  cout << "Popping everything from stack3. \n";
  while (stack3.pop(num))
	cout << num << " was successfully popped from stack3. \n";
  cout << "Stack3 is empty! \n";
  cout << "Press <Enter>";
  cin.get();
  clearScreen();
  
  //Test Overloaded Assignment Operator
  cout << "Testing Overloaded Assignment Operator by \n"
	   << "copying the stack1 into stack3. \n";
  stack3 = stack1;
  cout << "Press <Enter>";
  cin.get();
  cout << "\n";
  
  cout << "Pushing 4 digits onto stack1. \n";
  for (int i = 0; i < 4; i++)
	if (stack1.push(10 - i))
	  cout << 10 - i << " was successfully pushed onto stack1. \n";
	else
	  cout << "ERROR: could not push onto stack1! \n";
  cout << "Press <Enter>";
  cin.get();
  cout << "\n";
  
  cout << "Pushing 5 digits onto stack3. \n";
  for (int i = 0; i < 5; i++)
	if (stack3.push(4))
	  cout << 4 << " was successfully pushed onto stack3. \n";
	else
	  cout << "ERROR: could not push onto stack3! \n";
  cout << "Press <Enter>";
  cin.get();
  cout << "\n";
  
  //Check Popping
  cout << "Popping everything from stack1. \n";
  while (stack1.pop(num))
	cout << num << " was successfully popped from stack1. \n";
  cout << "Stack1 is empty! \n";
  cout << "Press <Enter>";
  cin.get();
  cout << "\n";
  
  cout << "Popping everything from stack3. \n";
  while (stack3.pop(num))
	cout << num << " was successfully popped from stack3. \n";
  cout << "Stack3 is empty! \n";
  cout << "Press <Enter>";
  cin.get();
  clearScreen();

  //Testing Queues
  //Test Ability to enqueue 8 digits onto a queue
  cout << "Enqueueing 8 digits to queue1. \n";
  for (int i = 0; i < 8; i++)
	if (queue1.enqueue(i * i))
	  cout << i * i << " was successfully enqueued to queue1. \n";
	else
	  cout << "ERROR: Could not enqueue to queue1! \n";
  cout << "Press <Enter>";
  cin.get();
  cout << "\n";
  
  //Test Ability to enqueue 14 digits to a queue
  cout << "Enqueueing 14 digits to queue2. \n";
  for (int i = 0; i < 14; i++)
	if (queue2.enqueue(i + 4))
	  cout << i + 4 << " was successfully enqueued to queue2. \n";
	else
	  cout << "ERROR: Could not enqueue to queue2. \n";
  cout << "Press <Enter>";
  cin.get();
  clearScreen();
  
  //Test frontIs function
  cout << "Testing the frontIs function. \n";
  if (queue1.frontIs(num))
	cout << "The front of queue1 is " << num << ". \n";
  else
	cout << "Queue1 is empty! \n";
  if (queue2.frontIs(num))
	cout << "The front of queue2 is " << num << ". \n";
  else
	cout << "Queue2 is empty! \n";
  cout << "Press <Enter>";
  cin.get();
  clearScreen();

  //Test Copy Constructor
  cout << "Testing the copy constructor by loading \n"
	   << "queue2 into a new instance called queue3. \n";
  Queue queue3 = queue2;
  cout << "Press <Enter>";
  cin.get();
  cout << "\n";

  cout << "Enqueueing 4 digits to queue2. \n";
  for (int i = 0; i < 4; i++)
	if (queue2.enqueue(i))
	  cout << i << " was successfully enqueued to queue2. \n";
	else
	  cout << "ERROR: could not enqueue to queue2! \n";
  cout << "Press <Enter>";
  cin.get();
  cout << "\n";
  
  cout << "Enqueueing 2 digits to queue3. \n";
  for (int i = 0; i < 2; i++)
	if (queue3.enqueue(i + i))
	  cout << i + i << " was successfully enqueued to queue3. \n";
	else
	  cout << "ERROR: could not enqueue to queue3! \n";
  cout << "Press <Enter>";
  cin.get();
  cout << "\n";
  
  //Check dequeuing function
  cout << "Dequeueing everything from stack2. \n";
  while (queue2.dequeue(num))
	cout << num << " was successfully dequeued from queue2. \n";
  cout << "Queue2 is empty! \n";
  cout << "Press <Enter>";
  cin.get();
  cout << "\n";
  
  cout << "Dequeuing everything from queue3. \n";
  while (queue3.dequeue(num))
	cout << num << " was successfully dequeued from queue3. \n";
  cout << "Queue3 is empty! \n";
  cout << "Press <Enter>";
  cin.get();
  clearScreen();
  
  //Test Overloaded Assignment Operator
  cout << "Testing Overloaded Assignment Operator by \n"
	   << "copying queue1 into queue3. \n";
  queue3 = queue1;
  cout << "Press <Enter>";
  cin.get();
  cout << "\n";

  cout << "Enqueueing 4 digits to queue1. \n";
  for (int i = 0; i < 4; i++)
	if (queue1.enqueue(10 - i))
	  cout << 10 - i << " was successfully enqueued to queue1. \n";
	else
	  cout << "ERROR: could not enqueue to queue1! \n";
  cout << "Press <Enter>";
  cin.get();
  cout << "\n";
  
  cout << "Enqueueing 5 digits to queue3. \n";
  for (int i = 0; i < 5; i++)
	if (queue3.enqueue(4))
	  cout << 4 << " was successfully enqueue to queue3. \n";
	else
	  cout << "ERROR: could not enqueue to queue3! \n";
  cout << "Press <Enter>";
  cin.get();
  cout << "\n";
  
  //Check Dequeueing
  cout << "Dequeueing everything from queue1. \n";
  while (queue1.dequeue(num))
	cout << num << " was successfully dequeued from queue1. \n";
  cout << "Queue1 is empty! \n";
  cout << "Press <Enter>";
  cin.get();
  cout << "\n";
  
  cout << "Dequeueing everything from queue3. \n";
  while (queue3.dequeue(num))
	cout << num << " was successfully dequeued from queue3. \n";
  cout << "Queue3 is empty! \n";
  cout << "Press <Enter>";
  cin.get();
  clearScreen();

  //Goodbye Message
  cout << "Testing is now complete! Goodbye. \n\n";
  return 0;
}

void clearScreen ()
{
  for (int i = 0; i < HEIGHT; i++)
	cout << "\n";
}
