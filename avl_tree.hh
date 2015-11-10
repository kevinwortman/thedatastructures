
#pragma once

#include <algorithm> // for abs and max
#include <cassert>
#include <cmath>
#include <iostream>

#include "exceptions.hh"

template<typename KEY, typename VALUE>
class AVLTree {
public:

  AVLTree() {
    _root = NULL;
    _size = 0;
  }

  ~AVLTree() {
    clear();
  }

  bool is_empty() {
    return (0 == _size);
  }

  int size() {
    return _size;
  }

  VALUE get(KEY key) throw(KeyException) {
    Node* node = search(key, _root);
    if (NULL == node) {
      throw KeyException();
    } else {
      return node->value;
    }
  }

  void put(KEY key, VALUE value) {
    Node* node = search(key, _root);
    if (NULL != node) {
      node->value = value;
    } else {
      _root = insert(key, value, _root).parent;
      _size++;
    }
  }

  void erase(KEY key) throw(KeyException) {
    if (NULL == search(key, _root)) {
      throw KeyException();
    } else {
      _root = remove(key, _root).parent;
      _size--;
    }
  }

  void clear() {
    clear_helper(_root);
    _root = NULL;
    _size = 0;
  }

  // Assert that all AVL invariants are satisfied, for debugging
  // purposes.
  void check() {
    // Check all per-node invariants.
    check_helper(_root);

    // Check overall tree height.
    assert(subtree_height(_root) <= 2.0 * std::ceil(std::log2(_size + 1)));
  }

  // Print out the tree, for debugging or educational purposes.
  void print() {
    std::cout << "---- AVL tree with size=" << _size << " ----" << std::endl;
    print_helper(_root);
    std::cout << std::endl;
  }
  
private:

  struct Node {
    // Create a leaf.
    Node(KEY the_key, VALUE the_value) {
      key = the_key;
      value = the_value;
      left = NULL;
      right = NULL;
      height = 1;
    }
    
    KEY key;
    VALUE value;
    Node *left, *right;
    int height;
  };

  // A Trail represents the two previous nodes visited by a recursive
  // insert or remove operation. Our insert and remove functions each
  // return a Trail, which makes it possible for the caller to
  // ascertain which rebalancing case we're in, without the use of
  // parent pointers.
  struct Trail {
    Trail(Node *the_parent, Node *the_child) {
      parent = the_parent;
      child = the_child;
    }
    
    Node *parent, *child;
  };

  // Entire tree's root node and size.
  Node *_root;
  int _size;

  // Search, identical to a plain BST.
  Node* search(KEY key, Node* subtree) {
    if (NULL == subtree) {
      return NULL;
    } else if (key < subtree->key) {
      return search(key, subtree->left);
    } else if (key > subtree->key) {
      return search(key, subtree->right);
    } else {
      return subtree;
    }
  }

  // Insert a new key-value association into subtree, and return a
  // Trail whose parent is the new root of the subtree, and whose
  // child is the descendant on the path to the newly-created
  // node. The returned subtree is locally balanced, though the
  // ancestors of the subtree may be imbalanced. This function assumes
  // that key *is not* currently in the tree.
  Trail insert(KEY key, VALUE value, Node *subtree) {
    if (NULL == subtree) {
      // new leaf node
      return Trail(new Node(key, value), NULL);
    } else if (key < subtree->key) {
      // Recursively insert into the left subtree, then restructure if
      // necessary
      return replace_left(subtree, insert(key, value, subtree->left));
    } else {
      // symmetric
      return replace_right(subtree, insert(key, value, subtree->right));
    }
  }

  // Remove the key-value association from subtree, and return a Trail
  // whose parent is the new root of the subtree, and whose child is
  // the descendant on the path to the removed node. The returned
  // subtree is locally balanced, though the ancestors of the subtree
  // may be imbalanced. This function assumes that key *is* currently
  // in the tree.
  Trail remove(KEY key, Node *subtree) {
    // If subtree is NULL then it can't possibly contain key.
    assert(NULL != subtree);
    if (key < subtree->key) {
      // Recursively remove from the left subtree, then restructure if
      // necessary.
      return replace_left(subtree, remove(key, subtree->left));
    } else if (key > subtree->key) {
      // symmetric
      return replace_right(subtree, remove(key, subtree->right));
    } else if ((NULL == subtree->left) && (NULL == subtree->right)) {
      // matching leaf node
      delete subtree;
      return Trail(NULL, NULL);
    } else if (NULL == subtree->left) {
      // right child only
      Node *child = subtree->right, *grandchild;
      // See p. 444 of Goodrich-Tamassia, if child's left child's
      // height is strictly greater than its sibling's, it may be
      // included in restructuring higher in the tree; otherwise
      // child->right may be involved.
      if (subtree_height(child->left) > subtree_height(child->right)) {
	grandchild = child->left;
      } else {
	grandchild = child->right;
      }
      delete subtree;
      return Trail(child, grandchild);
    } else if (NULL == subtree->right) {
      // symmetric
      Node *child = subtree->left, *grandchild;
      if (subtree_height(child->right) > subtree_height(child->left)) {
	grandchild = child->right;
      } else {
	grandchild = child->left;
      }
      delete subtree;
      return Trail(child, grandchild);
    } else {
      // Two children; as with a plain BST, locate the successor
      // key-value, move it to here, then recursively delete the
      // duplicate successor key.
      Node* successor = leftmost_leaf(subtree->right);
      subtree->key = successor->key;
      subtree->value = successor->value;
      // Restructure if necessary.
      return replace_right(subtree, remove(successor->key, subtree->right));
    }
  }

