#include <iostream>
#include <chrono>
#include <set>

#include "avl_tree.hpp"
#include "utils.hpp"

void userInput()
{
    Trees::MyTree<int> tree;
    std::string command;

    while (std::cin >> command)
    {
        if (std::cin.eof()) break;
        if (command == "k")
        {
            int key;
            if (std::cin >> key)
            {
                tree.insert(key);
            }
        }
        else if (command == "q")
        {
            int low, high;
            if (std::cin >> low >> high)
            {
                int count = range_query(tree, low, high);
                std::cout << count << " ";
            }
        }
        else if (command == "dumpc")
        {
            tree.dumpToStream(std::cout);
        }
        else if (command == "dumpf")
        {
            std::string filename;
            if (std::cin >> filename)
            {
                tree.dumpToFile(filename);
                std::cout << "Created " << filename << "\n";
            }
        }

        else
        {
            std::cout << "Wrong command - try \'k\' or \'q\' \n";
        }

    }
    std::cout << std::endl;
}

int main() {
    userInput();
    return 0;
}
