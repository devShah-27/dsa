// ==================================================
// PROBLEM
// - Given an array of coin denominations and a target amount.
// - Find the minimum number of coins needed to make the amount.
// - You have an infinite supply of each coin denomination.
// - Return -1 if the amount cannot be made.
// ==================================================

#include <bits/stdc++.h>
using namespace std;

// ==================================================
// RECURSIVE APPROACH
//
// Idea:
// - Recursively explore all combinations by choosing to either include or exclude the current coin denomination.
// - If included, the coin can be reused, so we do not decrement the current coin index.
// - If excluded, we simply move to the previous coin index without altering the remaining target amount.
// - Return the minimum coin count among valid paths.
//
// Time Complexity: O(>2^n) - Exponential due to infinite supply branching.
// Space Complexity: O(amount) - Auxiliary space required for the recursion stack.
// ==================================================

int helper(int idx, int target, const vector<int> &coins)
{
    // Base case: Evaluated down to the first coin denomination
    if (idx == 0)
    {
        // If the remaining target is perfectly divisible by this coin
        if (target % coins[0] == 0)
            return target / coins[0];

        // NOTE: Returning 1e9 instead of INT_MAX prevents integer overflow
        // when 1 is added to the returned value in the 'take' branch.
        return 1e9;
    }

    // Branch 1: Skip the current coin and move to the previous one
    int notTake = helper(idx - 1, target, coins);

    // Branch 2: Take the current coin if it fits within the target
    // Notice that idx is NOT decremented since we have an infinite supply
    int take = (target >= coins[idx])
                   ? 1 + helper(idx, target - coins[idx], coins)
                   : 1e9;

    // Return the minimum coin count between both choices
    return min(notTake, take);
}

int MinimumCoins(const vector<int> &coins, int amount)
{
    int n = coins.size();

    // Start evaluating combinations recursively from the last coin index
    int res = helper(n - 1, amount, coins);

    // If the result is >= 1e9, it means no valid combination exists
    if (res >= 1e9)
        return -1;

    return res;
}

// ==================================================
// RECURSION + MEMOIZATION (TOP-DOWN DP)
//
// Idea:
// - Optimize the naive recursive solution by caching the results of overlapping subproblems in a 2D table.
// - The state is defined by the current coin index and the remaining target amount we need.
// - If a state has already been calculated previously, immediately return its cached minimum coin count value.
//
// Time Complexity: O(n * amount) - Each unique state is computed exactly once.
// Space Complexity: O(n * amount) for DP table + O(amount) for recursion stack.
// ==================================================

int helper(int idx, int target, const vector<int> &coins, vector<vector<int>> &dp)
{
    // Base case: Reached the first coin denomination
    if (idx == 0)
    {
        if (target % coins[0] == 0)
            return target / coins[0];

        return 1e9; // Represents an invalid path
    }

    // Return the locally cached result if this state is already solved
    if (dp[idx][target] != -1)
        return dp[idx][target];

    // Branch 1: Exclude the current coin from the combination
    int notTake = helper(idx - 1, target, coins, dp);

    // Branch 2: Include the current coin and remain at the same index
    int take = (target >= coins[idx])
                   ? 1 + helper(idx, target - coins[idx], coins, dp)
                   : 1e9;

    // Cache the absolute minimum result in the DP matrix before returning
    return dp[idx][target] = min(notTake, take);
}

int MinimumCoins(const vector<int> &coins, int amount)
{
    int n = coins.size();

    // Initialize a 2D DP matrix filled with -1 to indicate uncomputed states
    vector<vector<int>> dp(n, vector<int>(amount + 1, -1));

    int res = helper(n - 1, amount, coins, dp);

    if (res >= 1e9)
        return -1;

    return res;
}

// ==================================================
// TABULATION (BOTTOM-UP DP)
//
// Idea:
// - Construct a bottom-up 2D dynamic programming table to iteratively compute the minimum coins for every amount.
// - Initialize the first row for the first coin by checking exact divisibility with the target amounts.
// - Iteratively combine the optimal results from including or excluding the current coin to build up solutions.
//
// Time Complexity: O(n * amount) - Nested loops evaluating every DP state.
// Space Complexity: O(n * amount) - Memory allocated for the 2D DP matrix.
// ==================================================

