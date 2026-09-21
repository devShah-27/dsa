// ==================================================
// PROBLEM
// - Given an array of n integers and an integer K.
// - Count the number of subsets that sum to exactly K.
// - Return the result modulo 10^9 + 7 to prevent overflow.
// ==================================================

#include <bits/stdc++.h>
using namespace std;

// ==================================================
// RECURSIVE APPROACH
//
// Idea:
// - Explore all possible subsets by recursively choosing whether to include or exclude each array element.
// - If an element is included, subtract its value from the target sum and move backward.
// - If excluded, keep the target sum completely unchanged and move to the previous index.
// - Return the total count of valid subset formations.
//
// Time Complexity: O(2^n) - Two independent choices explored per element.
// Space Complexity: O(n) - Auxiliary space required for the recursion stack.
// ==================================================

int helper(int idx, int target, int n, const vector<int> &arr, int MOD)
{
    // Base case: If the exact target is met, one valid subset is found
    if (target == 0)
        return 1;

    // Base case: At the very first element, check if it matches the required target
    if (idx == 0)
        return (arr[idx] == target);

    // Choice 1: Exclude the current element and maintain the current target
    int notPick = helper(idx - 1, target, n, arr, MOD);

    // Choice 2: Include the current element if it does not exceed the remaining target
    int pick = (target >= arr[idx])
                   ? helper(idx - 1, target - arr[idx], n, arr, MOD)
                   : 0;

    // Combine counts from both branches and apply modulo to avoid integer overflow
    return (notPick + pick) % MOD;
}

int perfectSum(const vector<int> &arr, int K)
{
    int n = arr.size();

    // Define the modulo value as specified by the problem constraints
    int MOD = 1e9 + 7;

    // Start evaluating subsets recursively from the last element of the array
    return helper(n - 1, K, n, arr, MOD);
}

// ==================================================
// RECURSION + MEMOIZATION (TOP-DOWN DP)
//
// Idea:
// - Optimize the naive recursive approach by caching subproblem results in a 2D memoization table.
// - The state is uniquely defined by the current array index and the remaining target sum.
// - If a state has already been evaluated, instantly return its previously cached integer result.
// - This effectively prunes redundant recursive branches entirely.
//
// Time Complexity: O(n * K) - Each distinct state is computed exactly once.
// Space Complexity: O(n * K) for the DP table + O(n) for the recursion stack.
// ==================================================

int helper(int idx, int target, int n, const vector<int> &arr, int MOD, vector<vector<int>> &dp)
{
    // Base case: Subset summing to the target is successfully identified
    if (target == 0)
        return 1;

    // Base case: Reached the last remaining element in the recursive path
    if (idx == 0)
        return (arr[idx] == target);

    // Return the locally cached result if this state is already computed
    if (dp[idx][target] != -1)
        return dp[idx][target];

    // Branch 1: Traverse backward without selecting the current item
    int notPick = helper(idx - 1, target, n, arr, MOD, dp);

    // Branch 2: Traverse backward selecting the current item, if capacity permits
    int pick = (target >= arr[idx])
                   ? helper(idx - 1, target - arr[idx], n, arr, MOD, dp)
                   : 0;

    // Store the newly computed subset count into the memoization table before returning
    return dp[idx][target] = (notPick + pick) % MOD;
}

int perfectSum(const vector<int> &arr, int K)
{
    int n = arr.size();

    int MOD = 1e9 + 7;

    // Initialize a 2D DP matrix of size n x (K + 1) filled with -1 to represent uncomputed states
    vector<vector<int>> dp(n, vector<int>(K + 1, -1));

    return helper(n - 1, K, n, arr, MOD, dp);
}

// ==================================================
// TABULATION (BOTTOM-UP DP)
//
// Idea:
// - Build a bottom-up 2D dynamic programming table to systematically accumulate valid subset counts iteratively.
// - The first column is initialized to one because a zero target has one empty subset.
// - Iteratively combine the valid subset counts from both the inclusion and exclusion decision branches.
// - The final answer resides at the bottom-right corner.
//
// Time Complexity: O(n * K) - Nested loops filling the entire DP table.
// Space Complexity: O(n * K) - Memory specifically allocated for the 2D DP matrix.
// ==================================================

int perfectSum(const vector<int> &arr, int K)
{
    int n = arr.size();

    int MOD = 1e9 + 7;

    // Initialize the tabulation matrix with zeros
    vector<vector<int>> dp(n, vector<int>(K + 1, 0));

    // Base case: A target sum of 0 is always achievable via an empty subset
    for (int idx = 0; idx < n; idx++)
        dp[idx][0] = 1;

    // Base case: The first element itself can form a valid subset if it matches the target
    if (arr[0] <= K)
        dp[0][arr[0]] = 1;

    // Progressively solve for larger sub-arrays and increasing target sums
    for (int idx = 1; idx < n; idx++)
    {
        for (int target = 1; target <= K; target++)
        {
            // Count of subsets formed by omitting the current array element
            int notPick = dp[idx - 1][target];

            // Count of subsets formed by strictly including the current element
            int pick = (target >= arr[idx])
                           ? dp[idx - 1][target - arr[idx]]
                           : 0;

            // Combine possibilities and apply modulo arithmetic to prevent overflow
            dp[idx][target] = (notPick + pick) % MOD;
        }
    }

    // Return the total valid subsets for the full array and original target
    return dp[n - 1][K];
}

// ==================================================
// SPACE OPTIMIZATION DP
//
// Idea:
// - Recognize that computing the current DP row strictly requires only the immediately previous row.
// - Replace the entire 2D table with two compact one-dimensional arrays to save significant memory.
// - Process each element by updating the current array using values from the previous array state.
// - Output the final target count from the previous array.
//
// Time Complexity: O(n * K) - Retains the identical loop iteration count as tabulation.
// Space Complexity: O(K) - Drastically reduced by utilizing just two 1D arrays.
// ==================================================

int perfectSum(const vector<int> &arr, int K)
{
    int n = arr.size();

    int MOD = 1e9 + 7;

    // Stores subset counts computed using elements up to the previous index
    vector<int> prev(K + 1, 0);

    // Base case: A target sum of 0 is achievable via an empty subset
    prev[0] = 1;

    if (arr[0] <= K)
        prev[arr[0]] = 1;

    // Iterate through the rest of the array elements sequentially
    for (int idx = 1; idx < n; idx++)
    {
        // Stores subset counts being actively evaluated for the current index
        vector<int> curr(K + 1, 0);

        // A target sum of 0 remains achievable via an empty subset at any index
        curr[0] = 1;

        for (int target = 1; target <= K; target++)
        {
            // Extract the previously computed subset count assuming exclusion
            int notPick = prev[target];

            // Extract the previously computed subset count assuming inclusion
            int pick = (target >= arr[idx])
                           ? prev[target - arr[idx]]
                           : 0;

            // Compute total combinations forming the target at the current index
            curr[target] = (notPick + pick) % MOD;
        }

        // Overwrite the previous state with the current state for the next cycle
        prev = curr;
    }

    // The last computed configuration contains the solution at the target index
    return prev[K];
}

int main()
{
    vector<int> arr = {1, 2, 2, 3};

    int k = 3;

    // Execute the algorithm and display the accumulated count of valid subsets
    cout << "The number of subsets found are " << perfectSum(arr, k);

    return 0;
}
