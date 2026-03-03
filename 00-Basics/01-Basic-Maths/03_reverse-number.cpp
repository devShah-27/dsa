// You are given an integer n. Return the integer formed by placing the digits of n in reverse order.

#include <bits/stdc++.h>
using namespace std;

int getReverseNumber(int num)
{
    int revNum = 0;

    while (num > 0)
    {
        int lastDigit = num % 10;
        revNum = (revNum * 10) + lastDigit;
        num = num / 10;
    }

    return revNum;
}

int main()
{
    int input;
    cin >> input;

    int reverseNumber = getReverseNumber(input);

    cout << "Reverse of " << input << " is " << reverseNumber << endl;
    return 0;
}