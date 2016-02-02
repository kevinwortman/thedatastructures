
#pragma once

#include <cassert>

#include "exceptions.hh"

template <typename KEY, typename VALUE>
class BSTNode {
public:
  BSTNode(BSTNode<KEY, VALUE>* left,
          KEY key,
          VALUE value,
          BSTNode<KEY, VALUE>* right) {
    _left = left;
    _key = key;
    _value = value;
    _right = right;
  }

  KEY key() {
    return _key;
  }

  void set_key(KEY key) {
    _key = key;
  }

  VALUE value() {
    return _value;
  }

  void set_value(VALUE value) {
    _value = value;
  }
  
  BSTNode<KEY, VALUE>* left() {
    return _left;
  }

  void set_left(BSTNode<KEY, VALUE> *left) {
    _left = left;
  }
  
  BSTNode<KEY, VALUE>* right() {
    return _right;
  }

  void set_right(BSTNode<KEY, VALUE> *right) {
    _right = right;
  }
  
private:
  KEY _key;
  VALUE _value;
  BSTNode<KEY, VALUE> *_left, *_right;
};

template <typename KEY, typename VALUE>
class BST {
public:
  BST() {
    _root = NULL;
    _size = 0;
  }

  ~BST() {
    clear();
  }

  bool is_empty() {
    return (0 == _size);
  }

  int size() {
    return _size;
  }
  
  VALUE get(KEY key) throw(KeyException) {
    // Use a recursive helper function to do all the work.
    BSTNode<KEY, VALUE> *node = search(key, _root);
    if (NULL == node) {
      // This key isn't in the tree.
      throw KeyException();
    } else {
      // Otherwise just use the node's value getter.
      return node->value();
    }
  }

  void put(KEY key, VALUE value) {
    // Use recursive helper functions to do all the work.
    BSTNode<KEY, VALUE> *node = search(key, _root);
    if (node != NULL) {
      // There's already a node for this key; update the node's value
      // member.
      node->set_value(value);
    } else {
      // Insert a new node for this key-value association.
      _root = insert(key, value, _root);
      _size++;
    }
  }

  void erase(KEY key) throw(KeyException) {
    // Use recursive helper functions to do all the work.
    if (search(key, _root) == NULL) {
      // This key isn't in the tree so we can't erase it.
      throw KeyException();
    } else {
      _root = remove(key, _root);
      _size--;
    }
  }

  void clear() {
    // Use a recursive helper function to do all the work.
    clear_helper(_root);
    _root = NULL;
    _size = 0;
  }
  
private:

  BSTNode<KEY, VALUE> *_root;
  int _size;

  // Return the node containing query, or NULL if no such node exists.
  BSTNode<KEY, VALUE>* search(KEY query, BSTNode<KEY, VALUE>* subtree) {
    if (NULL == subtree) {
      // We've run down past the bottom of the tree, and never found a
      // matching node.
      return NULL;
    } else if (query < subtree->key()) {
      // Continue searching left.
      return search(query, subtree->left());
    } else if (query == subtree->key()) {
      // Found it!
      return subtree;
    } else {
      // Continue searching right.
      return search(query, subtree->right());
    }
  }

  // Insert a new node with the given key and value. The subtree must
  // not already have a node with this key. Returns a pointer to a
  // subtree that contains this new node.
  BSTNode<KEY, VALUE>* insert(KEY key, VALUE value, BSTNode<KEY, VALUE>* subtree) {
    if (NULL == subtree) {
      // Replace an empty tree with a new leaf node.
      return new BSTNode<KEY, VALUE>(NULL, key, value, NULL);
    } else if (key < subtree->key()) {
      // Recursively add a node to the left subtree.
      subtree->set_left(insert(key, value, subtree->left()));
      return subtree;
    } else {
      // Confirm there's not already a node with this key.
      assert(key != subtree->key());
      // By process of elimination, key must be greater than subtree's
      // key.
      assert(key > subtree->key());
      // Recursively add a node to the right subtree.
      subtree->set_right(insert(key, value, subtree->right()));
      return subtree;
    }
  }

  // Remove the node containing key query from subtree. This function
  // assumes that subtree actually does contain such a
  // node. Therefore, subtree must not be NULL. Returns a pointer to
  // a subtree that does not include the offending node.
  BSTNode<KEY, VALUE>* remove(KEY query, BSTNode<KEY, VALUE>* subtree) {
    
    assert(NULL != subtree);

    // We will refer to these data members many times, so it's easier
    // to save them in local variables than to call the getters over
    // and over.
    KEY key = subtree->key();
    BSTNode<KEY, VALUE> *left = subtree->left(),
                        *right = subtree->right();

    if (query < key) {
      // Continue searching left.
      subtree->set_left(remove(query, left));
      return subtree;
    } else if (query > key) {
      // Continue searching right.
      subtree->set_right(remove(query, right));
      return subtree;
      // if we get past this if, we know by process of elimination
      // that (query == key)
    } else if ((NULL == left) && (NULL == right)) {
      // We've reached a leaf which, by process of elimination, must
      // be the node we need to delete. Just delete it and we're done.
      assert(query == key);
      delete subtree;
      return NULL;
    } else if (NULL == left) {
      // There is a right child but no left, so we can simply delete
      // this node and move the right child into the "hole" left
      // behind.
      assert(query == key);
      delete subtree;
      return right;
    } else if (NULL == right) {
      // Symmetrically, if there's no right child, the left child
      // takes the place of this node.
      assert(query == key);
      delete subtree;
      return left;
    } else {
      // Tricky case: this node contains query, and has two children.
      assert(query == key);
      assert(left != NULL);
      assert(right != NULL);
      // Find the node containing the key immediately following query
      // in an inorder traversal.
      BSTNode<KEY, VALUE>* successor = left_leaf(right);
      assert(NULL != successor);
      // Move that node's key and value here.
      subtree->set_key(successor->key());
      subtree->set_value(successor->value());
      // We've successfully removed query from the tree, but now there
      // are two copies of successor. We fix this by recursively
      // deleting the deeper copy, which must be in the right subtree.
      subtree->set_right(remove(query, right));
      return subtree;
    }
  }

  BSTNode<KEY, VALUE>* left_leaf(BSTNode<KEY, VALUE>* subtree) {
    assert(NULL != subtree);
    if (NULL == subtree->left()) {
      return subtree;
    } else {
      return left_leaf(subtree->left());
    }
  }
  
  void clear_helper(BSTNode<KEY, VALUE>* subtree) {
    if (NULL != subtree) {
      clear_helper(subtree->left());
      clear_helper(subtree->right());
      delete subtree;
    }
  }
};
