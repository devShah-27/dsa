// ==================================================
// PROBLEM
// - Given an array 'heights' where heights[i] represents the height of the ith step.
// - A frog starts at step 0 and aims to reach step (n - 1).
// - From step i, the frog can jump to either (i + 1) or (i + 2) with an energy cost of |heights[i] - heights[j]|.
// - Return the minimum total energy required to reach the last step.
// ==================================================

#include <bits/stdc++.h>
using namespace std;

// ==================================================
// BRUTE FORCE APPROACH — RECURSION
//
// Idea:
// - Express the problem recursively from target index (n - 1) down to index 0.
// - At any step idx, evaluate both choices: jumping from (idx - 1) or jumping from (idx - 2).
// - Base case: At step 0, 0 energy is required since the frog starts there.
// - Return the minimum energy between the two valid transitions.
//
// Time Complexity: O(2^n) - Each step branches into up to two recursive calls.
// Space Complexity: O(n) - Maximum depth of the recursive call stack.
// ==================================================

int helper(int idx, vector<int> &heights)
{
    // Base case: 0 energy needed to remain at the starting step
    if (idx == 0)
        return 0;

    // Option 1: Jump from the immediately preceding step (idx - 1)
    int oneStep = helper(idx - 1, heights) + abs(heights[idx] - heights[idx - 1]);

    int twoSteps = INT_MAX;

    // Option 2: Jump from two steps back (idx - 2), valid only if idx > 1
    if (idx > 1)
        twoSteps = helper(idx - 2, heights) + abs(heights[idx] - heights[idx - 2]);

    return min(oneStep, twoSteps);
}

int frogJump(vector<int> &heights)
{
    // Edge case: Empty input array
    if (heights.empty())
        return 0;

    int n = heights.size();

    return helper(n - 1, heights);
}

// ==================================================
// BETTER APPROACH — MEMOIZATION (TOP-DOWN DP)
//
// Idea:
// - Optimize recursion by storing the minimum energy required for each step in a DP array.
// - If the result for a given index is already computed (dp[idx] != -1), return it immediately.
// - Compute each unique state once, eliminating redundant overlapping subproblems.
//
// Time Complexity: O(n) - Each state from 0 to (n - 1) is computed and cached exactly once.
// Space Complexity: O(n) - O(n) for the memoization array + O(n) for the recursion call stack.
// ==================================================

int helper(int idx, vector<int> &heights, vector<int> &dp)
{
    // Base case: Starting position requires 0 energy
    if (idx == 0)
        return 0;

    // Return the precomputed minimum energy for the current step
    if (dp[idx] != -1)
        return dp[idx];

    // Transition 1: One-step jump
    int oneStep = helper(idx - 1, heights, dp) + abs(heights[idx] - heights[idx - 1]);

    int twoSteps = INT_MAX;

    // Transition 2: Two-step jump
    if (idx > 1)
        twoSteps = helper(idx - 2, heights, dp) + abs(heights[idx] - heights[idx - 2]);

    // Cache and return the optimal energy to reach step idx
    return dp[idx] = min(oneStep, twoSteps);
}

int frogJump(vector<int> &heights)
{
    // Edge case: Empty input array
    if (heights.empty())
        return 0;

    int n = heights.size();

    // Table to memoize solutions for steps 0 to (n - 1)
    vector<int> dp(n + 1, -1);

    return helper(n - 1, heights, dp);
}

// ==================================================
// BETTER APPROACH — TABULATION (BOTTOM-UP DP)
//
// Idea:
// - Iteratively compute the minimum energy to reach each step from step 0 up to (n - 1).
// - Initialize base condition dp[0] = 0.
// - Transition state: dp[i] = min(dp[i - 1] + |heights[i] - heights[i - 1]|, dp[i - 2] + |heights[i] - heights[i - 2]|).
//
// Time Complexity: O(n) - Single loop iterating from index 1 to (n - 1).
// Space Complexity: O(n) - 1D array of size n to store intermediate DP states.
// ==================================================

int frogJump(vector<int> &heights)
{
    // Edge case: Empty input array
    if (heights.empty())
        return 0;

    int n = heights.size();

    // dp[i] stores the minimum energy required to reach step i from step 0
    vector<int> dp(n, -1);

    // Base condition
    dp[0] = 0;

    // Iteratively compute minimum energy for each step
    for (int i = 1; i < n; i++)
    {
        int oneStep = dp[i - 1] + abs(heights[i] - heights[i - 1]);

        int twoSteps = INT_MAX;

        if (i > 1)
            twoSteps = dp[i - 2] + abs(heights[i] - heights[i - 2]);

        dp[i] = min(oneStep, twoSteps);
    }

    return dp[n - 1];
}

// ==================================================
// OPTIMAL APPROACH — SPACE-OPTIMIZED DP
//
// Idea:
// - Computing dp[i] depends only on the results of the previous two steps (dp[i - 1] and dp[i - 2]).
// - Maintain two scalar variables (prev and prev2) to track these states instead of a full array.
// - Update prev2 and prev at each iteration to achieve O(1) auxiliary space.
//
// Time Complexity: O(n) - Single linear iteration from step 1 to (n - 1).
// Space Complexity: O(1) - Constant auxiliary space using only scalar variables.
// ==================================================

int frogJump(vector<int> &heights)
{
    // Edge case: Empty input array
    if (heights.empty())
        return 0;

    int n = heights.size();

    // prev corresponds to dp[i - 1], prev2 corresponds to dp[i - 2]
    int prev = 0, prev2 = INT_MAX;

    for (int i = 1; i < n; i++)
    {
        int oneStep = prev + abs(heights[i] - heights[i - 1]);

        int twoSteps = INT_MAX;

        if (i > 1)
            twoSteps = prev2 + abs(heights[i] - heights[i - 2]);

        int curr = min(oneStep, twoSteps);

        // Slide the state variables forward
        prev2 = prev;
        prev = curr;
    }

    return prev;
}

int main()
{
    vector<int> heights = {2, 1, 3, 5, 4};

    int result = frogJump(heights);

    cout << "Minimum energy required: " << result << endl;

    return 0;
}
