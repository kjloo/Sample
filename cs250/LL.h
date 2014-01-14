//Kaleb Loo
//LL.h
//CPSC 250
//4/8/13

using namespace std;

#ifndef LL_H
#define LL_H

struct ListNode
{
  int data;
  ListNode *next;
};

class LL
{
 public:
  LL();
  //constructor
  
  ~LL();
  //destructor

  void insertNode(int num);
  //inserts a node into the linked list in an ordered fashion
  //IN: num
  //MODIFY: head

  void deleteNode(int num);
  //deletes a node from a linked list
  //IN: num
  //MODIFY: head

  void printList();
  //walk through list

  ListNode* traverse(int num);
  //returns the address of the node before data location
  //IN: num

 private:
  LL(const LL& l);
  //copy constructor

  LL& operator=(const LL& rhs);
  //overloaded assignment operator
    
  ListNode *head;  
};

#endif
