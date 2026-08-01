// Problem:
// Clear the i-th bit of a given integer.
// Clearing a bit means changing its value to 0 while keeping all other bits unchanged.

#include <bits/stdc++.h>
using namespace std;

// ==================================================
// OPTIMAL APPROACH
// Idea:
// Create a mask with only the i-th bit set using (1 << i).
// Invert the mask using NOT operation to make the i-th bit 0.
// Perform AND operation with the number to clear the i-th bit.
//
// Time Complexity: O(1)
// Space Complexity: O(1)
// ==================================================

int main()
{
    int n;
    cin >> n;

    int i;
    cin >> i;

    int res = n & ~(1 << i);

    cout << n << " after clearing ith bit is " << res;

    return 0;
}