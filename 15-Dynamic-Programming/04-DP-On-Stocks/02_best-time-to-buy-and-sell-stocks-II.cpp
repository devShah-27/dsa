// ==================================================
// PROBLEM
// - Given an array representing daily stock prices, find the maximum profit.
// - Unlimited transactions are allowed, but you can only hold one share at a time.
// - You must sell the current share before buying a new one.
// ==================================================

#include <bits/stdc++.h>
using namespace std;

// ==================================================
// RECURSIVE APPROACH
//
// Idea:
// - Simulate all possible decisions on each day recursively.
// - Maintain a boolean flag to track buying eligibility.
// - On each day, choose to either transact or skip.
// - Return the maximum profit from all possible valid paths. 
//
// Time Complexity: O(2^n) - At each step, we explore two choices (buy/sell or do nothing).
// Space Complexity: O(n) - Auxiliary space required for the recursion stack.
// ==================================================

int helper(int idx, bool allowedToBuy, vector<int> &arr, int n)
{
    // Base case: Reached the end of the days array
    if (idx == n)
        return 0;

    int profit = 0;

    if (allowedToBuy) // if buying is allowed
    {
        // Option 1: Buy the stock today (deduct price) and move to next day where buying is restricted
        int buyStock = helper(idx + 1, false, arr, n) - arr[idx];

        // Option 2: Do not buy today and move to next day where buying remains allowed
        int notBuyStock = helper(idx + 1, true, arr, n);

        profit = max(buyStock, notBuyStock);
    }
    else // if buying is not allowed (meaning we hold a stock)
    {
        // Option 1: Sell the stock today (add price) and move to next day where buying is allowed again
        int sellStock = arr[idx] + helper(idx + 1, true, arr, n);

        // Option 2: Do not sell today and move to next day holding the stock
        int notSellStock = helper(idx + 1, false, arr, n);

        profit = max(sellStock, notSellStock);
    }

    return profit;
}

int stockBuySell(vector<int> &arr, int n)
{
    // Start at day 0 with buying allowed
    return helper(0, true, arr, n);
}

// ==================================================
// RECURSION + MEMOIZATION (TOP-DOWN DP)
//
// Idea:
// - Cache the results of overlapping subproblems using memoization.
// - State is defined by the day index and eligibility.
// - Prevents redundant calculations of previously visited decision paths.
// - Significantly reduces the exponential time complexity to linear time.
//
// Time Complexity: O(n * 2) - At most 2 states per day are computed once.
// Space Complexity: O(n * 2) for DP array + O(n) for the recursion stack.
// ==================================================

int helper(int idx, bool allowedToBuy, vector<int> &arr, int n, vector<vector<int>> &dp)
{
    // Base case: No more days left to transact
    if (idx == n)
        return 0;

    int profit = 0;

    // Return the precomputed answer if it exists in the DP table
    if (dp[idx][allowedToBuy] != -1)
        return dp[idx][allowedToBuy];

    if (allowedToBuy) // if buying is allowed
    {
        int buyStock = helper(idx + 1, false, arr, n, dp) - arr[idx];
        int notBuyStock = helper(idx + 1, true, arr, n, dp);

        profit = max(buyStock, notBuyStock);
    }
    else // if buying is not allowed
    {
        int sellStock = arr[idx] + helper(idx + 1, true, arr, n, dp);
        int notSellStock = helper(idx + 1, false, arr, n, dp);

        profit = max(sellStock, notSellStock);
    }

    // Cache the result before returning
    return dp[idx][allowedToBuy] = profit;
}

int stockBuySell(vector<int> &arr, int n)
{
    // Initialize DP table of size n x 2 with -1 representing uncomputed states
    vector<vector<int>> dp(n, vector<int>(2, -1));

    return helper(0, true, arr, n, dp);
}

