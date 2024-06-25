#include "tree.hpp"
#include "complex.hpp"
#include <iostream>
#include <string>
#include <algorithm>
#include <vector>
#include <SFML/Graphics.hpp>
#include <cmath> 
#include <sstream> 

using namespace std;

// Template function to draw the tree nodes and edges
template <typename T>
void drawTree(sf::RenderWindow &window, Node<T>* node, sf::Vector2f position, float horizontalSpacing, float verticalSpacing) {
    if (!node) return;

    sf::CircleShape circle(20);
    circle.setFillColor(sf::Color(100, 100, 255)); 
    circle.setPosition(position.x - circle.getRadius(), position.y - circle.getRadius()); 
    window.draw(circle);

    // Draw value in the node
    sf::Font font;
    if (!font.loadFromFile("/usr/share/fonts/truetype/dejavu/DejaVuSans-Bold.ttf")) {
        cerr << "Could not load font" << endl;
        return;
    }
    sf::Text text;
    text.setFont(font);

    std::ostringstream oss;
    oss << node->value;
    text.setString(oss.str());
    
    text.setCharacterSize(14); 
    text.setFillColor(sf::Color(255, 255, 255)); 
    sf::FloatRect textRect = text.getLocalBounds();
    text.setOrigin(textRect.left + textRect.width / 2.0f, textRect.top + textRect.height / 2.0f); 
    text.setPosition(position);
    window.draw(text);

    int childCount = node->children.size();
    float startAngle = -90.0f - (childCount - 1) * 15.0f; 

    for (int i = 0; i < childCount; ++i) {
        auto& child = node->children[i];
        if (child) {
            float angle = startAngle + i * 30.0f; 
            float radianAngle = angle * M_PI / 180.0f;
            sf::Vector2f childPos = position + sf::Vector2f(cos(radianAngle) * horizontalSpacing, verticalSpacing);
            sf::Vertex line[] = {
                sf::Vertex(position + sf::Vector2f(0, 20)),
                sf::Vertex(childPos + sf::Vector2f(0, -20))
            };
            line->color = sf::Color(255, 165, 0); 
            window.draw(line, 2, sf::Lines);

            drawTree(window, child.get(), childPos, horizontalSpacing / 2.0f, verticalSpacing * 1.2f); 
        }
    }
}

// Template function to calculate the total levels in the tree
template <typename T>
int calculateTotalLevels(Node<T>* node) {
    if (!node) return 0;
    int maxDepth = 0;
    for (auto& child : node->children) {
        maxDepth = max(maxDepth, calculateTotalLevels(child.get()));
    }
    return maxDepth + 1;
}

// Template function to visualize the tree
template <typename T>
void visualizeTree(sf::RenderWindow& window, tree<T>& tree) {
    sf::Font font;
    if (!font.loadFromFile("/usr/share/fonts/truetype/dejavu/DejaVuSans-Bold.ttf")) {
        cerr << "Could not load font" << endl;
        return;
    }

    // Get the root node
    Node<T>* root = tree.getRoot();
    int totalLevels = calculateTotalLevels(root);

    // Calculate position for drawing
    sf::Vector2f startPosition(window.getSize().x / 2, 50);
    float horizontalSpacing = window.getSize().x / (pow(2, totalLevels - 1) + 1) * 2.5; 
    float verticalSpacing = window.getSize().y / (totalLevels + 1) * 1.5; 

    // Draw the tree
    drawTree(window, root, startPosition, horizontalSpacing, verticalSpacing);
}

