// ==================================================
// PROBLEM
// - Count ways to partition an array into two subsets.
// - The difference between subset sums must equal a given value.
// - Return the result modulo 10^9 + 7.
// ==================================================

#include <bits/stdc++.h>
using namespace std;

// ==================================================
// RECURSIVE APPROACH
//
// Idea:
// - We reduce the problem mathematically to finding a specific target subset sum, which is (totalSum - diff) / 2.
// - We recursively explore all subsets by including or excluding each element to see if it meets the target.
// - Base cases are carefully handled to accommodate zero values properly without missing valid subset combinations.
//
// Time Complexity: O(2^n) - We explore two choices per element.
// Space Complexity: O(n) - Auxiliary space required for the recursion stack.
// ==================================================

int helper(int idx, int target, const vector<int> &arr, int MOD)
{
    // Base case: Reached the very first element of the array
    if (idx == 0)
    {
        // If target is 0 and element is 0, two subsets are possible (pick or not pick)
        if (target == 0 && arr[idx] == 0)
            return 2;

        // If target is 0 (and element is not 0), or element matches the target exactly
        if (target == 0 || target == arr[idx])
            return 1;

        // Otherwise, no valid subset combination can be formed
        return 0;
    }

    // Branch 1: Exclude the current element and maintain the remaining target
    int notTake = helper(idx - 1, target, arr, MOD);

    // Branch 2: Include the current element if it does not exceed the target
    int take = (target >= arr[idx])
                   ? helper(idx - 1, target - arr[idx], arr, MOD)
                   : 0;

    // Combine valid combinations from both branches and apply modulo
    return (notTake + take) % MOD;
}

int countPartitions(int n, int diff, const vector<int> &arr)
{
    int totalSum = 0;

    // Accumulate the sum of all elements to find the total array sum
    for (auto it : arr)
        totalSum += it;

    // S1 + S2 = totalSum and S1 - S2 = diff
    // Therefore: totalSum - S2 - S2 = diff  =>  S2 = (totalSum - diff) / 2
    // If the difference is invalid or leads to a fractional target, return 0
    if ((totalSum - diff < 0) || ((totalSum - diff) % 2 == 1))
        return 0;

    // Calculate the exact subset sum target required to achieve the difference
    int target = (totalSum - diff) / 2;

    int MOD = 1e9 + 7;

    // Start the recursive evaluation from the last element
    return helper(n - 1, target, arr, MOD);
}

// ==================================================
// RECURSION + MEMOIZATION (TOP-DOWN DP)
//
// Idea:
// - We optimize the exponential recursion by caching overlapping subproblem results dynamically inside a 2D memoization table.
// - The unique state is defined by the current array index combined with the remaining target sum needed.
// - If a state has already been calculated previously, we immediately return its cached integer value to save time.
//
// Time Complexity: O(n * target) - Each distinct state is computed exactly once.
// Space Complexity: O(n * target) for the DP table + O(n) for the recursion stack.
// ==================================================

int helper(int idx, int target, const vector<int> &arr, int MOD, vector<vector<int>> &dp)
{
    // Base case: Reached the very first element of the array
    if (idx == 0)
    {
        if (target == 0 && arr[idx] == 0)
            return 2;

        if (target == 0 || target == arr[idx])
            return 1;

        return 0;
    }

    // Return the cached integer result if this state was already solved
    if (dp[idx][target] != -1)
        return dp[idx][target];

    // Branch 1: Skip the current element entirely
    int notTake = helper(idx - 1, target, arr, MOD, dp);

    // Branch 2: Select the current element if it fits within the remaining target
    int take = (target >= arr[idx])
                   ? helper(idx - 1, target - arr[idx], arr, MOD, dp)
                   : 0;

    // Store the computed modulo result directly into the DP table
    return dp[idx][target] = (notTake + take) % MOD;
}

int countPartitions(int n, int diff, const vector<int> &arr)
{
    int totalSum = 0;

    // Calculate the combined sum of the entire array
    for (auto it : arr)
        totalSum += it;

    // Validate that the target subset sum is a positive whole number
    if ((totalSum - diff < 0) || ((totalSum - diff) % 2 == 1))
        return 0;

    int target = (totalSum - diff) / 2;

    int MOD = 1e9 + 7;

    // Initialize a 2D DP table filled with -1 to track uncomputed states
    vector<vector<int>> dp(n, vector<int>(target + 1, -1));

    return helper(n - 1, target, arr, MOD, dp);
}

