#include "tree.hpp"
#include <iostream>
#include <string>
#include <algorithm>
#include <vector>
#include <SFML/Graphics.hpp>
#include <cmath> // Include for mathematical functions

using namespace std;

// Function to draw the tree nodes and edges
void drawTree(sf::RenderWindow &window, Node<int>* node, sf::Vector2f position, float horizontalSpacing, float verticalSpacing) {
    if (!node) return;

    sf::CircleShape circle(20);
    circle.setFillColor(sf::Color::Green);
    circle.setPosition(position.x - circle.getRadius(), position.y - circle.getRadius()); // Center the circle
    window.draw(circle);

    // Draw value in the node
    sf::Font font;
    if (!font.loadFromFile("/usr/share/fonts/truetype/dejavu/DejaVuSans-Bold.ttf")) {
        cerr << "Could not load font" << endl;
        return;
    }
    sf::Text text;
    text.setFont(font);
    text.setString(to_string(node->value));
    text.setCharacterSize(20);
    text.setFillColor(sf::Color::White);
    text.setPosition(position.x - 10, position.y - 15); // Center the text
    window.draw(text);

    float angleStep = 360.0f / node->children.size(); // Adjust the angle step based on the number of children
    int childIndex = 0;
    for (auto& child : node->children) {
        if (child) {
            float angle = -90 + childIndex * angleStep;
            float radianAngle = angle * M_PI / 180.0f;
            sf::Vector2f childPos = position + sf::Vector2f(cos(radianAngle) * horizontalSpacing, verticalSpacing);
            sf::Vertex line[] = {
                sf::Vertex(position + sf::Vector2f(0, 20)),
                sf::Vertex(childPos + sf::Vector2f(0, -20))
            };
            window.draw(line, 2, sf::Lines);

            drawTree(window, child.get(), childPos, horizontalSpacing * 0.75f, verticalSpacing);
            childIndex++;
        }
    }
}

// Function to calculate the total levels in the tree
template <typename T>
int calculateTotalLevels(Node<T>* node) {
    if (!node) return 0;
    int maxDepth = 0;
    for (auto& child : node->children) {
        maxDepth = max(maxDepth, calculateTotalLevels(child.get()));
    }
    return maxDepth + 1;
}

// Function to visualize the tree
void visualizeTree(sf::RenderWindow& window, tree<int>& tree) {
    sf::Font font;
    if (!font.loadFromFile("/usr/share/fonts/truetype/dejavu/DejaVuSans-Bold.ttf")) {
        cerr << "Could not load font" << endl;
        return;
    }

    // Get the root node
    Node<int>* root = tree.getRoot();
    int totalLevels = calculateTotalLevels(root);

    // Calculate position for drawing
    sf::Vector2f startPosition(window.getSize().x / 2, 50);
    float horizontalSpacing = window.getSize().x / (pow(2, totalLevels - 1) + 1);
    float verticalSpacing = window.getSize().y / (totalLevels + 1);

    // Draw the tree
    drawTree(window, root, startPosition, horizontalSpacing, verticalSpacing);
}

int main() {
    // Create a k-5 tree
    tree<int> ktree(5);

    ktree.add_root(1);
    ktree.add_sub_node(1, 2);
    ktree.add_sub_node(1, 3);
    ktree.add_sub_node(1, 4);
    ktree.add_sub_node(1, 5);
    ktree.add_sub_node(1, 6);
    ktree.add_sub_node(2, 7);
    ktree.add_sub_node(2, 8);
    ktree.add_sub_node(2, 9);
    ktree.add_sub_node(3, 10);
    ktree.add_sub_node(3, 11);

    cout << "Pre-order Traversal (k-5): ";
    for (auto it = ktree.begin_pre_order(); it != ktree.end_pre_order(); ++it) {
        cout << *it << " ";
    }
    cout << endl;

    cout << "Post-order Traversal (k-5): ";
    for (auto it = ktree.begin_post_order(); it != ktree.end_post_order(); ++it) {
        cout << *it << " ";
    }
    cout << endl;

    cout << "In-order Traversal (k-5): ";
    for (auto it = ktree.begin_in_order(); it != ktree.end_in_order(); ++it) {
        cout << *it << " ";
    }
    cout << endl;

    cout << "BFS Traversal (k-5): ";
    for (auto it = ktree.begin_bfs_scan(); it != ktree.end_bfs_scan(); ++it) {
        cout << *it << " ";
    }
    cout << endl;

    cout << "DFS Traversal (k-5): ";
    for (auto it = ktree.begin_dfs_scan(); it != ktree.end_dfs_scan(); ++it) {
        cout << *it << " ";
    }
    cout << endl;

    // Create a window to visualize the k-5 tree
    sf::RenderWindow window(sf::VideoMode(1200, 800), "Display Orel and K-5 Tree");

    while (window.isOpen()) {
        sf::Event event;
        while (window.pollEvent(event)) {
            if (event.type == sf::Event::Closed)
                window.close();
        }

        window.clear(sf::Color::Black);
        visualizeTree(window, ktree);
        window.display();
    }

    return 0;
}
