using namespace std;
#include <iostream>
#include "quasiUniqueQ.h"

int main()
{
  quasiUniqueQ a;
  quasiUniqueQ b;
  a.enqueue(3);
  a.enqueue(6);
  a.enqueue(4);
  a.enqueue(1);
  b = a;
  quasiUniqueQ c = a;
  a.enqueue(2);
  b.enqueue(1);
  c.enqueue(3);
  while (!a.isEmpty())
	cout << a.dequeue() << "\n";
  while (!b.isEmpty())
	cout << b.dequeue() << "\n";
  while (!c.isEmpty())
	cout << c.dequeue() << "\n";
}
