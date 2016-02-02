
#pragma once

#include <cstddef>

#include "exceptions.hh"

template <typename ELEMENT>
class DoublyLinkedNode {
public:
  DoublyLinkedNode(DoublyLinkedNode<ELEMENT>* prev, ELEMENT element, DoublyLinkedNode<ELEMENT>* next) {
    _prev = prev;
    _element = element;
    _next = next;
  }

  DoublyLinkedNode<ELEMENT>* prev() {
    return _prev;
  }
  
  ELEMENT element() {
    return _element;
  }
  
  DoublyLinkedNode<ELEMENT>* next() {
    return _next;
  }

  void set_prev(DoublyLinkedNode<ELEMENT>* prev) {
    _prev = prev;
  }
  
  void set_element(ELEMENT element) {
    _element = element;
  }
  
  void set_next(DoublyLinkedNode<ELEMENT>* next) {
    _next = next;
  }

private:
  ELEMENT _element;
  DoublyLinkedNode<ELEMENT> *_prev, *_next;
};

template <typename ELEMENT>
class DoublyLinkedList {
public:
  DoublyLinkedList() {
    _header = new DoublyLinkedNode<ELEMENT>(NULL, ELEMENT(), NULL);
    _trailer = new DoublyLinkedNode<ELEMENT>(_header, ELEMENT(), NULL);
    _header->set_next(_trailer);
  }

  ~DoublyLinkedList() {
    clear();
    delete _header;
    delete _trailer;
  }

  bool is_empty() {
    return (_header->next() == _trailer);
  }

  ELEMENT front() throw(UnderflowException) {
    if (is_empty())
      throw UnderflowException();
    return _header->next()->element();
  }

  ELEMENT back() throw(UnderflowException) {
    if (is_empty())
      throw UnderflowException();
    return _trailer->prev()->element();
  }
  
  void add_front(ELEMENT e) {
    add_before(_header->next(), e);
  }

  void add_back(ELEMENT e) {
    add_before(_trailer, e);
  }

  void remove_front() throw(UnderflowException) {
    if (is_empty())
      throw UnderflowException();
    remove(_header->next());
  }

  void remove_back() throw(UnderflowException) {
    if (is_empty())
      throw UnderflowException();
    remove(_trailer->prev());
  }

  void clear() {
    while (!is_empty())
      remove_front();
  }
  
private:
  DoublyLinkedNode<ELEMENT> *_header, *_trailer;

  void add_before(DoublyLinkedNode<ELEMENT>* where, ELEMENT e) {
    DoublyLinkedNode<ELEMENT>* new_node = new DoublyLinkedNode<ELEMENT>(where->prev(), e, where);
    where->prev()->set_next(new_node);
    where->set_prev(new_node);
  }

  void remove(DoublyLinkedNode<ELEMENT>* where) {
    where->prev()->set_next(where->next());
    where->next()->set_prev(where->prev());
    delete where;
  }
};
