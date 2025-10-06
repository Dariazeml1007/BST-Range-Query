#include <iostream>

#include "bin_tree.hpp"

void MyTree::insert(int key)
{
    if (root == nullptr)
    {
        root = new Node(key);
        return;
    }

    Node* current = root;
    Node* parent = nullptr;

    while (current != nullptr)
    {
        parent = current;

        if (key < current->key)
        {
            current = current->left;
        }
        else if (key > current->key)
        {
            current = current->right;
        }
        else
        {
            return;
        }
    }


    Node* new_node = new Node(key);
    new_node->parent = parent;

    if (key < parent->key)
    {
        parent->left = new_node;
    }
    else
    {
        parent->right = new_node;
    }
}

int MyTree::countInRange(int low, int high)
{
    return countInRangeRec(root, low, high);
}

int MyTree::countInRangeRec(Node* node, int low, int high)
{
    if (node == nullptr) return 0;

    int count = 0;
    if (node->key > low && node->key <= high)
    {
        count = 1;
    }

    return count +
           countInRangeRec(node->left, low, high) +
           countInRangeRec(node->right, low, high);
}
