
#include <algorithm>
#include <iostream>
#include <map>
#include <random>

#include "avl_tree.hh"
#include "bst.hh"

using namespace std;

const int N = 10000;

int random_index(int i) {
  return (rand() % i);
}

int main() {

  map<int, int> stl_tree;
  BST<int, int> bst;
  AVLTree<int, int> avl;
  
  vector<int> indices;
  for (int i = 0; i < N; ++i)
    indices.push_back(i);
  random_shuffle(indices.begin(), indices.end(), random_index);
  
  for (vector<int>::iterator i = indices.begin(); i != indices.end(); ++i) {
    int key = *i;
    int value = (rand() % 5000) * 2; // random even number between 0 and 10000
    stl_tree[key] = value;
    bst.put(key, value);
    avl.put(key, value);
    avl.check();
  }

  avl.print();

  assert(bst.size() == N);

  for (int i = 0; i < 10000; ++i) {
    // search for i and check that stl_tree and bst agree
    bool in_stl_tree = (stl_tree.find(i) != stl_tree.end());

    try {
      int value = bst.get(i);
      // if we got here, our tree found a match
      assert(in_stl_tree == true);
      assert(stl_tree[i] == value);
    } catch (KeyException e) {
      // our tree said i is not a key
      assert(in_stl_tree == false);
    }

    try {
      int value = avl.get(i);
      assert(in_stl_tree == true);
      assert(stl_tree[i] == value);
    } catch (KeyException e) {
      assert(in_stl_tree == false);
    }
  }

  // try deleting nodes one at a time
  for (int i = 0; i < N; ++i) {
    assert(bst.size() == (N - i));
    bst.erase(i);

    avl.erase(i);
    //avl.print();
  }

  assert(bst.is_empty());
  assert(avl.is_empty());
  
  return 0;
}
