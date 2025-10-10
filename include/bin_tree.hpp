#pragma once
#include <iostream> //std::string in dumpToFile
#include <string> //filename in dumpToFile()
#include <cstddef> //nullptr
#include <fstream> //dumpToFile() - record in .dot file

namespace Trees
{
    class TreeDumper;
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
                : key(k), left(nullptr), right(nullptr), parent(p), height_(1) {}


        };

        Node* root;
        Compare comp_;

        int height(Node* node) const
        {
            return node ? node->height_ : 0;
        }

        int balanceFactor(Node* node) const
        {
            if (!node) return 0;
            return height(node->left) - height(node->right);

        }

        void updateHeight(Node* node)
        {
            if (node)
            {
                node->height_ = 1 + std::max(height(node->left), height(node->right));

            }
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

            updateHeight(problem_node);
            updateHeight(new_root);

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

            updateHeight(problem_node);
            updateHeight(new_root);

            return new_root;
        }

        Node* balance(Node* node)
        {
            if (!node) return nullptr;

            updateHeight(node);
            int bf = balanceFactor(node);

            if (bf > 1 && balanceFactor(node->left) >= 0)
            {
                return rotateRight(node);
            }


            if (bf > 1 && balanceFactor(node->left) < 0)
            {
                node->left = rotateLeft(node->left);
                return rotateRight(node);
            }

            if (bf < -1 && balanceFactor(node->right) <= 0)
            {
                return rotateLeft(node);
            }


            if (bf < -1 && balanceFactor(node->right) > 0)
            {
                node->right = rotateRight(node->right);
                return rotateLeft(node);
            }

            return node;
        }


        void clearRec(Node* node)
        {
            if (node == nullptr) return;
            clearRec(node->left);
            clearRec(node->right);
            delete node;
        }

        Node* findMin(Node* node) const
        {
            while (node && node->left) node = node->left;
            return node;
        }

        Node* findSuccessor(Node* node) const
        {
            if (node->right) return findMin(node->right);
            Node* parent = node->parent;
            while (parent && node == parent->right)
            {
                node = parent;
                parent = parent->parent;
            }
            return parent;
        }

        Node* findLowerBound(KeyT key) const
        {
            Node* current = root;
            Node* result = nullptr;
            while (current)
            {
                if (current->key >= key)
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

        Node* findUpperBound(KeyT key) const
        {
            Node* current = root;
            Node* result = nullptr;
            while (current)
            {
                if (current->key > key)
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

        Node* insertRec(Node* node, KeyT key, Node* parent)
        {
            if (!node) return new Node(key, parent);

            if (comp_(key, node->key))
            {
                node->left = insertRec(node->left, key, node);
            }
            else if (comp_(node->key, key))
            {
                node->right = insertRec(node->right, key, node);
            }
            else
            {
                return node;
            }

            return balance(node);
        }

        void dumpNode(std::ofstream& file, Node* node) const
        {
            if (!node) return;
            file << "node" << node->key << " [label=\"" << node->key << "\"];\n";
            dumpNode(file, node->left);
            dumpNode(file, node->right);
        }

        void dumpEdges(std::ofstream& file, Node* node) const
        {
            if (!node) return;
            if (node->left)
            {
                file << "node" << node->key << " -> node" << node->left->key << ";\n";
                dumpEdges(file, node->left);
            }
            if (node->right)
            {
                file << "node" << node->key << " -> node" << node->right->key << ";\n";
                dumpEdges(file, node->right);
            }
        }



    public:

        void dumpToFile(const std::string& filename) const
        {
            std::ofstream file(filename);
            file << "digraph Tree {\n";
            file << "node [shape=circle];\n";
            dumpNode(file, root);
            dumpEdges(file, root);
            file << "}\n";
        }

        class iterator
        {
        private:
            Node* current;


            Node* findMin(Node* node) const
            {
                while (node && node->left) node = node->left;
                return node;
            }

            Node* findSuccessor(Node* node) const
            {
                if (node->right) return findMin(node->right);
                Node* parent = node->parent;
                while (parent && node == parent->right)
                {
                    node = parent;
                    parent = parent->parent;
                }
                return parent;
            }

        public:


            iterator(Node* node = nullptr) : current(node) {}

            const int& operator*() const
            {
                return current->key;
            }

            iterator& operator++()
            {
                current = findSuccessor(current);
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
        };

         MyTree() : root(nullptr), comp_() {}
        ~MyTree() { clear(); }

        void clear()
        {
            clearRec(root);
            root = nullptr;
        }

        friend class TreeDumper;
        Node* getRoot() const { return root; }

        void insert(KeyT key)
        {
            root = insertRec(root, key, nullptr);
        }


        iterator begin() const
        {
            return iterator(findMin(root));
        }

        iterator end() const
        {
            return iterator(nullptr);
        }

        iterator lower_bound(KeyT key) const
        {
            return iterator(findLowerBound(key));
        }

        iterator upper_bound(KeyT key) const
        {
            return iterator(findUpperBound(key));
        }

        MyTree(const MyTree&) = delete;
        MyTree& operator=(const MyTree&) = delete;

        MyTree(MyTree&& other) noexcept : root(other.root)//noexcept for making binary smaller and not processing exceptions
        {
            other.root = nullptr;
        }

        MyTree& operator=(MyTree&& other) noexcept
        {
            if (this != &other)
            {
                clear();
                root = other.root;
                other.root = nullptr;
            }
            return *this;
        }
    };
}
