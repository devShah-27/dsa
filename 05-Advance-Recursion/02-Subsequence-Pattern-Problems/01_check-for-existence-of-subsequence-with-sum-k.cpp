// Problem:
// Given an array of integers and a target sum k, determine whether there exists any subsequence whose elements add up exactly to k.
// Return true if such a subsequence exists, otherwise return false.

#include <bits/stdc++.h>
using namespace std;

// ============================================================================
// RECURSIVE BACKTRACKING APPROACH
//
// Idea:
// For every element, make two choices:
// 1. Include the current element in the subsequence.
// 2. Exclude the current element from the subsequence.
// If any choice leads to a subsequence with sum equal to k, return true.
//
// Time Complexity: O(2^n)
// Space Complexity: O(n) due to recursion stack
// ============================================================================

bool recursiveCheck(int index, vector<int> nums, int n, int k, int sum)
{
    // If current sum reaches the target, a valid subsequence is found.
    if (sum == k)
        return true;

    // If all elements are processed and target is not reached, return false.
    if (index == n)
        return false;

    // Choice 1: Include the current element.
    bool path1 = recursiveCheck(index + 1, nums, n, k, sum + nums[index]);

    // Early termination if a valid subsequence is found.
    if (path1)
        return true;

    // Choice 2: Exclude the current element.
    bool path2 = recursiveCheck(index + 1, nums, n, k, sum);

    return path2;
}

bool checkSubsequenceSum(vector<int> &nums, int k)
{
    int n = nums.size();

    return recursiveCheck(0, nums, n, k, 0);
}

int main()
{
    vector<int> nums = {1, 2, 3, 4};
    int target = 5;

    cout << checkSubsequenceSum(nums, target); // Expected output: true

    return 0;
}