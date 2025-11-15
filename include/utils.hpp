#pragma once
#include "avl_tree.hpp"
#include <functional> // для std::less
#include <iterator>   // std::distance

template <typename C, typename T>
typename C::difference_type range_query(const C& s, T low, T high)
{
    if (std::greater_equal<T>{}(low, high))
        return 0;

    auto start = s.lower_bound(low);
    auto fin = s.upper_bound(high);
    return std::distance(start, fin);
}
