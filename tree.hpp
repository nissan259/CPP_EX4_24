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

public:
    tree(int k = 2) : root(nullptr), k(k) {}

    void add_root(const T& value) {
        root = std::make_unique<Node<T>>(value, k);
    }

    void add_sub_node(const T& parent_value, const T& child_value) {
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

    Node<T>* getRoot() const { return root.get(); }

    BFSIterator<T> begin_bfs_scan() {
        return BFSIterator<T>(root.get());
    }

    BFSIterator<T> end_bfs_scan() {
        return BFSIterator<T>(nullptr);
    }

    DFSIterator<T> begin_dfs_scan() {
        return DFSIterator<T>(root.get());
    }

    DFSIterator<T> end_dfs_scan() {
        return DFSIterator<T>(nullptr);
    }

    PreOrderIterator<T> begin_pre_order() {
        return PreOrderIterator<T>(root.get());
    }

    PreOrderIterator<T> end_pre_order() {
        return PreOrderIterator<T>(nullptr);
    }

    PostOrderIterator<T> begin_post_order() {
        return PostOrderIterator<T>(root.get(), k);
    }

    PostOrderIterator<T> end_post_order() {
        return PostOrderIterator<T>(nullptr, k);
    }

    InOrderIterator<T> begin_in_order() {
        return InOrderIterator<T>(root, k);
    }

    InOrderIterator<T> end_in_order() {
        return InOrderIterator<T>(nullptr, k);
    }

    HeapIterator<T> begin_heap() {
        return HeapIterator<T>(root.get(), k);
    }

    HeapIterator<T> end_heap() {
        return HeapIterator<T>(nullptr, k);
    }

    ~tree() = default;
};

#endif // TREE_HPP