#ifndef PRE_ORDER_ITERATOR_HPP
#define PRE_ORDER_ITERATOR_HPP

#include <stack>
#include "node.hpp"

template <typename T>
class PreOrderIterator {
private:
    std::stack<Node<T>*> nodeStack;
    Node<T>* current;

public:
    PreOrderIterator(Node<T>* root);

    T& operator*();
    PreOrderIterator& operator++();
    bool operator!=(const PreOrderIterator& other) const;
};

template <typename T>
PreOrderIterator<T>::PreOrderIterator(Node<T>* root) : current(root) {
    if (root) {
        nodeStack.push(root);
    }
}

template <typename T>
T& PreOrderIterator<T>::operator*() {
    return current->value;
}

template <typename T>
PreOrderIterator<T>& PreOrderIterator<T>::operator++() {
    if (!nodeStack.empty()) {
        Node<T>* node = nodeStack.top();
        nodeStack.pop();

        for (auto it = node->children.rbegin(); it != node->children.rend(); ++it) {
            if (*it) {
                nodeStack.push(it->get());
            }
        }

        if (!nodeStack.empty()) {
            current = nodeStack.top();
        } else {
            current = nullptr;
        }
    }
    return *this;
}

template <typename T>
bool PreOrderIterator<T>::operator!=(const PreOrderIterator& other) const {
    return current != other.current;
}

#endif // PRE_ORDER_ITERATOR_HPP