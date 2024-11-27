#ifndef LINKEDLIST_HPP
#define LINKEDLIST_HPP

#include <iostream>

template <class T>
struct Node
{
    T key;
    Node<T>* next;
};

template <class T>
class LinkedList
{
public:
    LinkedList() = default;
    ~LinkedList();

    void append(T value); // insert a new node at the end of the list
    void push(T value); // insert a new node on the front of the list
    void reverse();
    void removeByPos(unsigned int pos);
    unsigned int size() const;
    void print();

private:
    Node<T>* m_head {nullptr};
    unsigned int m_size {0};

    Node<T>* newNode(T value);
    void deleteList();
};

template <class T>
LinkedList<T>::~LinkedList()
{
    deleteList();
}

template <class T> 
Node<T>* LinkedList<T>::newNode(T value)
{
    Node<T>* newNode = new Node<T>();
    newNode->key = value;
    newNode->next = nullptr;
    m_size++;
    return newNode;
}

template <class T> 
void LinkedList<T>::append(T value)
{
    Node<T>* node = newNode(value);
    
    if (m_head == nullptr)
    {
        m_head = node;
        return;
    }

    Node<T>* last = m_head;
    while (last->next != nullptr)
    {
        last = last->next;
    }

    last->next = node;
}

template <class T> 
void LinkedList<T>::push(T value)
{
    Node<T>* node = newNode(value);
    node->next = m_head;
    m_head = node;
}

template <class T>
void LinkedList<T>::print()
{
    Node<T>* current = m_head;
    while (current != nullptr)
    {
        std::cout << current->key << ", ";
        current = current->next;
    }

    std::cout << std::endl;
}

template <class T>
void LinkedList<T>::deleteList()
{   
    Node<T>* current = m_head;
    Node<T>* temp = nullptr;

    while (current != nullptr)
    {
        temp = current;
        current = current->next;
        delete temp;
        temp = nullptr;
    }
}

template <class T>
void LinkedList<T>::reverse()
{
    Node<T>* current = m_head;
    Node<T>* prev = nullptr;
    Node<T>* next = nullptr;

    while (current != nullptr)
    {
        next = current->next;
        current->next = prev;
        prev = current;
        current = next;
    }

    m_head = prev;
}

template <class T>
void LinkedList<T>::removeByPos(unsigned int pos)
{
    if (m_head == nullptr || pos >= m_size)
    {
        return;
    }
    
    Node<T>* temp = m_head;

    if (pos == 0)
    {
        m_head = temp->next;
        delete temp;
        --m_size;
        return;
    }

    // find the previous node of the node to be deleted
    int index = 0;
    while (index < pos - 1)
    {
        temp = temp->next;
        ++index;
    }

    Node<T>* next = temp->next->next;
    delete temp->next;
    temp->next = next;
    --m_size;
}

template <class T>
unsigned int LinkedList<T>::size() const
{
    return m_size;
}

#endif // LINKEDLIST_HPP