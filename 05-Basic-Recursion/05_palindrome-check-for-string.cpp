// Given a string s, return true if the string is palindrome, otherwise false.

// A string is called palindrome if it reads the same forward and backward.

#include <bits/stdc++.h>
using namespace std;

bool recursiveCheckPalindrome(string &s, int left, int right)
{
    if (left >= right)
        return true;

    if (s[left] != s[right])
        return false;

    return recursiveCheckPalindrome(s, left + 1, right - 1);
}

bool palindromeCheck(string &s)
{
    bool isPalindrome = recursiveCheckPalindrome(s, 0, s.size() - 1);
    return isPalindrome;
}

int main()
{
    string s = "hannah";

    bool isPalindrome = palindromeCheck(s);

    if (isPalindrome)
        cout << s << " is a palindrome" << endl;
    else
        cout << s << " is not a palindrome" << endl;

    return 0;
}