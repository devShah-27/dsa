// Problem:
// Given an integer array nums and an integer k, find the number of nice subarrays containing exactly k odd numbers.
// A subarray is a continuous part of the array.

#include <bits/stdc++.h>
using namespace std;

// ==================================================
// OPTIMAL APPROACH (SLIDING WINDOW + AT MOST TECHNIQUE)
//
// Idea:
// Count subarrays containing at most k odd numbers and subtract the count of subarrays containing at most k - 1 odd numbers.
// The difference gives the number of subarrays containing exactly k odd numbers.
//
// Time Complexity: O(2N)
// Space Complexity: O(1)
// ==================================================

int atMost(vector<int> &nums, int k)
{
    if (k < 0)
        return 0;

    int n = nums.size(), r = 0, l = 0;

    int ans = 0, oddCount = 0;

    while (r < n)
    {
        // Add current element's contribution to the odd count.
        oddCount += (nums[r] % 2);

        // Shrink the window until it contains at most k odd numbers.
        while (oddCount > k)
        {
            oddCount -= (nums[l] % 2);
            l++;
        }

        // Every subarray ending at r and starting from l to r is valid.
        ans += (r - l + 1);

        r++;
    }

    return ans;
}

int numberOfOddSubarrays(vector<int> &nums, int k)
{
    // Exactly k odd numbers = (At most k odd numbers) - (At most k-1 odd numbers)
    return atMost(nums, k) - atMost(nums, k - 1);
}

int main()
{
    vector<int> nums = {1, 1, 2, 1, 1};
    int k = 4;

    int ans = numberOfOddSubarrays(nums, k);

    cout << "Number of nice substrings with \"" << k << "\" odd numbers is: " << ans << endl;

    return 0;
}