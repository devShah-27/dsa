// ==================================================
// PROBLEM
// - Given an array of integers, determine if it can be partitioned into two subsets with equal sums.
// - This is equivalent to finding a subset with a sum exactly equal to half the total array sum.
// ==================================================

#include <bits/stdc++.h>
using namespace std;

// ==================================================
// RECURSIVE APPROACH
//
// Idea:
// - First calculate the total sum of the entire array.
// - If the total sum is odd, equal partition is impossible.
// - If even, the problem reduces to finding a single subset that sums to exactly half of the total.
// - We explore all subsets by recursively including or excluding elements to see if the target is reachable.
//
// Time Complexity: O(2^n) - We explore two choices per element.
// Space Complexity: O(n) - Auxiliary space required for the recursion stack.
// ==================================================

bool helper(int idx, int target, const vector<int> &arr)
{
    // Base case: If the target is met, a valid subset exists
    if (target == 0)
        return true;

    // Base case: At the first element, check if it matches the target
    if (idx == 0)
        return (arr[0] == target);

    // Choice 1: Exclude the current element from the subset
    bool notTake = helper(idx - 1, target, arr);

    // Choice 2: Include the current element if it does not exceed the target
    bool take = (target >= arr[idx]) ? helper(idx - 1, target - arr[idx], arr) : false;

    // Return true if either excluding or including the element works
    return (notTake | take);
}

bool isSubsetSum(const vector<int> &arr, int n, int target)
{
    // Start the recursive subset search from the last index
    return helper(n - 1, target, arr);
}

bool equalPartition(int n, const vector<int> &arr)
{
    int sum = 0;

    // Calculate the total sum of all elements in the array
    for (int i = 0; i < n; i++)
    {
        sum += arr[i];
    }

    // An odd total sum cannot be divided into two equal integer subsets
    if (sum % 2 == 1)
        return false;

    // The target sum for one subset is exactly half of the total sum
    int target = sum / 2;

    return isSubsetSum(arr, n, target);
}

// ==================================================
// RECURSION + MEMOIZATION (TOP-DOWN DP)
//
// Idea:
// - Enhance the recursive approach by caching the results of overlapping subproblems in a 2D memoization table.
// - The state is uniquely defined by the current index and the remaining target sum we need to find.
// - If a state has been evaluated before, we directly return its cached boolean value to prune the tree.
//
// Time Complexity: O(n * target) - Each state is computed exactly once.
// Space Complexity: O(n * target) for DP table + O(n) for recursion stack.
// ==================================================

bool helper(int idx, int target, const vector<int> &arr, vector<vector<int>> &dp)
{
    // Base case: If the target is met, a valid subset exists
    if (target == 0)
        return true;

    // Base case: At the first element, check if it matches the target
    if (idx == 0)
        return (arr[0] == target);

    // Return the cached result if this state has already been computed
    if (dp[idx][target] != -1)
        return dp[idx][target];

    // Choice 1: Exclude the current element from the subset
    bool notTake = helper(idx - 1, target, arr, dp);

    // Choice 2: Include the current element if it does not exceed the target
    bool take = (target >= arr[idx]) ? helper(idx - 1, target - arr[idx], arr, dp) : false;

    // Cache and return the result for the current state
    return dp[idx][target] = (notTake | take);
}

bool isSubsetSum(const vector<int> &arr, int n, int target)
{
    // Initialize a 2D DP table with -1 representing uncomputed states
    vector<vector<int>> dp(n, vector<int>(target + 1, -1));

    return helper(n - 1, target, arr, dp);
}

bool equalPartition(int n, const vector<int> &arr)
{
    int sum = 0;

    // Calculate the total sum of all elements in the array
    for (int i = 0; i < n; i++)
    {
        sum += arr[i];
    }

    // An odd total sum cannot be divided into two equal integer subsets
    if (sum % 2 == 1)
        return false;

    // The target sum for one subset is exactly half of the total sum
    int target = sum / 2;

    return isSubsetSum(arr, n, target);
}

// ==================================================
// TABULATION (BOTTOM-UP DP)
//
// Idea:
// - Construct a 2D DP table and build up the solution iteratively starting from the defined base cases.
// - The first column represents a target of zero, which is always trivially true using an empty subset.
// - We iteratively determine if each target up to the half-sum is reachable using subsets of increasing sizes.
//
// Time Complexity: O(n * target) - Nested loops filling the DP table.
// Space Complexity: O(n * target) - Dedicated memory for the 2D DP matrix.
// ==================================================

