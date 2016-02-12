
#include "doubly_linked_list.hh"

#include <cassert>
#include <iostream>

using namespace std;

int main() {
  const int MILLION = 1000000, TWO_MILLION = (2 * MILLION);
  cout << "Creating doubly linked list with 2 million elements...";
  DoublyLinkedList<int> list;
  for (int i = 1; i <= MILLION; i++) {
    list.add_front(i);
    list.add_back(i);
  }
  assert(TWO_MILLION == list.length());

  cout << endl << "Iterator...";
  int count = 0;
  for (DoublyLinkedListIterator<int> i(&list); !i.past_end(); i.advance()) {
    count++;
  }
  assert(TWO_MILLION == count);
  
  cout << endl << "Clearing list...";
  list.clear();
  assert(list.is_empty());
  assert(0 == list.length());

  cout << endl << "Empty iterator...";
  count = 0;
  for (DoublyLinkedListIterator<int> i(&list); !i.past_end(); i.advance()) {
    count++;
  }
  assert(0 == count);

  cout << endl;
  
  return 0;
}
