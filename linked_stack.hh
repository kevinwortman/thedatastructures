
#pragma once

#include "exceptions.hh"
#include "singly_linked_list.hh"

template<typename ELEMENT>
class LinkedStack {
public:
  LinkedStack() {
    _size = 0;
  }

  ~LinkedStack() {
  }

  int size() {
    return _size;
  }

  bool is_empty() {
    return (0 == _size);
  }

  ELEMENT peek() throw(UnderflowException) {
    if (is_empty())
      throw UnderflowException();
    return _elements.front();
  }

  void push(ELEMENT e) {
    _elements.add_front(e);
    _size++;
  }

  void pop() throw(UnderflowException) {
    if (is_empty())
      throw UnderflowException();
    _elements.remove_front();
    _size--;
  }

private:
  SinglyLinkedList<ELEMENT> _elements;
  int _size;
};
