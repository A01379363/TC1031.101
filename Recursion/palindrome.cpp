#include <iostream>
using namespace std;

string isPalindrome(string s)
{
    if (s.empty())
        return "Palindrome";
    if (s[0] != s[s.size() - 1])
        return "Not a palindrome";

    s.erase(0, 1);
    if (s.size() > 0)
        s.pop_back();

    return isPalindrome(s);
}

int main()
{
    string word;
    cout << "Enter word: ";
    cin >> word;
    cout << isPalindrome(word) << endl;
    return 0;
}