// You are given a string s. Return true if the string is palindrome, otherwise false.

// A string is called palindrome if it reads the same forward and backward.

#include <bits/stdc++.h>
using namespace std;

bool checkPalindrome(string &str)
{
    int left = 0, right = str.size() - 1;

    while (left < right)
    {
        if (str[left] != str[right])
            return false;

        left++, right--;
    }

    return true;
}

int main()
{
    string str = "hannah";

    bool isPalindrome = checkPalindrome(str);

    if (isPalindrome)
        cout << str << " is a palindrome" << endl;
    else
        cout << str << " is not a palindrome" << endl;

    return 0;
}