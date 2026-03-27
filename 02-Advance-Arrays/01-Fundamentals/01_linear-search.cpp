// ========================== PROBLEM ==========================
// Given an integer array and a target value, return the smallest
// index at which the target appears. If the target is not present,
// return -1.
// ============================================================

#include <bits/stdc++.h>
using namespace std;

// ========================== LINEAR SEARCH APPROACH ==========================
// Idea:
// Traverse the array from left to right and compare each element
// with the target. Return immediately when the first match is found.
// If no match is found after full traversal, return -1.
//
// Time Complexity: O(N)
// Space Complexity: O(1)
// ============================================================================
int linearSearch(vector<int> &nums, int target)
{
    for (int i = 0; i < nums.size(); i++)
    {
        if (nums[i] == target)
            return i; // Return first (smallest index) occurrence
    }

    return -1; // Target not found
}

int main()
{
    int size;
    cin >> size;

    vector<int> nums(size);

    // Input array elements
    for (int i = 0; i < size; i++)
        cin >> nums[i];

    int query;
    cin >> query;

    int index = linearSearch(nums, query);

    // Output result based on search outcome
    if (index == -1)
        cout << query << " was not found";
    else
        cout << query << " was found at index " << index;

    return 0;
}