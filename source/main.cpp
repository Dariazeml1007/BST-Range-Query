#include <iostream>
#include <chrono>
#include <set>

#include "bin_tree.hpp"
#include "utils.hpp"


#ifdef RUN_TESTS


void testRangeQuery(Trees::MyTree<int>& tree, const std::string& test_name, int low, int high, int expected)
{
    int result = range_query(tree, low, high);
    if (result == expected)
    {
        std::cout << " PASS: " << test_name << " (" << low << ", " << high
                  << ") = " << result << "\n";
    }
    else
    {
        std::cout << " FAIL: " << test_name << " (" << low << ", " << high
                  << ") = " << result << " expected " << expected << "\n";
    }
}

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

void runTests()
{
    std::cout << "=== TEST MODE ===\n";

    Trees::MyTree<int> tree;
    tree.insert(10); tree.insert(20); tree.insert(30); tree.insert(40);

    std::cout << "=== Testing range_query ===\n";
    testRangeQuery(tree, "Basic range", 8, 31, 3);      // 10, 20
    testRangeQuery(tree, "Empty range", 6, 9, 0);       // нет ключей
    testRangeQuery(tree, "Wide range", 15, 40, 3);      // 20, 30, 40
    testRangeQuery(tree, "Single element", 25, 35, 1);  // 30
    testRangeQuery(tree, "Exact bounds", 10, 10, 0);    // строго > low

    std::cout << "=== COMPARISON MODE ===\n";
    comparePerformance();
}


#else
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
        else if (command == "dump")
        {

            tree.dumpToFile("tree.dot");
            std::cout << "Created tree.dot\n";
        }

        else
        {
            std::cout << "Wrong command - try \'k\' or \'q\' \n";
        }

    }
    std::cout << std::endl;
}
#endif

int main() {
#ifdef RUN_TESTS
    runTests();
#else
    userInput();
#endif
    return 0;
}

