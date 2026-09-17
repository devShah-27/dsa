// ==================================================
// PROBLEM
// - Given an array representing daily stock prices, find the maximum profit.
// - You can complete at most two transactions in total.
// - You must sell the current share before buying a new one.
// ==================================================

#include <bits/stdc++.h>
using namespace std;

// ==================================================
// RECURSIVE APPROACH
//
// Idea:
// - Recursively explore all choices: buy, sell, or do nothing.
// - Maintain states for current day, buy eligibility, and remaining transactions.
// - Reduce the transaction capacity only when a stock is sold.
// - Return the maximum profit derived from valid sequences of decisions.
//
// Time Complexity: O(2^n) - At each step, we explore two branching choices.
// Space Complexity: O(n) - Auxiliary space required for the depth of recursion stack.
// ==================================================

int helper(int idx, bool allowedToBuy, int cap, int n, const vector<int> &arr)
{
    // Base case: Reached the end of the days or ran out of transaction capacity
    if (idx == n || cap == 0)
        return 0;

    int profit = 0;

    if (allowedToBuy)
    {
        // Option 1: Buy today (subtract price) and move to next day
        int buy = helper(idx + 1, false, cap, n, arr) - arr[idx];

        // Option 2: Skip buying today and move to next day
        int notBuy = helper(idx + 1, true, cap, n, arr);

        profit = max(buy, notBuy);
    }
    else
    {
        // Option 1: Sell today (add price), reduce transaction capacity, and move to next day
        int sell = arr[idx] + helper(idx + 1, true, cap - 1, n, arr);

        // Option 2: Skip selling today and hold the stock into the next day
        int notSell = helper(idx + 1, false, cap, n, arr);

        profit = max(sell, notSell);
    }

    return profit;
}

int stockBuySell(const vector<int> &arr, int n)
{
    // Start at day 0, buying allowed, and a maximum of 2 transactions
    return helper(0, true, 2, n, arr);
}

// ==================================================
// RECURSION + MEMOIZATION (TOP-DOWN DP)
//
// Idea:
// - Store overlapping subproblems in a 3D memoization table to prevent recalculation.
// - The state combines the day index, buy eligibility, and remaining capacity.
// - If a state is already computed, fetch its cached profit directly.
// - This prunes the massive recursion tree into a linear sequence.
//
// Time Complexity: O(n * 2 * 3) - Total unique states calculated exactly once.
// Space Complexity: O(n * 2 * 3) for the DP table + O(n) for recursion stack.
// ==================================================

int helper(int idx, bool allowedToBuy, int cap, int n, const vector<int> &arr, vector<vector<vector<int>>> &dp)
{
    // Base case: No more days left or no more transactions allowed
    if (idx == n || cap == 0)
        return 0;

    // Return the precomputed answer if it exists in the DP table
    if (dp[idx][allowedToBuy][cap] != -1)
        return dp[idx][allowedToBuy][cap];

    int profit = 0;

    if (allowedToBuy)
    {
        int buy = helper(idx + 1, false, cap, n, arr, dp) - arr[idx];
        int notBuy = helper(idx + 1, true, cap, n, arr, dp);

        profit = max(buy, notBuy);
    }
    else
    {
        int sell = arr[idx] + helper(idx + 1, true, cap - 1, n, arr, dp);
        int notSell = helper(idx + 1, false, cap, n, arr, dp);

        profit = max(sell, notSell);
    }

    // Cache the optimal result for this state before returning
    return dp[idx][allowedToBuy][cap] = profit;
}

int stockBuySell(const vector<int> &arr, int n)
{
    // Initialize a 3D DP table of size n x 2 x 3 with -1 representing uncomputed states
    vector<vector<vector<int>>> dp(n, vector<vector<int>>(2, vector<int>(3, -1)));

    return helper(0, true, 2, n, arr, dp);
}

// ==================================================
// TABULATION (BOTTOM-UP DP)
//
// Idea:
// - Construct a 3D DP table and fill it starting from the end.
// - Iteratively compute optimal profits for every state up to day zero.
// - Avoids the overhead and potential overflow risks of recursive function calls.
// - Evaluates dependencies safely since day zero depends on day one.
//
// Time Complexity: O(n * 2 * 3) - Three nested loops covering all state combinations.
// Space Complexity: O(n * 2 * 3) - Dedicated memory for the 3D DP array structures.
// ==================================================

int stockBuySell(const vector<int> &arr, int n)
{
    // Size n+1 handles the base cases seamlessly where day n returns 0
    vector<vector<vector<int>>> dp(n + 1, vector<vector<int>>(2, vector<int>(3, 0)));

    // Iterate backwards from the final day down to the first day
    for (int idx = n - 1; idx >= 0; idx--)
    {
        // Iterate through both buying states (0: not allowed, 1: allowed)
        for (int allowedToBuy = 0; allowedToBuy <= 1; allowedToBuy++)
        {
            // Iterate through transaction capacities (1 and 2, as 0 means no profit)
            for (int cap = 1; cap <= 2; cap++)
            {
                int profit = 0;

                if (allowedToBuy)
                {
                    int buy = dp[idx + 1][0][cap] - arr[idx];
                    int notBuy = dp[idx + 1][1][cap];

                    profit = max(buy, notBuy);
                }
                else
                {
                    // Note that capacity only reduces when a transaction completes (sell)
                    int sell = arr[idx] + dp[idx + 1][1][cap - 1];
                    int notSell = dp[idx + 1][0][cap];

                    profit = max(sell, notSell);
                }

                // Store optimal choice for the current state combination
                dp[idx][allowedToBuy][cap] = profit;
            }
        }
    }

    // The answer resides at day 0, buying allowed, with 2 transactions available
    return dp[0][1][2];
}

// ==================================================
// SPACE OPTIMIZATION DP
//
// Idea:
// - Notice that calculating the current day only requires the immediate next day.
// - Replace the large 3D DP table with two compact 2D matrices.
// - Shift the current day's results into the previous array after each step.
// - Greatly reduces memory footprint while maintaining optimal time execution.
//
// Time Complexity: O(n * 2 * 3) - Consistent number of loop iterations as tabulation.
// Space Complexity: O(2 * 3) -> O(1) - Uses constant extra space for states.
// ==================================================

int stockBuySell(const vector<int> &arr, int n)
{
    // Tracks the optimal profits from the immediate next day
    vector<vector<int>> prev(2, vector<int>(3, 0));

    for (int idx = n - 1; idx >= 0; idx--)
    {
        // Tracks the optimal profits being computed for the current day
        vector<vector<int>> curr(2, vector<int>(3, 0));

        for (int allowedToBuy = 0; allowedToBuy <= 1; allowedToBuy++)
        {
            for (int cap = 1; cap <= 2; cap++)
            {
                int profit = 0;

                if (allowedToBuy)
                {
                    int buy = prev[0][cap] - arr[idx];
                    int notBuy = prev[1][cap];

                    profit = max(buy, notBuy);
                }
                else
                {
                    int sell = arr[idx] + prev[1][cap - 1];
                    int notSell = prev[0][cap];

                    profit = max(sell, notSell);
                }

                curr[allowedToBuy][cap] = profit;
            }
        }

        // Shift current day's calculations into prev for the next backward step
        prev = curr;
    }

    // Return the final accumulated result starting at day 0
    return prev[1][2];
}

int main()
{
    int n = 8;

    vector<int> arr = {3, 3, 5, 0, 0, 3, 1, 4};

    cout << "The maximum profit that can be generated is " << stockBuySell(arr, n);

    return 0;
}
