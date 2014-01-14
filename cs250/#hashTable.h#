//Kaleb Loo
//hashTable.h Version 1.0
//CPSC 250
//5/21/13
//Provides the functionality of a Hash Table.  This includes constructing the
//Hash Table, deleting the Hash Table, inserting into the Hash Table, and
//finding if an element is in the Hash Table.
//The hashing function, and collision handling are private functions used by
//the insert function. The collsion handling is done by chaining.
//There is also functionality to print the hash table to the screen and to
//output a certain amount of data ordered in non-ascending order
//by frequency to a file.
//The copy constructor and the overloaded assignment operator are
//suppressed.

using namespace std;

#include <string>
#include <iomanip>
#include <iostream>
#include <fstream>

#ifndef HASHTABLE_H
#define HASHTABLE_H

class hashTable
{
 public:  
  hashTable(unsigned s = 650);
  //constructor
  //Assuming longest word/phrase length of 25 composed of the largest
  //letter value 25, the maximum key value that the
  //hash function will produce is 25 * 25 + 25 = 650  
  
  ~hashTable();
  //destructor

  void insert(string word);
  //Attempts to insert a word into the hash table
  //IN: word

  bool find(string word);
  //Attempts to find a word in the hash table
  //returns a true if the word is found and a false otherwise
  //IN: word
  //OUT: true/false

  void print();
  //Prints out words in the table

  void outputData(ofstream& outFile, int listSize);
  //Outputs data to a file by storing all valid data in an array
  //and then sorting the data by frequency using selection sort.
  //The amount of data outputted is determined by listSize.
  //IN: listSize
  //MODIFY: outFile
  
 private:
  struct ListNode
  {
	string data;
	int freq;
	ListNode *next;
  };
  
  hashTable(const hashTable& h);
  //copy constructor

  hashTable& operator=(const hashTable& rhs);
  //overloaded assignment operator

  int hashKey(string word);
  //Uses the hash function to change word into index of hash table
  //Hashes by adding up the ASCII values of each letter and then adding the
  //length of the word
  //IN: word
  //OUT: num

  bool insertElem(string word, ListNode* entryNode);
  //Attempts to insert a word into the hash table given a word and position
  //returns a true upon a success and a false otherwise
  //Increments frequency if the word is already in the hash table
  //Increments count of total unique elements in the hash table when
  //inserting a new word.
  //IN: word, entryNode
  //OUT: true/false

  bool isEmpty(ListNode* elem);
  //Returns a true if there is an open spot in the hash table and
  //returns a false otherwise
  //IN: elem
  //OUT: true/false
  
  void collisionFix(ListNode*& position);
  //Resolves collisions using chaining
  //MODIFY: position

  bool format(string& word);
  //Reformats the input word by removing punctuations and setting all
  //letters to lower case
  //Returns a false if there was no word to retrieve and returns a true
  //if it retrieved a word
  //MODIFY: word
  //OUT:true/false
  
  bool filter(string word);
  //Returns a true if word is on a common word and returns a false otherwise
  //IN: word

  void sort(ListNode*& list);
  //Sorts the list of words in non-ascending order by frequency
  //MODIFY: list

  void swap(ListNode& elemA, ListNode& elemB);
  //Swaps the values of elemA and elemB
  //MODIFY: elemA, elemB
  
  ListNode *array;
  int size; //used to keep track of the size of the hash table
  int count; //used to keep track of total unique elements in the hash table
};
#endif
