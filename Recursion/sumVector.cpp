#include <iostream>
#include <vector>
using namespace std;

int vectorSum(vector<int> v)
{
    if (v.size() == 0)
        return 0;

    int n = v[v.size() - 1];
    v.pop_back();
    return n + vectorSum(v);
}

int main()
{
    vector<int> v{30, 64, 17, 103, 28};
    int sum = vectorSum(v);
    cout << "Sum of elements in vector: " << sum << endl;
    return 0;
}