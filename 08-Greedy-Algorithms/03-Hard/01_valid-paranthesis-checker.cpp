#include <bits/stdc++.h>
using namespace std;

// BRUTE FORCE
// bool helperFun(string s, int idx, int count)
// {
//     if (count < 0)
//         return false;

//     if (idx == s.size())
//         return count == 0;

//     if (s[idx] == '(')
//         return helperFun(s, idx + 1, count + 1);
//     else if (s[idx] == ')')
//         return helperFun(s, idx + 1, count - 1);

//     return helperFun(s, idx + 1, count + 1) | helperFun(s, idx + 1, count - 1) | helperFun(s, idx + 1, count);
// }

// bool isValid(string s) // TC -> O(3^N), SC ->O(N)
// {
//     return helperFun(s, 0, 0);
// }

// OPTIMAL
bool isValid(string s) // TC ->O(N), SC -> O(1)
{
    int minOpen = 0, maxOpen = 0;

    for (char it : s)
    {
        if (it == '(')
        {
            minOpen++;
            maxOpen++;
        }
        else if (it == ')')
        {
            minOpen--;
            maxOpen--;
        }
        else
        {
            minOpen--;
            maxOpen++;
        }

        if (minOpen < 0)
            minOpen = 0;

        if (maxOpen < 0)
            return false;
    }

    return (minOpen == 0);
}

int main()
{
    string s = "())()";

    int ans = isValid(s);

    if (ans)
        cout << "The given string is valid.";
    else
        cout << "The given string is not valid";

    return 0;
}