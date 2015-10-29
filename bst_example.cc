
#include <algorithm>
#include <iostream>
#include <map>
#include <random>

#include "bst.hh"

using namespace std;

const int N = 1000;

int random_index(int i) {
  return (rand() % i);
}

int main() {
  const int N = 1000;

  map<int, int> stl_tree;
  BST<int, int> our_tree;
  
  vector<int> indices;
  for (int i = 0; i < N; ++i)
    indices.push_back(i);
  random_shuffle(indices.begin(), indices.end(), random_index);
  
  for (vector<int>::iterator i = indices.begin(); i != indices.end(); ++i) {
    int key = *i;
    int value = (rand() % 5000) * 2; // random even number between 0 and 10000
    stl_tree[key] = value;
    our_tree.put(key, value);
  }

  assert(our_tree.size() == N);

  for (int i = 0; i < 10000; ++i) {
    // search for i and check that stl_tree and our_tree agree
    bool in_stl_tree = (stl_tree.find(i) != stl_tree.end());

    try {
      int value = our_tree.get(i);
      // if we got here, our tree found a match
      assert(in_stl_tree == true);
      assert(stl_tree[i] == value);
    } catch (KeyException e) {
      // our tree said i is not a key
      assert(in_stl_tree == false);
    }
  }

  // try deleting nodes one at a time
  for (int i = 0; i < N; ++i) {
    assert(our_tree.size() == (N - i));
    our_tree.erase(i);
  }

  assert(our_tree.is_empty());

  return 0;
}
