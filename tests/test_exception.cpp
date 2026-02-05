#include "../include/avl_tree.hpp"
#include <gtest/gtest.h>
#include <memory>
#include <stdexcept>
#include <vector>

class ThrowOnCopy
{
    int value;

public:
    explicit ThrowOnCopy(int v) : value(v)
    {
    }

    ThrowOnCopy(const ThrowOnCopy& other)
    {
        if (other.value == 999)
        {
            throw std::runtime_error("Copy failed");
        }
        value = other.value;
    }

    ThrowOnCopy(ThrowOnCopy&&) noexcept = default;
    ThrowOnCopy& operator=(const ThrowOnCopy&) = default;
    ThrowOnCopy& operator=(ThrowOnCopy&&) noexcept = default;

    bool operator<(const ThrowOnCopy& other) const noexcept
    {
        return value < other.value;
    }
};

class ThrowOnConstruction
{
    int value;

public:
    static bool should_throw;

    explicit ThrowOnConstruction(int v) : value(v)
    {
        if (should_throw && v == 500)
        {
            throw std::runtime_error("Construction failed");
        }
    }

    bool operator<(const ThrowOnConstruction& other) const noexcept
    {
        return value < other.value;
    }
};

bool ThrowOnConstruction::should_throw = false;

TEST(ExceptionSafety, Destructor_NoThrowGuarantee)
{

    {
        auto empty_tree = std::make_unique<Trees::MyTree<int>>();
        EXPECT_NO_THROW(empty_tree.reset());
    }

    {
        auto tree = std::make_unique<Trees::MyTree<int>>();
        for (int i = 0; i < 100; ++i)
        {
            tree->insert(i);
        }
        EXPECT_NO_THROW(tree.reset());
    }

    {
        Trees::MyTree<int> tree;
        for (int i = 0; i < 50; ++i)
        {
            tree.insert(i);
        }
        EXPECT_NO_THROW(tree.clear());
        EXPECT_EQ(tree.begin(), tree.end());
    }
}

TEST(ExceptionSafety, Assignment_CopyAndSwapStrongGuarantee)
{
    Trees::MyTree<int> source;
    source.insert(10);
    source.insert(20);
    source.insert(30);

    Trees::MyTree<int> destination;
    destination.insert(1);
    destination.insert(2);

    destination = source;

    EXPECT_EQ(std::distance(source.begin(), source.end()),
              std::distance(destination.begin(), destination.end()));

    auto source_it = source.begin();
    auto dest_it = destination.begin();
    while (source_it != source.end() && dest_it != destination.end())
    {
        EXPECT_EQ(*source_it, *dest_it);
        ++source_it;
        ++dest_it;
    }
}

TEST(ExceptionSafety, Swap_Noexcept)
{
    Trees::MyTree<int> tree1, tree2;
    tree1.insert(1);
    tree2.insert(2);

    EXPECT_TRUE(noexcept(swap(tree1, tree2)));
    EXPECT_NO_THROW(swap(tree1, tree2));
}
