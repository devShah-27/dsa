// Problem:
// Given an array of n integers, return the sum of every possible subset.
// The order of the subset sums in the output does not matter.

#include <bits/stdc++.h>
using namespace std;

// ============================================================================
// RECURSIVE BACKTRACKING APPROACH
//
// Idea:
// For every element, make two choices:
// 1. Include the current element in the subset sum.
// 2. Exclude the current element from the subset sum.
// When all elements are processed, store the generated subset sum.
//
// Time Complexity: O(2^n)
// Space Complexity: O(n) due to recursion stack
// ============================================================================

void recursiveSubsetSums(vector<int> &nums, int n, vector<int> &result, int index, int sum)
{
    // Base case: all elements have been considered.
    // Store the sum of the current subset.
    if (index == n)
    {
        result.push_back(sum);
        return;
    }

    // Choice 1: Include the current element.
    sum += nums[index];

    recursiveSubsetSums(nums, n, result, index + 1, sum);

    // Backtrack: remove the current element contribution.
    sum -= nums[index];

    // Choice 2: Exclude the current element.
    recursiveSubsetSums(nums, n, result, index + 1, sum);
}

vector<int> subsetSums(vector<int> &nums)
{
    vector<int> result;

    int n = nums.size();

    recursiveSubsetSums(nums, n, result, 0, 0);

    return result;
}

int main()
{
    vector<int> nums = {5, 2, 1};

    vector<int> result = subsetSums(nums);

    cout << "Subset sums are: " << endl;

    for (int sum : result)
    {
        cout << sum << " " << endl;
    }

    return 0;
}