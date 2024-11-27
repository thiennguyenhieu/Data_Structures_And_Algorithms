
#ifndef AVLTREE_HPP
#define AVLTREE_HPP

#include <iostream>
#include <algorithm>

template <class T>
struct AVLNode
{
    T key;
    AVLNode<T>* left;
    AVLNode<T>* right;
    unsigned int height;
};

template <class T>
class AVLTree
{
public:
    AVLTree() = default;
    ~AVLTree();

    void insert(T value);
    void remove(T value);
    unsigned int size() const;

    // At first traverse left subtree then visit the root and then traverse the right subtree.
    void printInOrder();

    // At first traverse left subtree then traverse the right subtree and then visit the root.
    void printPostOrder();

    // At first visit the root then traverse left subtree and then traverse the right subtree.
    void printPreOrder();
 
private:
    AVLNode<T>* m_root {nullptr};
    unsigned int m_size {0};

    AVLNode<T>* newNode(T value);
    int getBalance(AVLNode<T>* node);
    unsigned int height(AVLNode<T>* node) const;
    AVLNode<T>* minValueNode(AVLNode<T>* node);
    AVLNode<T>* leftRotate(AVLNode<T>* x);
    AVLNode<T>* rightRotate(AVLNode<T>* y);
    AVLNode<T>* insert(AVLNode<T>* root, T value);
    AVLNode<T>* remove(AVLNode<T>* root, T value);
    void deleteTree(AVLNode<T>* root);
    void printInOrder(AVLNode<T>* node);
    void printPostOrder(AVLNode<T>* node);
    void printPreOrder(AVLNode<T>* node);
};

template <class T>
AVLTree<T>::~AVLTree()
{
    deleteTree(m_root);
}

template <class T> 
void AVLTree<T>::insert(T value)
{
    m_root = insert(m_root, value);
}

template <class T> 
void AVLTree<T>::remove(T value)
{
    m_root = remove(m_root, value);
}

template <class T> 
void AVLTree<T>::printInOrder()
{
    printInOrder(m_root);
    std::cout << std::endl;
}

template <class T> 
void AVLTree<T>::printPostOrder()
{
    printPostOrder(m_root);
    std::cout << std::endl;
}

template <class T> 
void AVLTree<T>::printPreOrder()
{
    printPreOrder(m_root);
    std::cout << std::endl;
}

template <class T> 
AVLNode<T>* AVLTree<T>::newNode(T value)
{
    auto newNode = new AVLNode<T>();
    newNode->key = value;
    newNode->left = nullptr;
    newNode->right = nullptr;
    newNode->height = 1;

    return newNode;
}

template <class T> 
int AVLTree<T>::getBalance(AVLNode<T>* node)  
{  
    if (node == nullptr) 
    {
        return 0;
    }

    return height(node->left) - height(node->right);  
}

template <class T> 
unsigned int AVLTree<T>::height(AVLNode<T>* node) const
{ 
    return (node == nullptr) ? 0 : node->height;
}

template <class T> 
AVLNode<T>* AVLTree<T>::minValueNode(AVLNode<T>* node)
{
    AVLNode<T>* current = node;
 
    /* loop down to find the leftmost leaf */
    while (current->left != NULL)
    {
        current = current->left;
    }
 
    return current;
}

template <class T>
AVLNode<T>* AVLTree<T>::leftRotate(AVLNode<T>* x)  
{  
    AVLNode<T>* y = x->right;  
    AVLNode<T>* T2 = y->left;  
  
    // Perform rotation  
    y->left = x;  
    x->right = T2;  
  
    // Update heights  
    x->height = std::max(height(x->left), height(x->right)) + 1;  
    y->height = std::max(height(y->left), height(y->right)) + 1;  

    // Return new root  
    return y;
}

template <class T>
AVLNode<T>* AVLTree<T>::rightRotate(AVLNode<T>* y)  
{  
    AVLNode<T>* x = y->left;  
    AVLNode<T>* T2 = x->right;  
  
    // Perform rotation  
    x->right = y;  
    y->left = T2;  
  
    // Update heights  
    y->height = std::max(height(y->left), height(y->right)) + 1;  
    x->height = std::max(height(x->left), height(x->right)) + 1;  
  
    // Return new root  
    return x;  
}

