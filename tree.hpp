#ifndef TREE_HPP
#define TREE_HPP

#include "node.hpp"
#include "bfs_iterator.hpp"
#include "dfs_iterator.hpp"
#include "pre_order_iterator.hpp"
#include "post_order_iterator.hpp"
#include "in_order_iterator.hpp"
#include "heap_iterator.hpp"
#include <queue>
#include <vector>
#include <algorithm>
#include <stdexcept>

template <typename T>
class tree {
private:
    std::unique_ptr<Node<T>> root;
    int k;

    void collectNodes(Node<T>* node, std::vector<Node<T>*>& nodes);
    void buildHeapTree(std::vector<Node<T>*>& nodes);
    void rebuildHeap(Node<T>* node, std::vector<Node<T>*>& nodes, int index);

public:
    tree(int k = 2);

    void add_root(const T& value);
    void add_sub_node(const T& parent_value, const T& child_value);
    Node<T>* getRoot() const { return root.get(); }

    BFSIterator<T> begin_bfs_scan();
    BFSIterator<T> end_bfs_scan();
    DFSIterator<T> begin_dfs_scan();
    DFSIterator<T> end_dfs_scan();
    PreOrderIterator<T> begin_pre_order();
    PreOrderIterator<T> end_pre_order();
    PostOrderIterator<T> begin_post_order();
    PostOrderIterator<T> end_post_order();
    InOrderIterator<T> begin_in_order();
    InOrderIterator<T> end_in_order();
    HeapIterator<T> begin_heap();
    HeapIterator<T> end_heap();

    ~tree();
};

template <typename T>
tree<T>::tree(int k) : root(nullptr), k(k) {}

template <typename T>
void tree<T>::add_root(const T& value) {
    root = std::make_unique<Node<T>>(value, k);
}

template <typename T>
void tree<T>::add_sub_node(const T& parent_value, const T& child_value) {
    if (!root) {
        throw std::runtime_error("Tree is empty");
    }

    std::queue<Node<T>*> q;
    q.push(root.get());

    while (!q.empty()) {
        Node<T>* node = q.front();
        q.pop();

        if (node->value == parent_value) {
            for (int i = 0; i < k; ++i) {
                if (!node->children[i]) {
                    node->children[i] = std::make_unique<Node<T>>(child_value, k);
                    return;
                }
            }
            throw std::runtime_error("All child nodes are occupied");
        }

        for (auto& child : node->children) {
            if (child) {
                q.push(child.get());
            }
        }
    }

    throw std::runtime_error("Parent node not found");
}

template <typename T>
BFSIterator<T> tree<T>::begin_bfs_scan() {
    return BFSIterator<T>(root.get());
}

template <typename T>
BFSIterator<T> tree<T>::end_bfs_scan() {
    return BFSIterator<T>(nullptr);
}

template <typename T>
DFSIterator<T> tree<T>::begin_dfs_scan() {
    return DFSIterator<T>(root.get());
}

template <typename T>
DFSIterator<T> tree<T>::end_dfs_scan() {
    return DFSIterator<T>(nullptr);
}

template <typename T>
PreOrderIterator<T> tree<T>::begin_pre_order() {
    return PreOrderIterator<T>(root.get());
}

template <typename T>
PreOrderIterator<T> tree<T>::end_pre_order() {
    return PreOrderIterator<T>(nullptr);
}

template <typename T>
PostOrderIterator<T> tree<T>::begin_post_order() {
    return PostOrderIterator<T>(root.get());
}

template <typename T>
PostOrderIterator<T> tree<T>::end_post_order() {
    return PostOrderIterator<T>(nullptr);
}

template <typename T>
InOrderIterator<T> tree<T>::begin_in_order() {
    return InOrderIterator<T>(root.get());
}

template <typename T>
InOrderIterator<T> tree<T>::end_in_order() {
    return InOrderIterator<T>(nullptr);
}

template <typename T>
HeapIterator<T> tree<T>::begin_heap() {
    return HeapIterator<T>(root.get());
}

template <typename T>
HeapIterator<T> tree<T>::end_heap() {
    return HeapIterator<T>(nullptr);
}

template <typename T>
tree<T>::~tree() {
    // Unique pointers will handle the cleanup
}

#endif // TREE_HPP