int main() {
    // Create a binary tree with integers
    tree<int> binaryTree(2);

    binaryTree.add_root(1);
    binaryTree.add_sub_node(1, 2); 
    binaryTree.add_sub_node(1, 3); 
    binaryTree.add_sub_node(2, 4); 
    binaryTree.add_sub_node(2, 5); 
    binaryTree.add_sub_node(3, 6); 
    binaryTree.add_sub_node(3, 7); 

    cout << "Pre-order Traversal (Binary Tree): ";
    for (auto it = binaryTree.begin_pre_order(); it != binaryTree.end_pre_order(); ++it) {
        cout << *it << " ";
    }
    cout << endl;

    cout << "Post-order Traversal (Binary Tree): ";
    for (auto it = binaryTree.begin_post_order(); it != binaryTree.end_post_order(); ++it) {
        cout << *it << " ";
    }
    cout << endl;

    cout << "In-order Traversal (Binary Tree): ";
    for (auto it = binaryTree.begin_in_order(); it != binaryTree.end_in_order(); ++it) {
        cout << *it << " ";
    }
    cout << endl;

    cout << "BFS Traversal (Binary Tree): ";
    for (auto it = binaryTree.begin_bfs_scan(); it != binaryTree.end_bfs_scan(); ++it) {
        cout << *it << " ";
    }
    cout << endl;

    cout << "DFS Traversal (Binary Tree): ";
    for (auto it = binaryTree.begin_dfs_scan(); it != binaryTree.end_dfs_scan(); ++it) {
        cout << *it << " ";
    }
    cout << endl;

    cout << "Heap Traversal (Binary Tree): ";
    for (auto it = binaryTree.begin_heap(); it != binaryTree.end_heap(); ++it) {
        cout << *it << " ";
    }
    cout << endl;

    vector<int> heap_values;
    for (auto it = binaryTree.begin_heap(); it != binaryTree.end_heap(); ++it) {
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

    // Create a binary tree with Complex numbers
    tree<Complex> binaryComplexTree(2);

    binaryComplexTree.add_root(Complex(1, 1));
    binaryComplexTree.add_sub_node(Complex(1, 1), Complex(2, 2)); 
    binaryComplexTree.add_sub_node(Complex(1, 1), Complex(3, 3)); 
    binaryComplexTree.add_sub_node(Complex(2, 2), Complex(4, 4)); 
    binaryComplexTree.add_sub_node(Complex(2, 2), Complex(5, 5)); 
    binaryComplexTree.add_sub_node(Complex(3, 3), Complex(6, 6)); 
    binaryComplexTree.add_sub_node(Complex(3, 3), Complex(7, 7)); 

    cout << "Pre-order Traversal (Binary Complex Tree): ";
    for (auto it = binaryComplexTree.begin_pre_order(); it != binaryComplexTree.end_pre_order(); ++it) {
        cout << *it << " ";
    }
    cout << endl;

    cout << "Post-order Traversal (Binary Complex Tree): ";
    for (auto it = binaryComplexTree.begin_post_order(); it != binaryComplexTree.end_post_order(); ++it) {
        cout << *it << " ";
    }
    cout << endl;

    cout << "In-order Traversal (Binary Complex Tree): ";
    for (auto it = binaryComplexTree.begin_in_order(); it != binaryComplexTree.end_in_order(); ++it) {
        cout << *it << " ";
    }
    cout << endl;

    cout << "BFS Traversal (Binary Complex Tree): ";
    for (auto it = binaryComplexTree.begin_bfs_scan(); it != binaryComplexTree.end_bfs_scan(); ++it) {
        cout << *it << " ";
    }
    cout << endl;

    cout << "DFS Traversal (Binary Complex Tree): ";
    for (auto it = binaryComplexTree.begin_dfs_scan(); it != binaryComplexTree.end_dfs_scan(); ++it) {
        cout << *it << " ";
    }
    cout << endl;

    cout << "Heap Traversal (Binary Complex Tree): ";
    for (auto it = binaryComplexTree.begin_heap(); it != binaryComplexTree.end_heap(); ++it) {
        cout << *it << " ";
    }
    cout << endl;

    // Create a k-3 tree with integers
    tree<int> k3Tree(3);

    k3Tree.add_root(1);
    k3Tree.add_sub_node(1, 2);
    k3Tree.add_sub_node(1, 3);
    k3Tree.add_sub_node(1, 4);
    k3Tree.add_sub_node(2, 5);
    k3Tree.add_sub_node(2, 6);
    k3Tree.add_sub_node(3, 7);
    k3Tree.add_sub_node(3, 8);
    k3Tree.add_sub_node(4, 9);
    k3Tree.add_sub_node(4, 10);

    cout << "Pre-order Traversal (k-3 Tree): ";
    for (auto it = k3Tree.begin_pre_order(); it != k3Tree.end_pre_order(); ++it) {
        cout << *it << " ";
    }
    cout << endl;

    cout << "Post-order Traversal (k-3 Tree): ";
    for (auto it = k3Tree.begin_post_order(); it != k3Tree.end_post_order(); ++it) {
        cout << *it << " ";
    }
    cout << endl;

    cout << "In-order Traversal (k-3 Tree): ";
    for (auto it = k3Tree.begin_in_order(); it != k3Tree.end_in_order(); ++it) {
        cout << *it << " ";
    }
    cout << endl;

    cout << "BFS Traversal (k-3 Tree): ";
    for (auto it = k3Tree.begin_bfs_scan(); it != k3Tree.end_bfs_scan(); ++it) {
        cout << *it << " ";
    }
    cout << endl;

    cout << "DFS Traversal (k-3 Tree): ";
    for (auto it = k3Tree.begin_dfs_scan(); it != k3Tree.end_dfs_scan(); ++it) {
        cout << *it << " ";
    }
    cout << endl;

    cout << "Heap Traversal (k-3 Tree): ";
    for (auto it = k3Tree.begin_heap(); it != k3Tree.end_heap(); ++it) {
        cout << *it << " ";
    }
    cout << endl;

    // Create a window to visualize the binary tree with integers
    sf::RenderWindow windowBinary(sf::VideoMode(1600, 1300), "Display Binary Tree"); 

    while (windowBinary.isOpen()) {
        sf::Event event;
        while (windowBinary.pollEvent(event)) {
            if (event.type == sf::Event::Closed)
                windowBinary.close();
        }

        windowBinary.clear(sf::Color::Black);
        visualizeTree(windowBinary, binaryTree);
        windowBinary.display();
    }

    // Create a window to visualize the binary tree with complex numbers
    sf::RenderWindow windowComplex(sf::VideoMode(1600, 1300), "Display Binary Complex Tree"); 

    while (windowComplex.isOpen()) {
        sf::Event event;
        while (windowComplex.pollEvent(event)) {
            if (event.type == sf::Event::Closed)
                windowComplex.close();
        }

        windowComplex.clear(sf::Color::Black);
        visualizeTree(windowComplex, binaryComplexTree);
        windowComplex.display();
    }

    // Create a window to visualize the k-3 tree with integers
    sf::RenderWindow windowK3(sf::VideoMode(1600, 1300), "Display k-3 Tree"); 

    while (windowK3.isOpen()) {
        sf::Event event;
        while (windowK3.pollEvent(event)) {
            if (event.type == sf::Event::Closed)
                windowK3.close();
        }

        windowK3.clear(sf::Color::Black);
        visualizeTree(windowK3, k3Tree);
        windowK3.display();
    }

    return 0;
}
