#include <iostream>
using namespace std;

string invert(string s)
{
    if (s.size() == 0)
        return "";

    string new_s;
    new_s = new_s + s[s.size() - 1];
    s.pop_back();

    return new_s + invert(s);
}

int main()
{
    string s;
    cout << "Number to invert: ";
    cin >> s;
    cout << invert(s) << endl;
    return 0;
}