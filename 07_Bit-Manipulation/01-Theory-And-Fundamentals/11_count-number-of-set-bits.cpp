// Problem:
// Count the number of set bits (bits with value 1) in the binary representation of a given integer.

#include <bits/stdc++.h>
using namespace std;

// ==================================================
// BRUTE FORCE APPROACH
// Idea:
// Traverse each bit of the number using right shift operations.
// Check the least significant bit using (copy & 1) and add it to the count.
//
// Time Complexity: O(log2(n))
// Space Complexity: O(1)
// ==================================================

// ==================================================
// OPTIMAL APPROACH
// Idea:
// Use Brian Kernighan's algorithm to remove the rightmost set bit in every iteration using (n & (n - 1)).
// The loop runs only once for every set bit present in the number.
//
// Time Complexity: O(k), where k is the number of set bits
// Space Complexity: O(1)
// ==================================================

int main()
{
    int n;
    cin >> n;

    int copy = n;

    int count = 0;

    // BRUTE FORCE
    // while (copy) // TC -> O(logN)
    // {
    //     count += (copy & 1);

    //     copy = copy >> 1;
    // }

    // OPTIMAL
    while (copy)
    {
        count++;
        copy = (copy & (copy - 1));
    }

    cout << n << "'s binary form has " << count << (count == 1 ? " one" : " ones") << endl;

    return 0;
}