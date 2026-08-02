// Problem:
// Given an array where every element appears three times except one element.
// Find the element that appears only once.

#include <bits/stdc++.h>
using namespace std;

// ==================================================
// BRUTE FORCE APPROACH
// Idea:
// Store the frequency of every element using a hash map.
// Traverse the map to find the element whose frequency is exactly one.
//
// Time Complexity: O(N)
// Space Complexity: O(N)
// ==================================================

// int singleNumber(vector<int> &nums)
// {
//     unordered_map<int, int> mpp;

//     for (int it : nums)
//     {
//         mpp[it]++;
//     }

//     for (auto it : mpp)
//     {
//         if (it.second == 1)
//             return it.first;
//     }

//     return -1;
// }

// ==================================================
// BETTER APPROACH 1: BIT COUNTING
// Idea:
// Count the number of set bits at every bit position across all numbers.
// Since duplicate numbers appear three times, their contribution will be
// a multiple of three. Remaining bits belong to the unique number.
//
// Time Complexity: O(32 * N)
// Space Complexity: O(1)
// ==================================================

// int singleNumber(vector<int> &nums)
// {
//     int ans = 0;

//     for (int bitIdx = 0; bitIdx <= 31; bitIdx++)
//     {
//         int count = 0;

//         for (int it : nums)
//         {
//             if (it & (1 << bitIdx))
//                 count++;
//         }

//         if (count % 3 != 0)
//             ans |= (1 << bitIdx);
//     }

//     return ans;
// }

// ==================================================
// BETTER APPROACH 2: SORTING
// Idea:
// Sort the array so that duplicate elements appear consecutively.
// Check every group of three elements to find the element that does not follow the repeating pattern.
//
// Time Complexity: O(NlogN)
// Space Complexity: O(1)
// ==================================================

// int singleNumber(vector<int> &nums)
// {
//     sort(nums.begin(), nums.end());

//     int n = nums.size();

//     for (int i = 1; i < n; i = i + 3)
//     {
//         if (nums[i] != nums[i - 1])
//             return nums[i - 1];
//     }

//     return nums[n - 1];
// }

// ==================================================
// OPTIMAL APPROACH: BIT STATE MACHINE
// Idea:
// Maintain two variables:
// - ones: bits that have appeared exactly once
// - twos: bits that have appeared exactly twice
// Each incoming number updates these states, and after the third occurrence the bit is removed from both states.
// The remaining bits in ones represent the unique number.
//
// Time Complexity: O(N)
// Space Complexity: O(1)
// ==================================================

int singleNumber(vector<int> &nums)
{
    int ones = 0, twos = 0;

    for (int it : nums)
    {
        ones = (ones ^ it) & ~twos;
        twos = (twos ^ it) & ~ones;
    }

    return ones;
}

int main()
{
    vector<int> nums = {2, 2, 2, 3};

    int ans = singleNumber(nums);

    cout << "The single number in given array is: " << ans;

    return 0;
}