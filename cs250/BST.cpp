//Kaleb Loo
//BST.cpp Version 2.0
//CPSC 250
//4/15/13

#include <iomanip>
#include <iostream>
#include "BST.h"

BST::BST()
{
  root = NULL;
}

BST::~BST()
{
}

bool BST::isEmpty()
{
  return (root == NULL);
}

void BST::insertNode(int num)
{
  if (!find(num)) {
	ListNode *tmp = new ListNode;
	ListNode *parent;
	tmp -> data = num;
	tmp -> right = NULL;
	tmp -> left = NULL;
	parent = NULL;
	
	if (isEmpty())
	  root = tmp;
	else {
	  ListNode *child = root;
	  while (child != NULL) {
		parent = child;
		if (num > child -> data)
		  child = child -> right;
		else
		  child = child -> left;
	  }
	  if (num < parent -> data)
		parent -> left = tmp;
	  else
		parent -> right = tmp;
	}
  }
}

bool BST::find(int num)
{
  ListNode *traverseP = root;
  while (traverseP != NULL && traverseP -> data != num) {
	if (traverseP -> data < num)
	  traverseP = traverseP -> right;
	else
	  traverseP = traverseP -> left;
  }
  return (traverseP != NULL);
}

void BST::printList()
{
  inOrder(root);
}

void BST::inOrder(ListNode *r)
{
  if (r != NULL) {
	inOrder(r -> left);
	print(r -> data);
	inOrder(r -> right);
  }
  return;
}

void BST::print(int num)
{
  cout << num << "\n";
}
