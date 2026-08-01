// Problem:
// Check whether a given integer is a power of two.
// A number is a power of two if its binary representation contains exactly one set bit.

#include <bits/stdc++.h>
using namespace std;

// ==================================================
// OPTIMAL APPROACH
// Idea:
// A power of two has only one bit set in its binary representation.
// Using n & (n - 1) removes the only set bit, making the result 0.
// If the result is 0, the number is a power of two.
//
// Time Complexity: O(1)
// Space Complexity: O(1)
// ==================================================

int main()
{
    int n;
    cin >> n;

    int res = n & (n - 1);

    if (res == 0)
        cout << n << " is a power of two";
    else
        cout << n << " is not a power of two";

    return 0;
}