AVL tree is a self-balancing Binary Search Tree (BST) where the difference between heights of left and right subtrees cannot be more than one for all nodes. 

Why AVL Trees? 
Most of the BST operations (e.g., search, max, min, insert, delete.. etc) take O(h) time where h is the height of the BST. The cost of these operations may become O(n) for a skewed Binary tree. If we make sure that the height of the tree remains O(log(n)) after every insertion and deletion, then we can guarantee an upper bound of O(log(n)) for all these operations. The height of an AVL tree is always O(log(n)) where n is the number of nodes in the tree.

Insertion in AVL Tree:
To make sure that the given tree remains AVL after every insertion, we must augment the standard BST insert operation to perform some re-balancing. 

![image](https://github.com/thiennguyenhieu/Data_Structures_And_Algorithms/blob/master/AVL_Tree/avl_insert.jpeg)
