
#pragma once

#include <cassert>

template <typename ELT>
class SinglyLinkedNode {
private:
  ELT _element;
  SinglyLinkedNode<ELT>* _next;

public:
  SinglyLinkedNode(ELT element, SinglyLinkedNode<ELT>* next) {
    _element = element;
    _next = next;
  }

  ELT element() { return _element; }

  void set_element(ELT element) { _element = element; }

  SinglyLinkedNode<ELT>* next() { return _next; }

  void set_next(SinglyLinkedNode<ELT>* next) { _next = next; }
};

template <typename ELT>
class SinglyLinkedListIterator;

template <typename ELT>
class SinglyLinkedList {

  friend SinglyLinkedListIterator<ELT>;
  
private:
  SinglyLinkedNode<ELT>* _head;
  int _length;

public:
  SinglyLinkedList() {
    _head = nullptr;
    _length = 0;
  }

  ~SinglyLinkedList() { clear(); }

  int length() { return _length; }

  bool is_empty() { return (nullptr == _head); }

  ELT front() {
    assert(!is_empty());
    return _head->element();
  }

  void add_front(ELT element) {
    SinglyLinkedNode<ELT> *new_head = new SinglyLinkedNode<ELT>(element, _head);
    _head = new_head;
    _length++;
  }
  
  void remove_front() {
    assert(!is_empty());
    SinglyLinkedNode<ELT>* new_head = _head->next();
    delete _head;
    _head = new_head;
    _length--;
  }

  void clear() {
    while (!is_empty()) {
      remove_front();
    }

    // double check invariants
    assert(is_empty());
    assert(0 == _length);
    assert(nullptr == _head);
  }
};

template <typename ELT>
class SinglyLinkedListIterator {
private:
  SinglyLinkedNode<ELT>* _location;

public:
  SinglyLinkedListIterator(SinglyLinkedList<ELT>* list) {
    assert(list != nullptr);
    _location = list->_head;
  }

  bool past_end() { return (nullptr == _location); }

  ELT get() {
    assert(!past_end());
    return _location->element();
  }

  void advance() {
    assert(!past_end());
    _location = _location->next();
  }
};
