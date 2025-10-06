#pragma once
#include <fstream>
#include <string>

// Forward declaration
class MyTree;

class TreeDumper {
public:
    static void dumpToFile(const MyTree& tree, const std::string& filename);

private:

    static void dumpNode(std::ofstream& file, const void* node);
    static void dumpEdges(std::ofstream& file, const void* node);
};
