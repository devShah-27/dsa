// Problem:
// Given an integer array that may contain duplicates, generate all possible subsets (power set) without including duplicate subsets.
// The order of subsets in the output does not matter.

#include <bits/stdc++.h>
using namespace std;

// ============================================================================
// BACKTRACKING APPROACH
//
// Idea:
// Sort the array so duplicate elements become adjacent.
// Generate subsets using recursion and skip duplicate elements at the same recursion level to avoid creating duplicate subsets.
// Each recursive call represents choosing the next element for the subset.
//
// Time Complexity: O(2^n * n) in the worst case due to subset generation
// Space Complexity: O(n) due to recursion stack excluding output storage
// ============================================================================

void recursiveSubsetsWithDup(int idx, int n, vector<int> &tempList, vector<int> &nums, vector<vector<int>> &result)
{
    // Store the current subset at every recursion state.
    result.push_back(tempList);

    for (int i = idx; i < n; i++)
    {
        // Skip duplicate elements at the same recursion level.
        // This prevents generating identical subsets.
        if (i > idx && nums[i] == nums[i - 1])
            continue;

        // Include the current element.
        tempList.push_back(nums[i]);

        // Move to the next index after choosing the current element.
        recursiveSubsetsWithDup(i + 1, n, tempList, nums, result);

        // Backtrack and remove the chosen element.
        tempList.pop_back();
    }
}

vector<vector<int>> subsetsWithDup(vector<int> &nums)
{
    vector<vector<int>> result;

    int n = nums.size();

    vector<int> tempList;

    // Sorting allows duplicate elements to be detected easily.
    sort(nums.begin(), nums.end());

    recursiveSubsetsWithDup(0, n, tempList, nums, result);

    return result;
}

int main()
{
    vector<int> nums = {1, 2, 2};

    vector<vector<int>> result = subsetsWithDup(nums);

    for (const auto &subset : result)
    {
        cout << "[ ";

        for (int num : subset)
        {
            cout << num << " ";
        }

        cout << "]\n";
    }

    return 0;
}