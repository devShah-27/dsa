// Given a string s, representing a large integer, the task is to return the largest-valued odd integer (as a string) that is a substring of the given string s.

// The number returned should not have leading zero's. But the given input string may have leading zero. (If no odd number is found, then return empty string.)

#include <bits/stdc++.h>
using namespace std;

string getMaxOddSubstr(string &str)
{
    int left = -1, right = -1;

    for (int i = str.size() - 1; i >= 0; i--)
    {
        if (str[i] % 2 == 1)
        {
            right = i;
            break;
        }
    }

    if (right == -1)
        return "";

    for (int i = 0; i < str.size(); i++)
    {
        if (str[i] != '0')
        {
            left = i;
            break;
        }
    }

    return str.substr(left, right - left + 1);
}

int main()
{
    string str = "00203456689";

    string maxOddSubstr = getMaxOddSubstr(str);

    cout << "Max odd substring of " << str << " is " << maxOddSubstr << endl;

    return 0;
}