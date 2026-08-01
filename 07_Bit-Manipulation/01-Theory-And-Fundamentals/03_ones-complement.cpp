// Problem:
// Find the one's complement of a given binary string.
// Flip every bit in the binary representation: 0 becomes 1 and 1 becomes 0.

#include <bits/stdc++.h>
using namespace std;

// ==================================================
// OPTIMAL APPROACH
// Idea:
// Traverse the binary string and invert each bit individually.
// Replace every '0' with '1' and every '1' with '0' to obtain the one's complement.
//
// Time Complexity: O(n), where n is the length of the binary string
// Space Complexity: O(n), for storing the resulting string
// ==================================================

string onesComplement(string st)
{
    string res = "";

    for (char it : st)
    {
        if (it == '0')
            res += '1';
        else
            res += '0';
    }

    return res;
}

int main()
{
    string st;
    cin >> st;

    string res = onesComplement(st);

    cout << "One's complement of " << st << " is " << res << endl;

    return 0;
}