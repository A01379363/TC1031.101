#include "Search.h"
#include <algorithm>
#include <stdlib.h>

template <typename T>
Search<T>::Search(vector<T> &v) : v(v) {}

template <typename T>
Search<T>::~Search() {}

template <typename T>
void Search<T>::fill_random(int N)
{
    for (size_t i = 0; i < N; i++)
    {
        v.push_back((T)rand() % 100000);
    }
}

template <typename T>
void Search<T>::order()
{
    sort(v.begin(), v.end());
}

template <typename T>
void Search<T>::print_vector()
{
    for (size_t i = 0; i < v.size(); i++)
        cout << v[i] << ", ";

    cout << endl;
}

template <typename T>
vector<T> Search<T>::get_vector()
{
    return v;
}

template <typename T>
int Search<T>::sequential(T val)
{
    for (size_t i = 0; i < v.size(); i++)
    {
        if (v[i] == val)
            return i;
    }

    return -1;
}

template <typename T>
int Search<T>::sequential_ordered1(T val)
{
    for (size_t i = 0; i < v.size(); i++)
    {
        if (v[i] == val)
            return i;

        else if (v[i] > val)
            break;
    }

    return -1;
}

template <typename T>
int Search<T>::sequential_ordered2(T val, int step, int first, int last)
{
    if (first > last)
        return -1;

    if (v[first] == val)
        return first;

    else if (v[last] == val)
        return last;

    else if (v[first] > val)
        return sequential_ordered2(val, step / 2, first - step, first - 1);

    return sequential_ordered2(val, step, first + step, last - 1);
}

template <typename T>
int Search<T>::binary(T val, int first, int last)
{
    if (last < first)
        return -1;
    else
    {
        int mid = (first + last) / 2;
        if (v[mid] == val)
            return mid;

        else if (v[mid] > val)
            return binary(val, first, mid - 1);

        else
            return binary(val, mid + 1, last);
    }
}