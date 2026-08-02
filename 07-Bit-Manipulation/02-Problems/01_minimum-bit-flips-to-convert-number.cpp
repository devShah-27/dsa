// Problem:
// Given two integers start and goal, find the minimum number of bit flips required to convert start into goal.
// A bit flip changes a bit from 0 to 1 or from 1 to 0.

#include <bits/stdc++.h>
using namespace std;

// ==================================================
// OPTIMAL APPROACH
// Idea:
// XOR between start and goal gives bits that are different in both numbers.
// The number of set bits in the XOR result represents the minimum flips required because only mismatched bits need to be toggled.
//
// Time Complexity: O(k), where k is the number of set bits in (start ^ goal)
// Space Complexity: O(1)
// ==================================================

// Returns the number of set bits in the given number
int countSetBits(int n)
{
    int count = 0;

    while (n)
    {
        count++;
        n = (n & (n - 1));
    }

    return count;
}

int minBitsFlip(int start, int goal)
{
    return countSetBits(start ^ goal);
}

int main()
{
    int start = 10, goal = 7;

    int ans = minBitsFlip(start, goal);

    cout << "The minimum bit flips to convert number is: " << ans;

    return 0;
}