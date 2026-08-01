// Problem:
// Convert a given binary string into its decimal representation.
// Return the corresponding decimal value of the binary number.

#include <bits/stdc++.h>
using namespace std;

// ==================================================
// OPTIMAL APPROACH
// Idea:
// Traverse the binary string from right to left, where each position represents an increasing power of 2.
// Add the corresponding power of 2 whenever the current bit is '1'.
//
// Time Complexity: O(n), where n is the length of the binary string
// Space Complexity: O(1)
// ==================================================

int convertToDecimal(string st)
{
    int len = st.size(), res = 0, powTwo = 1;

    for (int i = len - 1; i >= 0; i--)
    {
        if (st[i] == '1')
            res = res + powTwo;

        powTwo *= 2;
    }

    return res;
}

int main()
{
    string st;
    cin >> st;

    int decimal = convertToDecimal(st);

    cout << "Decimal of " << st << " is " << decimal << endl;

    return 0;
}