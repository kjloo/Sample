//Test File

using namespace std;

#include <iostream>
#include <iomanip>

int main ()
{
  int a = 10;
  int *b;
  b = &a;
  int *c = b;
  *c = 5;
  cout << a << "\n";
}
