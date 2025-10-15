#pragma once
#include <set>
#include <iterator>  // std::distance  std::iterator_traits
#include "avl_tree.hpp"

template <typename C, typename T>
typename std::iterator_traits<typename C::iterator>::difference_type
range_query(const C& s, T low, T high)
{
    if (low >= high)
        return 0;

    auto start = s.lower_bound(low);
    auto fin = s.upper_bound(high);

    return std::distance(start, fin);

}
