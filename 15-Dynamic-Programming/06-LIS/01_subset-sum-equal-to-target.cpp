// ==================================================
// PROBLEM
// - Given an array of n integers and a target sum.
// - Determine if any subset of the array sums to the exact given target.
// ==================================================

#include <bits/stdc++.h>
using namespace std;

// ==================================================
// RECURSIVE APPROACH
//
// Idea:
// - Recursively explore all subsets by either including or excluding the current element.
// - If we include it, reduce the target by the element's value and move backward.
// - If we exclude it, simply move to the previous element without changing the target.
// - Return true if the target exactly reaches zero.
//
// Time Complexity: O(2^n) - We explore two choices per element.
// Space Complexity: O(n) - Auxiliary space required for the recursion stack.
// ==================================================

bool helper(int idx, int target, const vector<int> &arr)
{
    // Base case: If target is met, subset exists
    if (target == 0)
        return true;

    // Base case: If we reach the first element, check if it matches target
    if (idx == 0)
        return arr[idx] == target;

    // Choice 1: Do not include the current element in the subset sum
    bool notTake = helper(idx - 1, target, arr);

    // Choice 2: Include the current element if it does not exceed target
    bool take = (target >= arr[idx])
                    ? helper(idx - 1, target - arr[idx], arr)
                    : false;

    // Return true if either choice yields a valid subset
    return (notTake || take);
}

bool isSubsetSum(const vector<int> &arr, int target)
{
    int n = arr.size();

    // Start recursion from the last element of the array
    return helper(n - 1, target, arr);
}

// ==================================================
// RECURSION + MEMOIZATION (TOP-DOWN DP)
//
// Idea:
// - Cache results in a 2D memoization table to prevent redundant recalculations of overlapping subproblems.
// - The state is uniquely defined by the current index and the remaining target sum.
// - If a state has been evaluated before, directly return its cached boolean value.
//
// Time Complexity: O(n * target) - Each state is computed exactly once.
// Space Complexity: O(n * target) for DP table + O(n) for recursion stack.
// ==================================================

bool helper(int idx, int target, const vector<int> &arr, vector<vector<int>> &dp)
{
    // Base case: Target sum successfully achieved
    if (target == 0)
        return true;

    // Base case: Only first element left
    if (idx == 0)
        return arr[idx] == target;

    // Return cached result if already calculated
    if (dp[idx][target] != -1)
        return dp[idx][target];

    bool notTake = helper(idx - 1, target, arr, dp);

    bool take = (target >= arr[idx])
                    ? helper(idx - 1, target - arr[idx], arr, dp)
                    : false;

    // Store the computed result in the DP table before returning
    return dp[idx][target] = (notTake || take);
}

bool isSubsetSum(const vector<int> &arr, int target)
{
    int n = arr.size();

    // Initialize DP table with -1 representing uncomputed states
    vector<vector<int>> dp(n, vector<int>(target + 1, -1));

    return helper(n - 1, target, arr, dp);
}

// ==================================================
// TABULATION (BOTTOM-UP DP)
//
// Idea:
// - Construct a 2D DP table and build up the solution iteratively from the base cases.
// - The first column represents a target of zero, which is always true (empty subset).
// - Iteratively determine if the current target is achievable by either taking or not taking the element.
//
// Time Complexity: O(n * target) - Nested loops filling the DP table.
// Space Complexity: O(n * target) - Dedicated memory for the 2D DP matrix.
// ==================================================

bool isSubsetSum(const vector<int> &arr, int target)
{
    int n = arr.size();

    // dp[i][j] stores whether target j can be achieved using a subset of arr[0...i]
    vector<vector<bool>> dp(n, vector<bool>(target + 1, false));

    // Base case: Target 0 is always achievable (empty subset)
    for (int idx = 0; idx < n; idx++)
    {
        dp[idx][0] = true;
    }

    // Base case: The first element can independently form a target equal to its value
    dp[0][arr[0]] = (arr[0] <= target) ? true : false;

    // Fill the DP table iteratively for the remaining elements
    for (int idx = 1; idx < n; idx++)
    {
        for (int currTarget = 1; currTarget <= target; currTarget++)
        {
            // Value if we don't take the current element
            bool notTake = dp[idx - 1][currTarget];

            // Value if we take the current element
            bool take = (currTarget >= arr[idx])
                            ? dp[idx - 1][currTarget - arr[idx]]
                            : false;

            // Current target is reachable if either choice works
            dp[idx][currTarget] = (notTake || take);
        }
    }

    // Return the result for the full array and original target
    return dp[n - 1][target];
}

// ==================================================
// SPACE OPTIMIZATION DP
//
// Idea:
// - Observe that calculating the current row only depends on values from the immediately previous row.
// - Replace the full 2D DP table with two 1D arrays: previous and current.
// - Greatly reduces memory footprint while maintaining the exact same optimal time execution.
//
// Time Complexity: O(n * target) - Consistent loop iterations as tabulation.
// Space Complexity: O(target) - Uses two 1D arrays of size target + 1.
// ==================================================

bool isSubsetSum(const vector<int> &arr, int target)
{
    int n = arr.size();

    // Array to track reachable targets using elements up to the previous index
    vector<bool> prev(target + 1, false);

    prev[0] = true;

    prev[arr[0]] = (arr[0] <= target) ? true : false;

    for (int idx = 1; idx < n; idx++)
    {
        // Array to track reachable targets for the current element
        vector<bool> curr(target + 1, false);

        curr[0] = true;

        for (int currTarget = 1; currTarget <= target; currTarget++)
        {
            // Fetch results from the previous row representation
            bool notTake = prev[currTarget];

            bool take = (currTarget >= arr[idx])
                            ? prev[currTarget - arr[idx]]
                            : false;

            curr[currTarget] = (notTake || take);
        }

        // Move current row data to previous row for the next step
        prev = curr;
    }

    // Final answer is stored in the last evaluated target of the previous row
    return prev[target];
}

int main()
{
    vector<int> arr = {1, 2, 3, 4};

    int target = 4;

    if (isSubsetSum(arr, target))
        cout << "Subset with the given target found";
    else
        cout << "Subset with the given target not found";

    return 0;
}
