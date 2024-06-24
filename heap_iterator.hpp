#ifndef HEAP_ITERATOR_HPP
#define HEAP_ITERATOR_HPP

#include <vector>
#include <algorithm>
#include "node.hpp"

template <typename T>
class HeapIterator {
public:
    HeapIterator(Node<T>* root);
    T& operator*();
    HeapIterator<T>& operator++();
    bool operator!=(const HeapIterator<T>& other) const;

private:
    std::vector<Node<T>*> nodes;
    size_t current;
    void buildHeap(Node<T>* node);
    void heapify();
};

template <typename T>
HeapIterator<T>::HeapIterator(Node<T>* root) : current(0) {
    if (root) {
        buildHeap(root);
        heapify();
    }
}

template <typename T>
void HeapIterator<T>::buildHeap(Node<T>* node) {
    if (!node) return;
    nodes.push_back(node);
    for (auto& child : node->children) {
        buildHeap(child.get());
    }
}

template <typename T>
void HeapIterator<T>::heapify() {
    std::make_heap(nodes.begin(), nodes.end(), [](Node<T>* a, Node<T>* b) { return a->value > b->value; }); // Min-heap
    std::sort_heap(nodes.begin(), nodes.end(), [](Node<T>* a, Node<T>* b) { return a->value > b->value; }); // Min-heap
}

template <typename T>
T& HeapIterator<T>::operator*() {
    return nodes[current]->value;
}

template <typename T>
HeapIterator<T>& HeapIterator<T>::operator++() {
    if (current < nodes.size()) {
        ++current;
    }
    return *this;
}

template <typename T>
bool HeapIterator<T>::operator!=(const HeapIterator<T>& other) const {
    return current != other.current;
}

#endif // HEAP_ITERATOR_HPP
