#pragma once

#include <cstddef>
#include <utility>
#include <stack>

#include "dArray.h"

template<typename TYPE>
static int Part(dArray<TYPE>& array, int left, int right)
{
    TYPE mid = array[(left + right) / 2];
    int i = left;
    int j = right;

    while (i <= j)
    {
        while (array[i] < mid) i++;
        while (array[j] > mid) j--;

        if (i >= j)
            break;

        std::swap(array[i++], array[j--]);
    }

    return j;
}

template<typename TYPE>
void QuickSort2(dArray<TYPE>& array, int left, int right)
{
    if (left < right)
    {
        int q = Part(array, left, right);
        QuickSort2(array, left, q);
        QuickSort2(array, q + 1, right);
    }
}
