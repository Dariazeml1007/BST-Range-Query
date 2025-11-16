#include "../include/utils.hpp"
#include <chrono>
#include <iostream>
#include <set>
#include <string>

int main()
{
    std::set<int> s;
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
                s.insert(key);
            }
        }
        else if (command == "q")
        {
            int low, high;
            if (std::cin >> low >> high)
            {
                range_query(s, low, high);
            }
        }
    }

    auto end = std::chrono::high_resolution_clock::now();
    auto duration =
        std::chrono::duration_cast<std::chrono::microseconds>(end - start);

    std::cout << "Set: " << duration.count() << " μs" << std::endl;

    return 0;
}
