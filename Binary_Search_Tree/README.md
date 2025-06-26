# Binary Search Tree (BST)
A Binary Search Tree (BST) is a hierarchical data structure that stores elements (often numbers or comparable types) in a sorted binary tree format. Each node in a BST contains:
- A value (key)
- A pointer to the left child (containing smaller values)
- A pointer to the right child (containing larger values)

This structure enforces the BST property:
For any given node, all elements in its left subtree are less than the node’s key, and all elements in the right subtree are greater.

## Example Tree Structure
Given the following insert sequence:
```cpp
bst.insert(8);
bst.insert(3);
bst.insert(10);
bst.insert(1);
bst.insert(6);
bst.insert(14);
bst.insert(4);
bst.insert(7);
bst.insert(13);
```
The resulting BST looks like this:
```
                              8
                          /       \
                         3        10
                       /   \        \ 
                      1     6       14
                          /   \     /
                         4     7   13
```