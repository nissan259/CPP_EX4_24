#define DOCTEST_CONFIG_IMPLEMENT_WITH_MAIN
#include "doctest.h"
#include "tree.hpp"
#include <iostream>
#include <string>
#include <vector>
#include <algorithm>

TEST_CASE("Tree Basic Operations") {
    tree<int> tr(3);
    tr.add_root(1);
    CHECK(tr.getRoot()->value == 1);
    tr.add_sub_node(1, 2);
    tr.add_sub_node(1, 3);
    tr.add_sub_node(1, 4);

    Node<int>* root = tr.getRoot();
    CHECK(root->children[0]->value == 2);
    CHECK(root->children[1]->value == 3);
    CHECK(root->children[2]->value == 4);
}

TEST_CASE("BFS Iterator") {
    tree<int> tr(3);
    tr.add_root(1);
    tr.add_sub_node(1, 2);
    tr.add_sub_node(1, 3);
    tr.add_sub_node(1, 4);
    tr.add_sub_node(2, 5);
    tr.add_sub_node(2, 6);

    std::vector<int> bfs_order = {1, 2, 3, 4, 5, 6};
    int i = 0;
    for (auto it = tr.begin_bfs_scan(); it != tr.end_bfs_scan(); ++it) {
        CHECK(*it == bfs_order[i]);
        ++i;
    }
}

TEST_CASE("DFS Iterator") {
    tree<int> tr(3);
    tr.add_root(1);
    tr.add_sub_node(1, 2);
    tr.add_sub_node(1, 3);
    tr.add_sub_node(1, 4);
    tr.add_sub_node(2, 5);
    tr.add_sub_node(2, 6);

    std::vector<int> dfs_order = {1, 2, 5, 6, 3, 4};
    int i = 0;
    for (auto it = tr.begin_dfs_scan(); it != tr.end_dfs_scan(); ++it) {
        CHECK(*it == dfs_order[i]);
        ++i;
    }
}

TEST_CASE("Pre-Order Iterator") {
    tree<int> tr(3);
    tr.add_root(1);
    tr.add_sub_node(1, 2);
    tr.add_sub_node(1, 3);
    tr.add_sub_node(1, 4);
    tr.add_sub_node(2, 5);
    tr.add_sub_node(2, 6);

    std::vector<int> pre_order = {1, 2, 5, 6, 3, 4};
    int i = 0;
    for (auto it = tr.begin_pre_order(); it != tr.end_pre_order(); ++it) {
        CHECK(*it == pre_order[i]);
        ++i;
    }
}

TEST_CASE("Post-Order Iterator") {
    tree<int> tr(3);
    tr.add_root(1);
    tr.add_sub_node(1, 2);
    tr.add_sub_node(1, 3);
    tr.add_sub_node(1, 4);
    tr.add_sub_node(2, 5);
    tr.add_sub_node(2, 6);

    std::vector<int> post_order = {5, 6, 2, 3, 4, 1};
    int i = 0;
    for (auto it = tr.begin_post_order(); it != tr.end_post_order(); ++it) {
        CHECK(*it == post_order[i]);
        ++i;
    }
}

TEST_CASE("In-Order Iterator") {
    tree<int> tr(2);
    tr.add_root(1);
    tr.add_sub_node(1, 2);
    tr.add_sub_node(1, 3);
    tr.add_sub_node(2, 4);
    tr.add_sub_node(2, 5);

    std::vector<int> in_order = {4, 2, 5, 1, 3};
    int i = 0;
    for (auto it = tr.begin_in_order(); it != tr.end_in_order(); ++it) {
        CHECK(*it == in_order[i]);
        ++i;
    }
}

TEST_CASE("Heap Iterator") {
    tree<int> tr(3);
    tr.add_root(5);
    tr.add_sub_node(5, 3);
    tr.add_sub_node(5, 8);
    tr.add_sub_node(5, 7);
    tr.add_sub_node(3, 1);
    tr.add_sub_node(3, 2);

    std::vector<int> heap_order = {1, 2, 3, 5, 7, 8};
    int i = 0;
    for (auto it = tr.begin_heap(); it != tr.end_heap(); ++it) {
        CHECK(*it == heap_order[i]);
        ++i;
    }
}

