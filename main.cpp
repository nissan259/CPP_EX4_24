#include "tree.hpp"
#include <iostream>
#include <string>
#include <algorithm>
#include <vector>
#include <SFML/Graphics.hpp>

using namespace std;

int main() {
    // Create a ternary tree (k=3)
    tree<int> ktree(3);

    ktree.add_root(1);
    ktree.add_sub_node(1, 2);
    ktree.add_sub_node(1, 3);
    ktree.add_sub_node(1, 4);
    ktree.add_sub_node(2, 5);
    ktree.add_sub_node(2, 6);
    ktree.add_sub_node(3, 7);

    cout << "Pre-order Traversal (Ternary): ";
    for (auto it = ktree.begin_pre_order(); it != ktree.end_pre_order(); ++it) {
        cout << *it << " ";
    }
    cout << endl;

    cout << "Post-order Traversal (Ternary): ";
    for (auto it = ktree.begin_post_order(); it != ktree.end_post_order(); ++it) {
        cout << *it << " ";
    }
    cout << endl;

    cout << "In-order Traversal (Ternary): ";
    for (auto it = ktree.begin_in_order(); it != ktree.end_in_order(); ++it) {
        cout << *it << " ";
    }
    cout << endl;

    cout << "BFS Traversal (Ternary): ";
    for (auto it = ktree.begin_bfs_scan(); it != ktree.end_bfs_scan(); ++it) {
        cout << *it << " ";
    }
    cout << endl;

    cout << "DFS Traversal (Ternary): ";
    for (auto it = ktree.begin_dfs_scan(); it != ktree.end_dfs_scan(); ++it) {
        cout << *it << " ";
    }
    cout << endl;

    // Create a binary tree (k=2)
    tree<int> btree(2);

    btree.add_root(7);
    btree.add_sub_node(7, 10);
    btree.add_sub_node(7, 3);
    btree.add_sub_node(10, 4);
    btree.add_sub_node(10, 8);

    cout << "Pre-order Traversal (Binary): ";
    for (auto it = btree.begin_pre_order(); it != btree.end_pre_order(); ++it) {
        cout << *it << " ";
    }
    cout << endl;

    cout << "Post-order Traversal (Binary): ";
    for (auto it = btree.begin_post_order(); it != btree.end_post_order(); ++it) {
        cout << *it << " ";
    }
    cout << endl;

    cout << "In-order Traversal (Binary): ";
    for (auto it = btree.begin_in_order(); it != btree.end_in_order(); ++it) {
        cout << *it << " ";
    }
    cout << endl;

    cout << "BFS Traversal (Binary): ";
    for (auto it = btree.begin_bfs_scan(); it != btree.end_bfs_scan(); ++it) {
        cout << *it << " ";
    }
    cout << endl;

    cout << "DFS Traversal (Binary): ";
    for (auto it = btree.begin_dfs_scan(); it != btree.end_dfs_scan(); ++it) {
        cout << *it << " ";
    }
    cout << endl;

    // Collect heap values
    vector<int> heap_values;
    for (auto it = btree.begin_heap(); it != btree.end_heap(); ++it) {
        heap_values.push_back(*it);
    }

    // Sort values in ascending order
    sort(heap_values.begin(), heap_values.end());

    // Print heap values in ascending order
    cout << "Heap Traversal: ";
    for (const auto& val : heap_values) {
        cout << val << " ";
    }
    cout << endl;

    // Additional scenario: Adding more nodes to the binary tree
    btree.add_sub_node(4, 1);
    btree.add_sub_node(4, 6);

    cout << "Updated BFS Traversal (Binary): ";
    for (auto it = btree.begin_bfs_scan(); it != btree.end_bfs_scan(); ++it) {
        cout << *it << " ";
    }
    cout << endl;

    cout << "Updated DFS Traversal (Binary): ";
    for (auto it = btree.begin_dfs_scan(); it != btree.end_dfs_scan(); ++it) {
        cout << *it << " ";
    }
    cout << endl;

    // Collect updated heap values
    heap_values.clear();
    for (auto it = btree.begin_heap(); it != btree.end_heap(); ++it) {
        heap_values.push_back(*it);
    }

    // Sort updated values in ascending order
    sort(heap_values.begin(), heap_values.end());

    // Print updated heap values in ascending order
    cout << "Updated Heap Traversal: ";
    for (const auto& val : heap_values) {
        cout << val << " ";
    }
    cout << endl;

    return 0;
}
