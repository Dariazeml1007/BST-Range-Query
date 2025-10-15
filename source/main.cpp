#include <iostream>
#include <chrono>
#include <set>

#include "avl_tree.hpp"
#include "utils.hpp"

void comparePerformance()
{
    std::cout << "=== Comparison with std::set ===\n";

    Trees::MyTree<int> my_tree;
    std::set<int> std_set;


    for (int i = 0; i < 10000; i++)
    {
        int val = rand() % 100000;
        my_tree.insert(val);
        std_set.insert(val);
    }

    auto start1 = std::chrono::high_resolution_clock::now();

    for (int i = 0; i < 1000; i++)
    {
        int low = rand() % 50000;
        int high = low + rand() % 50000;
        range_query(my_tree, low, high);
    }

    auto end1 = std::chrono::high_resolution_clock::now();

    auto start2 = std::chrono::high_resolution_clock::now();

    for (int i = 0; i < 1000; i++)
    {
        int low = rand() % 50000;
        int high = low + rand() % 50000;
        range_query(std_set, low, high);
    }
    auto end2 = std::chrono::high_resolution_clock::now();

    auto my_time = std::chrono::duration_cast<std::chrono::milliseconds>(end1 - start1);
    auto std_time = std::chrono::duration_cast<std::chrono::milliseconds>(end2 - start2);

    std::cout << "MyTree: " << my_time.count() << " ms\n";
    std::cout << "std::set: " << std_time.count() << " ms\n";
}

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
