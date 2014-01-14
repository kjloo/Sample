//Kaleb Loo
//BST.h Version 2.0
//CPSC 250
//4/15/13

using namespace std;

#ifndef BST_H
#define BST_H

class BST
{
 public:
  BST();
  //constructor
  
  ~BST();
  //destructor

  bool isEmpty();
  //returns a true if the list is empty and a false otherwise
  //OUT: true/false
  
  void insertNode(int num);
  //inserts data in order into the binary search tree
  //IN: num
  //MODIFY: root

  bool find(int num);
  //returns true if the data is found and a false otherwise
  //IN: num
  //OUT: true/false
  
  void printList();
  //prints the entire binary tree in order
  
 private:
  struct ListNode
  {
	int data;
	ListNode *right;
	ListNode *left;
  };
  
  BST(const BST& t);
  //copy constructor

  BST& operator=(const BST& rhs);
  //overloaded assignment operator
  
  void inOrder(ListNode *r);
  //recursively goes through all elements in the binary search tree
  //IN: root

  void print(int num);
  //prints data
  //IN: num

  ListNode *root;
};

#endif
