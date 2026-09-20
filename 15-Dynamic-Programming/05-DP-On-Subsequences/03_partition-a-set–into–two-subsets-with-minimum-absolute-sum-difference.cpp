// ==================================================
// PROBLEM
// - Given an array of integers, partition it into two subsets.
// - The goal is to ensure the absolute difference between their respective subset sums is minimized.
// ==================================================

#include <bits/stdc++.h>
using namespace std;

// ==================================================
// RECURSIVE APPROACH
//
// Idea:
// - Find the total sum of all elements in the array to define the maximum possible subset sum.
// - For every possible sum from zero to the total, recursively check if a valid subset exists.
// - If a subset sum is possible, calculate the absolute difference with the remaining array partition sum.
// - Track and return the minimum absolute difference found across all valid subset combinations in the array.
//
// Time Complexity: O(total * 2^n) - Recursive calls inside a loop.
// Space Complexity: O(n) - Auxiliary space required for the recursion stack.
// ==================================================

bool helper(int idx, int target, const vector<int> &arr, int n)
{
    // Base case: If the subset sum exactly matches the target, it's valid
    if (target == 0)
        return true;

    // Base case: If we are at the first element, check if it equals the target
    if (idx == 0)
        return (arr[idx] == target);

    // Choice 1: Exclude the current element from our subset sum
    bool notTake = helper(idx - 1, target, arr, n);

    // Choice 2: Include the current element if it does not exceed the target
    bool take = (target >= arr[idx]) ? helper(idx - 1, target - arr[idx], arr, n) : false;

    // Return true if either excluding or including the element works
    return notTake | take;
}

int minDifference(const vector<int> &arr, int n)
{
    int target = 0;

    // Calculate the total sum of all elements in the array
    // This total sum represents the maximum possible sum a subset could achieve
    for (int i = 0; i < n; i++)
    {
        target += arr[i];
    }

    // Initialize the minimum difference to a very large number
    int mini = 1e9;

    for (int i = 0; i <= target / 2; i++)
    {
        // Check if the current sum 'i' can be formed by any subset
        if (helper(n - 1, i, arr, n))
        {
            // If valid, calculate the absolute difference between partition 'i' and partition 'target - i'
            mini = min(mini, abs(i - (target - i)));
        }
    }

    return mini;
}

// ==================================================
// RECURSION + MEMOIZATION (TOP-DOWN DP)
//
// Idea:
// - Enhance the naive recursive search by introducing a two-dimensional memoization table to cache overlapping subproblem results.
// - The state is defined by the current index and the target sum we are trying to form.
// - Precompute all possible subset sums by running the memoized function for every target up to total.
// - Iterate through the computed states to find the minimum difference between two valid complimentary subset partitions.
//
// Time Complexity: O(n * total) - DP states are computed only once.
// Space Complexity: O(n * total) for DP table + O(n) for recursion stack.
// ==================================================

bool helper(int idx, int target, const vector<int> &arr, int n, vector<vector<int>> &dp)
{
    // Base case: Target sum successfully achieved
    if (target == 0)
        return true;

    // Base case: Only the first element is left to evaluate
    if (idx == 0)
        return (arr[idx] == target);

    // Return the cached result if this state has already been computed
    if (dp[idx][target] != -1)
        return dp[idx][target];

    // Branch 1: Move to the next element without taking the current one
    bool notTake = helper(idx - 1, target, arr, n, dp);

    // Branch 2: Take the current element if it fits within the remaining target
    bool take = (target >= arr[idx]) ? helper(idx - 1, target - arr[idx], arr, n, dp) : false;

    // Cache the optimal boolean result for this state before returning
    return dp[idx][target] = notTake | take;
}

int minDifference(const vector<int> &arr, int n)
{
    int target = 0;

    // Accumulate the total array sum
    for (int i = 0; i < n; i++)
    {
        target += arr[i];
    }

    // Initialize a 2D DP table of size n x (total sum + 1) filled with -1
    vector<vector<int>> dp(n, vector<int>(target + 1, -1));

    for (int i = 0; i <= target; i++)
    {
        dp[n - 1][i] = helper(n - 1, i, arr, n, dp);
    }

    int mini = 1e9;

    // Scan through all possible sums evaluated for the last index
    for (int i = 0; i <= target / 2; i++)
    {
        // If a subset can exactly sum up to 'i'
        if (dp[n - 1][i] == true)
        {
            // Minimize the absolute difference between the two subset halves
            mini = min(mini, abs(i - (target - i)));
        }
    }

    return mini;
}

