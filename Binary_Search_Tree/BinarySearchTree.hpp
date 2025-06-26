// Optimized BinarySearchTree.hpp
#ifndef BINARYSEARCHTREE_HPP
#define BINARYSEARCHTREE_HPP

#include <iostream>
#include <memory>

template <class T>
struct Node {
    T key;
    std::unique_ptr<Node<T>> left;
    std::unique_ptr<Node<T>> right;

    explicit Node(const T& val) : key(val) {}
};

template <class T>
class BinarySearchTree {
public:
    BinarySearchTree() = default;
    ~BinarySearchTree() = default;

    void insert(const T& value) { insert(m_root, value); }
    void remove(const T& value) { remove(m_root, value); }
    unsigned int size() const { return m_size; }

    void printInOrder() const { printInOrder(m_root.get()); std::cout << '\n'; }
    void printPostOrder() const { printPostOrder(m_root.get()); std::cout << '\n'; }
    void printPreOrder() const { printPreOrder(m_root.get()); std::cout << '\n'; }

private:
    std::unique_ptr<Node<T>> m_root;
    unsigned int m_size = 0;

    void insert(std::unique_ptr<Node<T>>& node, const T& value) {
        if (!node) {
            node = std::make_unique<Node<T>>(value);
            ++m_size;
            return;
        }

        if (value < node->key) insert(node->left, value);
        else if (value > node->key) insert(node->right, value);
    }

    void remove(std::unique_ptr<Node<T>>& node, const T& value) {
        if (!node) return;

        if (value < node->key) {
            remove(node->left, value);
        } else if (value > node->key) {
            remove(node->right, value);
        } else {
            // Node with one or no child
            if (!node->left) {
                node = std::move(node->right);
                --m_size;
            } else if (!node->right) {
                node = std::move(node->left);
                --m_size;
            } else {
                // Two children: find inorder successor
                Node<T>* succ = node->right.get();
                while (succ->left) succ = succ->left.get();
                node->key = succ->key;
                remove(node->right, succ->key);
            }
        }
    }

    void printInOrder(const Node<T>* node) const {
        if (!node) return;
        printInOrder(node->left.get());
        std::cout << node->key << ", ";
        printInOrder(node->right.get());
    }

    void printPostOrder(const Node<T>* node) const {
        if (!node) return;
        printPostOrder(node->left.get());
        printPostOrder(node->right.get());
        std::cout << node->key << ", ";
    }

    void printPreOrder(const Node<T>* node) const {
        if (!node) return;
        std::cout << node->key << ", ";
        printPreOrder(node->left.get());
        printPreOrder(node->right.get());
    }
};

#endif // BINARYSEARCHTREE_HPP