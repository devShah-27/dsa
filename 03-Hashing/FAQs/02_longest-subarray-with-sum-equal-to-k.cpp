// Problem:
// Given an integer array nums of size n and an integer k,
// return the length of the longest subarray whose sum equals k.
//
// If no such subarray exists, return 0.

#include <bits/stdc++.h>
using namespace std;

// ===================================================
// BRUTE FORCE APPROACH
//
// Idea:
// Generate all possible subarrays using two loops (i, j)
// and compute their sum using a third loop.
//
// For each subarray [i..j], check if its sum equals k.
// If yes, update the maximum length.
//
// Time Complexity: O(N^3)
// Space Complexity: O(1)
// ===================================================

// int longestSubarray(vector<int> &nums, int k)
// {
//     int n = nums.size();

//     int maxLen = 0;

//     for (int i = 0; i < n; i++)
//     {
//         for (int j = i; j < n; j++)
//         {
//             int sum = 0;

//             for (int k = i; k <= j; k++)
//             {
//                 sum += nums[k];
//             }

//             if (sum == k)
//                 maxLen = max(maxLen, j - i + 1);
//         }
//     }

//     return maxLen;
// }

// ===================================================
// IMPROVED BRUTE FORCE (Eliminate inner loop)
//
// Idea:
// Instead of recomputing the sum for every subarray,
// maintain a running sum while expanding j.
//
// For a fixed i, keep adding nums[j] as j increases.
// This removes the innermost loop.
//
// Time Complexity: O(N^2)
// Space Complexity: O(1)
// ===================================================

// int longestSubarray(vector<int> &nums, int k)
// {
//     int n = nums.size();

//     int maxLen = 0;

//     for (int i = 0; i < n; i++)
//     {
//         int sum = 0;

//         for (int j = i; j < n; j++)
//         {
//             sum += nums[j];

//             if (sum == k)
//                 maxLen = max(maxLen, j - i + 1);
//         }
//     }

//     return maxLen;
// }

// ===================================================
// OPTIMAL APPROACH (PREFIX SUM + HASH MAP)
//
// Idea:
// Maintain a running prefix sum while iterating.
//
// If prefixSum == k → subarray from index 0 to i is valid.
//
// For every index i:
// • Check if (prefixSum - k) has been seen before.
// • If yes, a subarray summing to k exists between the
//   previous index and current index.
//
// Store the first occurrence of each prefix sum in a map
// to maximize subarray length.
//
// Works for arrays containing positive, negative, and zero.
//
// Time Complexity: O(N) average (unordered_map)
// Space Complexity: O(N)
// ===================================================

// int longestSubarray(vector<int> &nums, int k)
// {
//     int n = nums.size();

//     int maxLen = 0;
//     long long prefixSum = 0;

//     map<long long, int> prefixSumMap;

//     for (int i = 0; i < n; i++)
//     {
//         prefixSum += nums[i];

//         if (prefixSum == k)
//             maxLen = i + 1;

//         long long remainingSum = prefixSum - k;

//         if (prefixSumMap.find(remainingSum) != prefixSumMap.end())
//         {
//             int length = i - prefixSumMap[remainingSum];
//             maxLen = max(maxLen, length);
//         }

//         // Store only the first occurrence to maximize length
//         if (prefixSumMap.find(prefixSum) == prefixSumMap.end())
//         {
//             prefixSumMap[prefixSum] = i;
//         }
//     }

//     return maxLen;
// }

// ===================================================
// OPTIMAL APPROACH (SLIDING WINDOW - ONLY POSITIVE)
//
// Idea:
// This approach works ONLY when all elements are positive.
//
// Use two pointers (left, right) and maintain a running sum:
// • Expand right to increase sum
// • Shrink left when sum > k
// • If sum == k, update max length
//
// Since all numbers are positive, shrinking reduces sum
// and expanding increases it — making this approach valid.
//
// Time Complexity: O(N)
// Space Complexity: O(1)
//
// NOTE: This approach will fail if negative numbers exist,
// since sum behavior becomes non-monotonic.
// ===================================================

int longestSubarray(vector<int> &nums, int k)
{
    int n = nums.size();

    int left = 0, right = 0, maxLen = 0;

    long long sum = nums[0];

    while (right < n)
    {
        // Shrink window if sum exceeds k
        while (left <= right && sum > k)
        {
            sum -= nums[left];
            left++;
        }

        // Check if current window satisfies condition
        if (sum == k)
            maxLen = max(maxLen, right - left + 1);

        right++;

        if (right < n)
            sum += nums[right];
    }

    return maxLen;
}

int main()
{
    vector<int> nums = {4, 1, 1, 1, 1};

    int target = 4;

    cout << "Array: ";
    for (int it : nums)
        cout << it << " ";
    cout << endl;

    int subarray = longestSubarray(nums, target);

    cout << "Longest subarray length with target = " << target << ": " << subarray;

    return 0;
}