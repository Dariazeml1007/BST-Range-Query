#include <gtest/gtest.h>
#include <set>
#include "../include/avl_tree.hpp"
#include "../include/utils.hpp"

TEST(HomeworkTest, ExactHomeworkExample)
{
     Trees::MyTree<int, std::less<int>> tree;

    // Вход: k 10 k 20 q 8 31 q 6 9 k 30 k 40 q 15 40
    tree.insert(10);
    tree.insert(20);

    // Первый запрос: q 8 31
    EXPECT_EQ(range_query(tree, 8, 31), 2);  // Ожидается: 2

    // Второй запрос: q 6 9
    EXPECT_EQ(range_query(tree, 6, 9), 0);   // Ожидается: 0

    tree.insert(30);
    tree.insert(40);

    // Третий запрос: q 15 40
    EXPECT_EQ(range_query(tree, 15, 40), 3); // Ожидается: 3
}

TEST(HomeworkTest, CompareWithStdSet)
{
     Trees::MyTree<int, std::less<int>> my_tree;
    std::set<int> std_set;

    // Те же операции что в домашке
    my_tree.insert(10); std_set.insert(10);
    my_tree.insert(20); std_set.insert(20);

    int my_result1 = range_query(my_tree, 8, 31);
    int std_result1 = range_query(std_set, 8, 31);
    EXPECT_EQ(my_result1, std_result1);

    int my_result2 = range_query(my_tree, 6, 9);
    int std_result2 = range_query(std_set, 6, 9);
    EXPECT_EQ(my_result2, std_result2);

    my_tree.insert(30); std_set.insert(30);
    my_tree.insert(40); std_set.insert(40);

    int my_result3 = range_query(my_tree, 15, 40);
    int std_result3 = range_query(std_set, 15, 40);
    EXPECT_EQ(my_result3, std_result3);
}

TEST(HomeworkTest, EdgeCasesFromHomework)
{
     Trees::MyTree<int, std::less<int>> tree;

    // Пустое дерево
    EXPECT_EQ(range_query(tree, 1, 10), 0);

    // Обратный диапазон (второй меньше первого)
    EXPECT_EQ(range_query(tree, 10, 5), 0);

    // Границы равны
    EXPECT_EQ(range_query(tree, 5, 5), 0);

    // Добавляем элементы
    tree.insert(5);
    tree.insert(10);
    tree.insert(15);

    // Граничные случаи
    EXPECT_EQ(range_query(tree, 4, 6), 1);   // 5
    EXPECT_EQ(range_query(tree, 5, 10), 1);  // 10 (5 исключается)
    EXPECT_EQ(range_query(tree, 9, 16), 2);  // 10, 15
}

TEST(HomeworkTest, MultipleElements)
{
     Trees::MyTree<int, std::less<int>> tree;

    // Вставляем много элементов
    for (int i = 0; i < 10; i++) {
        tree.insert(i * 10);  // 0, 10, 20, ..., 90
    }

    EXPECT_EQ(range_query(tree, 5, 25), 2);   // 10, 20
    EXPECT_EQ(range_query(tree, 15, 85), 7);  // 20, 30, 40, 50, 60, 70, 80
    EXPECT_EQ(range_query(tree, 95, 100), 0); // за пределами
    EXPECT_EQ(range_query(tree, -10, 5), 1);  // 0
}
