#include "tree.hpp"
#include "complex.hpp"
#include <iostream>
#include <string>
#include <algorithm>
#include <vector>
#include <SFML/Graphics.hpp>
#include <cmath> // Include for mathematical functions
#include <sstream> // Include this for std::ostringstream

using namespace std;

// Template function to draw the tree nodes and edges
template <typename T>
void drawTree(sf::RenderWindow &window, Node<T>* node, sf::Vector2f position, float horizontalSpacing, float verticalSpacing) {
    if (!node) return;

    sf::CircleShape circle(20);
    circle.setFillColor(sf::Color(100, 100, 255)); // Change color to light blue
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

    std::ostringstream oss;
    oss << node->value;
    text.setString(oss.str());
    
    text.setCharacterSize(14); // Slightly larger character size
    text.setFillColor(sf::Color(255, 255, 255)); // Change text color to white
    sf::FloatRect textRect = text.getLocalBounds();
    text.setOrigin(textRect.left + textRect.width / 2.0f, textRect.top + textRect.height / 2.0f); // Center the text
    text.setPosition(position);
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
            line->color = sf::Color(255, 165, 0); // Change line color to orange
            window.draw(line, 2, sf::Lines);

            drawTree(window, child.get(), childPos, horizontalSpacing * 0.75f, verticalSpacing * 1.2f); // Adjusted spacing
            childIndex++;
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
    float horizontalSpacing = window.getSize().x / (pow(2, totalLevels - 1) + 1) * 1.5; // Adjusted horizontal spacing
    float verticalSpacing = window.getSize().y / (totalLevels + 1) * 1.5; // Adjusted vertical spacing

    // Draw the tree
    drawTree(window, root, startPosition, horizontalSpacing, verticalSpacing);
}

int main() {
    // Create a k-5 tree with integers
    tree<int> ktreeInt(5);

    ktreeInt.add_root(1);
    ktreeInt.add_sub_node(1, 2);
    ktreeInt.add_sub_node(1, 3);
    ktreeInt.add_sub_node(1, 4);
    ktreeInt.add_sub_node(1, 5);
    ktreeInt.add_sub_node(1, 6);
    ktreeInt.add_sub_node(2, 7);
    ktreeInt.add_sub_node(2, 8);
    ktreeInt.add_sub_node(2, 9);
    ktreeInt.add_sub_node(3, 10);
    ktreeInt.add_sub_node(3, 11);

    cout << "Pre-order Traversal (k-5): ";
    for (auto it = ktreeInt.begin_pre_order(); it != ktreeInt.end_pre_order(); ++it) {
        cout << *it << " ";
    }
    cout << endl;

    cout << "Post-order Traversal (k-5): ";
    for (auto it = ktreeInt.begin_post_order(); it != ktreeInt.end_post_order(); ++it) {
        cout << *it << " ";
    }
    cout << endl;

    cout << "In-order Traversal (k-5): ";
    for (auto it = ktreeInt.begin_in_order(); it != ktreeInt.end_in_order(); ++it) {
        cout << *it << " ";
    }
    cout << endl;

    cout << "BFS Traversal (k-5): ";
    for (auto it = ktreeInt.begin_bfs_scan(); it != ktreeInt.end_bfs_scan(); ++it) {
        cout << *it << " ";
    }
    cout << endl;

    cout << "DFS Traversal (k-5): ";
    for (auto it = ktreeInt.begin_dfs_scan(); it != ktreeInt.end_dfs_scan(); ++it) {
        cout << *it << " ";
    }
    cout << endl;

    // Create a window to visualize the k-5 tree
    sf::RenderWindow windowInt(sf::VideoMode(1600, 1300), "Display Int Tree"); // Maintain larger window size

    while (windowInt.isOpen()) {
        sf::Event event;
        while (windowInt.pollEvent(event)) {
            if (event.type == sf::Event::Closed)
                windowInt.close();
        }

        windowInt.clear(sf::Color::Black);
        visualizeTree(windowInt, ktreeInt);
        windowInt.display();
    }

    // Create a k-5 tree with Complex numbers
    tree<Complex> ktreeComplex(5);

    ktreeComplex.add_root(Complex(1, 1));
    ktreeComplex.add_sub_node(Complex(1, 1), Complex(2, 2));
    ktreeComplex.add_sub_node(Complex(1, 1), Complex(3, 3));
    ktreeComplex.add_sub_node(Complex(1, 1), Complex(4, 4));
    ktreeComplex.add_sub_node(Complex(1, 1), Complex(5, 5));
    ktreeComplex.add_sub_node(Complex(1, 1), Complex(6, 6));
    ktreeComplex.add_sub_node(Complex(2, 2), Complex(7, 7));
    ktreeComplex.add_sub_node(Complex(2, 2), Complex(8, 8));
    ktreeComplex.add_sub_node(Complex(2, 2), Complex(9, 9));
    ktreeComplex.add_sub_node(Complex(3, 3), Complex(10, 10));
    ktreeComplex.add_sub_node(Complex(3, 3), Complex(11, 11));

    cout << "Pre-order Traversal (k-5): ";
    for (auto it = ktreeComplex.begin_pre_order(); it != ktreeComplex.end_pre_order(); ++it) {
        cout << *it << " ";
    }
    cout << endl;

    cout << "Post-order Traversal (k-5): ";
    for (auto it = ktreeComplex.begin_post_order(); it != ktreeComplex.end_post_order(); ++it) {
        cout << *it << " ";
    }
    cout << endl;

    cout << "In-order Traversal (k-5): ";
    for (auto it = ktreeComplex.begin_in_order(); it != ktreeComplex.end_in_order(); ++it) {
        cout << *it << " ";
    }
    cout << endl;

    cout << "BFS Traversal (k-5): ";
    for (auto it = ktreeComplex.begin_bfs_scan(); it != ktreeComplex.end_bfs_scan(); ++it) {
        cout << *it << " ";
    }
    cout << endl;

    cout << "DFS Traversal (k-5): ";
    for (auto it = ktreeComplex.begin_dfs_scan(); it != ktreeComplex.end_dfs_scan(); ++it) {
        cout << *it << " ";
    }
    cout << endl;

    // Create a window to visualize the k-5 tree
    sf::RenderWindow windowComplex(sf::VideoMode(1600, 1300), "Display Complex Tree"); // Maintain larger window size

    while (windowComplex.isOpen()) {
        sf::Event event;
        while (windowComplex.pollEvent(event)) {
            if (event.type == sf::Event::Closed)
                windowComplex.close();
        }

        windowComplex.clear(sf::Color::Black);
        visualizeTree(windowComplex, ktreeComplex);
        windowComplex.display();
    }

    return 0;
}
