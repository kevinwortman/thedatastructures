
#pragma once

#include <cstddef>

#include "exceptions.hh"

template <typename ELEMENT>
class SinglyLinkedNode {
public:
  SinglyLinkedNode(ELEMENT element, SinglyLinkedNode<ELEMENT>* next) {
    _element = element;
    _next = next;
  }

  ELEMENT element() {
    return _element;
  }

  void set_element(ELEMENT element) {
    _element = element;
  }

  SinglyLinkedNode<ELEMENT>* next() {
    return _next;
  }

  void set_next(SinglyLinkedNode<ELEMENT>* next) {
    _next = next;
  }

private:
  ELEMENT _element;
  SinglyLinkedNode<ELEMENT>* _next;
};

template <typename ELEMENT>
class SinglyLinkedList {
public:
  SinglyLinkedList() {
    _head = NULL;
  };

  ~SinglyLinkedList() {
    clear();
  }

  bool is_empty() {
    return (NULL == _head);
  }

  ELEMENT front() throw(UnderflowException) {
    if (is_empty()) {
      throw UnderflowException();
    } else {
      return _head->element();
    }
  }

  void add_front(ELEMENT e) {
    SinglyLinkedNode<ELEMENT>* new_head = new SinglyLinkedNode<ELEMENT>(e, _head);
    _head = new_head;
  }

  void remove_front() throw(UnderflowException) {
    if (is_empty()) {
      throw UnderflowException();
    } else {
      SinglyLinkedNode<ELEMENT>* new_head = _head->next();
      delete _head;
      _head = new_head;
    }
  }

  void clear() {
    while (!is_empty()) {
      remove_front();
    }
  }
      
private:
  SinglyLinkedNode<ELEMENT>* _head;  
};
