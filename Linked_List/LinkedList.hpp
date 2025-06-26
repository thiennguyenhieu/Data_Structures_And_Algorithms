// Optimized LinkedList.hpp
#ifndef LINKEDLIST_HPP
#define LINKEDLIST_HPP

#include <iostream>
#include <memory>

template <class T>
struct Node {
    T key;
    std::unique_ptr<Node<T>> next;

    explicit Node(const T& value) : key(value), next(nullptr) {}
};

template <class T>
class LinkedList {
public:
    LinkedList() = default;
    ~LinkedList() = default;

    void append(const T& value); // insert a new node at the end of the list
    void push(const T& value);   // insert a new node at the front of the list
    void reverse();
    void removeByPos(unsigned int pos);
    unsigned int size() const { return m_size; }
    void print() const;

private:
    std::unique_ptr<Node<T>> m_head;
    unsigned int m_size {0};
};

template <class T>
void LinkedList<T>::append(const T& value) {
    auto node = std::make_unique<Node<T>>(value);
    ++m_size;

    if (!m_head) {
        m_head = std::move(node);
        return;
    }

    Node<T>* current = m_head.get();
    while (current->next) {
        current = current->next.get();
    }
    current->next = std::move(node);
}

template <class T>
void LinkedList<T>::push(const T& value) {
    auto node = std::make_unique<Node<T>>(value);
    node->next = std::move(m_head);
    m_head = std::move(node);
    ++m_size;
}

template <class T>
void LinkedList<T>::print() const {
    Node<T>* current = m_head.get();
    while (current) {
        std::cout << current->key << ", ";
        current = current->next.get();
    }
    std::cout << std::endl;
}

template <class T>
void LinkedList<T>::reverse() {
    std::unique_ptr<Node<T>> prev = nullptr;
    std::unique_ptr<Node<T>> current = std::move(m_head);

    while (current) {
        auto next = std::move(current->next);
        current->next = std::move(prev);
        prev = std::move(current);
        current = std::move(next);
    }

    m_head = std::move(prev);
}

template <class T>
void LinkedList<T>::removeByPos(unsigned int pos) {
    if (!m_head || pos >= m_size) return;

    if (pos == 0) {
        m_head = std::move(m_head->next);
        --m_size;
        return;
    }

    Node<T>* current = m_head.get();
    for (unsigned int i = 0; i < pos - 1 && current->next; ++i) {
        current = current->next.get();
    }

    if (current->next) {
        current->next = std::move(current->next->next);
        --m_size;
    }
}

#endif // LINKEDLIST_HPP