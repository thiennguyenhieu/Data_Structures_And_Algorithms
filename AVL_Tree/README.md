## AVL Tree Implementation
This project implements an AVL Tree, a self-balancing binary search tree (BST). It ensures that the difference in height between the left and right subtrees of any node is at most one, maintaining O(log n) time complexity for insertion, deletion, and lookup operations.

## 📈 Balancing Logic
The tree automatically performs one of the four rotations after insertion or deletion to maintain balance:

- Right Rotation (LL case)
```text
Before Right Rotate(z):

      z
     / \
    y   T4
   / \
  x  T3
 / \
T1 T2

Right Rotate(z):

      y
     / \
    x   z
   / \  / \
  T1 T2 T3 T4
```

- Left Rotation (RR case)
```text
Before Left Rotate(z):

    z
   / \
  T1  y
      / \
     T2  x
         / \
        T3 T4

Left Rotate(z):

      y
     / \
    z   x
   / \ / \
  T1 T2 T3 T4
```

- Left-Right Rotation (LR case)
```text
Before:

      z
     / \
    y   T4
   / \
  T1  x
      / \
     T2 T3

Step 1: Left Rotate(y):

      z
     / \
    x   T4
   / \
  y  T3
 / \
T1 T2

Step 2: Right Rotate(z):

      x
     / \
    y   z
   / \  / \
  T1 T2 T3 T4
```

- Right-Left Rotation (RL case)
```text
Before:

      z
     / \
   T1   y
       / \
      x  T4
     / \
   T2  T3

Step 1: Right Rotate(y):

      z
     / \
   T1   x
        / \
      T2   y
          / \
        T3  T4

Step 2: Left Rotate(z):

      x
     / \
    z   y
   / \ / \
  T1 T2 T3 T4
```