
#pragma once

#include <algorithm> // for max()
#include <cassert>

template <typename ELEMENT>
class DynamicVector {
private:
  
  int _length, // current length
    _capacity; // length of allocated array

  // When _capacity > 0, this points to a heap-allocated array.
  // When _capacity == 0, this is uninitialized.
  ELEMENT* _elements;

public:
  
  DynamicVector() {
    _length = 0;
    _capacity = 0;
  }

  ~DynamicVector() { delete_elements(); }

  void clear() {
    delete_elements();
    _length = 0;
    _capacity = 0;
  }

  int length() { return _length; }
  bool is_empty() { return (0 == _length); }

  bool is_index(int i) { return ((i >= 0) && (i < _length)); }
  
  ELEMENT get(int index) {
    assert(is_index(index));
    return _elements[index];
  }

  void set(int index, ELEMENT e) {
    assert(is_index(index));
    _elements[index] = e;
  }
  
  void add_back(ELEMENT e) {
    if (_length == _capacity) {
      extend();
    }
    _elements[_length] = e;
    _length++;
  }

private:

  // Free _elements, if necessary.
  void delete_elements() {
    if (_capacity > 0) {
      delete _elements;
    }
  }
  
  void extend() {
    assert(_length == _capacity);
    int new_capacity = std::max(1, _capacity * 2);
    assert((new_capacity > 0) && (new_capacity > _capacity));
    ELEMENT* new_elements = new ELEMENT[new_capacity];
    for (int i = 0; i < _length; ++i) {
      new_elements[i] = _elements[i];
    }
    delete_elements();
    _capacity = new_capacity;
    _elements = new_elements;
  }
};

template <typename ELEMENT>
class DynamicVectorIterator {
private:
  DynamicVector<ELEMENT> *_vector;
  int _index;

public:
  DynamicVectorIterator(DynamicVector<ELEMENT>* vector) {
    _vector = vector;
    _index = 0;
  }

  bool past_end() { return (_vector->length() == _index); }

  ELEMENT get() {
    assert(!past_end());
    return _vector->get(_index);
  }

  void advance() {
    assert(!past_end());
    _index++;
  }
};
