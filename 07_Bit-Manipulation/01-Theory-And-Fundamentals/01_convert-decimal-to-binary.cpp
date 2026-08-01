// Problem:
// Convert a given decimal number into its binary representation.
// Return the binary equivalent as a string.

#include <bits/stdc++.h>
using namespace std;

// ==================================================
// OPTIMAL APPROACH
// Idea:
// Repeatedly divide the number by 2 and store the remainder bits.
// The remainders are generated in reverse order, so reverse the result at the end to obtain the correct binary representation.
//
// Time Complexity: O(log2(n))
// Space Complexity: O(log2(n)) (for storing the binary string)
// ==================================================

string convertToBinary(int n)
{
    string res = "";

    while (n)
    {
        if (n % 2 == 1)
            res += '1';
        else
            res += '0';

        n = n / 2;
    }

    reverse(res.begin(), res.end());

    return res;
}

int main()
{
    int n;
    cin >> n;

    string binary = convertToBinary(n);

    cout << "Binary of " << n << " is " << binary << endl;

    return 0;
}