// ==================================================
// TABULATION (BOTTOM-UP DP)
//
// Idea:
// - Build the solution bottom-up starting from the final day.
// - Iteratively compute profits for both buying and selling states.
// - This approach entirely eliminates the overhead of recursive calls.
// - Maintains the optimal linear time complexity of the algorithm.
//
// Time Complexity: O(n * 2) - Iterating backwards through the array.
// Space Complexity: O(n * 2) - For storing the 2D DP table.
// ==================================================

int stockBuySell(vector<int> &arr, int n)
{
    // Size n+1 handles the base case easily without out-of-bounds errors
    vector<vector<int>> dp(n + 1, vector<int>(2, 0));

    // Base case representation (redundant since vector initializes to 0, but explicit for clarity)
    dp[n][0] = dp[n][1] = 0;

    // Iterate backwards from the last day to the first day
    for (int idx = n - 1; idx >= 0; idx--)
    {
        // Try both states: allowedToBuy (1) and not allowedToBuy (0)
        for (int allowedToBuy = 0; allowedToBuy <= 1; allowedToBuy++)
        {
            int profit = 0;

            if (allowedToBuy)
            {
                int buyStock = dp[idx + 1][0] - arr[idx];
                int notBuyStock = dp[idx + 1][1];

                profit = max(buyStock, notBuyStock);
            }
            else
            {
                int sellStock = arr[idx] + dp[idx + 1][1];
                int notSellStock = dp[idx + 1][0];

                profit = max(sellStock, notSellStock);
            }

            // Store optimal choice for current state
            dp[idx][allowedToBuy] = profit;
        }
    }

    // Return the answer for day 0 where buying is allowed
    return dp[0][1];
}

// ==================================================
// SPACE OPTIMIZATION DP
//
// Idea:
// - Observe that the current day only depends on tomorrow.
// - Replace the full DP table with two small arrays.
// - This reduces the auxiliary space complexity to constant space.
// - Achieves the most optimal dynamic programming solution possible here.
//
// Time Complexity: O(n * 2) - Still single traversal with two states.
// Space Complexity: O(1) - Only uses two 1D arrays of size 2.
// ==================================================

int stockBuySell(vector<int> &arr, int n)
{
    // Tracks the optimal profits from the immediate next day
    vector<int> prev(2, 0);

    // Base case representation
    prev[0] = prev[1] = 0;

    for (int idx = n - 1; idx >= 0; idx--)
    {
        // Tracks the optimal profits computed for the current day
        vector<int> curr(2, 0);

        for (int allowedToBuy = 0; allowedToBuy <= 1; allowedToBuy++)
        {
            int profit = 0;

            if (allowedToBuy)
            {
                int buyStock = prev[0] - arr[idx];
                int notBuyStock = prev[1];

                profit = max(buyStock, notBuyStock);
            }
            else
            {
                int sellStock = arr[idx] + prev[1];
                int notSellStock = prev[0];

                profit = max(sellStock, notSellStock);
            }

            curr[allowedToBuy] = profit;
        }

        // Shift current day's results into prev for the next loop iteration
        prev = curr;
    }

    // Return result starting at day 0 with buying allowed
    return prev[1];
}

// ==================================================
// GREEDY APPROACH
//
// Idea:
// - Capture every single upward price movement in the array.
// - If today's price exceeds yesterday's, add the difference immediately.
// - This perfectly accumulates all local minimum-to-maximum profit segments.
// - It is the most optimal and intuitive solution overall.
//
// Time Complexity: O(n) - Single forward pass through the array.
// Space Complexity: O(1) - Uses no extra space.
// ==================================================

int stockBuySell(vector<int> &arr, int n)
{
    int profit = 0;

    // Traverse starting from day 1 to compare with the previous day
    for (int day = 1; day < n; day++)
    {
        // Whenever the price goes up, simulate a buy yesterday and sell today
        if (arr[day] > arr[day - 1])
        {
            profit += (arr[day] - arr[day - 1]);
        }
    }

    return profit;
}

int main()
{
    int n = 6;

    vector<int> arr = {7, 1, 5, 3, 6, 4};

    cout << "The maximum profit that can be generated is " << stockBuySell(arr, n);

    return 0;
}
