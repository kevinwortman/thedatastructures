
#pragma once

#include <cassert>

#include "doubly_linked_list.hh"
#include "fixed_vector.hh"

template <typename ELEMENT>
class CircularArrayDeque {
private:
  FixedVector<ELEMENT> *_vector;
  int _front,   // index of the front element
      _trailer, // index of the position immediately after the last element
      _size;    // number of elements in the queue

  int circular_index(int index_that_may_be_out_of_bounds) {
    return (index_that_may_be_out_of_bounds + _vector->length()) % _vector->length();
  }
  
public:
  
  CircularArrayDeque(int capacity) {
    assert(capacity > 0);
    _vector = new FixedVector<ELEMENT>(capacity, ELEMENT());
    _front = 0;
    _trailer = 0;
    _size = 0;
  }

  ~CircularArrayDeque() { delete _vector; }

  int size() { return _size; }
  int capacity() { return _vector->length(); }
  bool is_empty() { return (0 == _size); }
  bool is_full() { return (_size == capacity()); }

  ELEMENT front() {
    assert(!is_empty());
    return _vector->get(_front);
  }

  ELEMENT back() {
    assert(!is_empty());
    return _vector->get(circular_index(_trailer - 1));
  }

  void add_front(ELEMENT e) {
    assert(!is_full());
    _front = circular_index(_front - 1);
    _vector->set(_front, e);
    _size++;
  }

  void add_back(ELEMENT e) {
    assert(!is_full());
    _vector->set(_trailer, e);
    _trailer = circular_index(_trailer + 1);
    _size++;
  }

  void remove_front() {
    assert(!is_empty());
    _front = circular_index(_front + 1);
    _size--;
  }

  void remove_back() {
    assert(!is_empty());
    _trailer = circular_index(_trailer - 1);
    _size--;
  }
};

template <typename ELEMENT>
class LinkedDeque {
 private:
  // This is a very simple wrapper around DoublyLinkedList.
  DoublyLinkedList<ELEMENT> *_list;

public:

  LinkedDeque() { _list = new DoublyLinkedList<ELEMENT>(); }

  ~LinkedDeque() { delete _list; }

  int size() { return _list->length(); }
  bool is_empty() { return (0 == size()); }

  ELEMENT front() {
    assert(!is_empty());
    return _list->front();
  }

  ELEMENT back() {
    assert(!is_empty());
    return _list->back();
  }

  void add_front(ELEMENT e) { _list->add_front(e); }

  void add_back(ELEMENT e) { _list->add_back(e); }

  void remove_front() {
    assert(!is_empty());
    _list->remove_front();
  }

  void remove_back() {
    assert(!is_empty());
    _list->remove_back();
  }
};
