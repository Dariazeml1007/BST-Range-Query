#include "bin_tree.hpp"
#include "tree_dump.hpp"
#include <iostream>

#ifdef RUN_TESTS
void runTests()
{
    std::cout << "=== TEST MODE ===\n";

    MyTree tree;

    // Test 1:
    tree.insert(10);
    tree.insert(5);
    tree.insert(15);
    tree.insert(3);
    tree.insert(7);

    std::cout << "Тестовая вставка завершена\n";


    TreeDumper::dumpToFile(tree, "test_tree.dot");
    std::cout << "Создан test_tree.dot\n";

    // Test 2:
    int count1 = tree.countInRange(4, 12);
    std::cout << "countInRange(4, 12) = " << count1 << "\n";

    // Test 3:
    tree.insert(20);
    tree.insert(1);

    int count2 = tree.countInRange(0, 100);
    std::cout << "countInRange(0, 100) = " << count2 << "\n";
}
#else
void userInput()
{
    MyTree tree;
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
                int count = tree.countInRange(low, high);
                std::cout << count << " ";
            }
        }
        else if (command == "dump")
        {

            TreeDumper::dumpToFile(tree, "tree.dot");
            std::cout << "[DEBUG] Создан tree.dot\n";
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
