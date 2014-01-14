//Kaleb Loo
//parityBST.h Version 2.0
//CPSC 250
//4/22/13
//Provides the functionality of a Binary Search Tree. This includes
//constructing the BST, deleting the BST, inserting into the BST,
//checking if the BST is empty, removing
//from the BST, searching through the BST, and traversing the BST.
//Traversals include inorder, preorder, and postorder. The inorder and preorder
//traversals are done non-recursively, while the postorder traversal is
//done recursively. Each individual instance of a Parity Binary Search Tree
//will only store non-repetative values of either even or odd numbers,
//which is decided by the application programmer on instantiation.
//The copy constructor and overloaded assignment operator are suppressed.
//This class uses the STL stack.

using namespace std;

#include <stack>
#include <fstream>

#ifndef PARITYBST_H
#define PARITYBST_H

class parityBST
{
 public:
  parityBST(bool data = true);
  //constructor
  //DEFAULT: stores only odd numbers
  //IN: data - if data is true, then the binary search tree is set to store
  //           only odd numbers, if data is false, then the binary search
  //           tree is set to only store even numbers.
  
  ~parityBST();
  //destructor

  bool isEmpty();
  //returns a true if the list is empty and a false otherwise
  //OUT: true/false
  
  void insertNode(int num);
  //inserts data in order into the binary search tree
  //IN: num
  //MODIFY: root
  //Post-Condition: binary search tree will be not empty.

  bool find(int num);
  //returns true if the data is found and a false otherwise
  //IN: num
  //OUT: true/false

  void removeNode(int num);
  //removes data from the binary search tree
  //IN: num
  //MODIFY: root
  //Post-Condition: binary search tree may become empty.
  
  void outputList(ofstream& outFile);
  //outputs the entire binary tree in order to a file
  //MODIFY: outFile
  
 private:
  struct ListNode
  {
	int data;
	ListNode *right;
	ListNode *left;
  };
  
  parityBST(const parityBST& t);
  //copy constructor

  parityBST& operator=(const parityBST& rhs);
  //overloaded assignment operator
  
  void inOrder(ofstream& outFile);
  //iteratively goes through all elements in the binary search tree inorder
  //MODIFY: outFile
  
  void preOrder();
  //interatively goes through all elements in the binary search tree preorder

  void postOrderRemove(ListNode *r);
  //recursively goes through all elements in post order fashion and
  //deletes the node.
  //IN: root

  bool filter(int num);
  //returns a true if the BST is an odd tree and the data is odd or if
  //the BST is an even tree and the data is even and returns false otherwise.
  //IN: num
  //OUT: true/false

  ListNode *root;
  bool type;
  //if set to true, BST tree is set to store only odd numbers
  //if set to false, BST tree is set to store only even numbers
};

#endif
