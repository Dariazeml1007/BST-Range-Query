#include <iostream>
#include <chrono>
#include <set>
#include <random>
#include "avl_tree.hpp"
#include "utils.hpp"

void comparePerformance()
{
    std::cout << "=== Comparison with std::set ===\n";

    Trees::MyTree<int> my_tree;
    std::set<int> std_set;

    std::random_device rd;
    std::mt19937 gen(rd());
    std::uniform_int_distribution<int> dist(0, 100000);

    for (int i = 0; i < 10000; i++)
    {
        int val = dist(gen);
        my_tree.insert(val);
        std_set.insert(val);
    }

    auto start1 = std::chrono::high_resolution_clock::now();
    for (int i = 0; i < 1000; i++)
    {
        int low = dist(gen) % 50000;
        int high = low + dist(gen) % 50000;
        range_query(my_tree, low, high);
    }
    auto end1 = std::chrono::high_resolution_clock::now();


    auto start2 = std::chrono::high_resolution_clock::now();
    for (int i = 0; i < 1000; i++)
    {
        int low = dist(gen) % 50000;
        int high = low + dist(gen) % 50000;
        range_query(std_set, low, high);
    }
    auto end2 = std::chrono::high_resolution_clock::now();

    auto my_time = std::chrono::duration_cast<std::chrono::milliseconds>(end1 - start1);
    auto std_time = std::chrono::duration_cast<std::chrono::milliseconds>(end2 - start2);

    std::cout << "MyTree: " << my_time.count() << " ms\n";
    std::cout << "std::set: " << std_time.count() << " ms\n";
    std::cout << "Speed ratio: " << (double)std_time.count() / my_time.count() << "x\n";
}

int main()
{
    comparePerformance();
    return 0;
}
