#include <iostream>
#include <map>
using namespace std;
// T(n) = T(n-1) + T(n-2) + 6
int fibonacci(int n)
{
    if (n < 0)                           // O(1)
        throw "illegal negative number"; // O(1)

    if (n < 2)    // O(1)
        return n; // O(1)

    return fibonacci(n - 1) + fibonacci(n - 2); // T(n-1) + T(n-2) + 2
} // This Function is O(2^n)

// T(n) = T(n-1) + T(n-2) + 11
int fibonacci_v2(int n, map<int, int> &cache)
{
    if (n < 0)                           // O(1)
        throw "illegal negative number"; // O(1)

    if (n < 2)    // O(1)
        return n; // O(1)

    if (cache.find(n) != cache.end()) // O(1)
        return cache[n];              // O(1)

    // T(n-1) + T(n-2) + 2 but T(n-2) is in the cache which would make it O(1)
    int val = fibonacci_v2(n - 1, cache) + fibonacci_v2(n - 2, cache); // therefore T(n-1) + 1
    cache[n] = val;                                                    // O(1)
    return val;                                                        // O(1)
} // T(n) = T(n-1) + 1 = T(n-n) + n = T(0) + n = 2 + n = O(2+n)
// This funtion is O(n)

// T(n) = n + 11
int fibonacci_v3(int n)
{
    int a = 0, b = 1, ans;          // O(1)
    for (int i = 0; i < n - 1; i++) // O(n)
    {
        ans = a + b; // O(1)
        a = b;       // O(1)
        b = ans;     // O(1)
    }
    return ans; // O(1)
} // This function is O(n)

int main()
{
    int ans, number;
    cout << "Enter the index for the Fibonacci sequence: ";
    cin >> number;
    ans = fibonacci(number);
    cout << "Recursive: " << ans << endl;

    map<int, int> cache;
    int ans2 = fibonacci_v2(number, cache);
    cout << "Recursive Memory Cache: " << ans2 << endl;

    int ans3 = fibonacci_v3(number);
    cout << "Iterative: " << ans3 << endl;

    return 0;
}