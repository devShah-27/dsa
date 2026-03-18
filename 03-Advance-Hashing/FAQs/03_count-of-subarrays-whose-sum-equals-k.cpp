// Problem:
// Given an integer array nums and an integer k,
// return the total number of subarrays whose sum equals k.
//
// A subarray is a contiguous sequence of elements.

#include <bits/stdc++.h>
using namespace std;

// ===================================================
// BRUTE FORCE APPROACH
//
// Idea:
// Generate all possible subarrays using three nested loops.
// For every subarray [i..j], compute its sum using a third loop.
// If the sum equals k, increment the count.
//
// Time Complexity: O(N^3)
// Space Complexity: O(1)
// ===================================================

// int subarraySum(vector<int> &nums, int k)
// {
//     int n = nums.size(), subarrayCount = 0;

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
//                 subarrayCount++;
//         }
//     }

//     return subarrayCount;
// }

// ===================================================
// IMPROVED BRUTE FORCE
//
// Idea:
// Eliminate the innermost loop by maintaining a running sum.
// For each starting index i, keep adding nums[j] as j expands.
//
// This avoids recomputing sums for overlapping subarrays.
//
// Time Complexity: O(N^2)
// Space Complexity: O(1)
// ===================================================

// int subarraySum(vector<int> &nums, int k)
// {
//     int n = nums.size(), subarrayCount = 0;

//     for (int i = 0; i < n; i++)
//     {
//         int sum = 0;

//         for (int j = i; j < n; j++)
//         {
//             sum += nums[j];

//             if (sum == k)
//                 subarrayCount++;
//         }
//     }

//     return subarrayCount;
// }

// ===================================================
// OPTIMAL APPROACH (PREFIX SUM + HASH MAP)
//
// Idea:
// Use prefix sum to track cumulative sum up to index i.
//
// For each index:
// • currentPrefixSum = sum of elements from 0 to i
// • We want to find number of previous prefix sums such that:
//   previousPrefixSum = currentPrefixSum - k
//
// Store frequencies of prefix sums in a hashmap.
// This allows counting multiple valid subarrays ending at i.
//
// Initialize map with prefixSum 0 having frequency 1 to handle
// subarrays starting from index 0.
//
// Time Complexity: O(N) average
// Space Complexity: O(N)
// ===================================================

int subarraySum(vector<int> &nums, int k)
{
    int n = nums.size(), subarrayCount = 0, currentPrefixSum = 0;

    unordered_map<int, int> prefixSumMap; // {prefix_sum -> frequency}

    prefixSumMap[0] = 1;

    for (int i = 0; i < n; i++)
    {
        currentPrefixSum += nums[i];

        int sumToRemove = currentPrefixSum - k;

        if (prefixSumMap.find(sumToRemove) != prefixSumMap.end())
        {
            subarrayCount += prefixSumMap[sumToRemove];
        }

        prefixSumMap[currentPrefixSum]++;
    }

    return subarrayCount;
}

int main()
{
    vector<int> nums = {3, 1, 2, 4};

    int target = 6;

    cout << "Array: ";
    for (int it : nums)
        cout << it << " ";
    cout << endl;

    int subarray = subarraySum(nums, target);

    cout << "No. of subarray for target sum " << target << ": " << subarray;

    return 0;
}