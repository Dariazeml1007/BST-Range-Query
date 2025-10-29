#include <gtest/gtest.h>
#include <set>
#include "../include/avl_tree.hpp"
#include "../include/utils.hpp"

TEST(AVLTreeTest, ExactHomeworkExample)
{
    Trees::MyTree<int, std::less<int>> tree;

    tree.insert(10);
    tree.insert(20);
    EXPECT_EQ(range_query(tree, 8, 31), 2);
    EXPECT_EQ(range_query(tree, 6, 9), 0);

    tree.insert(30);
    tree.insert(40);
    EXPECT_EQ(range_query(tree, 15, 40), 3);
}


TEST(AVLTreeTest, EmptyTreeAndEdgeCases)
{
    Trees::MyTree<int, std::less<int>> tree;

   EXPECT_EQ(range_query(tree, 1, 10), 0);
   EXPECT_EQ(range_query(tree, 10, 5), 0);
   EXPECT_EQ(range_query(tree, 5, 5), 0);

    tree.insert(5);
    tree.insert(10);
    tree.insert(15);


    EXPECT_EQ(range_query(tree, 5, 10), 1);

    EXPECT_EQ(range_query(tree, 9, 16), 2);
}

TEST(AVLTreeTest, MultipleElementsRangeQueries)
{
    Trees::MyTree<int, std::less<int>> tree;

    for (int i = 0; i < 10; i++)
    {
        tree.insert(i * 10);
    }

    EXPECT_EQ(range_query(tree, 5, 25), 2);
    EXPECT_EQ(range_query(tree, 15, 85), 7);
    EXPECT_EQ(range_query(tree, 95, 100), 0);
    EXPECT_EQ(range_query(tree, -10, 5), 1);
}

TEST(AVLTreeTest, SingleElementTree)
{
    Trees::MyTree<int, std::less<int>> tree;
    tree.insert(42);

    EXPECT_EQ(range_query(tree, 40, 45), 1);
    EXPECT_EQ(range_query(tree, 42, 42), 0);
    EXPECT_EQ(range_query(tree, 50, 60), 0);
    EXPECT_EQ(range_query(tree, 30, 40), 0);
}
