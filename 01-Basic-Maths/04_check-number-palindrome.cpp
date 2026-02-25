// You are given an integer n. You need to check whether the number is a palindrome number or not. Return true if it's a palindrome number, otherwise return false.

// A palindrome number is a number which reads the same both left to right and right to left.

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

bool checkPalindrome(int num)
{
    int revNum = getReverseNumber(num);

    return (num == revNum);
}

int main()
{
    int input;
    cin >> input;

    bool isPalindrome = checkPalindrome(input);

    if (isPalindrome)
        cout << input << " is a Palindrome" << endl;
    else
        cout << input << " is a not Palindrome" << endl;

    return 0;
}