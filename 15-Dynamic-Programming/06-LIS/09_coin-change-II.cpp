// ==================================================
// PROBLEM
// - Given an array of coin denominations and a target amount.
// - Find the total number of distinct combinations that sum exactly to the specified target amount.
// - You have an infinite supply of each coin denomination.
// ==================================================

#include <bits/stdc++.h>
using namespace std;

// ==================================================
// RECURSIVE APPROACH
//
// Idea:
// - Recursively explore all combinations by either including or excluding the current coin denomination.
// - Because we have an infinite supply, taking a coin does not decrement the current index.
// - Return the accumulated count of valid combinations that successfully reduce the target amount exactly to zero.
//
// Time Complexity: O(>2^N) - Exponential branching due to infinite coin supply.
// Space Complexity: O(amount) - Auxiliary space required for the recursion stack.
// ==================================================

int helper(int idx, int target, const vector<int> &coins, int MOD)
{
    // Base case: Reached the very first coin denomination
    if (idx == 0)
    {
        // If the remaining target is a perfect multiple of the coin, it forms 1 valid combination
        return (target % coins[0] == 0);
    }

    // Branch 1: Exclude the current coin and move to the previous denomination
    int notTake = helper(idx - 1, target, coins, MOD);

    // Branch 2: Include the current coin if it does not exceed the remaining target
    // NOTE: We do not decrement idx, effectively allowing multiple uses of the same coin
    int take = (target >= coins[idx])
                   ? helper(idx, target - coins[idx], coins, MOD)
                   : 0;

    // Combine valid permutations from both branches and apply modulo constraint
    return (notTake + take) % MOD;
}

int count(const vector<int> &coins, int N, int amount)
{
    // Define the modulo value as specified by the problem constraints
    int MOD = 1e9 + 7;

    // Start evaluating combinations recursively from the last coin index
    return helper(N - 1, amount, coins, MOD);
}

// ==================================================
// RECURSION + MEMOIZATION (TOP-DOWN DP)
//
// Idea:
// - Optimize the naive exponential recursion by caching overlapping subproblem results in a 2D memoization table.
// - The state is uniquely defined by the current coin index and the remaining target amount.
// - Retrieve and return cached answers immediately to bypass redundant recursive branching and save computation time.
//
// Time Complexity: O(N * amount) - Each unique state is computed exactly once.
// Space Complexity: O(N * amount) for DP table + O(amount) for recursion stack.
// ==================================================

int helper(int idx, int target, const vector<int> &coins, int MOD, vector<vector<int>> &dp)
{
    // Base case: Reached the first coin denomination
    if (idx == 0)
    {
        // Return 1 if the exact remaining amount can be formed by this coin
        return (target % coins[0] == 0);
    }

    // Immediately return the stored integer result if this state is already solved
    if (dp[idx][target] != -1)
        return dp[idx][target];

    // Evaluate paths where the current coin is skipped
    int notTake = helper(idx - 1, target, coins, MOD, dp);

    // Evaluate paths where the current coin is picked (staying on the same index)
    int take = (target >= coins[idx])
                   ? helper(idx, target - coins[idx], coins, MOD, dp)
                   : 0;

    // Cache the summed modulo result into the matrix before returning
    return dp[idx][target] = (notTake + take) % MOD;
}

int count(const vector<int> &coins, int N, int amount)
{
    int MOD = 1e9 + 7;

    // Initialize a 2D DP matrix filled with -1 to indicate uncomputed states
    vector<vector<int>> dp(N, vector<int>(amount + 1, -1));

    return helper(N - 1, amount, coins, MOD, dp);
}

// ==================================================
// TABULATION (BOTTOM-UP DP)
//
// Idea:
// - Construct a bottom-up 2D dynamic programming table to systematically accumulate valid coin combinations iteratively.
// - Initialize the first row by evaluating if the target is perfectly divisible by the first coin.
// - Iteratively combine the subsets formed by either skipping or repeatedly picking the current coin denomination.
//
// Time Complexity: O(N * amount) - Nested loops traversing the entire DP table.
// Space Complexity: O(N * amount) - Memory specifically allocated for the 2D DP matrix.
// ==================================================

int count(const vector<int> &coins, int N, int amount)
{
    int MOD = 1e9 + 7;

    // Initialize the tabulation matrix completely with zeros
    vector<vector<int>> dp(N, vector<int>(amount + 1, 0));

    // Properly initialize the base state for the very first coin
    for (int target = 0; target <= amount; target++)
    {
        // If the target is achievable with only the first coin, mark it as 1 valid way
        if (target % coins[0] == 0)
            dp[0][target] = 1;
    }

    // Build up the solution iteratively for the remaining coin denominations
    for (int idx = 1; idx < N; idx++)
    {
        for (int target = 0; target <= amount; target++)
        {
            // Combinations achieved by ignoring the current coin
            int notTake = dp[idx - 1][target];

            // Combinations achieved by integrating the current coin (reusing the same row index)
            int take = (target >= coins[idx])
                           ? dp[idx][target - coins[idx]]
                           : 0;

            // Store the aggregate valid configurations safely utilizing modulo arithmetic
            dp[idx][target] = (notTake + take) % MOD;
        }
    }

    // Extract the final total combination count from the bottom-right coordinate
    return dp[N - 1][amount];
}

// ==================================================
// SPACE OPTIMIZATION DP
//
// Idea:
// - Recognize that computing the current dynamic programming row strictly requires data from the previous row and itself.
// - Replace the large two-dimensional matrix with two compact one-dimensional arrays to substantially reduce memory usage.
// - Systematically update the current array using combinations safely extracted from the previously calculated array state.
//
// Time Complexity: O(N * amount) - Retains the identical loop iteration count as tabulation.
// Space Complexity: O(amount) - Drastically reduced by utilizing just two 1D arrays.
// ==================================================

int count(const vector<int> &coins, int N, int amount)
{
    int MOD = 1e9 + 7;

    // Allocate two 1D arrays to manage state transitions optimally
    vector<int> prev(amount + 1, 0), curr(amount + 1, 0);

    // Initialize the fundamental base cases strictly for the first coin
    for (int target = 0; target <= amount; target++)
    {
        if (target % coins[0] == 0)
            prev[target] = 1;
    }

    // Loop continuously through the array sequentially updating combination counts
    for (int idx = 1; idx < N; idx++)
    {
        for (int target = 0; target <= amount; target++)
        {
            // Fetch combinations recorded where this coin was skipped previously
            int notTake = prev[target];

            // Fetch combinations where incorporating this coin satisfied constraints
            // Notice it retrieves data from 'curr' due to infinite coin supply
            int take = (target >= coins[idx])
                           ? curr[target - coins[idx]]
                           : 0;

            // Merge possibilities and lock them into the current state array
            curr[target] = (notTake + take) % MOD;
        }

        // Shift the completed current state downward to become the previous state
        prev = curr;
    }

    // Return the fully accumulated integer count resting at the target position
    return prev[amount];
}

int main()
{
    vector<int> coins = {1, 2, 3};

    int amount = 4;

    int N = coins.size();

    // Trigger the dynamic programming sequence and display the evaluated answer
    cout << "The total number of ways is " << count(coins, N, amount) << endl;

    return 0;
}
