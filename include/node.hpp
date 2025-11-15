#pragma once
#include <algorithm>
#include <utility>

namespace Trees
{

template <typename KeyT> struct Node
{
    KeyT key;
    Node* left;
    Node* right;
    Node* parent;
    int height_;

    Node(KeyT k, Node* p = nullptr)
        : key(std::move(k)), left(nullptr), right(nullptr), parent(p),
          height_(1)
    {
    }

    static int height(const Node* node)
    {
        return node ? node->height_ : 0;
    }
    static int balanceFactor(const Node* node)
    {
        if (!node)
            return 0;
        return height(node->left) - height(node->right);
    }
    static void updateHeight(Node* node)
    {
        if (node)
        {
            node->height_ =
                1 + std::max(height(node->left), height(node->right));
        }
    }

    static Node* rotateRight(Node* problem_node)
    {
        Node* new_root = problem_node->left;
        Node* problem_node_right_subtree = new_root->right;

        new_root->right = problem_node;
        problem_node->left = problem_node_right_subtree;

        if (problem_node_right_subtree)
            problem_node_right_subtree->parent = problem_node;

        new_root->parent = problem_node->parent;
        problem_node->parent = new_root;

        updateHeight(problem_node);
        updateHeight(new_root);
        return new_root;
    }

    static Node* rotateLeft(Node* problem_node)
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

    static Node* balance(Node* node)
    {
        if (!node)
            return nullptr;
        updateHeight(node);
        int bf = Node::balanceFactor(node);

        if (bf > 1)
        {
            auto bf_left = Node::balanceFactor(node->left);
            if (bf_left < 0)
            {
                node->left = rotateLeft(node->left);
            }
            return rotateRight(node);
        }
        else if (bf < -1)
        {
            auto bf_right = Node::balanceFactor(node->right);
            if (bf_right > 0)
            {
                node->right = rotateRight(node->right);
            }
            return rotateLeft(node);
        }
        return node;
    }

    static void clearRec(Node* node)
    {
        while (node)
        {
            if (node->left)
            {

                Node* predecessor = node->left;
                while (predecessor->right && predecessor->right != node)
                {
                    predecessor = predecessor->right;
                }

                if (!predecessor->right)
                {

                    predecessor->right = node;
                    Node* temp = node;
                    node = node->left;
                    temp->left = nullptr;
                }
                else
                {

                    predecessor->right = nullptr;
                    Node* to_delete = node;
                    node = node->right;
                    delete to_delete;
                }
            }

            else
            {
                Node* to_delete = node;
                node = node->right;
                delete to_delete;
            }
        }
    }

    static Node* findMin(Node* node)
    {
        while (node && node->left)
            node = node->left;
        return node;
    }

    static Node* findSuccessor(const Node* node)
    {
        if (!node)
            return nullptr;

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
};

} // namespace Trees