TEST_CASE("4-tree Basic Operations and Iterators") {
    tree<int> tr(4);
    tr.add_root(10);
    tr.add_sub_node(10, 20);
    tr.add_sub_node(10, 30);
    tr.add_sub_node(10, 40);
    tr.add_sub_node(10, 50);
    tr.add_sub_node(20, 60);
    tr.add_sub_node(20, 70);
    tr.add_sub_node(20, 80);
    tr.add_sub_node(20, 90);

    Node<int>* root = tr.getRoot();
    CHECK(root->value == 10);
    CHECK(root->children[0]->value == 20);
    CHECK(root->children[1]->value == 30);
    CHECK(root->children[2]->value == 40);
    CHECK(root->children[3]->value == 50);

    std::vector<int> bfs_order = {10, 20, 30, 40, 50, 60, 70, 80, 90};
    int i = 0;
    for (auto it = tr.begin_bfs_scan(); it != tr.end_bfs_scan(); ++it) {
        CHECK(*it == bfs_order[i]);
        ++i;
    }

    std::vector<int> dfs_order = {10, 20, 60, 70, 80, 90, 30, 40, 50};
    i = 0;
    for (auto it = tr.begin_dfs_scan(); it != tr.end_dfs_scan(); ++it) {
        CHECK(*it == dfs_order[i]);
        ++i;
    }

    std::vector<int> pre_order = {10, 20, 60, 70, 80, 90, 30, 40, 50};
    i = 0;
    for (auto it = tr.begin_pre_order(); it != tr.end_pre_order(); ++it) {
        CHECK(*it == pre_order[i]);
        ++i;
    }

    std::vector<int> post_order = {60, 70, 80, 90, 20, 30, 40, 50, 10};
    i = 0;
    for (auto it = tr.begin_post_order(); it != tr.end_post_order(); ++it) {
        CHECK(*it == post_order[i]);
        ++i;
    }

    std::vector<int> heap_order = {10, 20, 30, 40, 50, 60, 70, 80, 90};
    std::sort(heap_order.begin(), heap_order.end());
    i = 0;
    for (auto it = tr.begin_heap(); it != tr.end_heap(); ++it) {
        CHECK(*it == heap_order[i]);
        ++i;
    }
}

TEST_CASE("5-tree Basic Operations and Iterators") {
    tree<int> tr(5);
    tr.add_root(15);
    tr.add_sub_node(15, 25);
    tr.add_sub_node(15, 35);
    tr.add_sub_node(15, 45);
    tr.add_sub_node(15, 55);
    tr.add_sub_node(15, 65);
    tr.add_sub_node(25, 75);
    tr.add_sub_node(25, 85);
    tr.add_sub_node(25, 95);
    tr.add_sub_node(25, 105);
    tr.add_sub_node(25, 115);

    Node<int>* root = tr.getRoot();
    CHECK(root->value == 15);
    CHECK(root->children[0]->value == 25);
    CHECK(root->children[1]->value == 35);
    CHECK(root->children[2]->value == 45);
    CHECK(root->children[3]->value == 55);
    CHECK(root->children[4]->value == 65);

    std::vector<int> bfs_order = {15, 25, 35, 45, 55, 65, 75, 85, 95, 105, 115};
    int i = 0;
    for (auto it = tr.begin_bfs_scan(); it != tr.end_bfs_scan(); ++it) {
        CHECK(*it == bfs_order[i]);
        ++i;
    }

    std::vector<int> dfs_order = {15, 25, 75, 85, 95, 105, 115, 35, 45, 55, 65};
    i = 0;
    for (auto it = tr.begin_dfs_scan(); it != tr.end_dfs_scan(); ++it) {
        CHECK(*it == dfs_order[i]);
        ++i;
    }

    std::vector<int> pre_order = {15, 25, 75, 85, 95, 105, 115, 35, 45, 55, 65};
    i = 0;
    for (auto it = tr.begin_pre_order(); it != tr.end_pre_order(); ++it) {
        CHECK(*it == pre_order[i]);
        ++i;
    }

    std::vector<int> post_order = {75, 85, 95, 105, 115, 25, 35, 45, 55, 65, 15};
    i = 0;
    for (auto it = tr.begin_post_order(); it != tr.end_post_order(); ++it) {
        CHECK(*it == post_order[i]);
        ++i;
    }

    std::vector<int> heap_order = {15, 25, 35, 45, 55, 65, 75, 85, 95, 105, 115};
    std::sort(heap_order.begin(), heap_order.end());
    i = 0;
    for (auto it = tr.begin_heap(); it != tr.end_heap(); ++it) {
        CHECK(*it == heap_order[i]);
        ++i;
    }
}
