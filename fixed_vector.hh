
#pragma once

#include "exceptions.hh"

template <typename ELEMENT>
class FixedVector {
public:
  FixedVector(int capacity) throw(ArgumentException) {
    if (capacity <= 0)
      throw ArgumentException("capacity must be positive");

    _capacity = capacity;
    _array = new ELEMENT[_capacity];
  }

  ~FixedVector() {
    delete [] _array;
  }

  int capacity() {
    return _capacity;
  }

  ELEMENT get(int index) {
    check_index(index);
    return _array[index];
  }

  void set(int index, ELEMENT value) {
    check_index(index);
    _array[index] = value;
  }

private:
  int _capacity;
  ELEMENT* _array;

  void check_index(int i) {
    if ((i < 0) || (i >= _capacity))
      throw IndexException(_capacity, i);
  }
};
