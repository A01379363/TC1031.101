#pragma once
#include <iostream>
#include <vector>

using namespace std;

template <typename T>
class Search
{
private:
    vector<T> v;

public:
    Search() = default;
    Search(vector<T> &v) : v(v) {}
    ~Search() {}

    void fill_random(int N)
    {
        for (size_t i = 0; i < N; i++)
        {
            v.push_back((T)rand() % 100000);
        }
    }

    void order()
    {
        sort(v.begin(), v.end());
    }

    void print_vector()
    {
        for (size_t i = 0; i < v.size(); i++)
            cout << v[i] << ", ";

        cout << endl;
    }

    vector<T> get_vector() { return v; }

    void push(T val)
    {
        v.push_back(val);
    }

    int sequential(T val)
    {
        for (size_t i = 0; i < v.size(); i++)
        {
            if (v[i] == val)
                return i;
        }

        return -1;
    }

    int sequential_ordered1(T val)
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

    int sequential_ordered2(T val, int step, int first, int last)
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

    int binary(T val, int first, int last, bool (*compare)(T &a, T &b))
    {
        if (last < first)
            return -1;
        else
        {
            int mid = (first + last) / 2;
            if (v[mid] == val)
                return mid;

            else if ((*compare)(val, v[mid])) // v[mid] > val
                return binary(val, first, mid - 1, compare);

            else
                return binary(val, mid + 1, last, compare);
        }
    }
};