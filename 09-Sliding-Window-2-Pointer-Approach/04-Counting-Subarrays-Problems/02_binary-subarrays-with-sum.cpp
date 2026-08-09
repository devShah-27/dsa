// Problem:
// Given a binary array nums and an integer goal, find the number of non-empty subarrays whose sum is exactly equal to goal.
// A subarray is a continuous part of the array.

#include <bits/stdc++.h>
using namespace std;

// ==================================================
// OPTIMAL APPROACH (SLIDING WINDOW + PREFIX COUNT)
//
// Idea:
// For binary arrays, the number of subarrays with sum exactly goal can be found using the difference between subarrays with sum at most goal and at most goal - 1.
// Use a sliding window to count subarrays with sum within a given limit.
//
// Time Complexity: O(2N)
// Space Complexity: O(1)
// ==================================================

int atMost(vector<int> &nums, int goal)
{
    if (goal < 0)
        return 0;

    int n = nums.size(), count = 0;

    int r = 0, l = 0, sum = 0;

    while (r < n)
    {
        sum += nums[r];

        while (sum > goal)
        {
            sum -= nums[l];
            l++;
        }

        // Every subarray ending at r and starting from l to r has sum <= goal.
        count += (r - l + 1);

        r++;
    }

    return count;
}

int numSubarraysWithSum(vector<int> &nums, int goal)
{
    // Exact sum = (sum <= goal) - (sum <= goal - 1)
    return atMost(nums, goal) - atMost(nums, goal - 1);
}

int main()
{
    vector<int> nums = {1, 0, 0, 1, 1, 0};
    int goal = 2;

    int ans = numSubarraysWithSum(nums, goal);

    cout << "Number of substrings with sum \"" << goal << "\" is: " << ans << endl;

    return 0;
}