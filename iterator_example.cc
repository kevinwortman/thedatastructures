
#include <iostream>

#include "dynamic_vector_with_iterator.hh"
#include "singly_linked_list_with_iterator.hh"

using namespace std;

int main() {

  const int N = 10;

  cout << "Generating the first " << N << " perfect squares...";
  DynamicVector<int> squares;
  for (int i = 0; i < N; i++)
    squares.add_back(i * i);
  cout << "done" << endl;

  cout << "They are:" << endl;
  for (DynamicVectorIterator<int> i = squares.begin(); !i.past_end(); i.next())
    cout << "    " << i.get() << endl;

  cout << "Copying to singly linked list...";
  SinglyLinkedList<int> list;
  for (DynamicVectorIterator<int> i = squares.begin(); !i.past_end(); i.next())
    list.add_front(i.get());
  cout << "done" << endl;

  cout << "Contents of the list:" << endl;
  for (SinglyLinkedListIterator<int> i = list.begin(); !i.past_end(); i.next())
    cout << i.get() << endl;
  
  return 0;
}
