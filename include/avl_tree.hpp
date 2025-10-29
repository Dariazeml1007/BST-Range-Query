#pragma once
#include <string>      // для dumpToFile(std::string)
#include <fstream>     // для std::ofstream
#include <functional>  // для std::less<KeyT>
#include <algorithm>   // для std::max в updateHeight
#include <stack>

namespace Trees
{

template<typename KeyT, typename Compare = std::less<KeyT>>
class MyTree
{
private:
    struct Node
    {
        KeyT key;
        Node* left;
        Node* right;
        Node* parent;
        int height_;

        Node(KeyT k, Node* p = nullptr)
        : key(std::move(k))
        , left(nullptr)
        , right(nullptr)
        , parent(p)
        , height_(1)
        {}

        static int height(const Node* node)
        {
            return node ? node->height_ : 0;
        }

        static int balanceFactor(const Node* node)
        {
            if (!node) return 0;
            return height(node->left) - height(node->right);
        }

        void updateHeight()
        {
            height_ = 1 + std::max(height(left), height(right));
        }
    };

    Node* root;
    [[no_unique_address]] Compare comp_; // 0 byte (think of it)

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
            } else {
                return current;
            }
        }
        return nullptr;
    }


    Node* rotateRight(Node* problem_node)
    {
        Node* new_root = problem_node->left;
        Node* problem_node_right_subtree =  new_root->right;

        new_root->right = problem_node;
        problem_node->left = problem_node_right_subtree;

        if (problem_node_right_subtree)
            problem_node_right_subtree->parent = problem_node;

        new_root->parent = problem_node->parent;
        problem_node->parent =  new_root;

        problem_node->updateHeight();
        new_root->updateHeight();
        return new_root;
    }

    Node* rotateLeft(Node* problem_node)
    {
        Node* new_root = problem_node->right;
        Node* problem_node_left_subtree = new_root->left;

        new_root->left = problem_node;
        problem_node->right = problem_node_left_subtree;

        if (problem_node_left_subtree)
            problem_node_left_subtree->parent = problem_node;

        new_root->parent = problem_node->parent;
        problem_node->parent = new_root;

        problem_node->updateHeight();
        new_root->updateHeight();
        return new_root;
    }

    Node* balance(Node* node)
    {
        if (!node) return nullptr;
        node->updateHeight();
        int bf = Node::balanceFactor(node);
        if (bf > 1 && Node::balanceFactor(node->left) >= 0)
        {
            return rotateRight(node);
        }
        if (bf > 1 && Node::balanceFactor(node->left) < 0)
        {
            node->left = rotateLeft(node->left);
            return rotateRight(node);
        }
        if (bf < -1 && Node::balanceFactor(node->right) <= 0)
        {
            return rotateLeft(node);
        }
        if (bf < -1 && Node::balanceFactor(node->right) > 0)
        {
            node->right = rotateRight(node->right);
            return rotateLeft(node);
        }
        return node;
    }

   void clearRec(Node* node)
    {
        if (!node) return;

        std::stack<Node*> nodes;
        nodes.push(node);

        while (!nodes.empty())
        {
            Node* current = nodes.top();
            nodes.pop();

            if (current->left) nodes.push(current->left);
            if (current->right) nodes.push(current->right);

            delete current;
        }
    }

    Node* findMin(Node* node) const
    {
        while (node && node->left) node = node->left;
        return node;
    }

   Node* findSuccessor(const Node* node) const
    {
        if (!node) return nullptr;

        if (node->right)
        {
            auto result = findMin(node->right);
            return result;
        }

        Node* parent = node->parent;
        const Node* current = node;


        while (parent && current == parent->right)
        {
            current = parent;
            parent = parent->parent;
        }

        return parent;
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

        return balance(node);
    }

    void dumpNode(std::ostream& os, Node* node) const
    {
        if (!node) return;
        os << "node" << node->key << " [label=\"" << node->key << "\"];\n";
        dumpNode(os, node->left);
        dumpNode(os, node->right);
    }

    void dumpEdges(std::ostream& os, Node* node) const
    {
        if (!node) return;
        if (node->left)
        {
            os << "node" << node->key << " -> node" << node->left->key << ";\n";
            dumpEdges(os, node->left);
        }
        if (node->right)
        {
            os << "node" << node->key << " -> node" << node->right->key << ";\n";
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

    void dumpToFile(const std::string& filename) const
    {
        std::ofstream file(filename);
        dumpToStream(file);
    }

    class iterator
{
private:
    Node* current;
    const MyTree* tree;

public:
    using iterator_category = std::forward_iterator_tag;
    using value_type = KeyT;
    using difference_type = std::ptrdiff_t;
    using pointer = const KeyT*;
    using reference = const KeyT&;

    iterator(Node* node = nullptr, const MyTree* t = nullptr)
    : current(node), tree(t) {}


    const KeyT& operator*() const { return current->key; }
    const KeyT* operator->() const { return &current->key; }

    iterator& operator++()
    {
        current = tree->findSuccessor(current);
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


    template<typename Other>
    bool operator==(const Other& other) const
    {
        return current == other.current;
    }

    template<typename Other>
    bool operator!=(const Other& other) const
    {
        return current != other.current;
    }
};

     void clear()
     {
        clearRec(root);
     }

    MyTree() : root(nullptr), comp_() {}


    MyTree(const Compare& comp) : root(nullptr), comp_(comp) {}


    MyTree(Compare&& comp) : root(nullptr), comp_(std::move(comp)) {}



    Node* getRoot() const { return root; }

    std::pair<iterator, bool> insert(const KeyT& key)
    {
        bool inserted = false;
        root = insertRec(root, key, nullptr, inserted);


        Node* inserted_node = findNode(key);
        return std::make_pair(iterator(inserted_node), inserted);
    }

    iterator begin() const
    {
        Node* current = root;
        while (current && current->left)
        {
            current = current->left;
        }
        return iterator(current, this);
    }

    iterator end() const
    {

        return iterator(nullptr, this);
    }

    iterator lower_bound(const KeyT& key) const
    {
        return iterator(findLowerBound(key));
    }

    iterator upper_bound(const KeyT& key) const
    {
        return iterator(findUpperBound(key));
    }

    //Rule of 5

    // 1.
    MyTree(const MyTree& other)
    {
        root = copyRec(other.root, nullptr);
        comp_ = other.comp_;
    }

    Node* copyRec(Node* other_node, Node* parent)
    {
        if (!other_node) return nullptr;

        Node* new_node = new Node(other_node->key, parent);
        new_node->left = copyRec(other_node->left, new_node);
        new_node->right = copyRec(other_node->right, new_node);
        new_node->height_ = other_node->height_;

        return new_node;
    }
    //2.
    MyTree& operator=(const MyTree& other)
    {
        if (this != &other)
        {
            clearRec(root);
            root = copyRec(other.root, nullptr);
            comp_ = other.comp_;
        }
        return *this;
    }
    // 3. Move
    MyTree(MyTree&& other) noexcept
    : root(other.root)
    , comp_(std::move(other.comp_))
    {
        other.root = nullptr;
    }
    // 4. Move
   MyTree& operator=(MyTree&& other) noexcept
    {
        if (this != &other)
        {
            std::swap(root, other.root);
            std::swap(comp_, other.comp_);

        }
        return *this;
    }
    // 5. Destructer
    ~MyTree()
    {
        clearRec(root);
    }
};
}
