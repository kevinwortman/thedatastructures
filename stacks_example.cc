
/* output:

pushing onto a linked stack: 1 2 3 4 5 6 7 8 9 10
transferring to a fixed stack: 10 9 8 7 6 5 4 3 2 1
popping fixed stack: 1 2 3 4 5 6 7 8 9 10

 */

#include <iostream>

#include "stacks.hh"

using namespace std;

int main() {
  const int COUNT = 10;

  LinkedStack<int> linked;
  cout << "pushing onto a linked stack:";
  for (int i = 1; i <= COUNT; ++i) {
    cout << " " << i;
    linked.push(i);
  }
  cout << endl;

  FixedStack<int> fixed(COUNT);
  cout << "transferring to a fixed stack:";
  while (!linked.is_empty()) {
    int e = linked.peek();
    cout << " " << e;
    linked.pop();
    fixed.push(e);
  }
  cout << endl;

  cout << "popping fixed stack:";
  while (!fixed.is_empty()) {
    cout << " " << fixed.peek();
    fixed.pop();
  }
  cout << endl;
    
  return 0;
}
