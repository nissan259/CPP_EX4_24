#ifndef HEAP_ITERATOR_HPP
#define HEAP_ITERATOR_HPP

#include "node.hpp"
#include <vector>
#include <algorithm>
#include <iostream>

template <typename T>
class HeapIterator {
private:
    std::vector<Node<T>*> heap; // Vector storing node pointers in heap order

    struct CompareNodes {
        bool operator()(const Node<T>* a, const Node<T>* b) const {
            return a->value > b->value;
        }
    };

    void collectNodes(Node<T>* node) {
        if (node) {
            heap.push_back(node);
            for (auto& child : node->children) {
                if (child) {
                    collectNodes(child.get());
                }
            }
        }
    }

public:
    HeapIterator(Node<T>* root, int k) {
        if (k == 2) {
            if (root) {
                collectNodes(root);
                std::make_heap(heap.begin(), heap.end(), CompareNodes());
            }
        } else if (k > 2) {
            std::cout << "Warning: HeapIterator is only supported for binary trees (k = 2). The iterator will be empty." << std::endl;
        }
    }

    HeapIterator(const HeapIterator& other) : heap(other.heap) {}

    T& operator*() const {
        return heap.front()->value;
    }

    T* operator->() const {
        return &(heap.front()->value);
    }

    HeapIterator& operator++() {
        std::pop_heap(heap.begin(), heap.end(), CompareNodes());
        heap.pop_back();
        return *this;
    }

    bool operator==(const HeapIterator& other) const {
        return heap == other.heap;
    }

    bool operator!=(const HeapIterator& other) const {
        return !(*this == other);
    }

    HeapIterator& operator=(const HeapIterator& other) {
        if (this != &other) {
            heap = other.heap;
        }
        return *this;
    }
};

#endif // HEAP_ITERATOR_HPP