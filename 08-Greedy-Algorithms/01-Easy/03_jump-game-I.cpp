// Problem:
// Given an array where each element represents the maximum jump length from that index, determine whether it is possible to reach the last index starting from index 0.
// Return true if the last index can be reached, otherwise return false.

#include <bits/stdc++.h>

using namespace std;

// ==================================================
// GREEDY APPROACH
//
// Idea:
// Track the farthest index that can be reached while traversing the array.
// If the current index is beyond the maximum reachable position, reaching the end is impossible. Otherwise, keep updating the farthest reachable index.
//
// Time Complexity: O(N)
// Space Complexity: O(1)
// ==================================================

bool canJump(vector<int> &nums)
{
    int n = nums.size(), maxReachableIdx = 0;

    for (int i = 0; i < n; i++)
    {
        if (i > maxReachableIdx)
            return false;

        maxReachableIdx = max(maxReachableIdx, i + nums[i]);

        if (maxReachableIdx >= n)
            return true;
    }

    return true;
}

int main()
{
    vector<int> nums = {3, 2, 1, 0, 4};

    cout << "Array representing maximum jump from each index: ";
    for (int i = 0; i < nums.size(); i++)
    {
        cout << nums[i] << " ";
    }
    cout << endl;

    bool ans = canJump(nums);

    if (ans)
    {
        cout << "It is possible to reach the last index." << endl;
    }
    else
    {
        cout << "It is not possible to reach the last index." << endl;
    }

    return 0;
}