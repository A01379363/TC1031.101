#include "Search.cpp"
#include "mytimer.h"

int main()
{
    vector<int> v;
    int val[5] = {5, 5 * 5, 5 * 5 * 5, 5 * 5 * 5 * 5, 5 * 5 * 5 * 5 * 5};

    Search<int> mySearch(v);

    mySearch.fill_random(100000);

    for (size_t i = 0; i < 5; i++)
    {
        for (size_t j = 0; j < 10; j++)
        {
            DECLARE_TIMING(t);
            START_TIMING(t);
            cout << "Value (" << val[i] << ") found using 'sequential' at index:           " << mySearch.sequential(val[i]) << endl;
            STOP_TIMING(t);
            SHOW_TIMING(t, "SelectionSort");
            cout << endl;
        }

        cout << "------------------------------------------------------------------------------" << endl;
    }

    mySearch.order();

    for (size_t i = 0; i < 5; i++)
    {
        for (size_t j = 0; j < 10; j++)
        {
            DECLARE_TIMING(t);
            START_TIMING(t);
            cout << "Value (" << val[i] << ") found using 'sequential ordered 1' at index: " << mySearch.sequential_ordered1(val[i]) << endl;
            STOP_TIMING(t);
            SHOW_TIMING(t, "SelectionSort");
            cout << endl;
        }

        cout << "------------------------------------------------------------------------------" << endl;
    }

    for (size_t i = 0; i < 5; i++)
    {
        for (size_t j = 0; j < 10; j++)
        {
            DECLARE_TIMING(t);
            START_TIMING(t);
            cout << "Value (" << val[i] << ") found using 'sequential ordered 2' at index: " << mySearch.sequential_ordered2(val[i], 4, 0, mySearch.get_vector().size() - 1) << endl;
            STOP_TIMING(t);
            SHOW_TIMING(t, "SelectionSort");
            cout << endl;
        }

        cout << "------------------------------------------------------------------------------" << endl;
    }

    for (size_t i = 0; i < 5; i++)
    {
        for (size_t j = 0; j < 10; j++)
        {
            DECLARE_TIMING(t);
            START_TIMING(t);
            cout << "Value (" << val[i] << ") found using 'binary search' at index:        " << mySearch.binary(val[i], 0, mySearch.get_vector().size() - 1) << endl;
            STOP_TIMING(t);
            SHOW_TIMING(t, "SelectionSort");
            cout << endl;
        }

        cout << "------------------------------------------------------------------------------" << endl;
    }

    return 0;
}