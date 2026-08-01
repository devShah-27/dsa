// Problem:
// Check whether the i-th bit of a given integer is set or not.
// A bit is considered set if its value is 1, otherwise it is unset.

#include <bits/stdc++.h>
using namespace std;

int main()
{
    int n;
    cin >> n;

    int i;
    cin >> i;

    // ==================================================
    // OPTIMAL APPROACH 1: USING LEFT SHIFT
    // Idea:
    // Create a mask with only the i-th bit set using (1 << i).
    // Perform AND operation with the number to check whether the i-th bit is present in the original number.
    //
    // Time Complexity: O(1)
    // Space Complexity: O(1)
    // ==================================================

    if ((n & (1 << i)) > 0)
        cout << "Bit " << i << " is set in " << n << " (Left Shift)";
    else
        cout << "Bit " << i << " is not set in " << n << " (Left Shift)";

    cout << endl;

    // ==================================================
    // OPTIMAL APPROACH 2: USING RIGHT SHIFT
    // Idea:
    // Right shift the number by i positions to bring the required bit to the least significant position, then check it using AND with 1.
    //
    // Time Complexity: O(1)
    // Space Complexity: O(1)
    // ==================================================

    if (((n >> i) & 1) > 0)
        cout
            << "Bit " << i << " is set in " << n << " (Right Shift)";
    else
        cout << "Bit " << i << " is not set in " << n << " (Right Shift)";

    return 0;
}