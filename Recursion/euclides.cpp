#include <iostream>
using namespace std;

int euclides(int m, int n)
{
    if (m < n)
        throw "illegal set of numbers";

    if (m % n == 0)
        return n;

    return euclides(n, m % n);
}

int main()
{
    int ans, num1, num2;
    cout << "First number: ";
    cin >> num1;
    cout << "Second number: ";
    cin >> num2;
    ans = euclides(num1, num2);
    cout << "GCD: " << ans << endl;

    return 0;
}