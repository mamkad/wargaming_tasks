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


template<typename TYPE>
void QuickSort(dArray<TYPE>& array, int left, int right)
{
    std::stack<std::pair<int, int>> stkOper;
    int mid;

    stkOper.push({ left, right });

    while (!stkOper.empty())
    {
        left = stkOper.top().first;
        right = stkOper.top().second;
        stkOper.pop();

        if (right <= left)
            continue;

        mid = Part(array, left, right);

        if ( (mid - left) > (right - mid) )
        {
            stkOper.push({ left, mid - 1  } );
            stkOper.push({ mid + 1, right } );
        }
        else
        {
            stkOper.push({  mid + 1, right } );
            stkOper.push({  left, mid - 1  } );
        }
    }
}


template<typename TYPE>
void InsertSort(dArray<TYPE> & array, size_t array_size)
{
    long int j, i;
    TYPE key;

    for (size_t j = 1; j < array_size; ++j)
    {
        key = array[j];
  
        for(i = j - 1; i >= 0 && array[i] > key; --i)
            array[i + 1] = array[i];

        array[i + 1] = key;
    }
}
