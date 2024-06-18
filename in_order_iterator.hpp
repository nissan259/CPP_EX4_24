#ifndef IN_ORDER_ITERATOR_HPP
#define IN_ORDER_ITERATOR_HPP

#include <stack>
#include "node.hpp"

template <typename T>
class InOrderIterator {
private:
    std::stack<Node<T>*> nodeStack;
    Node<T>* current;
    void pushLeftNodes(Node<T>* node);

public:
    InOrderIterator(Node<T>* root);
    T& operator*();
    InOrderIterator& operator++();
    bool operator!=(const InOrderIterator& other) const;
};

template <typename T>
InOrderIterator<T>::InOrderIterator(Node<T>* root) : current(nullptr) {
    pushLeftNodes(root);
    if (!nodeStack.empty()) {
        current = nodeStack.top();
        nodeStack.pop();
    }
}

template <typename T>
void InOrderIterator<T>::pushLeftNodes(Node<T>* node) {
    while (node) {
        nodeStack.push(node);
        if (!node->children.empty()) {
            node = node->children[0].get();
        } else {
            break;
        }
    }
}

template <typename T>
T& InOrderIterator<T>::operator*() {
    return current->value;
}

template <typename T>
InOrderIterator<T>& InOrderIterator<T>::operator++() {
    if (current) {
        if (current->children.size() > 1) {
            pushLeftNodes(current->children[1].get());
        }
        if (!nodeStack.empty()) {
            current = nodeStack.top();
            nodeStack.pop();
        } else {
            current = nullptr;
        }
    }
    return *this;
}

template <typename T>
bool InOrderIterator<T>::operator!=(const InOrderIterator& other) const {
    return current != other.current;
}

#endif // IN_ORDER_ITERATOR_HPP
