
#include "singly_linked_list.hh"

#include <cassert>
#include <iostream>

using namespace std;

int main() {
  const int MILLION = 1000000;
  cout << "Creating linked list with 1 million elements...";
  SinglyLinkedList<int> list;
  assert(list.is_empty());
  for (int i = 1; i <= MILLION; i++) {
    list.add_front(i);
    assert(!list.is_empty());
  }
  assert(MILLION == list.length());

  // iteration
  bool iterated = false;
  int count = 0;
  for (SinglyLinkedListIterator<int> i(&list); !i.past_end(); i.advance()) {
    iterated = true;
    count++;
  }
  assert(iterated);
  assert(MILLION == count);
  
  cout << endl << "Clearing list...";
  list.clear();
  cout << endl;
  assert(0 == list.length());
  assert(list.is_empty());

  // iteration through empty list
  iterated = false;
  for (SinglyLinkedListIterator<int> i(&list); !i.past_end(); i.advance()) {
    iterated = true;
  }
  assert(!iterated);
  
  return 0;
}
