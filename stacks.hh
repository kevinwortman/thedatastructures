
#pragma once

#include <cassert>

#include "fixed_vector.hh"
#include "singly_linked_list.hh"

template<typename ELT>
class LinkedStack {
private:
  SinglyLinkedList<ELT> _elements;

public:
  LinkedStack() { }

  int size() { return _elements.length(); }
  bool is_empty() { return _elements.is_empty(); }

  ELT peek() {
    assert(!is_empty());
    return _elements.front();
  }

  void push(ELT e) { _elements.add_front(e); }
  
  void pop() {
    assert(!is_empty());
    _elements.remove_front();
  }
};

template<typename ELT>
class FixedStack {
private:
  FixedVector<ELT>* _elements;
  int _size;

public:
  FixedStack(int capacity) {
    assert(capacity > 0);
    _elements = new FixedVector<ELT>(capacity, ELT());
    _size = 0;
  }

  ~FixedStack() { delete _elements; }

  int size() { return _size; }
  bool is_empty() { return (0 == _size); }
  
  ELT peek() {
    assert(!is_empty());
    return _elements->get(_size - 1);
  }

  void push(ELT e) {
    assert(_size < _elements->length());
    _elements->set(_size, e);
    _size++;
  }

  void pop() {
    assert(!is_empty());
    _size--;
  }
};
