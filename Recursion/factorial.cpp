#include <iostream>
using namespace std;

int factorial(int n)
{
    if (n < 0)
        throw "illegal negative number";

    if (n == 0)
        return 1;

    if (n > 0)
        return n * factorial(n - 1);
}

int main()
{
    int ans, number;
    cout << "Enter number to compute the factorial: ";
    cin >> number;
    ans = factorial(number);
    cout << "The factorial is: " << ans << endl;
    return 0;
}