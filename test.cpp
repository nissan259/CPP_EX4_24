#define DOCTEST_CONFIG_IMPLEMENT_WITH_MAIN
#include "doctest.h"
#include "tree.hpp"
#include "complex.hpp"
#include <iostream>
#include <string>
#include <vector>
#include <algorithm>

// Basic Operations and Iterators for tree<int>
TEST_CASE("Tree Basic Operations for int") {
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

TEST_CASE("Tree Add More than k Children for int") {
    tree<int> tr(3);
    tr.add_root(1);
    tr.add_sub_node(1, 2);
    tr.add_sub_node(1, 3);
    tr.add_sub_node(1, 4);
    CHECK_THROWS_AS(tr.add_sub_node(1, 5), std::runtime_error); // Should throw an error

    Node<int>* root = tr.getRoot();
    CHECK(root->children[0]->value == 2);
    CHECK(root->children[1]->value == 3);
    CHECK(root->children[2]->value == 4);
}

// Iterator Tests for tree<int>
TEST_CASE("BFS Iterator for int") {
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

TEST_CASE("DFS Iterator for int") {
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

TEST_CASE("Pre-Order Iterator for int") {
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


TEST_CASE("In-Order Iterator for int") {
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

TEST_CASE("Heap Iterator for int") {
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
TEST_CASE("Heap Iterator for int") {
    tree<int> tr(2);
    tr.add_root(5);
    tr.add_sub_node(5, 3);
    tr.add_sub_node(5, 8);
    tr.add_sub_node(3, 1);
    tr.add_sub_node(3, 2);

    std::vector<int> heap_order = {1, 2, 3, 5, 8};
    int i = 0;
    for (auto it = tr.begin_heap(); it != tr.end_heap(); ++it) {
        CHECK(*it == heap_order[i]);
        ++i;
    }
}


// Basic Operations and Iterators for tree<double>
TEST_CASE("Tree Basic Operations for double") {
    tree<double> tr(3);
    tr.add_root(1.1);
    CHECK(tr.getRoot()->value == 1.1);
    tr.add_sub_node(1.1, 2.2);
    tr.add_sub_node(1.1, 3.3);
    tr.add_sub_node(1.1, 4.4);

    Node<double>* root = tr.getRoot();
    CHECK(root->children[0]->value == 2.2);
    CHECK(root->children[1]->value == 3.3);
    CHECK(root->children[2]->value == 4.4);
}

// Iterator Tests for tree<double>
TEST_CASE("BFS Iterator for double") {
    tree<double> tr(3);
    tr.add_root(1.1);
    tr.add_sub_node(1.1, 2.2);
    tr.add_sub_node(1.1, 3.3);
    tr.add_sub_node(1.1, 4.4);
    tr.add_sub_node(2.2, 5.5);
    tr.add_sub_node(2.2, 6.6);

    std::vector<double> bfs_order = {1.1, 2.2, 3.3, 4.4, 5.5, 6.6};
    int i = 0;
    for (auto it = tr.begin_bfs_scan(); it != tr.end_bfs_scan(); ++it) {
        CHECK(*it == bfs_order[i]);
        ++i;
    }
}

TEST_CASE("DFS Iterator for double") {
    tree<double> tr(3);
    tr.add_root(1.1);
    tr.add_sub_node(1.1, 2.2);
    tr.add_sub_node(1.1, 3.3);
    tr.add_sub_node(1.1, 4.4);
    tr.add_sub_node(2.2, 5.5);
    tr.add_sub_node(2.2, 6.6);

    std::vector<double> dfs_order = {1.1, 2.2, 5.5, 6.6, 3.3, 4.4};
    int i = 0;
    for (auto it = tr.begin_dfs_scan(); it != tr.end_dfs_scan(); ++it) {
        CHECK(*it == dfs_order[i]);
        ++i;
    }
}

TEST_CASE("Pre-Order Iterator for double") {
    tree<double> tr(3);
    tr.add_root(1.1);
    tr.add_sub_node(1.1, 2.2);
    tr.add_sub_node(1.1, 3.3);
    tr.add_sub_node(1.1, 4.4);
    tr.add_sub_node(2.2, 5.5);
    tr.add_sub_node(2.2, 6.6);

    std::vector<double> pre_order = {1.1, 2.2, 5.5, 6.6, 3.3, 4.4};
    int i = 0;
    for (auto it = tr.begin_pre_order(); it != tr.end_pre_order(); ++it) {
        CHECK(*it == pre_order[i]);
        ++i;
    }
}



TEST_CASE("Heap Iterator for double") {
    tree<double> tr(3);
    tr.add_root(5.5);
    tr.add_sub_node(5.5, 3.3);
    tr.add_sub_node(5.5, 8.8);
    tr.add_sub_node(5.5, 7.7);
    tr.add_sub_node(3.3, 1.1);
    tr.add_sub_node(3.3, 2.2);

    std::vector<double> heap_order = {1.1, 2.2, 3.3, 5.5, 7.7, 8.8};
    int i = 0;
    for (auto it = tr.begin_heap(); it != tr.end_heap(); ++it) {
        CHECK(*it == heap_order[i]);
        ++i;
    }
}

// Basic Operations and Iterators for tree<Complex>
TEST_CASE("Tree Basic Operations for Complex") {
    tree<Complex> tr(3);
    tr.add_root(Complex(1, 1));
    CHECK(tr.getRoot()->value == Complex(1, 1));
    tr.add_sub_node(Complex(1, 1), Complex(2, 2));
    tr.add_sub_node(Complex(1, 1), Complex(3, 3));
    tr.add_sub_node(Complex(1, 1), Complex(4, 4));

    Node<Complex>* root = tr.getRoot();
    CHECK(root->children[0]->value == Complex(2, 2));
    CHECK(root->children[1]->value == Complex(3, 3));
    CHECK(root->children[2]->value == Complex(4, 4));
}

TEST_CASE("Tree Add More than k Children for Complex") {
    tree<Complex> tr(3);
    tr.add_root(Complex(1, 1));
    tr.add_sub_node(Complex(1, 1), Complex(2, 2));
    tr.add_sub_node(Complex(1, 1), Complex(3, 3));
    tr.add_sub_node(Complex(1, 1), Complex(4, 4));
    CHECK_THROWS_AS(tr.add_sub_node(Complex(1, 1), Complex(5, 5)), std::runtime_error); // Should throw an error

    Node<Complex>* root = tr.getRoot();
    CHECK(root->children[0]->value == Complex(2, 2));
    CHECK(root->children[1]->value == Complex(3, 3));
    CHECK(root->children[2]->value == Complex(4, 4));
}

// Iterator Tests for tree<Complex>
TEST_CASE("BFS Iterator for Complex") {
    tree<Complex> tr(3);
    tr.add_root(Complex(1, 1));
    tr.add_sub_node(Complex(1, 1), Complex(2, 2));
    tr.add_sub_node(Complex(1, 1), Complex(3, 3));
    tr.add_sub_node(Complex(1, 1), Complex(4, 4));
    tr.add_sub_node(Complex(2, 2), Complex(5, 5));
    tr.add_sub_node(Complex(2, 2), Complex(6, 6));

    std::vector<Complex> bfs_order = {Complex(1, 1), Complex(2, 2), Complex(3, 3), Complex(4, 4), Complex(5, 5), Complex(6, 6)};
    int i = 0;
    for (auto it = tr.begin_bfs_scan(); it != tr.end_bfs_scan(); ++it) {
        CHECK(*it == bfs_order[i]);
        ++i;
    }
}

TEST_CASE("DFS Iterator for Complex") {
    tree<Complex> tr(3);
    tr.add_root(Complex(1, 1));
    tr.add_sub_node(Complex(1, 1), Complex(2, 2));
    tr.add_sub_node(Complex(1, 1), Complex(3, 3));
    tr.add_sub_node(Complex(1, 1), Complex(4, 4));
    tr.add_sub_node(Complex(2, 2), Complex(5, 5));
    tr.add_sub_node(Complex(2, 2), Complex(6, 6));

    std::vector<Complex> dfs_order = {Complex(1, 1), Complex(2, 2), Complex(5, 5), Complex(6, 6), Complex(3, 3), Complex(4, 4)};
    int i = 0;
    for (auto it = tr.begin_dfs_scan(); it != tr.end_dfs_scan(); ++it) {
        CHECK(*it == dfs_order[i]);
        ++i;
    }
}

TEST_CASE("Pre-Order Iterator for Complex") {
    tree<Complex> tr(3);
    tr.add_root(Complex(1, 1));
    tr.add_sub_node(Complex(1, 1), Complex(2, 2));
    tr.add_sub_node(Complex(1, 1), Complex(3, 3));
    tr.add_sub_node(Complex(1, 1), Complex(4, 4));
    tr.add_sub_node(Complex(2, 2), Complex(5, 5));
    tr.add_sub_node(Complex(2, 2), Complex(6, 6));

    std::vector<Complex> pre_order = {Complex(1, 1), Complex(2, 2), Complex(5, 5), Complex(6, 6), Complex(3, 3), Complex(4, 4)};
    int i = 0;
    for (auto it = tr.begin_pre_order(); it != tr.end_pre_order(); ++it) {
        CHECK(*it == pre_order[i]);
        ++i;
    }
}



TEST_CASE("Heap Iterator for Complex") {
    tree<Complex> tr(3);
    tr.add_root(Complex(5, 5));
    tr.add_sub_node(Complex(5, 5), Complex(3, 3));
    tr.add_sub_node(Complex(5, 5), Complex(8, 8));
    tr.add_sub_node(Complex(5, 5), Complex(7, 7));
    tr.add_sub_node(Complex(3, 3), Complex(1, 1));
    tr.add_sub_node(Complex(3, 3), Complex(2, 2));

    std::vector<Complex> heap_order = {Complex(1, 1), Complex(2, 2), Complex(3, 3), Complex(5, 5), Complex(7, 7), Complex(8, 8)};
    int i = 0;
    for (auto it = tr.begin_heap(); it != tr.end_heap(); ++it) {
        CHECK(*it == heap_order[i]);
        ++i;
    }
}
TEST_CASE("Post-Order Iterator for int") {
    tree<int> tr(2);
    tr.add_root(1);
    tr.add_sub_node(1, 2); // Left child of root
    tr.add_sub_node(1, 3); // Right child of root
    tr.add_sub_node(2, 4); // Left child of node 2
    tr.add_sub_node(2, 5); // Right child of node 2
    tr.add_sub_node(3, 6); // Left child of node 3
    tr.add_sub_node(3, 7); // Right child of node 3

    std::vector<int> post_order = {4, 5, 2, 6, 7, 3, 1};
    int i = 0;
    for (auto it = tr.begin_post_order(); it != tr.end_post_order(); ++it) {
        CHECK(*it == post_order[i]);
        ++i;
    }
}

// Post-Order Iterator Tests for tree<double>
TEST_CASE("Post-Order Iterator for double") {
    tree<double> tr(2);
    tr.add_root(1.1);
    tr.add_sub_node(1.1, 2.2); // Left child of root
    tr.add_sub_node(1.1, 3.3); // Right child of root
    tr.add_sub_node(2.2, 4.4); // Left child of node 2
    tr.add_sub_node(2.2, 5.5); // Right child of node 2
    tr.add_sub_node(3.3, 6.6); // Left child of node 3
    tr.add_sub_node(3.3, 7.7); // Right child of node 3

    std::vector<double> post_order = {4.4, 5.5, 2.2, 6.6, 7.7, 3.3, 1.1};
    int i = 0;
    for (auto it = tr.begin_post_order(); it != tr.end_post_order(); ++it) {
        CHECK(*it == post_order[i]);
        ++i;
    }
}

// Post-Order Iterator Tests for tree<Complex>
TEST_CASE("Post-Order Iterator for Complex") {
    tree<Complex> tr(2);
    tr.add_root(Complex(1, 1));
    tr.add_sub_node(Complex(1, 1), Complex(2, 2)); // Left child of root
    tr.add_sub_node(Complex(1, 1), Complex(3, 3)); // Right child of root
    tr.add_sub_node(Complex(2, 2), Complex(4, 4)); // Left child of node 2
    tr.add_sub_node(Complex(2, 2), Complex(5, 5)); // Right child of node 2
    tr.add_sub_node(Complex(3, 3), Complex(6, 6)); // Left child of node 3
    tr.add_sub_node(Complex(3, 3), Complex(7, 7)); // Right child of node 3

    std::vector<Complex> post_order = {Complex(4, 4), Complex(5, 5), Complex(2, 2), Complex(6, 6), Complex(7, 7), Complex(3, 3), Complex(1, 1)};
    int i = 0;
    for (auto it = tr.begin_post_order(); it != tr.end_post_order(); ++it) {
        CHECK(*it == post_order[i]);
        ++i;
    }
}

// Pre-Order Iterator Tests for tree<int> with k=3
TEST_CASE("Pre-Order Iterator for k-3 Tree") {
    tree<int> tr(3);
    tr.add_root(1);
    tr.add_sub_node(1, 2);
    tr.add_sub_node(1, 3);
    tr.add_sub_node(1, 4);
    tr.add_sub_node(2, 5);
    tr.add_sub_node(2, 6);
    tr.add_sub_node(3, 7);
    tr.add_sub_node(3, 8);
    tr.add_sub_node(4, 9);
    tr.add_sub_node(4, 10);

    std::vector<int> pre_order = {1, 2, 5, 6, 3, 7, 8, 4, 9, 10};
    int i = 0;
    for (auto it = tr.begin_pre_order(); it != tr.end_pre_order(); ++it) {
        CHECK(*it == pre_order[i]);
        ++i;
    }
}
