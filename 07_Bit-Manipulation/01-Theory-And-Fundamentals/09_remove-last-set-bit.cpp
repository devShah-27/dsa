// Problem:
// Remove the last set bit (rightmost bit with value 1) from a given integer.
// Return the resulting number after clearing the rightmost set bit.

#include <bits/stdc++.h>
using namespace std;

// ==================================================
// OPTIMAL APPROACH
// Idea:
// Use the property of n & (n - 1), which removes the rightmost set bit from the binary representation of a number.
// All bits before the rightmost set bit remain unchanged, and that bit becomes 0.
//
// Time Complexity: O(1)
// Space Complexity: O(1)
// ==================================================

int main()
{
    int n;
    cin >> n;

    int res = n & (n - 1);

    cout << n << " after removing last set bit is " << res;

    return 0;
}