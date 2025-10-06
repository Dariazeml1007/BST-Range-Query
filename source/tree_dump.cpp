#include "tree_dump.hpp"
#include "bin_tree.hpp"
#include <fstream>

void TreeDumper::dumpToFile(const MyTree& tree, const std::string& filename)
{
    std::ofstream file(filename);
    file << "digraph Tree {\n";
    file << "node [shape=circle, style=filled, fillcolor=lightblue];\n";

    // Используем getRoot() или прямой доступ через friend
    dumpNode(file, tree.root);
    dumpEdges(file, tree.root);

    file << "}\n";
}

void TreeDumper::dumpNode(std::ofstream& file, const void* node_ptr)
{
    if (!node_ptr) return;

    // Приводим к правильному типу
    const MyTree::Node* node = static_cast<const MyTree::Node*>(node_ptr);

    file << "node" << node->key << " [label=\"" << node->key << "\"];\n";

    dumpNode(file, node->left);
    dumpNode(file, node->right);
}

void TreeDumper::dumpEdges(std::ofstream& file, const void* node_ptr)
{
    if (!node_ptr) return;

    const MyTree::Node* node = static_cast<const MyTree::Node*>(node_ptr);

    if (node->left) {
        file << "node" << node->key << " -> node" << node->left->key << " [label=\"L\"];\n";
        dumpEdges(file, node->left);
    }
    if (node->right) {
        file << "node" << node->key << " -> node" << node->right->key << " [label=\"R\"];\n";
        dumpEdges(file, node->right);
    }
}
