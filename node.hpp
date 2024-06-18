#ifndef NODE_HPP
#define NODE_HPP

#include <vector>
#include <memory>

template <typename T>
class Node {
public:
    T value;
    std::vector<std::unique_ptr<Node<T>>> children;

    Node(T val, int k);
};

template <typename T>
Node<T>::Node(T val, int k) : value(val), children(k) {}

#endif // NODE_HPP