template <class T> 
AVLNode<T>* AVLTree<T>::insert(AVLNode<T>* root, T value)
{
    /* Perform the normal BST insertion */
    if(!root)
    {
        root = newNode(value);
        
        if (m_size == 0)
        {
            m_root = root;
        }

        m_size++;

        return root;
    }

    if (value < root->key)
    {
        root->left = insert(root->left, value);        
    }
    else if (value > root->key)
    {
        root->right = insert(root->right, value);
    }
    else
    {
        return root;
    }

    /* Update height of this ancestor node */
    root->height = 1 + std::max(height(root->left), height(root->right)); 

    /* Get the balance factor of this ancestor  
    node to check whether this node became unbalanced */
    int balance = getBalance(root);

    // If this node becomes unbalanced, then there are 4 cases  
  
    // Left Left Case  
    if (balance > 1 && value < root->left->key)
    {
        return rightRotate(root);
    }
  
    // Right Right Case  
    if (balance < -1 && value > root->right->key)
    {
        return leftRotate(root);
    }
  
    // Left Right Case  
    if (balance > 1 && value > root->left->key)  
    {  
        root->left = leftRotate(root->left);  
        return rightRotate(root);  
    }  
  
    // Right Left Case  
    if (balance < -1 && value < root->right->key)  
    {  
        root->right = rightRotate(root->right);  
        return leftRotate(root);  
    }  
  
    /* return the (unchanged) node pointer */
    return root; 
}

template <class T>
AVLNode<T>* AVLTree<T>::remove(AVLNode<T>* root, T value)
{
    // STEP 1: PERFORM STANDARD BST DELETE
    if (root == nullptr)
    {
        return root;
    }
 
    if (value < root->key)
    {
        root->left = remove(root->left, value);
    }
    else if(value > root->key)
    {
        root->right = remove(root->right, value);
    }
    else // if key is same as root's key, then this is the node to be deleted
    {
        // node with only one child or no child
        if((root->left == nullptr) || (root->right == nullptr))
        {
            AVLNode<T>* temp = root->left ? root->left : root->right;
 
            // No child case
            if (temp == nullptr)
            {
                temp = root;
                root = nullptr;
            }
            else // One child case
            {
                *root = *temp; // Copy the contents of the non-empty child
            }
            
            m_size--;
            delete temp;
        }
        else
        {
            // node with two children: Get the inorder
            // successor (smallest in the right subtree)
            AVLNode<T>* temp = minValueNode(root->right);
 
            // Copy the inorder successor's data to this node
            root->key = temp->key;
 
            // Delete the inorder successor
            root->right = remove(root->right, temp->key);
        }
    }
 
    // If the tree had only one node then return
    if (root == nullptr)
    {
        return root;
    }
 
    // STEP 2: UPDATE HEIGHT OF THE CURRENT NODE
    root->height = 1 + std::max(height(root->left), height(root->right));
 
    // STEP 3: GET THE BALANCE FACTOR OF THIS NODE (to
    // check whether this node became unbalanced)
    int balance = getBalance(root);
 
    // If this node becomes unbalanced, then there are 4 cases
 
    // Left Left Case
    if (balance > 1 && getBalance(root->left) >= 0)
    {
        return rightRotate(root);
    }
 
    // Left Right Case
    if (balance > 1 && getBalance(root->left) < 0)
    {
        root->left =  leftRotate(root->left);
        return rightRotate(root);
    }
 
    // Right Right Case
    if (balance < -1 && getBalance(root->right) <= 0)
    {
        return leftRotate(root);
    }
 
    // Right Left Case
    if (balance < -1 && getBalance(root->right) > 0)
    {
        root->right = rightRotate(root->right);
        return leftRotate(root);
    }
 
    return root;
}

template <class T> 
void AVLTree<T>::deleteTree(AVLNode<T>* root)
{
    if(root != nullptr)
    {
        deleteTree(root->left);
        deleteTree(root->right);
        delete root;
        root = nullptr;
    }
}

template <class T> 
unsigned int AVLTree<T>::size() const
{
    return m_size;
}

template <class T> 
void AVLTree<T>::printInOrder(AVLNode<T>* node)
{
    if(node != NULL)
    {
        printInOrder(node->left);
        std::cout << node->key << ", ";
        printInOrder(node->right);
    }
}

template <class T> 
void AVLTree<T>::printPostOrder(AVLNode<T>* node)
{
    if(node != NULL)
    {
        printPostOrder(node->left);
        printPostOrder(node->right);
        std::cout << node->key << ", ";
    }
}

template <class T> 
void AVLTree<T>::printPreOrder(AVLNode<T>* node)
{
    if(node != NULL)
    {
        std::cout << node->key << ", ";
        printPreOrder(node->left);
        printPreOrder(node->right);
    }
}
#endif //AVLTREE_HPP