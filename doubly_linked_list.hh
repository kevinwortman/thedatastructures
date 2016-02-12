
#pragma once

#include <cassert>
#include <cstddef>

template <typename ELT>
class DoublyLinkedNode {
public:
  DoublyLinkedNode(DoublyLinkedNode<ELT>* prev, ELT element, DoublyLinkedNode<ELT>* next) {
    _prev = prev;
    _element = element;
    _next = next;
  }

  DoublyLinkedNode<ELT>* prev() {
    return _prev;
  }
  
  ELT element() {
    return _element;
  }
  
  DoublyLinkedNode<ELT>* next() {
    return _next;
  }

  void set_prev(DoublyLinkedNode<ELT>* prev) {
    _prev = prev;
  }
  
  void set_element(ELT element) {
    _element = element;
  }
  
  void set_next(DoublyLinkedNode<ELT>* next) {
    _next = next;
  }

private:
  ELT _element;
  DoublyLinkedNode<ELT> *_prev, *_next;
};

template<typename ELT>
class DoublyLinkedListIterator;

template <typename ELT>
class DoublyLinkedList {

  friend class DoublyLinkedListIterator<ELT>;
  
public:
  DoublyLinkedList() {
    // Create header and trailer nodes.
    _header = new DoublyLinkedNode<ELT>(NULL, ELT(), NULL);
    _trailer = new DoublyLinkedNode<ELT>(NULL, ELT(), NULL);

    // Make the header and trailer point to each other.
    _header->set_next(_trailer);
    _trailer->set_prev(_header);

    _length = 0;
  }

  ~DoublyLinkedList() {
    // Remove all nodes.
    clear();

    // Free the header and trailer too.
    delete _header;
    delete _trailer;
  }

  int length() { return _length; }
  
  bool is_empty() {
    // There are at least two valid ways we could implement this.
    assert( (_header->next() == _trailer) == (0 == _length) );
    return (0 == _length);
  }

  ELT front() {
    assert(!is_empty());
    return _header->next()->element();
  }

  ELT back() {
    assert(!is_empty());
    return _trailer->prev()->element();
  }
  
  void add_front(ELT e) {
    // Note that _header->next() is valid, even when the list is
    // empty, due to the trailer node.
    add_before(_header->next(), e);
  }

  void add_back(ELT e) {
    add_before(_trailer, e);
  }

  void remove_front() {
    assert(!is_empty());
    remove(_header->next());
  }

  void remove_back() {
    assert(!is_empty());
    remove(_trailer->prev());
  }

  void clear() {
    while (!is_empty())
      remove_front();
  }
  
private:
  DoublyLinkedNode<ELT> *_header, *_trailer;
  int _length;

  void add_before(DoublyLinkedNode<ELT>* where, ELT e) {
    assert(nullptr != where);
    DoublyLinkedNode<ELT>* new_node = new DoublyLinkedNode<ELT>(where->prev(), e, where);
    where->prev()->set_next(new_node);
    where->set_prev(new_node);
    _length++;
  }

  void remove(DoublyLinkedNode<ELT>* where) {
    assert(nullptr != where);
    where->prev()->set_next(where->next());
    where->next()->set_prev(where->prev());
    delete where;
    _length--;
  }
};

// This iterator class is almost the same as for a singly linked
// list. The main difference is that the iterator needs a pointer to
// the original list so we can tell when we reach the trailer node.
template<typename ELT>
class DoublyLinkedListIterator {
private:
  DoublyLinkedList<ELT>* _list;
  DoublyLinkedNode<ELT> *_location;
  
public:
  DoublyLinkedListIterator(DoublyLinkedList<ELT>* list) {
    assert(nullptr != list);
    _list = list;
    _location = list->_header->next();
  }

  bool past_end() { return (_location == _list->_trailer); }

  ELT get() {
    assert(!past_end());
    return _location->element();
  }

  void advance() {
    assert(!past_end());
    _location = _location->next();
  }
};
