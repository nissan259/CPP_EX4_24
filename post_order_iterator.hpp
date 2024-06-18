#ifndef POST_ORDER_ITERATOR_HPP
#define POST_ORDER_ITERATOR_HPP

#include <stack>
#include "node.hpp"

template <typename T>
class PostOrderIterator {
private:
    std::stack<Node<T>*> nodeStack;
    std::stack<bool> visitedStack;
    Node<T>* current;

    void advance();

public:
    PostOrderIterator(Node<T>* root);

    T& operator*();
    PostOrderIterator& operator++();
    bool operator!=(const PostOrderIterator& other) const;
};

template <typename T>
PostOrderIterator<T>::PostOrderIterator(Node<T>* root) : current(nullptr) {
    if (root) {
        nodeStack.push(root);
        visitedStack.push(false);
        advance();
    }
}

template <typename T>
void PostOrderIterator<T>::advance() {
    while (!nodeStack.empty()) {
        Node<T>* node = nodeStack.top();
        bool visited = visitedStack.top();
        nodeStack.pop();
        visitedStack.pop();

        if (visited) {
            current = node;
            return;
        } else {
            nodeStack.push(node);
            visitedStack.push(true);

            for (auto it = node->children.rbegin(); it != node->children.rend(); ++it) {
                if (*it) {
                    nodeStack.push(it->get());
                    visitedStack.push(false);
                }
            }
        }
    }
    current = nullptr;
}

template <typename T>
T& PostOrderIterator<T>::operator*() {
    return current->value;
}

template <typename T>
PostOrderIterator<T>& PostOrderIterator<T>::operator++() {
    advance();
    return *this;
}

template <typename T>
bool PostOrderIterator<T>::operator!=(const PostOrderIterator& other) const {
    return current != other.current;
}

#endif // POST_ORDER_ITERATOR_HPP
