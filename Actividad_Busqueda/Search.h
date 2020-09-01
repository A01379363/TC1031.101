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
    Search(vector<T> &v);
    ~Search();

    void fill_random(int N);
    void order();
    void print_vector();
    vector<T> get_vector();

    int sequential(T val);
    int sequential_ordered1(T val);
    int sequential_ordered2(T val, int step, int first, int last);
    int binary(T val, int first, int last);
};