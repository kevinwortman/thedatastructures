
#include <iostream>

#include "binary_tree.hh"

using namespace std;

int main() {

  /* create the following binary tree:

     8
    / \
   7   11
      /  \
     3    4
    / \
   5   2

  */

  BinaryTree<int> tree;
  tree.set_root(new BinaryNode<int>(NULL, 8, NULL));
  tree.root()->set_left_leaf(7);
  tree.root()->set_right_leaf(11);
  tree.root()->right()->set_left_leaf(3);
  tree.root()->right()->left()->set_left_leaf(5);
  tree.root()->right()->left()->set_right_leaf(2);
  tree.root()->right()->set_right_leaf(4);

  cout << "Preorder:" << endl;
  tree.print_preorder();
  /* prints

     8
     7
     11
     3
     5
     2
     4
     
   */
  
  cout << endl << "Inorder:" << endl;
  tree.print_inorder();
  /* prints

     7
     8
     5
     3
     2
     11
     4

  */
  
  cout << endl << "Postorder:" << endl;
  tree.print_postorder();
  /* prints

     7
     5
     2
     3
     4
     11
     8

  */

  cout << endl << "Iterator:" << endl;
  for (BinaryTreeIterator<int> i = tree.begin(); !i.past_end(); i.next()) {
    cout << i.get() << endl;
  }
  cout << endl;
  /* prints

     7
     8
     5
     3
     2
     11
     4

  */
  
  return 0;
}
