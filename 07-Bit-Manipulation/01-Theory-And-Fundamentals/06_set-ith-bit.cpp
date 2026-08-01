// Problem:
// Set the i-th bit of a given integer.
// Setting a bit means changing its value to 1 while keeping all other bits unchanged.

#include <bits/stdc++.h>
using namespace std;

// ==================================================
// OPTIMAL APPROACH
// Idea:
// Create a mask with only the i-th bit set using (1 << i).
// Perform OR operation with the number to force the i-th bit to become 1.
// OR operation preserves all other bits of the original number.
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

    int res = n | (1 << i);

    cout << n << " after setting ith bit is " << res;

    return 0;
}