# thedatastructures
Fundamental data structures used as class examples.

This code is intended for pedagogical use, so it prioritizes readability and simplicity over industrial-grade efficiency and completeness. In particular:
* Interfaces and implementations are mere conventions, not formalized through virtual abstract classes.
* Classes implement only fundamental operations, and lack derived utility functions.
* Arguments are always pass-by-value or pass-by-pointer, never pass-by-reference, for clarity.
* We don't use initializer lists, again for clarity.
* There is some unnecessary copying in a few places (see the above bullet item).
* The code is not const-correct.
* Recursion is preferred over loops, to provide ample examples of correct recursive code.
* Constant factors are a low priority. For example, the BST insertion and deletion functions call the search function to determine whether nodes actually need to be changed, which means these functions navigate the tree twice even though it is possible to do this only once. Similarly, there is one general AVL rotation function that branches to determine whether to rotate left or right, even though it's possible to write specialized left-rotation and right-rotation functions to avoid that branch.