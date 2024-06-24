#ifndef POST_ORDER_ITERATOR_HPP
#define POST_ORDER_ITERATOR_HPP

#include <stack>
#include "node.hpp"

template <typename T>
class PostOrderIterator {
private:
    std::stack<Node<T>*> nodeStack;
    Node<T>* current;
    int k;

    void pushLeftmostPath(Node<T>* node) {
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
    PostOrderIterator(Node<T>* root, int k) : current(nullptr), k(k) {
        if (root) {
            if (k == 2) {
                // Post-order traversal for binary trees
                pushLeftmostPath(root);
            } else {
                // DFS for k-ary trees
                nodeStack.push(root);
            }
        }
        ++(*this); // Move to the first valid node
    }

    T& operator*() {
        return current->value;
    }

    PostOrderIterator& operator++() {
        if (k == 2) {
            // Post-order traversal for binary trees
            if (!nodeStack.empty()) {
                Node<T>* node = nodeStack.top();
                nodeStack.pop();
                if (!nodeStack.empty()) {
                    Node<T>* parent = nodeStack.top();
                    if (parent->children.size() > 1 && node == parent->children[0].get()) {
                        pushLeftmostPath(parent->children[1].get());
                    }
                }
                current = node;
            } else {
                current = nullptr;
            }
        } else {
            // DFS for k-ary trees
            if (!nodeStack.empty()) {
                Node<T>* node = nodeStack.top();
                nodeStack.pop();
                for (auto it = node->children.rbegin(); it != node->children.rend(); ++it) {
                    if (*it) {
                        nodeStack.push(it->get());
                    }
                }
                current = node;
            } else {
                current = nullptr;
            }
        }
        return *this;
    }

    bool operator!=(const PostOrderIterator& other) const {
        return current != other.current;
    }
};

#endif // POST_ORDER_ITERATOR_HPP