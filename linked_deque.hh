
#pragma once

#include "exceptions.hh"
#include "doubly_linked_list.hh"

template <typename ELEMENT>
class LinkedDeque {
public:
  LinkedDeque() {
    _size = 0;
  }

  int size() {
    return _size;
  }

  bool is_empty() {
    return (0 == _size);
  }

  ELEMENT front() throw(UnderflowException) {
    return _list.front();
  }

  ELEMENT back() throw(UnderflowException) {
    return _list.back();
  }

  void add_front(ELEMENT e) {
    _list.add_front(e);
    _size++;
  }

  void add_back(ELEMENT e) {
    _list.add_back(e);
    _size++;
  }

  void remove_front() throw(UnderflowException) {
    _list.remove_front();
    _size--;
  }

  void remove_back() throw(UnderflowException) {
    _list.remove_back();
    _size--;
  }

private:
  DoublyLinkedList<ELEMENT> _list;
  int _size;
};
