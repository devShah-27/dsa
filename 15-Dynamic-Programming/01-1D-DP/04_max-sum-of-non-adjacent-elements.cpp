// ==================================================
// PROBLEM
// - Given an integer array 'nums' of size n.
// - Find the maximum sum of a subsequence such that no two selected elements are adjacent in nums.
// - Return the maximum possible sum.
// ==================================================

#include <bits/stdc++.h>
using namespace std;

// ==================================================
// BRUTE FORCE APPROACH — RECURSION
//
// Idea:
// - At each index 'idx', make a choice either to pick or skip the element nums[idx].
// - If picked, add nums[idx] and recurse on (idx - 2) to skip the adjacent element.
// - If skipped (not picked), recurse on (idx - 1) to consider the immediate predecessor.
// - Base cases: If idx == 0, return nums[0]; if idx < 0, return 0.
//
// Time Complexity: O(2^n) - Each element branches into two recursive decisions (pick or skip).
// Space Complexity: O(n) - Maximum depth of the recursive call stack.
// ==================================================

int helper(int idx, vector<int> &nums)
{
    // Base case: Out of bounds (no elements left to choose)
    if (idx < 0)
        return 0;

    // Base case: Only the first element remains
    if (idx == 0)
        return nums[idx];

    // Choice 1: Pick the current element and move to index (idx - 2)
    int pick = nums[idx] + helper(idx - 2, nums);

    // Choice 2: Skip the current element and move to index (idx - 1)
    int notPick = helper(idx - 1, nums);

    return max(pick, notPick);
}

int nonAdjacent(vector<int> &nums)
{
    int n = nums.size();

    return helper(n - 1, nums);
}

// ==================================================
// BETTER APPROACH — MEMOIZATION (TOP-DOWN DP)
//
// Idea:
// - Store computed maximum sums for each index in a DP array initialized to -1.
// - If the state for index 'idx' is already computed (dp[idx] != -1), return it immediately.
// - Recursively evaluate pick and notPick options, cache the maximum result, and return it.
//
// Time Complexity: O(n) - Each state from index 0 to (n - 1) is computed and memoized once.
// Space Complexity: O(n) - O(n) for the memoization array + O(n) for the recursion call stack.
// ==================================================

int helper(int idx, vector<int> &nums, vector<int> &dp)
{
    // Base cases
    if (idx < 0)
        return 0;

    if (idx == 0)
        return nums[idx];

    // Return the cached result if already calculated
    if (dp[idx] != -1)
        return dp[idx];

    // Explore pick and notPick transitions
    int pick = nums[idx] + helper(idx - 2, nums, dp);

    int notPick = helper(idx - 1, nums, dp);

    // Memoize and return the optimal sum for the current prefix
    return dp[idx] = max(pick, notPick);
}

int nonAdjacent(vector<int> &nums)
{
    int n = nums.size();

    // Table to memoize solutions for subproblems from index 0 to (n - 1)
    vector<int> dp(n, -1);

    return helper(n - 1, nums, dp);
}

// ==================================================
// BETTER APPROACH — TABULATION (BOTTOM-UP DP)
//
// Idea:
// - Iteratively compute the maximum sum for each prefix from index 0 up to (n - 1).
// - Base case: dp[0] = nums[0].
// - Transition: dp[idx] = max(nums[idx] + (idx >= 2 ? dp[idx - 2] : 0), dp[idx - 1]).
//
// Time Complexity: O(n) - Single loop iterating from index 1 to (n - 1).
// Space Complexity: O(n) - 1D array of size n to store intermediate states.
// ==================================================

int nonAdjacent(vector<int> &nums)
{
    int n = nums.size();

    // dp[idx] stores the maximum non-adjacent sum possible from nums[0...idx]
    vector<int> dp(n, 0);

    // Base condition
    dp[0] = nums[0];

    // Iteratively build the solution from smaller subproblems
    for (int idx = 1; idx < n; idx++)
    {
        int pick = nums[idx], notPick = dp[idx - 1];

        // Add solution of (idx - 2) if it exists
        if (idx - 2 >= 0)
            pick += dp[idx - 2];

        dp[idx] = max(pick, notPick);
    }

    return dp[n - 1];
}

// ==================================================
// OPTIMAL APPROACH — SPACE-OPTIMIZED DP
//
// Idea:
// - The current state dp[idx] depends only on the previous two states: dp[idx - 1] and dp[idx - 2].
// - Replace the DP array with two scalar variables: 'prev' (for idx - 1) and 'prev2' (for idx - 2).
// - Update these variables on each step to reduce auxiliary space to O(1).
//
// Time Complexity: O(n) - Single linear iteration from index 1 to (n - 1).
// Space Complexity: O(1) - Constant auxiliary space using scalar variables.
// ==================================================

int nonAdjacent(vector<int> &nums)
{
    int n = nums.size();

    // prev corresponds to dp[idx - 1], prev2 corresponds to dp[idx - 2]
    int prev2 = 0, prev = nums[0];

    for (int idx = 1; idx < n; idx++)
    {
        int pick = nums[idx], notPick = prev;

        if (idx - 2 >= 0)
            pick += prev2;

        int curr = max(pick, notPick);

        // Slide the window forward
        prev2 = prev;
        prev = curr;
    }

    return prev;
}

int main()
{
    vector<int> arr{2, 1, 4, 9};

    cout << nonAdjacent(arr);

    return 0;
}
