#ifndef AVLTREE_HPP
#define AVLTREE_HPP

#include <iostream>
#include <algorithm>
#include <memory>

template <class T>
struct AVLNode
{
    T key;
    std::unique_ptr<AVLNode<T>> left;
    std::unique_ptr<AVLNode<T>> right;
    unsigned int height = 1;
};

template <class T>
class AVLTree
{
public:
    AVLTree() = default;
    ~AVLTree() = default;

    void insert(const T& value) { m_root = insert(std::move(m_root), value); }
    void remove(const T& value) { m_root = remove(std::move(m_root), value); }
    unsigned int size() const { return m_size; }

    void printInOrder() const { printInOrder(m_root.get()); std::cout << '\n'; }
    void printPostOrder() const { printPostOrder(m_root.get()); std::cout << '\n'; }
    void printPreOrder() const { printPreOrder(m_root.get()); std::cout << '\n'; }

private:
    std::unique_ptr<AVLNode<T>> m_root;
    unsigned int m_size = 0;

    unsigned int height(const std::unique_ptr<AVLNode<T>>& node) const {
        return node ? node->height : 0;
    }

    int getBalance(const std::unique_ptr<AVLNode<T>>& node) const {
        return node ? static_cast<int>(height(node->left)) - static_cast<int>(height(node->right)) : 0;
    }

    void updateHeight(AVLNode<T>* node) {
        node->height = 1 + std::max(height(node->left), height(node->right));
    }

    std::unique_ptr<AVLNode<T>> rightRotate(std::unique_ptr<AVLNode<T>> y) {
        auto x = std::move(y->left);
        auto T2 = std::move(x->right);
        x->right = std::move(y);
        x->right->left = std::move(T2);
        updateHeight(x->right.get());
        updateHeight(x.get());
        return x;
    }

    std::unique_ptr<AVLNode<T>> leftRotate(std::unique_ptr<AVLNode<T>> x) {
        auto y = std::move(x->right);
        auto T2 = std::move(y->left);
        y->left = std::move(x);
        y->left->right = std::move(T2);
        updateHeight(y->left.get());
        updateHeight(y.get());
        return y;
    }

    AVLNode<T>* minValueNode(AVLNode<T>* node) const {
        while (node && node->left) node = node->left.get();
        return node;
    }

    std::unique_ptr<AVLNode<T>> insert(std::unique_ptr<AVLNode<T>> node, const T& value) {
        if (!node) {
            m_size++;
            return std::make_unique<AVLNode<T>>(AVLNode<T>{value});
        }

        if (value < node->key) node->left = insert(std::move(node->left), value);
        else if (value > node->key) node->right = insert(std::move(node->right), value);
        else return node;

        updateHeight(node.get());
        return balance(std::move(node), value);
    }

    std::unique_ptr<AVLNode<T>> remove(std::unique_ptr<AVLNode<T>> node, const T& value) {
        if (!node) return nullptr;

        if (value < node->key) node->left = remove(std::move(node->left), value);
        else if (value > node->key) node->right = remove(std::move(node->right), value);
        else {
            if (!node->left || !node->right) {
                m_size--;
                return node->left ? std::move(node->left) : std::move(node->right);
            } else {
                AVLNode<T>* temp = minValueNode(node->right.get());
                node->key = temp->key;
                node->right = remove(std::move(node->right), temp->key);
            }
        }

        updateHeight(node.get());
        return balanceAfterDeletion(std::move(node));
    }

    std::unique_ptr<AVLNode<T>> balance(std::unique_ptr<AVLNode<T>> node, const T& value) {
        int balance = getBalance(node);
        if (balance > 1 && value < node->left->key) return rightRotate(std::move(node));
        if (balance < -1 && value > node->right->key) return leftRotate(std::move(node));
        if (balance > 1 && value > node->left->key) {
            node->left = leftRotate(std::move(node->left));
            return rightRotate(std::move(node));
        }
        if (balance < -1 && value < node->right->key) {
            node->right = rightRotate(std::move(node->right));
            return leftRotate(std::move(node));
        }
        return node;
    }

    std::unique_ptr<AVLNode<T>> balanceAfterDeletion(std::unique_ptr<AVLNode<T>> node) {
        int balance = getBalance(node);
        if (balance > 1 && getBalance(node->left) >= 0) return rightRotate(std::move(node));
        if (balance > 1 && getBalance(node->left) < 0) {
            node->left = leftRotate(std::move(node->left));
            return rightRotate(std::move(node));
        }
        if (balance < -1 && getBalance(node->right) <= 0) return leftRotate(std::move(node));
        if (balance < -1 && getBalance(node->right) > 0) {
            node->right = rightRotate(std::move(node->right));
            return leftRotate(std::move(node));
        }
        return node;
    }

    void printInOrder(const AVLNode<T>* node) const {
        if (node) {
            printInOrder(node->left.get());
            std::cout << node->key << ", ";
            printInOrder(node->right.get());
        }
    }

    void printPostOrder(const AVLNode<T>* node) const {
        if (node) {
            printPostOrder(node->left.get());
            printPostOrder(node->right.get());
            std::cout << node->key << ", ";
        }
    }

    void printPreOrder(const AVLNode<T>* node) const {
        if (node) {
            std::cout << node->key << ", ";
            printPreOrder(node->left.get());
            printPreOrder(node->right.get());
        }
    }
};

#endif // AVLTREE_HPP