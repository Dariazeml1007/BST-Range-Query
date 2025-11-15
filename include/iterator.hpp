#pragma once
#include "node.hpp"
#include <iterator>

namespace Trees
{

template <typename KeyT, typename Compare> class MyTree;

template <typename KeyT, typename Compare = std::less<KeyT>> class iterator
{
private:
    using Node = Trees::Node<KeyT>;
    Node* current;

public:
    using iterator_category = std::forward_iterator_tag;
    using value_type = KeyT;
    using difference_type = std::ptrdiff_t;
    using pointer = const KeyT*;
    using reference = const KeyT&;

    iterator(Node* node = nullptr) : current(node)
    {
    }

    reference operator*() const
    {
        return current->key;
    }
    pointer operator->() const
    {
        return &current->key;
    }

    iterator& operator++()
    {
        current = Node::findSuccessor(current);
        return *this;
    }

    iterator operator++(int)
    {
        iterator temp = *this;
        ++(*this);
        return temp;
    }

    bool operator==(const iterator& other) const
    {
        return current == other.current;
    }

    bool operator!=(const iterator& other) const
    {
        return current != other.current;
    }

    template <typename Other> bool operator==(const Other& other) const
    {
        return current == other.current;
    }

    template <typename Other> bool operator!=(const Other& other) const
    {
        return current != other.current;
    }
};

} // namespace Trees
