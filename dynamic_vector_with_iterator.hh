
#pragma once

#include <cassert>

#include "exceptions.hh"
#include "fixed_vector.hh"

// Forward declaration, so that DynamicVectorIterator can refer to
// DynamicVector without creating compile errors.
template <typename ELEMENT> class DynamicVector;

template <typename ELEMENT>
class DynamicVectorIterator {
public:
  // These functions cannot be defined inline, because they refer to
  // DynamicVector's data members, and those haven't been declared
  // yet.

  DynamicVectorIterator(DynamicVector<ELEMENT>* vector);
  void next() throw(IteratorException);
  bool past_end();
  ELEMENT get() throw(IteratorException);

private:
  DynamicVector<ELEMENT> *_vector;
  int _index;
};
  
template <typename ELEMENT>
class DynamicVector {
  // This statement gives DynamicVectorIterator access to
  // DynamicVector's private members.
  friend class DynamicVectorIterator<ELEMENT>;
public:
  // New function: return an iterator located at the first element in
  // the vector

  DynamicVectorIterator<ELEMENT> begin() {
    return DynamicVectorIterator<ELEMENT>(this);
  }
  
  // The rest of the DynamicVector class is unchanged.
  
  DynamicVector() {
    // start out empty with capacity 1
    _size = 0;
    _storage = new FixedVector<ELEMENT>(1);
  }

  ~DynamicVector() {
    delete _storage;
  }

  int size() {
    return _size;
  }

  bool is_empty() {
    return (0 == _size);
  }

  ELEMENT get(int index) throw(IndexException) {
    check_index(index);
    return _storage->get(index);
  }

  void set(int index, ELEMENT e) throw(IndexException) {
    check_index(index);
    _storage->set(index, e);
  }

  void add_back(ELEMENT e) {
    // n < c
    assert(_size < current_capacity());

    _storage->set(_size, e);
    _size++;

    maintain();
  }

  void remove_back() throw(UnderflowException) {
    if (is_empty())
      throw UnderflowException();

    _size--;

    maintain();
  }

  void clear() {
    _size = 0;
    maintain();
    assert(1 == current_capacity());
  }

private:
  FixedVector<ELEMENT> *_storage;
  int _size;

  void check_index(int index) throw(IndexException) {
    if ((index < 0) || (index >= _size))
      throw IndexException(index, _size);
  }

  int current_capacity() {
    return _storage->capacity();
  }

  // Guarantee that capacity invariants are met, by resizing only when necessary.
  void maintain() {
    int c = current_capacity();
    if (_size == c) {
      // grow to double current capacity
      resize(c * 2);
    } else if (_size == 0) {
      // shrink to capacity 1
      resize(1);
    } else if (3*_size < c) {
      // shrink to half current capacity
      resize(c / 2);
    } else {
      // no maintenance required
    }
  }
    
  void resize(int new_capacity) {
    assert(new_capacity > 0);
    assert(new_capacity >= _size);

    // allocate new fixed vector
    FixedVector<ELEMENT> *new_storage = new FixedVector<ELEMENT>(new_capacity);

    // copy elements over to new vector
    for (int i = 0; i < _size; ++i)
      new_storage->set(i, _storage->get(i));

    // free old vector, start using new vector
    delete _storage;
    _storage = new_storage;
  }

};

template <typename ELEMENT>
DynamicVectorIterator<ELEMENT>::DynamicVectorIterator(DynamicVector<ELEMENT> *vector) {
  _vector = vector;
  _index = 0;
}

template <typename ELEMENT>
void DynamicVectorIterator<ELEMENT>::next() throw(IteratorException) {
  if (past_end()) {
    // already at the end, can't go farther
    throw IteratorException();
  }
  
  _index++;
}

template <typename ELEMENT>
bool DynamicVectorIterator<ELEMENT>::past_end() {
  return (_index == _vector->_size);
}

template <typename ELEMENT>
ELEMENT DynamicVectorIterator<ELEMENT>::get() throw(IteratorException) {
  if (past_end())
    throw IteratorException();
  
  return _vector->get(_index);
}
