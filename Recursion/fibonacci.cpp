#include <iostream>
#include <map>
using namespace std;

int fibonacci(int n)
{
    if (n < 0)
        throw "illegal negative number";

    if (n < 2)
        return n;

    return fibonacci(n - 1) + fibonacci(n - 2);
}

int fibonacci_v2(int n, map<int, int> &cache)
{
    if (n < 0)
        throw "illegal negative number";

    if (n < 2)
        return n;

    if (cache.find(n) != cache.end())
        return cache[n];

    int val = fibonacci_v2(n - 1, cache) + fibonacci_v2(n - 2, cache);
    cache[n] = val;
    return val;
}

int main()
{
    int ans, number;
    cout << "Enter the index for the Fibonacci sequence: ";
    cin >> number;
    ans = fibonacci(number);
    cout << ans << endl;

    map<int, int> cache;
    int ans2 = fibonacci_v2(number, cache);
    cout << ans2 << endl;

    return 0;
}