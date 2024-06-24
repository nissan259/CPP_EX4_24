#ifndef IN_ORDER_ITERATOR_HPP
#define IN_ORDER_ITERATOR_HPP

#include <stack>
#include <memory>
#include "node.hpp"

template <typename T>
class InOrderIterator {
private:
    std::stack<Node<T>*> nodeStack;
    Node<T>* current;
    int k;

    void pushLeftNodes(Node<T>* node) {
        while (node) {
            nodeStack.push(node);
            if (!node->children.empty()) {
                node = node->children[0].get();
            } else {
                break;
            }
        }
    }

public:
    InOrderIterator(const std::unique_ptr<Node<T>>& root, int k) : current(nullptr), k(k) {
        if (k == 2) {
            pushLeftNodes(root.get());
        } else if (root) {
            nodeStack.push(root.get());
        }
        ++(*this); // Move to the first valid node
    }

    T& operator*() {
        return current->value;
    }

    InOrderIterator& operator++() {
        if (k == 2) {
            // In-order traversal for binary trees
            if (current) {
                if (current->children.size() > 1) {
                    pushLeftNodes(current->children[1].get());
                }
            }
            if (!nodeStack.empty()) {
                current = nodeStack.top();
                nodeStack.pop();
            } else {
                current = nullptr;
            }
        } else {
            // DFS traversal for k-ary trees
            if (!nodeStack.empty()) {
                Node<T>* node = nodeStack.top();
                nodeStack.pop();
                current = node;

                for (auto it = node->children.rbegin(); it != node->children.rend(); ++it) {
                    if (*it) {
                        nodeStack.push(it->get());
                    }
                }
            } else {
                current = nullptr;
            }
        }
        return *this;
    }

    bool operator!=(const InOrderIterator& other) const {
        return current != other.current;
    }
};

#endif // IN_ORDER_ITERATOR_HPP