// ==================================================
// TABULATION (BOTTOM-UP DP)
//
// Idea:
// - We construct a bottom-up 2D dynamic programming table to accumulate valid subset counts iteratively without recursion overhead.
// - Base cases are initialized to strictly account for array elements that might hold a value of absolute zero.
// - We iteratively combine the subset combinations formed by either including or excluding the current array integer element.
//
// Time Complexity: O(n * target) - Nested loops filling the entire DP table.
// Space Complexity: O(n * target) - Memory allocated for the 2D DP matrix.
// ==================================================

int countPartitions(int n, int diff, const vector<int> &arr)
{
    int totalSum = 0;

    // Determine the maximum theoretical sum of the entire array
    for (auto it : arr)
        totalSum += it;

    // Discard impossible partition difference constraints immediately
    if ((totalSum - diff < 0) || ((totalSum - diff) % 2 == 1))
        return 0;

    // Derive the subset sum target we need to look for
    int target = (totalSum - diff) / 2;

    int MOD = 1e9 + 7;

    // Initialize the 2D DP table with zeros
    vector<vector<int>> dp(n, vector<int>(target + 1, 0));

    // Initialize base case for the first element when target is 0
    if (arr[0] == 0)
        dp[0][0] = 2; // Can pick or not pick the 0
    else
        dp[0][0] = 1; // Can only achieve 0 by not picking

    // Initialize base case if the first element matches the required non-zero target
    if (arr[0] != 0 && arr[0] <= target)
        dp[0][arr[0]] = 1;

    // Build the table iteratively for the remaining array items
    for (int idx = 1; idx < n; idx++)
    {
        for (int currTarget = 0; currTarget <= target; currTarget++)
        {
            // Value retrieved if we do not include the current element
            int notTake = dp[idx - 1][currTarget];

            // Value retrieved if we safely include the current element
            int take = (currTarget >= arr[idx])
                           ? dp[idx - 1][currTarget - arr[idx]]
                           : 0;

            // Merge both possibility counts applying the required modulo constraint
            dp[idx][currTarget] = (notTake + take) % MOD;
        }
    }

    // The final count is located at the bottom-right corner
    return dp[n - 1][target];
}

// ==================================================
// SPACE OPTIMIZATION DP
//
// Idea:
// - We recognize that computing the current dynamic programming row strictly requires only the data from the previous row.
// - We replace the large 2D matrix with two compact 1D arrays to drastically reduce overall memory consumption.
// - We systematically update the current array using subset values retrieved from the previously calculated array state.
//
// Time Complexity: O(n * target) - Retains the identical loop iteration count as tabulation.
// Space Complexity: O(target) - Drastically reduced by utilizing just two 1D arrays.
// ==================================================

int countPartitions(int n, int diff, const vector<int> &arr)
{
    int totalSum = 0;

    // Sum all integers to find the array's total capacity
    for (auto it : arr)
        totalSum += it;

    // Ensure the required subset partition difference is mathematically viable
    if ((totalSum - diff < 0) || ((totalSum - diff) % 2 == 1))
        return 0;

    int target = (totalSum - diff) / 2;

    int MOD = 1e9 + 7;

    // Utilize two single-dimensional arrays for state transition storage
    vector<int> prev(target + 1, 0), curr(target + 1, 0);

    // Base case mapping for the target 0 at index 0
    if (arr[0] == 0)
        prev[0] = curr[0] = 2;
    else
        prev[0] = curr[0] = 1;

    // Base case mapping if the first array element matches a non-zero target
    if (arr[0] != 0 && arr[0] <= target)
        prev[arr[0]] = curr[arr[0]] = 1;

    // Evaluate subset combinations for the rest of the array sequentially
    for (int idx = 1; idx < n; idx++)
    {
        for (int currTarget = 0; currTarget <= target; currTarget++)
        {
            // Count inherited from the previous row when excluding this element
            int notTake = prev[currTarget];

            // Count inherited from the previous row when including this element
            int take = (currTarget >= arr[idx])
                           ? prev[currTarget - arr[idx]]
                           : 0;

            // Total valid permutations for the current target at this step
            curr[currTarget] = (notTake + take) % MOD;
        }

        // Overwrite the previous state vector with the newly completed row
        prev = curr;
    }

    // The definitive answer remains at the target index of the previous array
    return prev[target];
}

int main()
{
    vector<int> arr = {5, 2, 6, 4};

    int n = arr.size();

    int diff = 3;

    // Display the computed number of valid subsets matching the difference
    cout << "The number of subsets found are " << countPartitions(n, diff, arr) << endl;

    return 0;
}
