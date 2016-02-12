
#pragma once

#include <cassert>

template <typename ELT>
class FixedVector {
private:
  int _length;
  ELT *_array;

public:
  // length copies of default_value
  FixedVector(int length, ELT default_value) {
    assert(length >= 0);
    _length = length;
    _array = new ELT[length];
    for (int i = 0; i < length; ++i) {
      _array[i] = default_value;
    }
  }

  // empty vector
  FixedVector() {
    _length = 0;
    _array = new ELT[0];
  }

  ~FixedVector() { delete [] _array; }

  int length() { return _length; }

  bool is_empty() { return (_length == 0); }
  
  ELT get(int index) {
    assert(!is_empty());
    assert((index >= 0) && (index < _length));
    return _array[index];
  }

  void set(int index, ELT value) {
    assert(!is_empty());
    assert((index >= 0) && (index < _length));
    _array[index] = value;
  }
};

template <typename ELT>
class FixedVectorIterator {
private:
  FixedVector<ELT> *_vector;
  int _index;
  
public:
  FixedVectorIterator(FixedVector<ELT>* vector) {
    assert(vector != nullptr);
    _vector = vector;
    _index = 0;
  }

  bool past_end() {
    return (_index == _vector->length());
  }
  
  ELT get() {
    assert(!past_end());
    return _vector->get(_index);
  }

  void advance() {
    assert(!past_end());
    _index++;
  }
};    
