#ifndef BFS_ITERATOR_HPP
#define BFS_ITERATOR_HPP

#include <queue>
#include "node.hpp"

template <typename T>
class BFSIterator {
private:
    std::queue<Node<T>*> nodeQueue;
    Node<T>* current;

public:
    BFSIterator(Node<T>* root);

    T& operator*();
    BFSIterator& operator++();
    bool operator!=(const BFSIterator& other) const;
};

template <typename T>
BFSIterator<T>::BFSIterator(Node<T>* root) : current(root) {
    if (root) {
        nodeQueue.push(root);
    }
}

template <typename T>
T& BFSIterator<T>::operator*() {
    return current->value;
}

template <typename T>
BFSIterator<T>& BFSIterator<T>::operator++() {
    if (!nodeQueue.empty()) {
        Node<T>* node = nodeQueue.front();
        nodeQueue.pop();

        for (auto& child : node->children) {
            if (child) {
                nodeQueue.push(child.get());
            }
        }

        if (!nodeQueue.empty()) {
            current = nodeQueue.front();
        } else {
            current = nullptr;
        }
    }
    return *this;
}

template <typename T>
bool BFSIterator<T>::operator!=(const BFSIterator& other) const {
    return current != other.current;
}

#endif // BFS_ITERATOR_HPP
