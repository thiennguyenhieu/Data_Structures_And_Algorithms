
#ifndef BINARYSEARCHTREE_HPP
#define BINARYSEARCHTREE_HPP

#include <iostream>

template <class T>
struct Node
{
    T key;
    Node<T>* left;
    Node<T>* right;
};

template <class T>
class BinarySearchTree
{
public:
    BinarySearchTree() = default;
    ~BinarySearchTree();

    void insert(T value);
    void remove(T value);
    uint size() const;

    // At first traverse left subtree then visit the root and then traverse the right subtree.
    void printInOrder();

    // At first traverse left subtree then traverse the right subtree and then visit the root.
    void printPostOrder();

    // At first visit the root then traverse left subtree and then traverse the right subtree.
    void printPreOrder();
 
private:
    Node<T>* m_root {nullptr};
    uint m_size {0};

    Node<T>* newNode(T value);
    Node<T>* insert(Node<T>* root, T value);
    Node<T>* remove(Node<T>* root, T value);
    void deleteTree(Node<T>* root);
    void printInOrder(Node<T>* node);
    void printPostOrder(Node<T>* node);
    void printPreOrder(Node<T>* node);
};

template <class T>
BinarySearchTree<T>::~BinarySearchTree()
{
    deleteTree(m_root);
}

template <class T> 
void BinarySearchTree<T>::insert(T value)
{
    insert(m_root, value);
}

template <class T> 
void BinarySearchTree<T>::remove(T value)
{
    remove(m_root, value);
}

template <class T> 
void BinarySearchTree<T>::printInOrder()
{
    printInOrder(m_root);
    std::cout << std::endl;
}

template <class T> 
void BinarySearchTree<T>::printPostOrder()
{
    printPostOrder(m_root);
    std::cout << std::endl;
}

template <class T> 
void BinarySearchTree<T>::printPreOrder()
{
    printPreOrder(m_root);
    std::cout << std::endl;
}

template <class T> 
Node<T>* BinarySearchTree<T>::newNode(T value)
{
    auto newNode = new Node<T>();
    newNode->key = value;
    newNode->left = nullptr;
    newNode->right = nullptr;

    return newNode;
}

template <class T> 
Node<T>* BinarySearchTree<T>::insert(Node<T>* root, T value)
{
    if(!root)
    {
        root = newNode(value);
        
        if (m_size == 0)
        {
            m_root = root;
        }

        m_size++;
    }

    if (value < root->key)
    {
        root->left = insert(root->left, value);        
    }
    else if (value > root->key)
    {
        root->right = insert(root->right, value);
    }

    return root;
}

template <class T>
Node<T>* BinarySearchTree<T>::remove(Node<T>* root, T value)
{
    if (root == nullptr)
    {
       return nullptr;
    }
 
    // Recursive calls for ancestors of node to be deleted
    if (value < root->key) 
    {
        root->left = remove(root->left, value);
        return root;
    }
    else if (value > root->key) 
    {
        root->right = remove(root->right, value);
        return root;
    }
 
    if (root->left == nullptr) // If the left child is empty (also the case of both children are empty)
    {
        Node<T>* temp = root->right;
        delete root;
        m_size--;
        return temp;
    }
    else if (root->right == nullptr) // If the right child is empty
    {
        Node<T>* temp = root->left;
        delete root;
        m_size--;
        return temp;
    }
    else // If both children exist
    {
        Node<T>* succParent = root;
 
        // Find successor
        Node<T>* succ = root->right;
        while (succ->left != nullptr) 
        {
            succParent = succ;
            succ = succ->left;
        }
 
        // Delete successor.  Since successor is always left child of its parent
        // we can safely make successor's right child as left of its parent.
        // If there is no succ, then assign succ->right to succParent->right
        if (succParent != root)
        {
            succParent->left = succ->right;
        }
        else
        {
            succParent->right = succ->right;
        }
 
        // Copy Successor Data to root
        root->key = succ->key;
 
        // Delete Successor and return root
        delete succ;
        m_size--;
        return root;
    }
}

template <class T> 
void BinarySearchTree<T>::deleteTree(Node<T>* root)
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
uint BinarySearchTree<T>::size() const
{
    return m_size;
}

template <class T> 
void BinarySearchTree<T>::printInOrder(Node<T>* node)
{
    if(node != NULL)
    {
        printInOrder(node->left);
        std::cout << node->key << ", ";
        printInOrder(node->right);
    }
}

template <class T> 
void BinarySearchTree<T>::printPostOrder(Node<T>* node)
{
    if(node != NULL)
    {
        printPostOrder(node->left);
        printPostOrder(node->right);
        std::cout << node->key << ", ";
    }
}

template <class T> 
void BinarySearchTree<T>::printPreOrder(Node<T>* node)
{
    if(node != NULL)
    {
        std::cout << node->key << ", ";
        printPreOrder(node->left);
        printPreOrder(node->right);
    }
}
#endif //BINARYSEARCHTREE_HPP