bool isSubsetSum(const vector<int> &arr, int n, int target)
{
    // Initialize a 2D DP table with false
    vector<vector<bool>> dp(n, vector<bool>(target + 1, false));

    // Base case: A target of 0 is always achievable (empty subset)
    for (int idx = 0; idx < n; idx++)
    {
        dp[idx][0] = true;
    }

    // Base case: The first element can achieve a target exactly equal to itself
    if (arr[0] <= target)
        dp[0][arr[0]] = true;

    // Iterate through the remaining array elements
    for (int idx = 1; idx < n; idx++)
    {
        // Iterate through all possible targets up to the required half-sum
        for (int currTarget = 1; currTarget <= target; currTarget++)
        {
            // State if we don't include the current element
            bool notTake = dp[idx - 1][currTarget];

            // State if we include the current element (ensure it doesn't exceed target)
            bool take = (currTarget >= arr[idx]) ? dp[idx - 1][currTarget - arr[idx]] : false;

            // Current target is reachable if either choice yields true
            dp[idx][currTarget] = (take | notTake);
        }
    }

    // The final answer for the full array and target is at the bottom-right
    return dp[n - 1][target];
}

bool equalPartition(int n, const vector<int> &arr)
{
    int sum = 0;

    // Calculate the total sum of all elements in the array
    for (int i = 0; i < n; i++)
    {
        sum += arr[i];
    }

    // An odd total sum cannot be divided into two equal integer subsets
    if (sum % 2 == 1)
        return false;

    // The target sum for one subset is exactly half of the total sum
    int target = sum / 2;

    return isSubsetSum(arr, n, target);
}

// ==================================================
// SPACE OPTIMIZATION DP
//
// Idea:
// - Observe that calculating the current row only depends on the boolean values from the immediately previous row.
// - We can replace the full 2D DP table with two 1D arrays representing the previous and current states.
// - This heavily reduces the memory footprint while maintaining the exact same optimal time complexity as the tabulation approach.
//
// Time Complexity: O(n * target) - Consistent loop iterations as tabulation.
// Space Complexity: O(target) - Uses two 1D arrays of size target + 1.
// ==================================================

bool isSubsetSum(const vector<int> &arr, int n, int target)
{
    // prev array stores the subset sum results for the previous index
    vector<bool> prev(target + 1, false);

    // Base case: Target of 0 is achievable
    prev[0] = true;

    // Base case: First element can form a subset matching its own value
    if (arr[0] <= target)
        prev[arr[0]] = true;

    // Process each subsequent element in the array
    for (int idx = 1; idx < n; idx++)
    {
        // curr array stores the subset sum results for the current index
        vector<bool> curr(target + 1, false);

        // Target of 0 is always achievable
        curr[0] = true;

        for (int currTarget = 1; currTarget <= target; currTarget++)
        {
            // Fetch result if we skip the current element
            bool notTake = prev[currTarget];

            // Fetch result if we include the current element
            bool take = (currTarget >= arr[idx]) ? prev[currTarget - arr[idx]] : false;

            // Combine both possibilities
            curr[currTarget] = (take | notTake);
        }

        // Move current results to prev for the next iteration
        prev = curr;
    }

    // The final answer is found at the target index of the last computed row
    return prev[target];
}

bool equalPartition(int n, const vector<int> &arr)
{
    int sum = 0;

    // Calculate the total sum of all elements in the array
    for (int i = 0; i < n; i++)
    {
        sum += arr[i];
    }

    // An odd total sum cannot be divided into two equal integer subsets
    if (sum % 2 == 1)
        return false;

    // The target sum for one subset is exactly half of the total sum
    int target = sum / 2;

    return isSubsetSum(arr, n, target);
}

int main()
{
    vector<int> arr = {2, 3, 3, 3, 4, 5};

    int n = arr.size();

    // Check if array can be evenly partitioned
    if (equalPartition(n, arr))
        cout << "The Array can be partitioned into two equal subsets";
    else
        cout << "The Array cannot be partitioned into two equal subsets";

    return 0;
}
