// ==================================================
// PROBLEM
// - Given an array of integers and a target.
// - Assign a '+' or '-' to each integer.
// - Count the number of ways to evaluate to the target.
// - Return the count modulo 1e9+7 to prevent overflow.
// ==================================================

#include <bits/stdc++.h>
using namespace std;

// ==================================================
// RECURSIVE APPROACH
//
// Idea:
// - Mathematically reduce the expression problem into a standard subset sum problem finding a specific target.
// - Recursively evaluate including or excluding each array element to form the derived subset sum accurately.
// - Base cases properly account for array elements that might hold a strict value of zero.
//
// Time Complexity: O(2^n) - Two independent choices explored per element.
// Space Complexity: O(n) - Auxiliary space required for the recursion stack.
// ==================================================

int helper(int idx, int target, const vector<int> &nums, int MOD)
{
    // Base case: Reached the very first element of the array
    if (idx == 0)
    {
        // If target is 0 and the element is 0, we have two valid choices (+0, -0)
        if (nums[idx] == 0 && target == 0)
            return 2;

        // If target is 0 (element non-zero) or element perfectly matches the target
        if (target == 0 || target == nums[idx])
            return 1;

        // Target cannot be formed with the remaining elements
        return 0;
    }

    // Branch 1: Assign a '-' sign, effectively excluding it from the subset sum
    int notTake = helper(idx - 1, target, nums, MOD);

    // Branch 2: Assign a '+' sign, effectively including it in the subset sum
    int take = (target >= nums[idx])
                   ? helper(idx - 1, target - nums[idx], nums, MOD)
                   : 0;

    // Return the combined valid permutations, keeping the modulo constraint
    return (notTake + take) % MOD;
}

int targetSum(int n, int target, const vector<int> &nums)
{
    int totalSum = 0;

    // Calculate the total absolute sum of all elements in the array
    for (int it : nums)
        totalSum += it;

    // Subset sum mathematically translates to (totalSum - target) / 2.
    // If the difference is negative or odd, no valid integer partition exists.
    if (totalSum - target < 0 || (totalSum - target) % 2 == 1)
        return 0;

    int MOD = 1e9 + 7;

    // This derived target represents the sum of elements assigned a '-' sign
    int actualTarget = (totalSum - target) / 2;

    // Initiate the recursive search from the very last element
    return helper(n - 1, actualTarget, nums, MOD);
}

// ==================================================
// RECURSION + MEMOIZATION (TOP-DOWN DP)
//
// Idea:
// - Optimize the naive exponential recursion by caching overlapping subproblem results in a 2D memoization table.
// - The state combines the current array index and the remaining derived target sum requirement.
// - Skip redundant recursive branches by instantly returning previously cached integer outcomes from the matrix.
//
// Time Complexity: O(n * target) - Each distinct state is computed exactly once.
// Space Complexity: O(n * target) for the DP table + O(n) for the recursion stack.
// ==================================================

int helper(int idx, int target, const vector<int> &nums, int MOD, vector<vector<int>> &dp)
{
    // Base case: Reached the very first element of the array
    if (idx == 0)
    {
        if (nums[idx] == 0 && target == 0)
            return 2;

        if (target == 0 || target == nums[idx])
            return 1;

        return 0;
    }

    // Immediately return the stored integer result if this state is already solved
    if (dp[idx][target] != -1)
        return dp[idx][target];

    // Evaluate paths where the current element is excluded from the subset
    int notTake = helper(idx - 1, target, nums, MOD, dp);

    // Evaluate paths where the current element is included in the subset
    int take = (target >= nums[idx])
                   ? helper(idx - 1, target - nums[idx], nums, MOD, dp)
                   : 0;

    // Cache the summed modulo result into the matrix before returning
    return dp[idx][target] = (notTake + take) % MOD;
}

int targetSum(int n, int target, const vector<int> &nums)
{
    int totalSum = 0;

    // Aggregate the sum to establish the maximum possible bounds
    for (int it : nums)
        totalSum += it;

    // Eliminate mathematically impossible subset partition requirements immediately
    if (totalSum - target < 0 || (totalSum - target) % 2 == 1)
        return 0;

    int MOD = 1e9 + 7;

    int actualTarget = (totalSum - target) / 2;

    // Construct a 2D DP table initialized with -1 representing uncomputed states
    vector<vector<int>> dp(n, vector<int>(actualTarget + 1, -1));

    return helper(n - 1, actualTarget, nums, MOD, dp);
}

