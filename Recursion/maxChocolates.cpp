#include <iostream>
using namespace std;

int wrapChoc(int chocBought, int wrap)
{
    if (chocBought < wrap)
        return 0;

    int newChoc = chocBought / wrap;

    return newChoc + wrapChoc(newChoc + chocBought % wrap, wrap);
}

int maxChoc(int money, int price, int wrap)
{
    int chocBought = money / price;

    return chocBought + wrapChoc(chocBought, wrap);
}

int main()
{
    cout << maxChoc(20, 3, 5) << endl;
    return 0;
}