// ==================================================
// TABULATION (BOTTOM-UP DP)
//
// Idea:
// - Build a dynamic programming table iteratively from the ground up to track all possible subset sums.
// - Evaluate each element to see which target sums can be formed by either including or excluding it.
// - The final row of the table reveals all the reachable subset sums for the entire array.
// - Scan this last row to easily identify the partition that yields the minimum possible absolute difference.
//
// Time Complexity: O(n * total) - Nested loops filling the DP table.
// Space Complexity: O(n * total) - Dedicated memory for the 2D DP matrix.
// ==================================================

int minDifference(const vector<int> &arr, int n)
{
    int target = 0;

    // Calculate total sum of the array to determine column size of DP table
    for (int i = 0; i < n; i++)
    {
        target += arr[i];
    }

    // Initialize a 2D boolean DP table with false
    vector<vector<bool>> dp(n, vector<bool>(target + 1, false));

    // Base case: A target sum of 0 is always achievable (empty subset)
    for (int idx = 0; idx < n; idx++)
        dp[idx][0] = true;

    // Base case: The first element can form a subset sum equal to its own value
    if (target >= arr[0])
        dp[0][arr[0]] = true;

    // Iteratively build up solutions for the rest of the array elements
    for (int idx = 1; idx < n; idx++)
    {
        for (int currTarget = 1; currTarget <= target; currTarget++)
        {
            // Result if we choose to exclude the current element
            bool notTake = dp[idx - 1][currTarget];

            // Result if we choose to include the current element
            bool take = (currTarget >= arr[idx]) ? dp[idx - 1][currTarget - arr[idx]] : false;

            // Target is reachable if either excluding or including the element worked
            dp[idx][currTarget] = notTake | take;
        }
    }

    int mini = 1e9;

    // The last row (n-1) holds boolean values indicating if a sum 'i' is reachable
    for (int i = 0; i <= target / 2; i++)
    {
        if (dp[n - 1][i] == true)
        {
            // Find the minimum difference among all reachable subset sums
            mini = min(mini, abs(i - (target - i)));
        }
    }

    return mini;
}

// ==================================================
// SPACE OPTIMIZATION DP
//
// Idea:
// - Notice that computing the current row only requires access to the results of the previous row.
// - Replace the large two-dimensional table with two compact one-dimensional arrays to save a significant amount of memory.
// - Iteratively update the reachable targets in the current array based on the previously computed boolean states.
// - Use the final populated array to calculate the minimum difference between the two valid subset partitions.
//
// Time Complexity: O(n * total) - Consistent loop iterations as tabulation.
// Space Complexity: O(total) - Uses two 1D arrays of size (total sum + 1).
// ==================================================

int minDifference(const vector<int> &arr, int n)
{
    int target = 0;

    // Accumulate the array sum to act as the upper bound for subset targets
    for (int i = 0; i < n; i++)
    {
        target += arr[i];
    }

    // Array to track reachable target sums using elements up to the previous index
    vector<bool> prev(target + 1, false);

    prev[0] = true;

    // Base case initialization for the first element
    if (target >= arr[0])
        prev[arr[0]] = true;

    // Process each remaining element in the array one by one
    for (int idx = 1; idx < n; idx++)
    {
        // Array to track reachable targets when considering the current element
        vector<bool> curr(target + 1, false);

        curr[0] = true;

        for (int currTarget = 1; currTarget <= target; currTarget++)
        {
            // Fetch the result from the previous row if we skip this element
            bool notTake = prev[currTarget];

            // Fetch the result from the previous row if we use this element
            bool take = (currTarget >= arr[idx]) ? prev[currTarget - arr[idx]] : false;

            // Combine both possibilities to update the current state
            curr[currTarget] = notTake | take;
        }

        // Shift the current row's results into the previous row for the next iteration
        prev = curr;
    }

    int mini = 1e9;

    // The 'prev' array now contains the final results for the entire array
    for (int i = 0; i <= target / 2; i++)
    {
        if (prev[i] == true)
        {
            // Evaluate the partition difference to find the absolute minimum
            mini = min(mini, abs(i - (target - i)));
        }
    }

    return mini;
}

int main()
{
    vector<int> arr = {1, 2, 3, 4};

    int n = arr.size();

    // Calculate and print the minimized absolute difference between subset partitions
    cout << "The minimum absolute difference is: " << minDifference(arr, n);

    return 0;
}
