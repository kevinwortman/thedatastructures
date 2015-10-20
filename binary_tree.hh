
#pragma once

#include <cassert>
#include <iostream>

#include "exceptions.hh"
#include "linked_stack.hh"

template <typename ELEMENT>
class BinaryNode {
public:
  BinaryNode(BinaryNode<ELEMENT> *left,
	     ELEMENT element,
	     BinaryNode<ELEMENT> *right) {
    _left = left;
    _element = element;
    _right = right;
  }

  ELEMENT element() {
    return _element;
  }

  void set_element(ELEMENT e) {
    _element = e;
  }

  BinaryNode<ELEMENT>* left() {
    return _left;
  }

  void set_left(BinaryNode<ELEMENT> *left) {
    _left = left;
  }
  
  BinaryNode<ELEMENT>* right() {
    return _right;
  }

  void set_right(BinaryNode<ELEMENT> *right) {
    _right = right;
  }

  void set_left_leaf(ELEMENT e) {
    assert(NULL == _left);
    _left = new BinaryNode<ELEMENT>(NULL, e, NULL);
  }

  void set_right_leaf(ELEMENT e) {
    assert(NULL == _right);
    _right = new BinaryNode<ELEMENT>(NULL, e, NULL);
  }


private:
  ELEMENT _element;
  BinaryNode<ELEMENT> *_left, *_right;
};

template <typename ELEMENT>
class BinaryTreeIterator {
public:
  BinaryTreeIterator(BinaryNode<ELEMENT> *root) {
    push_lefts(root);
  }

  void next() throw(IteratorException) {
    if (past_end())
      throw IteratorException();
    BinaryNode<ELEMENT> *top = _stack.peek();
    _stack.pop();
    push_lefts(top->right());
  }

  bool past_end() {
    return _stack.is_empty();
  }

  ELEMENT get() throw(IteratorException) {
    if (past_end())
      throw IteratorException();
    return _stack.peek()->element();
  }

private:
  LinkedStack<BinaryNode<ELEMENT>*> _stack;

  void push_lefts(BinaryNode<ELEMENT>* node) {
    while (node != NULL) {
      _stack.push(node);
      node = node->left();
    }
  }
};

template <typename ELEMENT>
class BinaryTree {
public:
  BinaryTree() {
    _root = NULL;
  }

  ~BinaryTree() {
    clear();
  }

  bool is_empty() {
    return (NULL == _root);
  }
  
  BinaryNode<ELEMENT>* root() {
    return _root;
  }

  void set_root(BinaryNode<ELEMENT> *root) {
    _root = root;
  }

  BinaryTreeIterator<ELEMENT> begin() {
    return BinaryTreeIterator<ELEMENT>(_root);
  }

  void clear() {
    clear_recurse(_root);
    _root = NULL;
  }
  
  void print_preorder() {
    preorder_recurse(_root);
  }

  void print_inorder() {
    inorder_recurse(_root);
  }

  void print_postorder() {
    postorder_recurse(_root);
  }

private:
  BinaryNode<ELEMENT> *_root;

  void clear_recurse(BinaryNode<ELEMENT> *node) {
    if (NULL == node)
      return;

    clear_recurse(node->left());
    clear_recurse(node->right());
    delete node;
  }

  void print(ELEMENT e) {
    std::cout << e << std::endl;
  }

  void preorder_recurse(BinaryNode<ELEMENT> *node) {
    if (NULL == node)
      return;
    print(node->element());
    preorder_recurse(node->left());
    preorder_recurse(node->right());
  }

  void inorder_recurse(BinaryNode<ELEMENT> *node) {
    if (NULL == node)
      return;
    inorder_recurse(node->left());
    print(node->element());
    inorder_recurse(node->right());
  }

  void postorder_recurse(BinaryNode<ELEMENT> *node) {
    if (NULL == node)
      return;
    postorder_recurse(node->left());
    postorder_recurse(node->right());
    print(node->element());
  }
};
