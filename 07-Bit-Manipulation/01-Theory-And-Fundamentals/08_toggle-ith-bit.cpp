// Problem:
// Toggle the i-th bit of a given integer.
// Toggling a bit changes 0 to 1 and 1 to 0 while keeping all other bits unchanged.

#include <bits/stdc++.h>
using namespace std;

// ==================================================
// OPTIMAL APPROACH
// Idea:
// Create a mask with only the i-th bit set using (1 << i).
// Apply XOR operation with the number to flip the i-th bit.
// XOR with 1 toggles a bit, while XOR with 0 keeps it unchanged.
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

    int res = n ^ (1 << i);

    cout << n << " after toggling ith bit is " << res;

    return 0;
}