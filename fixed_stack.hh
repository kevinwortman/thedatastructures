
#pragma once

#include "exceptions.hh"
#include "fixed_vector.hh"

template <typename ELEMENT>
class FixedStack {
public:
  FixedStack(int capacity) throw(ArgumentException) {
    _elements = new FixedVector<ELEMENT>(capacity);
    _size = 0;
  }

  ~FixedStack() {
    delete _elements;
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
    return _elements->get(_size - 1);
  }

  void push(ELEMENT e) throw(OverflowException) {
    if (_size == _elements->capacity())
      throw OverflowException();
    _elements->set(_size, e);
    _size++;
  }

  void pop() throw(UnderflowException) {
    if (is_empty())
      throw UnderflowException();
    _size--;
  }

private:
  FixedVector<ELEMENT> *_elements;
  int _size;
};