// ==================================================
// TABULATION (BOTTOM-UP DP)
//
// Idea:
// - Construct a bottom-up 2D dynamic programming table to accumulate valid subset counts systematically and iteratively.
// - Base cases are carefully mapped for the first element, properly addressing zero value possibilities.
// - Iteratively combine the optimal combinations formed by either including or excluding the current array integer.
//
// Time Complexity: O(n * target) - Nested loops filling the entire DP table.
// Space Complexity: O(n * target) - Memory specifically allocated for the 2D DP matrix.
// ==================================================

int targetSum(int n, int target, const vector<int> &nums)
{
    int totalSum = 0;

    // Compute the sum of the array to derive the required subset partition
    for (int it : nums)
        totalSum += it;

    // Reject invalid target sums that cannot be partitioned evenly
    if (totalSum - target < 0 || (totalSum - target) % 2 == 1)
        return 0;

    int MOD = 1e9 + 7;

    int actualTarget = (totalSum - target) / 2;

    // Initialize the tabulation matrix entirely with zeros
    vector<vector<int>> dp(n, vector<int>(actualTarget + 1, 0));

    // Properly initialize the base state for the first element
    if (nums[0] == 0)
        dp[0][0] = 2; // Two ways: picking or not picking the zero
    else
        dp[0][0] = 1; // One way: strictly not picking a non-zero element

    // If the first element matches a non-zero valid target, log it
    if (nums[0] != 0 && nums[0] <= actualTarget)
        dp[0][nums[0]] = 1;

    // Build up the solution iteratively for the remaining array items
    for (int idx = 1; idx < n; idx++)
    {
        for (int currTarget = 0; currTarget <= actualTarget; currTarget++)
        {
            // The number of valid expressions ignoring the current element
            int notTake = dp[idx - 1][currTarget];

            // The number of valid expressions integrating the current element
            int take = (currTarget >= nums[idx])
                           ? dp[idx - 1][currTarget - nums[idx]]
                           : 0;

            // Store the aggregate valid configurations safely utilizing modulo arithmetic
            dp[idx][currTarget] = (notTake + take) % MOD;
        }
    }

    // Extract the final configuration count from the bottom-right coordinate
    return dp[n - 1][actualTarget];
}

// ==================================================
// SPACE OPTIMIZATION DP
//
// Idea:
// - Recognize that computing the current dynamic programming row strictly requires data from the previous row.
// - Replace the large two-dimensional matrix with two compact one-dimensional arrays to substantially save memory.
// - Systematically update the current array using values safely extracted from the previously calculated array state.
//
// Time Complexity: O(n * target) - Retains the identical loop iteration count as tabulation.
// Space Complexity: O(target) - Drastically reduced by utilizing just two 1D arrays.
// ==================================================

int targetSum(int n, int target, const vector<int> &nums)
{
    int totalSum = 0;

    // Calculate the array sum to isolate the necessary mathematical offset
    for (int it : nums)
        totalSum += it;

    // Filter out logically inaccessible target differences right away
    if (totalSum - target < 0 || (totalSum - target) % 2 == 1)
        return 0;

    int MOD = 1e9 + 7;

    int actualTarget = (totalSum - target) / 2;

    // Allocate two 1D arrays to manage state transitions optimally
    vector<int> prev(actualTarget + 1, 0), curr(actualTarget + 1, 0);

    // Initialize the fundamental base cases strictly for the first element
    if (nums[0] == 0)
        prev[0] = 2;
    else
        prev[0] = 1;

    if (nums[0] != 0 && nums[0] <= actualTarget)
        prev[nums[0]] = 1;

    // Loop continuously through the array sequentially updating subset counts
    for (int idx = 1; idx < n; idx++)
    {
        for (int currTarget = 0; currTarget <= actualTarget; currTarget++)
        {
            // Fetch combinations recorded where this item was skipped previously
            int notTake = prev[currTarget];

            // Fetch combinations where incorporating this item mathematically satisfied constraints
            int take = (currTarget >= nums[idx])
                           ? prev[currTarget - nums[idx]]
                           : 0;

            // Merge possibilities and lock them into the current state array
            curr[currTarget] = (notTake + take) % MOD;
        }

        // Shift the completed current state downward to become the previous state
        prev = curr;
    }

    // Return the fully accumulated integer count resting at the target position
    return prev[actualTarget];
}

int main()
{
    vector<int> nums = {1, 2, 3, 1};

    int target = 3;

    int n = nums.size();

    // Trigger the dynamic programming sequence and display the evaluated answer
    cout << "The total number of ways is " << targetSum(n, target, nums) << endl;

    return 0;
}
