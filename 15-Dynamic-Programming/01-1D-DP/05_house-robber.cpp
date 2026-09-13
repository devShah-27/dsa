// ==================================================
// PROBLEM
// - Houses are arranged in a circular street; the first and last houses are adjacent.
// - Given an integer array 'money' where money[i] represents the loot at the (i+1)th house.
// - Cannot rob two adjacent houses. Return the maximum money that can be looted without alerting the police.
// ==================================================

#include <bits/stdc++.h>
using namespace std;

// ==================================================
// BRUTE FORCE APPROACH — RECURSION
//
// Idea:
// - Because the first and last houses are adjacent, both  cannot be robbed simultaneously.
// - Split the circle into two linear subproblems: omitting  the first house [1...n-1] and omitting the last house [0...n-2].
// - For each linear subproblem, recursively evaluate the  decision to pick or skip each house.
// - Return the maximum loot obtained between the two  subproblems.
//
// Time Complexity: O(2^n) - Exponential branching for each of the two recursive explorations.
// Space Complexity: O(n) - O(n) for linear sub-arrays and the recursion call stack.
// ==================================================

int helper(int idx, vector<int> &nums)
{
    // Base case: Out of bounds
    if (idx < 0)
        return 0;

    // Base case: Reached the first house of the subproblem
    if (idx == 0)
        return nums[idx];

    // Choice 1: Rob the current house and recurse on (idx - 2)
    int pick = nums[idx] + helper(idx - 2, nums);

    // Choice 2: Skip the current house and recurse on (idx - 1)
    int notPick = helper(idx - 1, nums);

    return max(pick, notPick);
}

int nonAdjacent(vector<int> &nums)
{
    int n = nums.size();

    return helper(n - 1, nums);
}

int houseRobber(vector<int> &money)
{
    int n = money.size();

    // Base cases for empty or single-element inputs
    if (n == 0)
        return 0;

    if (n == 1)
        return money[0];

    vector<int> omitStart, omitEnd;

    // Separate into two linear configurations
    for (int i = 0; i < n; i++)
    {
        if (i != 0)
            omitStart.push_back(money[i]);

        if (i != n - 1)
            omitEnd.push_back(money[i]);
    }

    return max(nonAdjacent(omitStart), nonAdjacent(omitEnd));
}

// ==================================================
// BETTER APPROACH — MEMOIZATION (TOP-DOWN DP)
//
// Idea:
// - Divide the circular problem into two linear subproblems (omitting the first and last houses).
// - Solve each linear problem with top-down dynamic programming using a DP array initialized to -1.
// - Cache computed results to eliminate redundant overlapping subproblem evaluations.
//
// Time Complexity: O(n) - Two linear DP executions, each solving (n - 1) states in O(1) time.
// Space Complexity: O(n) - O(n) for memoization arrays, recursion call stacks, and sub-arrays.
// ==================================================

int helper(int idx, vector<int> &nums, vector<int> &dp)
{
    // Base cases
    if (idx < 0)
        return 0;

    if (idx == 0)
        return nums[idx];

    // Return the cached result if already computed
    if (dp[idx] != -1)
        return dp[idx];

    // Choice transitions: pick vs not pick
    int pick = nums[idx] + helper(idx - 2, nums, dp);

    int notPick = helper(idx - 1, nums, dp);

    // Cache and return optimal loot
    return dp[idx] = max(pick, notPick);
}

int nonAdjacent(vector<int> &nums)
{
    int n = nums.size();

    // Table to memoize results for indices 0 to (n - 1)
    vector<int> dp(n, -1);

    return helper(n - 1, nums, dp);
}

int houseRobber(vector<int> &money)
{
    int n = money.size();

    // Edge cases
    if (n == 0)
        return 0;

    if (n == 1)
        return money[0];

    vector<int> omitStart, omitEnd;

    // Create linear subarrays
    for (int i = 0; i < n; i++)
    {
        if (i != 0)
            omitStart.push_back(money[i]);

        if (i != n - 1)
            omitEnd.push_back(money[i]);
    }

    return max(nonAdjacent(omitStart), nonAdjacent(omitEnd));
}

// ==================================================
// BETTER APPROACH — TABULATION (BOTTOM-UP DP)
//
// Idea:
// - Deconstruct the circle into two linear arrays: omitting the first house and omitting the last house.
// - Solve each linear array iteratively using a 1D DP table: dp[idx] = max(nums[idx] + dp[idx - 2], dp[idx - 1]).
// - Return the maximum value produced between the two tabulated runs.
//
// Time Complexity: O(n) - Two linear iterations over arrays of size (n - 1).
// Space Complexity: O(n) - O(n) for 1D DP arrays and auxiliary subarray copies.
// ==================================================

int nonAdjacent(vector<int> &nums)
{
    int n = nums.size();

    // dp[idx] stores the maximum loot possible from subarray nums[0...idx]
    vector<int> dp(n, -1);

    // Base condition
    dp[0] = nums[0];

    // Iteratively build solutions from bottom to top
    for (int idx = 1; idx < n; idx++)
    {
        int pick = nums[idx], notPick = dp[idx - 1];

        if (idx > 1)
            pick += dp[idx - 2];

        dp[idx] = max(pick, notPick);
    }

    return dp[n - 1];
}

int houseRobber(vector<int> &money)
{
    int n = money.size();

    // Edge cases
    if (n == 0)
        return 0;

    if (n == 1)
        return money[0];

    vector<int> omitStart, omitEnd;

    // Populate subarrays excluding first and last elements respectively
    for (int i = 0; i < n; i++)
    {
        if (i != 0)
            omitStart.push_back(money[i]);

        if (i != n - 1)
            omitEnd.push_back(money[i]);
    }

    return max(nonAdjacent(omitStart), nonAdjacent(omitEnd));
}

// ==================================================
// OPTIMAL APPROACH — SPACE-OPTIMIZED DP
//
// Idea:
// - For both linear subproblems, computing state idx depends only on the previous two states.
// - Optimize DP space to O(1) by maintaining two scalar variables (prev and prev2).
// - Compare the maximum loot obtained from omitting the first versus the last house.
//
// Time Complexity: O(n) - Two linear iterations over (n - 1) elements.
// Space Complexity: O(n) - O(n) auxiliary space due to subarray creation (omitStart and omitEnd).
// ==================================================

int nonAdjacent(vector<int> &nums)
{
    int n = nums.size();

    // prev corresponds to dp[idx - 1], prev2 corresponds to dp[idx - 2]
    int prev2 = 0;
    int prev = nums[0];

    for (int idx = 1; idx < n; idx++)
    {
        int pick = nums[idx], notPick = prev;

        if (idx > 1)
            pick += prev2;

        int curr = max(pick, notPick);

        // Slide the state variables forward
        prev2 = prev;
        prev = curr;
    }

    return prev;
}

int houseRobber(vector<int> &money)
{
    int n = money.size();

    // Edge cases
    if (n == 0)
        return 0;

    if (n == 1)
        return money[0];

    vector<int> omitStart, omitEnd;

    // Separate into linear subarrays
    for (int i = 0; i < n; i++)
    {
        if (i != 0)
            omitStart.push_back(money[i]);

        if (i != n - 1)
            omitEnd.push_back(money[i]);
    }

    return max(nonAdjacent(omitStart), nonAdjacent(omitEnd));
}

int main()
{
    vector<int> arr{1, 5, 1, 2, 6};

    cout << houseRobber(arr);
}
