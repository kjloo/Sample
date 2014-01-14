//STL Functions reverse, reverse_copy,
//    rotate, and rotate_copy

#include <iostream>
#include <algorithm>
#include <iterator>
#include <list>

using namespace std;

int main()
{
  int temp[10] = {1, 3, 5, 7, 9, 0, 2, 4, 6, 8};//Line 1

  list<int> intList(temp, temp + 10);//Line 2
  list<int> resultList;
  list<int>::iterator listItr;//Line 4

  ostream_iterator<int> screen(cout, " ");//Line 5

  cout << "Line 6: intList: ";//Line 6
  copy(intList.begin(), intList.end(), screen);//Line 7
  cout << endl;//Line 8

  //reverse
  reverse(intList.begin(), intList.end());//Line 9

  cout << "Line 10: intList after reversal: ";//Line 10
  copy(intList.begin(), intList.end(), screen);//Line 11
  cout << endl;//Line 12

  //reverse_copy
  reverse_copy(intList.begin(), intList.end(),
			   back_inserter(resultList));//Line 13

  cout << "Line 14: resultList: ";//Line 14
  copy(resultList.begin(), resultList.end(), screen);//Line 15
  cout << endl;//Line 16

  listItr = intList.begin();//Line 17
  listItr++;//Line 18
  listItr++;//Line 19
  listItr++;

  cout << "Line 20: intList before rotating: ";//Line 20
  copy(intList.begin(), intList.end(), screen);//Line 21
  cout << endl;//Line 22

  //rotate
  rotate(intList.begin(), listItr, intList.end());//Line 23

  cout << "Line 24: intList after rotating: ";//Line 24
  copy(intList.begin(), intList.end(), screen);//Line 25
  cout << endl;//Line 26

  //rotate_copy
  resultList.clear();//Line 27
  listItr = intList.begin();
  listItr++;
  listItr++;
  rotate_copy(intList.begin(), listItr, intList.end(),
			  back_inserter(resultList));//Line 28

  cout << "Line 29: intList after rotating and "
	   << "copying: ";//Line 29
  copy(intList.begin(), intList.end(), screen);//Line 30
  cout << endl;//Line 31

  cout << "Line 32: resultList after rotating and "
	   << "copying: ";//Line 32
  copy(resultList.begin(), resultList.end(), screen);//Line 33
  cout << endl;//Line 34

  resultList.clear();//Line 35

  rotate_copy(intList.begin(),
			  find(intList.begin(), intList.end(), 6),
			  intList.end(),
			  back_inserter(resultList));//Line 36

  cout << "Line 37: resultList after rotating and "
	   << "copying: ";//Line 37
  copy(resultList.begin(), resultList.end(), screen);//Line 38
  cout << endl;//Line 39

  //rotate back
  listItr = intList.end();//Line 40
  listItr--;
  listItr--;
  listItr--;

  cout << "Line 41: intList after rotating back: ";//Line 41
  rotate(intList.begin(), listItr, intList.end());//Line 42
  copy(intList.begin(), intList.end(), screen);//Line 43
  cout << endl;//Line 44

  //reverse back
  reverse(intList.begin(), intList.end());//Line 45
  cout << "Line 46: intList after reversal; ";//Line 46
  copy(intList.begin(), intList.end(), screen);//Line 47
  cout << endl;//Line 48

  //direct copy
  resultList.clear();//Line 49
  copy(intList.begin(), intList.end(), back_inserter(resultList));//Line 50
  cout << "Line 51: resultList after copy: ";//Line 51
  copy(resultList.begin(), resultList.end(), screen);//Line 52
  cout << endl;//Line 53
  
  return 0;
}
