#include <iostream>
#include <vector>
using namespace std;

int digitSum(int n)
{
    if (n < 1)
        return 0;

    return n % 10 + digitSum(n / 10);
}

int main()
{
    int n;
    cout << "Number: ";
    cin >> n;
    cout << digitSum(n) << endl;
    return 0;
}