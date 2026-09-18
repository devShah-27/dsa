// ==================================================
// PROBLEM
// - Given an array of stock prices and a transaction fee.
// - Find the maximum profit from unlimited transactions.
// - A fee is deducted for each complete transaction (on sell).
// - You must sell the current stock before buying again.
// ==================================================

#include <bits/stdc++.h>
using namespace std;

// ==================================================
// RECURSIVE APPROACH
//
// Idea:
// - Recursively explore all possible choices on each day.
// - Decisions include buying, selling, or simply doing nothing.
// - Deduct the specified transaction fee when a stock is sold.
// - Return the maximum profit derived from all valid decision paths.
//
// Time Complexity: O(2^n) - Two choices explored at each step.
// Space Complexity: O(n) - Auxiliary space required for the recursion stack.
// ==================================================

int helper(int idx, bool allowedToBuy, const vector<int> &arr, int n, int fee)
{
    // Base case: Reached the end of the days array
    if (idx == n)
        return 0;

    int profit = 0;

    if (allowedToBuy)
    {
        // Option 1: Buy today (subtract price) and move to next day
        int buy = helper(idx + 1, false, arr, n, fee) - arr[idx];

        // Option 2: Skip buying today and move to next day
        int notBuy = helper(idx + 1, true, arr, n, fee);

        profit = max(buy, notBuy);
    }
    else
    {
        // Option 1: Sell today (add price), deduct fee, and move to next day
        int sell = arr[idx] + helper(idx + 1, true, arr, n, fee) - fee;

        // Option 2: Skip selling today and hold the stock into the next day
        int notSell = helper(idx + 1, false, arr, n, fee);

        profit = max(sell, notSell);
    }

    return profit;
}

int stockBuySell(const vector<int> &arr, int n, int fee)
{
    // Start at day 0 with buying allowed
    return helper(0, true, arr, n, fee);
}

// ==================================================
// RECURSION + MEMOIZATION (TOP-DOWN DP)
//
// Idea:
// - Cache overlapping subproblems in a 2D memoization table.
// - The state combines the day index and buy eligibility.
// - If a state is already computed, fetch its cached profit.
// - This heavily prunes the massive recursion tree into linear time.
//
// Time Complexity: O(n * 2) - Total unique states calculated exactly once.
// Space Complexity: O(n * 2) for the DP table + O(n) for recursion stack.
// ==================================================

int helper(int idx, bool allowedToBuy, const vector<int> &arr, int n, int fee, vector<vector<int>> &dp)
{
    // Base case: No more days left to transact
    if (idx == n)
        return 0;

    // Return the precomputed answer if it exists in the DP table
    if (dp[idx][allowedToBuy] != -1)
        return dp[idx][allowedToBuy];

    int profit = 0;

    if (allowedToBuy)
    {
        int buy = helper(idx + 1, false, arr, n, fee, dp) - arr[idx];
        int notBuy = helper(idx + 1, true, arr, n, fee, dp);

        profit = max(buy, notBuy);
    }
    else
    {
        int sell = arr[idx] + helper(idx + 1, true, arr, n, fee, dp) - fee;
        int notSell = helper(idx + 1, false, arr, n, fee, dp);

        profit = max(sell, notSell);
    }

    // Cache the optimal result for this state before returning
    return dp[idx][allowedToBuy] = profit;
}

int stockBuySell(const vector<int> &arr, int n, int fee)
{
    // Initialize a 2D DP table of size (n+1) x 2 with -1 representing uncomputed states
    vector<vector<int>> dp(n + 1, vector<int>(2, -1));

    return helper(0, true, arr, n, fee, dp);
}

// ==================================================
// TABULATION (BOTTOM-UP DP)
//
// Idea:
// - Construct a 2D DP table and fill it iteratively backwards.
// - Compute optimal profits for every state up to day zero.
// - Avoids the overhead and potential stack overflow of recursive calls.
// - Evaluates dependencies safely since earlier days depend on later days.
//
// Time Complexity: O(n * 2) - Two nested loops covering all state combinations.
// Space Complexity: O(n * 2) - Dedicated memory for the 2D DP array structures.
// ==================================================

int stockBuySell(const vector<int> &arr, int n, int fee)
{
    // Size n+1 handles the base cases seamlessly where day n returns 0
    vector<vector<int>> dp(n + 1, vector<int>(2, 0));

    // Iterate backwards from the final day down to the first day
    for (int idx = n - 1; idx >= 0; idx--)
    {
        // Iterate through both buying states (0: not allowed, 1: allowed)
        for (int allowedToBuy = 0; allowedToBuy <= 1; allowedToBuy++)
        {
            int profit = 0;

            if (allowedToBuy)
            {
                int buy = dp[idx + 1][0] - arr[idx];
                int notBuy = dp[idx + 1][1];

                profit = max(buy, notBuy);
            }
            else
            {
                // Deduct the fee at the point of selling
                int sell = arr[idx] + dp[idx + 1][1] - fee;
                int notSell = dp[idx + 1][0];

                profit = max(sell, notSell);
            }

            // Store optimal choice for the current state combination
            dp[idx][allowedToBuy] = profit;
        }
    }

    // The answer resides at day 0, buying allowed
    return dp[0][1];
}

// ==================================================
// SPACE OPTIMIZATION DP
//
// Idea:
// - Notice that calculating the current day only requires tomorrow.
// - Replace the 2D DP table with two small 1D arrays.
// - Shift the current day's results into the previous array backwards.
// - Greatly reduces memory footprint while maintaining optimal time execution.
//
// Time Complexity: O(n * 2) - Consistent number of loop iterations as tabulation.
// Space Complexity: O(1) - Uses constant extra space relative to n.
// ==================================================

int stockBuySell(const vector<int> &arr, int n, int fee)
{
    // Tracks the optimal profits from the immediate next day
    vector<int> after(2, 0);

    for (int idx = n - 1; idx >= 0; idx--)
    {
        // Tracks the optimal profits being computed for the current day
        vector<int> curr(2, 0);

        for (int allowedToBuy = 0; allowedToBuy <= 1; allowedToBuy++)
        {
            int profit = 0;

            if (allowedToBuy)
            {
                int buy = after[0] - arr[idx];
                int notBuy = after[1];

                profit = max(buy, notBuy);
            }
            else
            {
                int sell = arr[idx] + after[1] - fee;
                int notSell = after[0];

                profit = max(sell, notSell);
            }

            curr[allowedToBuy] = profit;
        }

        // Shift current day's calculations into 'after' for the next backward step
        after = curr;
    }

    // Return the final accumulated result starting at day 0
    return after[1];
}

int main()
{
    int n = 5;

    vector<int> arr = {1, 3, 4, 0, 2};

    int fee = 1;

    cout << "The maximum profit that can be generated is " << stockBuySell(arr, n, fee);

    return 0;
}
