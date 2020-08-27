#include <iostream>
#include <vector>
#include <numeric>
using namespace std;

int vectorSum(vector<int> v)
{
    if (v.size() == 0)
        return 0;

    int n = v[v.size() - 1];
    v.pop_back();
    return n + vectorSum(v);
}

int matrixSum(vector<vector<int>> m)
{
    if (m.size() == 0)
        return 0;

    int n = accumulate(m[m.size() - 1].begin(), m[m.size() - 1].end(), 0);
    m.pop_back();
    return n + matrixSum(m);
}

int main()
{
    vector<int> v{30, 64, 17, 103, 28};
    int sum = vectorSum(v);
    cout << "Sum of elements in vector: " << sum << endl;

    vector<vector<int>> m{
        {1, 2, 3},
        {1, 2, 3},
        {1, 2, 3},
        {1, 2, 3},
    };
    int sum2 = matrixSum(m);
    cout << "Sum of elements in matrix: " << sum2 << endl;

    return 0;
}