  // Replace subtree's left child with trail.parent, update heights,
  // restructure if necessary to maintain balance, and return a Trail
  // with subtree as parent.
  Trail replace_left(Node* subtree, Trail trail) {
    subtree->left = trail.parent;
    update_height(subtree);
    return maintain(subtree, trail);
  }

  // Symmetric to replace_left.
  Trail replace_right(Node* subtree, Trail trail) {
    subtree->right = trail.parent;
    update_height(subtree);
    return maintain(subtree, trail);
  }

  // Calculate the height of a subtree, which may be NULL.
  int subtree_height(Node* subtree) {
    if (NULL == subtree) {
      return 0;
    } else {
      return subtree->height;
    }
  }

  // Update node's height based on its current children's heights.
  void update_height(Node* node) {
    assert(NULL != node);
    node->height = (1 + std::max(subtree_height(node->left),
				 subtree_height(node->right)));
  }

  // Leftmost descendant of subtree.
  Node* leftmost_leaf(Node* subtree) {
    assert(NULL != subtree);
    if (NULL == subtree->left) {
      return subtree;
    } else {
      return leftmost_leaf(subtree->left);
    }
  }

  // Return true iff node is a balanced, non-NULL node.
  bool is_balanced(Node* node) {
    assert(NULL != node);
    int l = subtree_height(node->left),
        r = subtree_height(node->right);
    // AVL height-balance property: a node is balanced when its
    // childrens' heights differ by at most one.
    return (std::abs(l - r) <= 1);
  }
  
  Trail maintain(Node* subtree, Trail trail) {
    if ((NULL == subtree) ||       // Nodes at height 0 and 1 are implicitly
	(NULL == trail.parent) ||  // balanced.
	(NULL == trail.child) ||
	is_balanced(subtree)) {    // Or, a higher node is often balanced.
      // Balanced so do nothing.
      return Trail(subtree, trail.parent);
    } else {
      // COMMENCE TRINODE RESTRUCTURING

      // determine which of the four cases we're in, so we can
      // identify the relevant subtrees. Refer to figure 10.10 in
      // Goodrich-Tamassia.
      Node *a, *b, *c, *T0, *T1, *T2, *T3;
      if (subtree->right == trail.parent) {
	// left rotation of some kind
	if (trail.parent->right == trail.child) {
	  // single left rotation, case (a)
	  a = subtree;
	  b = trail.parent;
	  c = trail.child;
	  T0 = a->left;
	  T1 = b->left;
	  T2 = c->left;
	  T3 = c->right;
	} else {
	  // double left rotation, case (c)
	  a = subtree;
	  b = trail.child;
	  c = trail.parent;
	  T0 = a->left;
	  T1 = b->left;
	  T2 = b->right;
	  T3 = c->right;
	}
      } else {
	// right rotation of some kind
	if (trail.parent->left == trail.child) {
	  // single right rotation, case (b)
	  a = trail.child;
	  b = trail.parent;
	  c = subtree;
	  T0 = a->left;
	  T1 = a->right;
	  T2 = b->right;
	  T3 = c->right;
	} else {
	  // double right rotation, case (d)
	  a = trail.parent;
	  b = trail.child;
	  c = subtree;
	  T0 = a->left;
	  T1 = b->left;
	  T2 = b->right;
	  T3 = c->right;
	}
      }

      // reassemble
      set_children(a, T0, T1);
      set_children(c, T2, T3);
      set_children(b, a, c);

      // Note that the imbalanced node was rotated to the trail's
      // parent position, so the trail's child is undefined, and we
      // use NULL. Put another way: after this restructuring, b's
      // parent is never unbalanced.
      return Trail(b, NULL);
    }
  }

  // Assign new left and right children to node, and update node's
  // height.
  void set_children(Node *node, Node *left, Node *right) {
    node->left = left;
    node->right = right;
    update_height(node);
  }

  void clear_helper(Node* subtree) {
    if (NULL != subtree) {
      clear_helper(subtree->left);
      clear_helper(subtree->right);
      delete subtree;
    }
  }

  void check_helper(Node* subtree) {
    if (NULL != subtree) {
      if (NULL != subtree->left) {
	check_helper(subtree->left);
	assert(subtree->left->key < subtree->key);
      }
      if (NULL != subtree->right) {
	check_helper(subtree->right);
	assert(subtree->right->key > subtree->key);
      }
      assert(is_balanced(subtree));
    }
  }

  void print_helper(Node* subtree) {
    if (NULL != subtree) {
      print_helper(subtree->left);

      int indent = subtree_height(_root) - subtree_height(subtree);
      for (int i = 0; i < indent; ++i)
	std::cout << "    ";
      std::cout << "k=" << subtree->key << ", h=" << subtree_height(subtree) << std::endl;
      
      print_helper(subtree->right);
    }
  }
};
