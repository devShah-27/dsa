// ==================================================
// PROBLEM
// - Given an array representing daily stock prices, find the maximum profit.
// - You can complete at most k transactions in total.
// - You must sell the current share before buying a new one.
// ==================================================

#include <bits/stdc++.h>
using namespace std;

// ==================================================
// RECURSIVE APPROACH
//
// Idea:
// - Recursively explore all possible choices on each day: buy, sell, or simply do nothing.
// - Maintain states for the current day index, the remaining transaction capacity, and buy eligibility.
// - Reduce the transaction capacity only when a stock is successfully sold.
// - Return the maximum profit derived from all valid sequences of decisions.
//
// Time Complexity: O(2^n) - Two choices explored at each step.
// Space Complexity: O(n) - Auxiliary space required for the recursion stack.
// ==================================================

int helper(int idx, int cap, bool allowedToBuy, const vector<int> &arr, int n)
{
    // Base case: Reached the end of the days or ran out of transaction capacity
    if (idx == n || cap == 0)
        return 0;

    int profit = 0;

    if (allowedToBuy)
    {
        // Option 1: Buy today (subtract price) and move to next day
        int buy = helper(idx + 1, cap, false, arr, n) - arr[idx];

        // Option 2: Skip buying today and move to next day
        int notBuy = helper(idx + 1, cap, true, arr, n);

        profit = max(buy, notBuy);
    }
    else
    {
        // Option 1: Sell today (add price), reduce transaction capacity, and move to next day
        int sell = arr[idx] + helper(idx + 1, cap - 1, true, arr, n);

        // Option 2: Skip selling today and hold the stock into the next day
        int notSell = helper(idx + 1, cap, false, arr, n);

        profit = max(sell, notSell);
    }

    return profit;
}

int stockBuySell(const vector<int> &arr, int n, int k)
{
    // Start at day 0, buying allowed, and a maximum of k transactions
    return helper(0, k, true, arr, n);
}

// ==================================================
// RECURSION + MEMOIZATION (TOP-DOWN DP)
//
// Idea:
// - Store overlapping subproblems in a 3D memoization table to prevent redundant recalculation.
// - The state combines the day index, remaining capacity, and buy eligibility.
// - If a state is already computed, fetch its cached profit directly.
// - This heavily prunes the massive recursion tree into a linear sequence.
//
// Time Complexity: O(n * k * 2) - Total unique states calculated exactly once.
// Space Complexity: O(n * k * 2) for the DP table + O(n) for recursion stack.
// ==================================================

int helper(int idx, int cap, bool allowedToBuy, const vector<int> &arr, int n, vector<vector<vector<int>>> &dp)
{
    // Base case: No more days left or no more transactions allowed
    if (idx == n || cap == 0)
        return 0;

    // Return the precomputed answer if it exists in the DP table
    if (dp[idx][cap][allowedToBuy] != -1)
        return dp[idx][cap][allowedToBuy];

    int profit = 0;

    if (allowedToBuy)
    {
        int buy = helper(idx + 1, cap, false, arr, n, dp) - arr[idx];
        int notBuy = helper(idx + 1, cap, true, arr, n, dp);

        profit = max(buy, notBuy);
    }
    else
    {
        int sell = arr[idx] + helper(idx + 1, cap - 1, true, arr, n, dp);
        int notSell = helper(idx + 1, cap, false, arr, n, dp);

        profit = max(sell, notSell);
    }

    // Cache the optimal result for this state before returning
    return dp[idx][cap][allowedToBuy] = profit;
}

int stockBuySell(const vector<int> &arr, int n, int k)
{
    // Initialize a 3D DP table of size (n+1) x (k+1) x 2 with -1 representing uncomputed states
    vector<vector<vector<int>>> dp(n + 1, vector<vector<int>>(k + 1, vector<int>(2, -1)));

    return helper(0, k, true, arr, n, dp);
}

// ==================================================
// TABULATION (BOTTOM-UP DP)
//
// Idea:
// - Construct a 3D DP table and fill it iteratively starting from the end.
// - Compute optimal profits for every state up to day zero.
// - Avoids the overhead and potential stack overflow risks of recursive function calls.
// - Evaluates dependencies safely since earlier days depend on later days.
//
// Time Complexity: O(n * k * 2) - Three nested loops covering all state combinations.
// Space Complexity: O(n * k * 2) - Dedicated memory for the 3D DP array structures.
// ==================================================

int stockBuySell(const vector<int> &arr, int n, int k)
{
    // Size n+1 handles the base cases seamlessly where day n returns 0
    vector<vector<vector<int>>> dp(n + 1, vector<vector<int>>(k + 1, vector<int>(2, 0)));

    // Iterate backwards from the final day down to the first day
    for (int idx = n - 1; idx >= 0; idx--)
    {
        // Iterate through all valid transaction capacities up to k
        for (int cap = 1; cap <= k; cap++)
        {
            // Iterate through both buying states (0: not allowed, 1: allowed)
            for (int allowedToBuy = 0; allowedToBuy <= 1; allowedToBuy++)
            {
                int profit = 0;

                if (allowedToBuy)
                {
                    int buy = dp[idx + 1][cap][0] - arr[idx];
                    int notBuy = dp[idx + 1][cap][1];

                    profit = max(buy, notBuy);
                }
                else
                {
                    // Note that capacity only reduces when a transaction completes (sell)
                    int sell = arr[idx] + dp[idx + 1][cap - 1][1];
                    int notSell = dp[idx + 1][cap][0];

                    profit = max(sell, notSell);
                }

                // Store optimal choice for the current state combination
                dp[idx][cap][allowedToBuy] = profit;
            }
        }
    }

    // The answer resides at day 0, buying allowed, with k transactions available
    return dp[0][k][1];
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
// Time Complexity: O(n * k * 2) - Consistent number of loop iterations as tabulation.
// Space Complexity: O(k * 2) - Uses constant extra space relative to n.
// ==================================================

int stockBuySell(const vector<int> &arr, int n, int k)
{
    // Tracks the optimal profits from the immediate next day
    vector<vector<int>> after(k + 1, vector<int>(2, 0));

    for (int idx = n - 1; idx >= 0; idx--)
    {
        // Tracks the optimal profits being computed for the current day
        vector<vector<int>> curr(k + 1, vector<int>(2, 0));

        for (int cap = 1; cap <= k; cap++)
        {
            for (int allowedToBuy = 0; allowedToBuy <= 1; allowedToBuy++)
            {
                int profit = 0;

                if (allowedToBuy)
                {
                    int buy = after[cap][0] - arr[idx];
                    int notBuy = after[cap][1];

                    profit = max(buy, notBuy);
                }
                else
                {
                    int sell = arr[idx] + after[cap - 1][1];
                    int notSell = after[cap][0];

                    profit = max(sell, notSell);
                }

                curr[cap][allowedToBuy] = profit;
            }
        }

        // Shift current day's calculations into 'after' for the next backward step
        after = curr;
    }

    // Return the final accumulated result starting at day 0
    return after[k][1];
}

int main()
{
    int n = 8;

    vector<int> arr = {3, 3, 5, 0, 0, 3, 1, 4};

    int k = 3;

    cout << "The maximum profit that can be generated is " << stockBuySell(arr, n, k);

    return 0;
}
