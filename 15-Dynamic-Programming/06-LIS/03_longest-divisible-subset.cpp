// ==================================================
// PROBLEM
// - Given an array of positive integers, find the largest divisible subset.
// - Every pair (a, b) in the subset must satisfy a % b == 0 or b % a == 0.
// - Return the valid subset in any order (any valid solution is accepted).
// ==================================================

#include <bits/stdc++.h>
using namespace std;

// ==================================================
// SORTING + TABULATION (LIS VARIATION)
//
// Idea:
// - Sort the array so divisibility becomes transitive, reducing the problem to finding a Longest Increasing Subsequence (LIS).
// - Compute maximum subset lengths iteratively while storing parent indices.
// - Backtrack from the globally optimal index using the parent array to reconstruct the final largest divisible subset.
//
// Time Complexity: O(n^2) - Sorting takes O(n log n) and nested DP loops take O(n^2).
// Space Complexity: O(n) - Auxiliary arrays used for DP states and parent tracking.
// ==================================================

vector<int> largestDivisibleSubset(vector<int> nums)
{
    int n = nums.size();

    // dp[i] stores the size of the largest divisible subset ending at index i
    // parent[i] tracks the previous index to reconstruct the subset later
    vector<int> dp(n, 1), parent(n);

    // Sort the array so that if nums[i] % nums[j] == 0 (for j < i),
    // nums[i] is also divisible by all elements in the valid subset ending at j
    sort(nums.begin(), nums.end());

    // Track the maximum subset length found so far and its ending index
    int maxLen = INT_MIN, idx = 0;

    for (int i = 0; i < n; i++)
    {
        // Initialize each element as the start of its own subset
        parent[i] = i;

        // Check all smaller elements prior to the current index
        for (int j = 0; j < i; j++)
        {
            // Since the array is sorted (nums[i] >= nums[j]), we only check if nums[i] % nums[j] == 0
            // Found a larger valid subset by appending nums[i] to the subset ending at j
            if (nums[i] % nums[j] == 0 && dp[i] < dp[j] + 1)
            {
                dp[i] = dp[j] + 1;
                parent[i] = j;
            }
        }

        // Update the global maximum subset length and its corresponding tail index
        if (dp[i] > maxLen)
        {
            maxLen = dp[i];
            idx = i;
        }
    }

    // Reconstruct the largest divisible subset by backtracking through parent pointers
    vector<int> res;

    // Push the last element of the optimal subset first
    res.push_back(nums[idx]);

    // Traverse backwards until reaching the base element that points to itself
    while (parent[idx] != idx)
    {
        idx = parent[idx];
        res.push_back(nums[idx]);
    }

    return res;
}

int main()
{
    vector<int> nums = {3, 5, 10, 20};

    // Compute and retrieve the largest divisible subset
    vector<int> ans = largestDivisibleSubset(nums);

    cout << "The largest divisible subset is: ";

    for (int x : ans)
        cout << x << " ";

    return 0;
}
