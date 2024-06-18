#ifndef DFS_ITERATOR_HPP
#define DFS_ITERATOR_HPP

#include <stack>
#include "node.hpp"

template <typename T>
class DFSIterator {
private:
    std::stack<Node<T>*> nodeStack;
    Node<T>* current;

public:
    DFSIterator(Node<T>* root);

    T& operator*();
    DFSIterator& operator++();
    bool operator!=(const DFSIterator& other) const;
};

template <typename T>
DFSIterator<T>::DFSIterator(Node<T>* root) : current(root) {
    if (root) {
        nodeStack.push(root);
    }
}

template <typename T>
T& DFSIterator<T>::operator*() {
    return current->value;
}

template <typename T>
DFSIterator<T>& DFSIterator<T>::operator++() {
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
bool DFSIterator<T>::operator!=(const DFSIterator& other) const {
    return current != other.current;
}

#endif // DFS_ITERATOR_HPP