int MinimumCoins(const vector<int> &coins, int amount)
{
    int n = coins.size();

    // Initialize the tabulation matrix with zeros
    vector<vector<int>> dp(n, vector<int>(amount + 1, 0));

    // Base case setup: Populate the first row for the first coin denomination
    for (int target = 0; target <= amount; target++)
    {
        if (target % coins[0] == 0)
            dp[0][target] = target / coins[0];
        else
            dp[0][target] = 1e9; // Mark unreachable amounts as invalid
    }

    // Process the remaining coin denominations progressively
    for (int idx = 1; idx < n; idx++)
    {
        for (int target = 0; target <= amount; target++)
        {
            // Minimum coins if we choose to exclude the current coin
            int notTake = dp[idx - 1][target];

            // Minimum coins if we choose to include it (stays on the same row)
            int take = (target >= coins[idx])
                           ? 1 + dp[idx][target - coins[idx]]
                           : 1e9;

            // Merge possibilities and save the optimal minimum count
            dp[idx][target] = min(notTake, take);
        }
    }

    // Retrieve the optimal count for the full array and target amount
    int res = dp[n - 1][amount];

    if (res >= 1e9)
        return -1;

    return res;
}

// ==================================================
// 2-ROW SPACE OPTIMIZATION
//
// Idea:
// - Recognize that evaluating the current row only requires access to the previously computed row's optimal data.
// - Replace the entire 2D table with two compact one-dimensional arrays to substantially reduce memory usage.
// - Systematically evaluate the current array states using the values stored safely in the previous array state.
//
// Time Complexity: O(n * amount) - Retains the identical loop iteration count.
// Space Complexity: O(amount) - Drastically reduced by utilizing just two 1D arrays.
// ==================================================

int MinimumCoins(const vector<int> &coins, int amount)
{
    int n = coins.size();

    // Utilize two single-dimensional arrays for state transition storage
    vector<int> prev(amount + 1, 0), curr(amount + 1, 0);

    // Initialize the base configuration for the very first coin
    for (int target = 0; target <= amount; target++)
    {
        if (target % coins[0] == 0)
            prev[target] = target / coins[0];
        else
            prev[target] = 1e9;
    }

    // Evaluate combinations iteratively for the rest of the coins
    for (int idx = 1; idx < n; idx++)
    {
        for (int target = 0; target <= amount; target++)
        {
            // Inherited minimum coin count when skipping the current coin
            int notTake = prev[target];

            // Calculated minimum count when including the current coin
            // NOTE: It refers to 'curr' because of the infinite supply property
            int take = (target >= coins[idx])
                           ? 1 + curr[target - coins[idx]]
                           : 1e9;

            // Store the best valid outcome in the current array
            curr[target] = min(notTake, take);
        }

        // Overwrite the previous state vector with the completed current row
        prev = curr;
    }

    // The definitive answer remains at the target index of the previous array
    int res = prev[amount];

    if (res >= 1e9)
        return -1;

    return res;
}

// ==================================================
// 1-ROW SPACE OPTIMIZATION
//
// Idea:
// - Optimize memory further by using a single array to store and update all minimum coin counts.
// - Since we have an infinite supply of coins, we iterate left-to-right to use newly updated values.
// - This perfectly mimics the behavior of the current row while using only one single array structure.
//
// Time Complexity: O(n * amount) - Still retains the identical iteration bounds.
// Space Complexity: O(amount) - Achieves the absolute minimum memory using just one array.
// ==================================================

int MinimumCoins(const vector<int> &coins, int amount)
{
    int n = coins.size();

    // Utilize a single dimensional array to maintain state transitions in place
    vector<int> prev(amount + 1, 0);

    // Populate the base state combinations for the first coin
    for (int target = 0; target <= amount; target++)
    {
        if (target % coins[0] == 0)
            prev[target] = target / coins[0];
        else
            prev[target] = 1e9;
    }

    // Iterate through all remaining coin denominations
    for (int idx = 1; idx < n; idx++)
    {
        // NOTE: Iterating left-to-right is critical for unbounded knapsack variants.
        // It guarantees that prev[target - coins[idx]] uses the updated value
        // of the current coin index, perfectly simulating an infinite supply.
        for (int target = 0; target <= amount; target++)
        {
            // The value if we choose not to take is naturally already in prev[target]
            int notTake = prev[target];

            // Calculate the value if we successfully take the coin
            int take = (target >= coins[idx])
                           ? 1 + prev[target - coins[idx]]
                           : 1e9;

            // Update the array position in place with the optimal minimum
            prev[target] = min(notTake, take);
        }
    }

    // Return the minimum coins found at the extreme end of the array
    int res = prev[amount];

    if (res >= 1e9)
        return -1;

    return res;
}

int main()
{
    vector<int> coins = {1, 2, 3};

    int amount = 7;

    // Execute the algorithm and display the absolute minimum coins required
    cout << "The total number of ways is " << MinimumCoins(coins, amount) << endl;

    return 0;
}
