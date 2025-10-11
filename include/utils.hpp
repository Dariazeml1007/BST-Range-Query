// utils.hpp
#pragma once //multiple inclusion protection

template<typename Iterator> //iterator argument for using various type
int mydistance(Iterator start, Iterator end)
{
    int count = 0;
    while (start != end)
    {
        ++count;
        ++start;
    }
    return count;
}

template <typename C, typename T>
int range_query(const C& s, T low, T high)//Generic function for comparing my container and std::set

{
    if (low >= high)
        return 0;

    using itt = typename C::iterator;
    itt start = s.lower_bound(low);
    itt fin = s.upper_bound(high);
    return mydistance(start, fin);
}
