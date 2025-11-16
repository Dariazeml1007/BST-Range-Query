#include "../include/avl_tree.hpp"
#include "../include/utils.hpp"
#include <chrono>
#include <iostream>
#include <string>

int main()
{
    Trees::MyTree<int> tree;
    std::string command;

    auto start = std::chrono::high_resolution_clock::now();

    while (std::cin >> command)
    {
        if (std::cin.eof())
            break;

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
                range_query(tree, low, high);
            }
        }
    }

    auto end = std::chrono::high_resolution_clock::now();
    auto duration =
        std::chrono::duration_cast<std::chrono::microseconds>(end - start);

    std::cout << "Tree: " << duration.count() << " μs" << std::endl;

    return 0;
}
