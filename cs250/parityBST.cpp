//Kaleb Loo
//parityBST.cpp Version 2.0
//CPSC 250
//4/22/13
//Implementation of the parityBST.h header file.
//NOTE: preorder traversal is unused since it did not have a purpose in
//this programming assignment

#include <iomanip>
#include "parityBST.h"

parityBST::parityBST(bool data)
{
  root = NULL;
  type = data;
}

parityBST::~parityBST()
{
  postOrderRemove(root);
}

bool parityBST::isEmpty()
{
  return (root == NULL);
}

void parityBST::insertNode(int num)
{
  if (filter(num)) {
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
}

bool parityBST::find(int num)
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

void parityBST::removeNode(int num)
{
  if (find(num)) {
	ListNode *child;
	ListNode *parent;
	child = root;
	//Find node prior
	while (child != NULL && child -> data != num) {
	  parent = child;
	  if (child -> data < num)
		child = child -> right;
	  else
		child = child -> left;
	}
	//Removing leaf node
	if (child -> left == NULL && child -> right == NULL) {
	  if (parent -> left == child)
		parent -> left = NULL;
	  else
		parent -> right = NULL;
	  delete child;
	}else if (child -> right == NULL && child -> left != NULL ||
			  child -> left == NULL && child -> right != NULL) {
	  //Removing node with one child
	  if (parent -> left == child) {
		if (child -> left != NULL) {
		  parent -> left = child -> left;
		  delete child;
		}else {
		  parent -> left = child -> right;
		  delete child;
		}
	  }else {
		if (child -> left != NULL) {
		  parent -> right = child -> left;
		  delete child;
		}else {
		  parent -> right = child -> right;
		  delete child;
		}
	  }
	}else {
	  //Removing node with two children
	  //Move to left subtree
	  ListNode *leftMaxChild = child -> left;
	  ListNode *leftMaxParent = child -> left;
	  //Find inorder Predecessor
	  while (leftMaxChild -> right != NULL) {
		leftMaxParent = leftMaxChild;
		leftMaxChild = leftMaxChild -> right;
	  }
	  if (leftMaxChild == leftMaxParent) {
		child -> data = leftMaxChild -> data;
		child -> left = leftMaxChild -> left;
	  }else {
		leftMaxParent -> right = leftMaxChild -> left;
		child -> data = leftMaxChild -> data;
	  }
	  delete leftMaxChild;
	}
  }
}

void parityBST::outputList(ofstream& outFile)
{
  inOrder(outFile);
}

void parityBST::inOrder(ofstream& outFile)
{
  ListNode *current = root;
  stack <ListNode*> s;
  while (current != NULL || !s.empty()) {
	if (current != NULL) {
	  s.push(current);
	  current = current -> left;
	}else {
	  current = s.top();
	  s.pop();
	  outFile << current -> data << "\n";
	  current = current -> right;
	}
  }
}

void parityBST::preOrder()
{
  ListNode *current = root;
  stack <ListNode*> s;
  while (current != NULL || !s.empty()) {
	while (current  != NULL) {
	  //EXAMINE DATA would occur here but we didn't have a purpose
	  //for this traversal in the assignment
	  //print(current -> data);
	  s.push(current);
	  current = current -> left;
	}
	current = s.top();
	s.pop();
	current = current -> right;
  }
}


void parityBST::postOrderRemove(ListNode *r)
{
  if (r != NULL) {
	postOrderRemove(r -> left);
	postOrderRemove(r -> right);
	delete r;
  }
  return;
}

bool parityBST::filter(int num)
{
  return (type && num % 2 != 0 || !type && num % 2 == 0);
}
