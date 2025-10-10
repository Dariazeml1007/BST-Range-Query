#include <iostream>

#include "bin_tree.hpp"
#include "utils.hpp"


#ifdef RUN_TESTS
void runTests()
{
    std::cout << "=== TEST MODE ===\n";

    Trees::MyTree<int> tree;

    // Test 1:
    tree.insert(10);
    tree.insert(5);
    tree.insert(15);
    tree.insert(3);
    tree.insert(7);

    std::cout << "Tests\n";


    tree.dumpToFile("test_tree.dot");
    std::cout << "Created test_tree.dot\n";

    // Test 2:
    int count1 = range_query(tree, 4, 12);
    if (count1 != 3)
        std::cout << "Wrong answer, correct is 3, and we get" <<count1<<" \n";
    else
        std::cout <<"Correct \n";
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
