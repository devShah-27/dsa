// Problem:
// Given an array of integers and a target sum k, count the number of non-empty subsequences whose elements add up exactly to k.

#include <bits/stdc++.h>
using namespace std;

// ============================================================================
// RECURSIVE BACKTRACKING APPROACH
//
// Idea:
// For every element, make two choices:
// 1. Include the current element in the subsequence.
// 2. Exclude the current element from the subsequence.
// Whenever the current sum becomes equal to k, count that subsequence as a valid answer and stop exploring further from that path.
//
// Time Complexity: O(2^n)
// Space Complexity: O(n) due to recursion stack
// ============================================================================

int recursiveCheck(int index, vector<int> nums, int n, int k, int sum, int count)
{
    // A valid subsequence is found when the current sum matches the target.
    if (sum == k)
    {
        count += 1;
        return count;
    }

    // No more elements left to process.
    if (index == n)
        return 0;

    // Choice 1: Include the current element.
    int path1Count = recursiveCheck(index + 1, nums, n, k, sum + nums[index], count);

    // Choice 2: Exclude the current element.
    int path2Count = recursiveCheck(index + 1, nums, n, k, sum, count);

    // Total valid subsequences from both choices.
    return path1Count + path2Count;
}

int countSubsequenceWithTargetSum(vector<int> &nums, int k)
{
    int n = nums.size();

    return recursiveCheck(0, nums, n, k, 0, 0);
}

int main()
{
    vector<int> nums = {1, 2, 3, 4, 5};
    int target = 5;

    cout << "Number of subsequences with target sum " << target << ": "
         << countSubsequenceWithTargetSum(nums, target) << endl;

    return 0;
}