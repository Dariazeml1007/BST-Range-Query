#include <iostream>    // для std::cin, std::cout
#include <string>      // для std::string
#include <cstddef>     // для nullptr_t (опционально)

class TreeDumper;

class MyTree
{
private:
    struct Node
    {
        int key;
        Node* left;
        Node* right;
        Node* parent;

        Node(int k) : key(k), left(nullptr), right(nullptr), parent(nullptr){}
    };

    Node* root;
    void clearRec(Node* node)
    {
        if (node == nullptr) return;

        clearRec(node->left);
        clearRec(node->right);
        delete node;
    }
    int countInRangeRec(Node* node, int low, int high);
public:
    MyTree() : root(nullptr) {}

    ~MyTree() {clear();}


    void clear()
    {
        clearRec(root);
        root = nullptr;
    }

    friend class TreeDumper;

    Node* getRoot() const { return root; }

    void insert(int key);
    int countInRange(int low, int high);
};
