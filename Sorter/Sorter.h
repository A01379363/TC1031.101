#ifndef sorter_h
#define sorter_h

#include <iostream>
#include <vector>

template <typename T>
class Sorter
{
public:
    Sorter(){};
    ~Sorter(){};

    void swap(int i, int j, std::vector<T> &arr)
    {
        T aux = arr[i];
        arr[i] = arr[j];
        arr[j] = aux;
    }

    virtual void sort(std::vector<T> &arr){};
};

template <typename T>
class selectionSort : public Sorter<T>
{
public:
    selectionSort(){};
    ~selectionSort(){};

    void sort(std::vector<T> &arr)
    {
        for (size_t i = 0; i < arr.size() - 1; i++)
        {
            size_t min = i;
            for (size_t j = i + 1; j < arr.size(); j++)
            {
                if (arr[j] < arr[min])
                    min = j;
            }

            Sorter<T>::swap(i, min, arr);
        }
    }
};

template <typename T>
class bubbleSort : public Sorter<T>
{
public:
    bubbleSort(){};
    ~bubbleSort(){};

    void sort(std::vector<T> &arr)
    {
        for (size_t i = 0; i < arr.size() - 1; i++)
        {
            bool swapped = false;
            for (size_t j = i + 1; j < arr.size(); j++)
            {
                if (arr[i] > arr[j])
                {
                    Sorter<T>::swap(i, j, arr);
                    swapped = true;
                }
            }
            if (swapped == false)
                break;
        }
    }
};

template <typename T>
class insertionSort : public Sorter<T>
{
public:
    insertionSort(){};
    ~insertionSort(){};

    void sort(std::vector<T> &arr)
    {
        /*int j;
        for (size_t i = 1; i < arr.size(); i++)
        {
            j = i;
            while (j > 0 && arr[j - 1] > arr[j])
            {
                Sorter<T>::swap(j, j - 1, arr);
                j--;
            }
        }*/

        T key;
        for (size_t i = 1; i < arr.size(); i++)
        {
            key = arr[i];
            int j = i - 1;
            while (j >= 0 && arr[j] > key)
            {
                arr[j + 1] = arr[j];
                j--;
            }
            arr[j + 1] = key;
        }
    }
};

template <typename T>
class mergeSort : public Sorter<T>
{
public:
    mergeSort(){};
    ~mergeSort(){};

    void sort(std::vector<T> &arr)
    {
        merge_sort(arr, 0, arr.size() - 1);
    }

    void merge_sort(std::vector<T> &arr, int l, int r)
    {
        if (l < r)
        {
            int m = l + (r - l) / 2;

            merge_sort(arr, l, m);
            merge_sort(arr, m + 1, r);

            merge(arr, l, m, r);
        }
    }

    void merge(std::vector<T> &arr, int l, int m, int r)
    {
        std::vector<T> L, R;
        for (size_t i = l; i < m + 1; i++)
            L.push_back(arr[i]);
        for (size_t j = m + 1; j < r + 1; j++)
            R.push_back(arr[j]);

        int i = 0, j = 0, k = l;
        while (i < L.size() && j < R.size())
        {
            if (L[i] <= R[j])
            {
                arr[k] = L[i];
                i++;
            }
            else
            {
                arr[k] = R[j];
                j++;
            }
            k++;
        }

        while (i < L.size())
        {
            arr[k] = L[i];
            i++;
            k++;
        }

        while (j < R.size())
        {
            arr[k] = R[j];
            j++;
            k++;
        }
    }
};

#endif