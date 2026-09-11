// ==================================================
// PROBLEM
// - Given an integer n representing a staircase with n steps, starting from step 0.
// - Determine the number of unique ways to reach the nth step.
// - Each move allows climbing either 1 step or 2 steps at a time.
// ==================================================

#include <bits/stdc++.h>
using namespace std;

// ==================================================
// BRUTE FORCE APPROACH — RECURSION
//
// Idea:
// - To reach step n, the last move must have been from step (n - 1) or step (n - 2).
// - Recursively calculate the sum of ways: climbStairs(n - 1) + climbStairs(n - 2).
// - Base cases: If n <= 1, there is exactly 1 valid way (step 0 or step 1).
//
// Time Complexity: O(2^n) - Exponential growth due to overlapping subproblems in the recursion tree.
// Space Complexity: O(n) - Maximum depth of the recursion call stack.
// ==================================================

int climbStairs(int n)
{
    // Base cases: 1 way for 0 steps (stay put) or 1 step (single 1-step move)
    if (n <= 1)
        return 1;

    // Explore both choices: taking 1 step or taking 2 steps
    return climbStairs(n - 1) + climbStairs(n - 2);
}

// ==================================================
// BETTER APPROACH — MEMOIZATION (TOP-DOWN DP)
//
// Idea:
// - Top-down dynamic programming storing subproblem results in a dp array initialized to -1.
// - Recursively break down the problem and cache the result for state n once computed.
// - Reuse stored results on subsequent calls to eliminate redundant recursive calculations.
//
// Time Complexity: O(n) - Each state from 0 to n is computed and solved exactly once.
// Space Complexity: O(n) - O(n) for the dp memoization table + O(n) for the auxiliary recursion stack.
// ==================================================

int memoizationDP(int n, vector<int> &dp)
{
    // Base cases
    if (n <= 1)
        return 1;

    // Return already computed subproblem
    if (dp[n] != -1)
        return dp[n];

    // Compute, cache, and return result
    return dp[n] = memoizationDP(n - 1, dp) + memoizationDP(n - 2, dp);
}

int climbStairs(int n)
{
    // Table to memoize solutions for states 0 to n
    vector<int> dp(n + 1, -1);
    return memoizationDP(n, dp);
}

// ==================================================
// BETTER APPROACH — TABULATION (BOTTOM-UP DP)
//
// Idea:
// - Bottom-up dynamic programming iteratively filling a dp table from base cases up to n.
// - Initialize dp[0] = 1 and dp[1] = 1.
// - Transition state: dp[i] = dp[i - 1] + dp[i - 2] for all i from 2 to n.
//
// Time Complexity: O(n) - Single loop running from 2 to n.
// Space Complexity: O(n) - 1D array of size (n + 1) to store intermediate states.
// ==================================================

int climbStairs(int n)
{
    // Allocate DP table to store answers from 0 to n
    vector<int> dp(n + 1, -1);

    // Base cases
    dp[0] = 1;
    dp[1] = 1;

    // Iteratively build the solution from smaller subproblems
    for (int i = 2; i <= n; i++)
    {
        dp[i] = dp[i - 1] + dp[i - 2];
    }

    return dp[n];
}

// ==================================================
// OPTIMAL APPROACH — SPACE-OPTIMIZED DP
//
// Idea:
// - Since computing the current step only depends on the previous two steps, avoid the full array.
// - Use two variables (prev and prev2) to represent dp[i - 1] and dp[i - 2].
// - Update variables iteratively at each step to achieve O(1) auxiliary space.
//
// Time Complexity: O(n) - Single loop iterating from 2 to n.
// Space Complexity: O(1) - Uses only two integer variables for state transitions.
// ==================================================

int climbStairs(int n)
{
    // prev2 corresponds to dp[i - 2], prev corresponds to dp[i - 1]
    int prev2 = 1;
    int prev = 1;

    for (int i = 2; i <= n; i++)
    {
        int curr = prev + prev2;
        prev2 = prev;
        prev = curr;
    }

    return prev;
}

int main()
{
    int n = 3;

    cout << "The total number of ways: " << climbStairs(n) << endl;

    return 0;
}
