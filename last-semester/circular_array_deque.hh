
#pragma once

#include "exceptions.hh"
#include "fixed_vector.hh"

template<typename ELEMENT>
class CircularArrayDeque {
public:
  CircularArrayDeque(int capacity) {
    _vector = new FixedVector<ELEMENT>(capacity);
    _size = 0;
    _front_index = 0;
  }

  ~CircularArrayDeque() {
    delete _vector;
  }

  int capacity() {
    return _vector->capacity();
  }

  int size() {
    return _size;
  }

  bool is_empty() {
    return (0 == _size);
  }

  ELEMENT front() throw(UnderflowException) {
    if (is_empty())
      throw UnderflowException();
    return _vector->get(_front_index);
  }

  ELEMENT back() throw(UnderflowException) {
    if (is_empty())
      throw UnderflowException();
    return _vector->get(back_index());
  }
    
  void add_front(ELEMENT e) throw(OverflowException) {
    if (is_full())
      throw OverflowException();

    _front_index = fix_index(_front_index - 1);
    _vector->set(_front_index, e);
    _size++;
  }

  void add_back(ELEMENT e) throw(OverflowException) {
    if (is_full())
      throw OverflowException();

    _vector->set(fix_index(back_index() + 1), e);
    _size++;
  }

  void remove_front() throw(UnderflowException) {
    if (is_empty())
      throw UnderflowException();

    _front_index = fix_index(_front_index + 1);
    _size--;
  }

  void remove_back() throw(UnderflowException) {
    if (is_empty())
      throw UnderflowException();

    _size--;
  }

private:
  FixedVector<ELEMENT> *_vector;
  int _size, _front_index;

  int fix_index(int index) {
    int fixed = index;

    if (fixed < 0) {
      fixed += capacity();
    } else if (fixed >= capacity()) {
      fixed -= capacity();
    }

    assert((fixed >= 0) && (fixed < capacity()));

    return fixed;
  }

  int back_index() {
    return fix_index(_front_index + _size - 1);
  }

  bool is_full() {
    return (_size == capacity());
  }
};
