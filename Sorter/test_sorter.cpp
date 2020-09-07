#include <iostream>
#include <vector>
#include <stdlib.h>
#include "sorter.h"
#include "mytimer.h"

using namespace std;

template <typename T>
void print_vector(vector<T> arr, int N)
{
    for (size_t i = 0; i < arr.size() && i < N; i++)
    {
        cout << arr[i] << ", ";
    }
    cout << endl;
}

int main()
{
    vector<float> arr;
    int count = 100000;
    for (size_t i = 0; i < count; i++)
        arr.push_back((float)rand() / RAND_MAX);

    cout << "Unsorted: " << endl;
    print_vector(arr, 20);

    for (int i = 0; i < 10; i++)
    {
        vector<float> arr_selection = arr;
        vector<float> arr_bubble = arr;
        vector<float> arr_insertion = arr;
        vector<float> arr_merge = arr;

        cout << endl;
        DECLARE_TIMING(t1);
        START_TIMING(t1);
        selectionSort<float> sel_sort;
        sel_sort.sort(arr_selection);
        STOP_TIMING(t1);
        cout << i + 1 << ") ";
        SHOW_TIMING(t1, "Selection Sort: ");

        cout << "Selection Sorted: " << endl;
        print_vector(arr_selection, 10);

        cout << endl;
        DECLARE_TIMING(t2);
        START_TIMING(t2);
        bubbleSort<float> bub_sort;
        bub_sort.sort(arr_bubble);
        STOP_TIMING(t2);
        cout << i + 1 << ") ";
        SHOW_TIMING(t2, "Bubble Sort: ");

        cout << "Bubble Sorted: " << endl;
        print_vector(arr_bubble, 10);

        cout << endl;
        DECLARE_TIMING(t3);
        START_TIMING(t3);
        insertionSort<float> ins_sort;
        ins_sort.sort(arr_insertion);
        STOP_TIMING(t3);
        cout << i + 1 << ") ";
        SHOW_TIMING(t3, "Insertion Sort:");

        cout << "Insertion Sorted: " << endl;
        print_vector(arr_insertion, 10);

        cout << endl;
        DECLARE_TIMING(t4);
        START_TIMING(t4);
        mergeSort<float> m_sort;
        m_sort.sort(arr_merge);
        STOP_TIMING(t4);
        cout << i + 1 << ") ";
        SHOW_TIMING(t4, "Merge Sort:");

        cout << "Merge Sorted: " << endl;
        print_vector(arr_merge, 10);
    }

    return 0;
}