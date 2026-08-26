// Problem:
// Given an array of unique candidates and a target value, find all combinations where selected numbers add up to the target. Each candidate can be selected unlimited times, and every valid combination should be included exactly once.

#include <bits/stdc++.h>
using namespace std;

// ============================================================================
// BACKTRACKING APPROACH
//
// Idea:
// For every candidate, make two choices:
// 1. Pick the current candidate and continue from the same index because the
//    candidate can be reused multiple times.
// 2. Skip the current candidate and move to the next index.
//
// Backtrack whenever the current sum exceeds the target or a valid combination is found.
//
// Time Complexity: O(2^t) where t is the target value (approximate)
// Space Complexity: O(t) due to recursion depth excluding output storage
// ============================================================================

void helperFun(int index, vector<vector<int>> &result, vector<int> &candidates, vector<int> &tempList, int target, int n, int sum)
{
    // Current combination reaches the target sum.
    if (sum == target)
    {
        result.push_back(tempList);
        return;
    }

    // Current sum exceeds the target, so this path cannot form a valid answer.
    if (sum > target)
        return;

    // No candidates are left to explore.
    if (index == n)
        return;

    // Choice 1: Include the current candidate.
    // The same index is passed because a candidate can be reused infinitely.
    tempList.push_back(candidates[index]);
    sum += candidates[index];

    helperFun(index, result, candidates, tempList, target, n, sum);

    // Backtrack and remove the selected candidate.
    tempList.pop_back();
    sum -= candidates[index];

    // Choice 2: Skip the current candidate and move to the next candidate.
    helperFun(index + 1, result, candidates, tempList, target, n, sum);
}

vector<vector<int>> combinationSum(vector<int> &candidates, int target)
{
    int n = candidates.size();

    vector<vector<int>> result;

    vector<int> tempList;

    helperFun(0, result, candidates, tempList, target, n, 0);

    return result;
}

int main()
{
    vector<int> candidates = {3, 4, 5, 6};
    int target = 10;

    vector<vector<int>> result = combinationSum(candidates, target);

    for (const auto &combination : result)
    {
        for (int num : combination)
        {
            cout << num << " ";
        }

        cout << endl;
    }

    return 0;
}