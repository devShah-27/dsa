// Problem:
// Given an array of unique integers, generate all possible subsets (power set).
// The answer should contain every possible combination of elements exactly once.

#include <bits/stdc++.h>
using namespace std;

// ============================================================================
// RECURSIVE BACKTRACKING APPROACH
//
// Idea:
// For every element, make two choices:
// 1. Include the current element in the subset.
// 2. Exclude the current element from the subset.
// Continue recursively until all elements are processed, then store the formed subset in the answer.
//
// Time Complexity: O(2^n)
// Space Complexity: O(n * 2^n) including output storage
// ============================================================================

void generatePowerSet(vector<int> &nums, int index, vector<int> subsequence, vector<vector<int>> &ans, int n)
{
    // Base case: all elements have been considered.
    // Store the currently generated subset.
    if (index == n)
    {
        ans.push_back(subsequence);
        return;
    }

    // Choice 1: Include the current element.
    subsequence.push_back(nums[index]);
    generatePowerSet(nums, index + 1, subsequence, ans, n);

    // Backtrack: remove the element to explore the exclude choice.
    subsequence.pop_back();

    // Choice 2: Exclude the current element.
    generatePowerSet(nums, index + 1, subsequence, ans, n);
}

vector<vector<int>> powerSet(vector<int> &nums)
{
    vector<vector<int>> ans;

    int n = nums.size();

    generatePowerSet(nums, 0, {}, ans, n);

    return ans;
}

int main()
{
    vector<int> nums = {1, 2, 3};

    vector<vector<int>> result = powerSet(nums);

    for (const auto &subset : result)
    {
        cout << "[";

        for (int num : subset)
        {
            cout << num << " ";
        }

        cout << "]" << endl;
    }

    return 0;
}