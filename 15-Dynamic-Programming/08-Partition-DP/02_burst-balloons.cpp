// ==================================================
// PROBLEM
// - Given n balloons with values in array nums, burst all of them.
// - Bursting balloon i gives nums[i - 1] * nums[i] * nums[i + 1] coins.
// - Out-of-bounds neighbors count as a balloon with value 1.
// - Return the maximum coins obtainable by choosing the bursting order wisely.
// ==================================================

#include <bits/stdc++.h>
using namespace std;

// ==================================================
// RECURSIVE APPROACH
//
// Idea:
// - Choose the last balloon to burst in range [i, j], instead of the first one.
// - If idx is burst last, its neighbors are the boundary balloons nums[i - 1] and nums[j + 1].
// - This makes the left and right sub-ranges independent, because idx separates them until the very end.
// - Pad nums with 1 at both ends to handle out-of-bounds neighbors.
// - Return the maximum coins across all choices of idx.
//
// Time Complexity: O(3^n) roughly - Exponential branching, overlapping sub-ranges are recomputed.
// Space Complexity: O(n) - Auxiliary space required for the recursion stack.
// ==================================================

int helper(int i, int j, vector<int> &nums)
{
    // Base case: Empty range, no balloons left to burst
    if (i > j)
        return 0;

    int maxi = INT_MIN;

    // Try every balloon in [i, j] as the last one to burst
    for (int idx = i; idx <= j; idx++)
    {
        // Coins for bursting idx last: its neighbors are the range boundaries
        int currCost = (nums[i - 1] * nums[idx] * nums[j + 1]);

        // Total coins = coins for idx + best coins from the left and right sub-ranges
        int totalCost = currCost + helper(i, idx - 1, nums) + helper(idx + 1, j, nums);

        maxi = max(maxi, totalCost);
    }

    return maxi;
}

int maxCoins(vector<int> &nums)
{
    int n = nums.size();

    // Pad both ends with 1 to represent out-of-bounds balloons
    nums.insert(nums.begin(), 1);
    nums.push_back(1);

    // The real balloons now live at indices 1 to n
    return helper(1, n, nums);
}

// ==================================================
// RECURSION + MEMOIZATION (TOP-DOWN DP)
//
// Idea:
// - The recursive solution repeatedly solves the same ranges (i, j).
// - Cache each range result in a 2D table indexed by (i, j).
// - Return the stored answer immediately when a range is already solved.
// - Each range still tries every balloon as the last one to burst.
//
// Time Complexity: O(n^3) - O(n^2) states, each iterating over O(n) choices.
// Space Complexity: O(n^2) for DP table + O(n) for recursion stack.
// ==================================================

int helper(int i, int j, vector<int> &nums, vector<vector<int>> &dp)
{
    // Base case: Empty range, no balloons left to burst
    if (i > j)
        return 0;

    // Return the stored result if this range is already solved
    if (dp[i][j] != -1)
        return dp[i][j];

    int maxi = INT_MIN;

    // Try every balloon in [i, j] as the last one to burst
    for (int idx = i; idx <= j; idx++)
    {
        // Coins for bursting idx last: its neighbors are the range boundaries
        int currCost = (nums[i - 1] * nums[idx] * nums[j + 1]);

        // Total coins = coins for idx + best coins from the left and right sub-ranges
        int totalCost = currCost + helper(i, idx - 1, nums, dp) + helper(idx + 1, j, nums, dp);

        maxi = max(maxi, totalCost);
    }

    // Cache the maximum coins before returning
    return dp[i][j] = maxi;
}

int maxCoins(vector<int> &nums)
{
    int n = nums.size();

    // Pad both ends with 1 to represent out-of-bounds balloons
    nums.insert(nums.begin(), 1);
    nums.push_back(1);

    // Initialize the DP table with -1 to indicate uncomputed states
    vector<vector<int>> dp(n + 1, vector<int>(n + 1, -1));

    return helper(1, n, nums, dp);
}

// ==================================================
// TABULATION (BOTTOM-UP DP)
//
// Idea:
// - Convert the memoized recursion into iterative table filling.
// - State dp[i][j] stores the maximum coins from bursting range [i, j].
// - Iterate i from bottom to top and j from left to right, so dp[i][idx - 1] and dp[idx + 1][j] are ready before use.
// - Empty ranges (i > j) stay 0 from initialization.
//
// Time Complexity: O(n^3) - Three nested loops over i, j, and idx.
// Space Complexity: O(n^2) - Memory allocated for the 2D DP matrix.
// ==================================================

int maxCoins(vector<int> &nums)
{
    int n = nums.size();

    // Pad both ends with 1 to represent out-of-bounds balloons
    nums.insert(nums.begin(), 1);
    nums.push_back(1);

    // Initialize with 0, which also covers the empty-range base case
    // Size n + 2 keeps dp[idx + 1][j] and dp[i][idx - 1] within bounds
    vector<vector<int>> dp(n + 2, vector<int>(n + 2, 0));

    // i moves from the last balloon down to the first
    for (int i = n; i >= 1; i--)
    {
        for (int j = i; j <= n; j++)
        {
            int maxi = INT_MIN;

            // Try every balloon in [i, j] as the last one to burst
            for (int idx = i; idx <= j; idx++)
            {
                // Coins for bursting idx last: its neighbors are the range boundaries
                int currCost = (nums[i - 1] * nums[idx] * nums[j + 1]);

                // Total coins = coins for idx + best coins from the left and right sub-ranges
                int totalCost = currCost + dp[i][idx - 1] + dp[idx + 1][j];

                maxi = max(maxi, totalCost);
            }

            dp[i][j] = maxi;
        }
    }

    // Answer for the full range of real balloons
    return dp[1][n];
}

int main()
{
    vector<int> nums = {3, 1, 5, 8};

    cout << "Maximum coins obtained: " << maxCoins(nums);

    return 0;
}