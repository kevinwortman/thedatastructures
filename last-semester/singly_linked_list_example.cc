
#include "singly_linked_list.hh"

#include <cassert>
#include <iostream>

using namespace std;

int main() {
  const int MILLION = 1000000;
  cout << "Creating linked list with 1 million elements...";
  SinglyLinkedList<int> list;
  for (int i = 1; i <= MILLION; i++)
    list.add_front(i);

  cout << endl << "Clearing list...";
  list.clear();
  cout << endl;

  assert(list.is_empty());
  
  return 0;
}
