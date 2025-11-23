#pragma once
#include <algorithm>  // для std::max в updateHeight
#include <fstream>    // для std::ofstream
#include <functional> // для std::less<KeyT>
#include <string>     // для dumpToFile(std::string)
#include <utility>

#include "iterator.hpp"
#include "node.hpp"

namespace Trees
{

template <typename KeyT, typename Compare = std::less<KeyT>> class MyTree
{
public:
    using Node = Trees::Node<KeyT>;
    using iterator = Trees::iterator<KeyT, Compare>;
    using difference_type = std::ptrdiff_t;

    using const_iterator = iterator;
    using reverse_iterator = std::reverse_iterator<iterator>;
    using const_reverse_iterator = std::reverse_iterator<const_iterator>;

private:
    Node* root;
    Node* min_node;
    [[no_unique_address]] Compare comp_; // 0 byte (think of it)

    void updateMinNode()
    {
        if (!root)
        {
            min_node = nullptr;
            return;
        }

        min_node = root;
        while (min_node->left)
        {
            min_node = min_node->left;
        }
    }

    static Node* copyRec(Node* other_node, Node* parent)
    {
        if (!other_node)
            return nullptr;

        Node* new_node = new Node(other_node->key, parent);
        try
        {
            new_node->left = copyRec(other_node->left, new_node);
            new_node->right = copyRec(other_node->right, new_node);
            new_node->height_ = other_node->height_;
        }
        catch (...)
        {
            Node::clearRec(new_node);
            throw;
        }

        return new_node;
    }

    Node* findNode(const KeyT& key) const
    {
        Node* current = root;
        while (current)
        {
            if (comp_(key, current->key))
            {
                current = current->left;
            }
            else if (comp_(current->key, key))
            {
                current = current->right;
            }
            else
            {
                return current;
            }
        }
        return nullptr;
    }

    Node* findLowerBound(const KeyT& key) const
    {
        Node* current = root;
        Node* result = nullptr;
        while (current)
        {
            if (!comp_(current->key, key)) // current->key >= key
            {
                result = current;
                current = current->left;
            }
            else
            {
                current = current->right;
            }
        }

        return result;
    }

    Node* findUpperBound(const KeyT& key) const
    {
        Node* current = root;
        Node* result = nullptr;
        while (current)
        {
            if (comp_(key, current->key)) // key < current->key
            {

                result = current;
                current = current->left;
            }
            else
            {
                current = current->right;
            }
        }

        return result;
    }

    Node* insertRec(Node* node, const KeyT key, Node* parent, bool& inserted)
    {
        if (!node)
        {
            inserted = true;
            return new Node(key, parent);
        }

        if (comp_(key, node->key))
        {
            node->left = insertRec(node->left, key, node, inserted);
        }
        else if (comp_(node->key, key))
        {
            node->right = insertRec(node->right, key, node, inserted);
        }
        else
        {
            inserted = false;
            return node;
        }

        return Node::balance(node);
    }

    static void dumpNode(std::ostream& os, const Node* node)
    {
        if (!node)
            return;
        os << "node" << node->key << " [label=\"" << node->key << "\"];\n";
        dumpNode(os, node->left);
        dumpNode(os, node->right);
    }

    static void dumpEdges(std::ostream& os, const Node* node)
    {
        if (!node)
            return;
        if (node->left)
        {
            os << "node" << node->key << " -> node" << node->left->key << ";\n";
            dumpEdges(os, node->left);
        }
        if (node->right)
        {
            os << "node" << node->key << " -> node" << node->right->key
               << ";\n";
            dumpEdges(os, node->right);
        }
    }

public:
    void dumpToStream(std::ostream& os) const
    {
        os << "digraph Tree {\n";
        os << "node [shape=circle];\n";
        dumpNode(os, root);
        dumpEdges(os, root);
        os << "}\n";
    }

    void clear()
    {
        Node::clearRec(root);
    }

    MyTree() : root(nullptr), min_node(nullptr), comp_()
    {
    }
    MyTree(const Compare& comp) : root(nullptr), min_node(nullptr), comp_(comp)
    {
    }
    MyTree(Compare&& comp)
        : root(nullptr), min_node(nullptr), comp_(std::move(comp))
    {
    }

    std::pair<iterator, bool> insert(const KeyT& key)
    {
        bool inserted = false;
        root = insertRec(root, key, nullptr, inserted);

        Node* inserted_node = findNode(key);

        if (inserted && (!min_node || comp_(key, min_node->key)))
        {
            min_node = inserted_node;
        }

        return std::make_pair(iterator(inserted_node), inserted);
    }

    iterator begin() const
    {
        return iterator(min_node); // O(1)!
    }

    iterator end() const
    {
        return iterator(nullptr);
    }

    reverse_iterator rbegin() const
    {
        return reverse_iterator(end());
    }
    reverse_iterator rend() const
    {
        return reverse_iterator(begin());
    }

    iterator lower_bound(const KeyT& key) const
    {
        return iterator(findLowerBound(key));
    }

    iterator upper_bound(const KeyT& key) const
    {
        return iterator(findUpperBound(key));
    }

    // Rule of 5

    // 1. Copy constructor
    MyTree(const MyTree& other)
        : root(copyRec(other.root, nullptr)), min_node(nullptr),
          comp_(other.comp_)
    {
        updateMinNode();
    }

    // 2. Move constructor

    MyTree(MyTree&& other) noexcept
        : root(std::exchange(other.root, nullptr)),
          min_node(std::exchange(other.min_node, nullptr)),
          comp_(std::move(other.comp_))
    {
    }

    // 3.

    MyTree& operator=(MyTree other) noexcept
    {
        swap(*this, other);
        return *this;
    }

    // 4.
    friend void swap(MyTree& first, MyTree& second) noexcept
    {
        using std::swap;
        swap(first.root, second.root);
        swap(first.min_node, second.min_node);
        swap(first.comp_, second.comp_);
    }

    // 5.
    ~MyTree()
    {
        Node::clearRec(root);
    }
};
} // namespace Trees
