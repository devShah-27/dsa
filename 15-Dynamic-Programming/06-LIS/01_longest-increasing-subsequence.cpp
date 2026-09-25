// ==================================================
// PROBLEM
// - Given an integer array nums, return the length of the longest strictly increasing subsequence.
// - A subsequence is derived by deleting elements without changing the remaining elements' order.
// - Find the length of the longest subsequence where every element is greater than the previous.
// ==================================================

#include <bits/stdc++.h>
using namespace std;

// NOTE: Can also be solved using Power Set method but it will give TLE or MLE because of its implementation requiring exponential time complexity.

// ==================================================
// RECURSIVE APPROACH 
//
// Idea:
// - Recursively explore subsequences by choosing to either include or exclude the current element while iterating through the array.
// - An element is included if strictly greater than previous choices.
// - Return the maximum length from both recursive branching paths.
//
// Time Complexity: O(2^n) - Exponential branching as each element has two choices.
// Space Complexity: O(n) - Auxiliary space required for the recursion stack.
// ==================================================

int helper(int idx, int prev_idx, int n, vector<int> &nums)
{
    // Base case: Reached the end of the array, yielding 0 length
    if (idx == n)
        return 0;

    // Branch 1: Skip the current element and proceed to the next
    int length = helper(idx + 1, prev_idx, n, nums);

    // Branch 2: Take the current element if it maintains the strictly increasing property
    if (prev_idx == -1 || nums[idx] > nums[prev_idx])
        length = max(length, 1 + helper(idx + 1, idx, n, nums));

    // Return the maximum length found from both branching choices
    return length;
}

int LIS(vector<int> &nums)
{
    int n = nums.size();

    // Start recursive evaluation from the first index with no previous element chosen
    return helper(0, -1, n, nums);
}

// ==================================================
// RECURSION + MEMOIZATION (TOP-DOWN DP)
//
// Idea:
// - Optimize the naive recursion by caching overlapping subproblem results inside a 2D dynamic programming memoization table for reuse.
// - The state is defined by the current array index and the previously included element index, safely shifted by one.
//
// Time Complexity: O(n^2) - There are n * (n + 1) unique states computed once.
// Space Complexity: O(n^2) for DP table + O(n) for recursion stack.
// ==================================================

int helper(int idx, int prev_idx, int n, vector<int> &nums, vector<vector<int>> &dp)
{
    // Base case: Reached the end of the array
    if (idx == n)
        return 0;

    // Return the cached result immediately if this state is already solved
    // NOTE: prev_idx is shifted by +1 to handle the initial -1 value safely
    if (dp[idx][prev_idx + 1] != -1)
        return dp[idx][prev_idx + 1];

    // Evaluate the branch where the current element is excluded
    int length = helper(idx + 1, prev_idx, n, nums, dp);

    // Evaluate the branch where the current element is included safely
    if (prev_idx == -1 || nums[idx] > nums[prev_idx])
        length = max(length, 1 + helper(idx + 1, idx, n, nums, dp));

    // Store the optimal result in the DP table before returning it
    return dp[idx][prev_idx + 1] = length;
}

int LIS(vector<int> &nums)
{
    int n = nums.size();

    // Initialize a 2D DP matrix filled with -1 to indicate uncomputed states
    vector<vector<int>> dp(n, vector<int>(n + 1, -1));

    return helper(0, -1, n, nums, dp);
}

// ==================================================
// TABULATION (BOTTOM-UP DP)
//
// Idea:
// - Construct a bottom-up 2D dynamic programming table to systematically accumulate maximum subsequence lengths iteratively without any recursion overhead.
// - Traverse backwards while evaluating inclusion or exclusion for every possible previously selected element index to build optimal answe 
// Time Complexity: O(n^2) - Nested loops traversing the entire 2D table.
// Space Complexity: O(n^2) - Memory specifically allocated for the 2D matrix.
// ==================================================

int LIS(vector<int> &nums)
{
    int n = nums.size();

    // Initialize a 2D DP matrix filled with 0 for base states
    // Dimensions are (n+1) x (n+1) to smoothly handle shifted prev_idx
    vector<vector<int>> dp(n + 1, vector<int>(n + 1, 0));

    // Iterate backwards from the end of the array up to the start
    for (int idx = n - 1; idx >= 0; idx--)
    {
        // Iterate backwards through all possible previously chosen element indices
        for (int prev_idx = idx - 1; prev_idx >= -1; prev_idx--)
        {
            // Subsequence length achieved by ignoring the current array element
            int length = dp[idx + 1][prev_idx + 1];

            // Subsequence length achieved by including the current element if valid
            if (prev_idx == -1 || nums[idx] > nums[prev_idx])
                length = max(length, 1 + dp[idx + 1][idx + 1]);

            // Store the optimal maximum length found for this specific state
            dp[idx][prev_idx + 1] = length;
        }
    }

    // Return the maximum subsequence length evaluated from the starting index
    return dp[0][0];
}

// ==================================================
// SPACE OPTIMIZATION
//
// Idea:
// - Recognize that computing the current dynamic programming row strictly requires data from only the immediate next row of states.
// - Replace the large 2D matrix with two compact 1D arrays to substantially reduce the overall memory footprint required.
//
// Time Complexity: O(n^2) - Retains the identical loop iteration count as tabulation.
// Space Complexity: O(n) - Drastically reduced by utilizing just two 1D arrays.
// ==================================================

int LIS(vector<int> &nums)
{
    int n = nums.size();

    // Allocate two 1D arrays to manage consecutive state transitions optimally
    vector<int> prev(n + 1, 0), curr(n + 1, 0);

    // Traverse the array iteratively in strict reverse order
    for (int idx = n - 1; idx >= 0; idx--)
    {
        // Evaluate optimal choices for all valid previous elements
        for (int prev_idx = idx - 1; prev_idx >= -1; prev_idx--)
        {
            // Fetch the maximum length recorded where this element was skipped
            int length = prev[prev_idx + 1];

            // Fetch the maximum length where incorporating this element was completely valid
            if (prev_idx == -1 || nums[idx] > nums[prev_idx])
                length = max(length, 1 + prev[idx + 1]);

            // Store the optimal choice securely into the current state array
            curr[prev_idx + 1] = length;
        }

        // Shift the fully updated current state to become the previous state
        prev = curr;
    }

    // Extract the completely accumulated maximum length configuration
    return prev[0];
}

// ==================================================
// BINARY SEARCH APPROACH
//
// Idea:
// - Maintain a dynamic list tracking the smallest tail element for all increasing subsequences of various possible lengths currently found.
// - Append elements that are strictly greater to extend length, otherwise use binary search to replace the next largest element.
//
// Time Complexity: O(n log n) - Binary search is executed per array element.
// Space Complexity: O(n) - Memory required for the temporary tracking array.
// ==================================================

int LIS(vector<int> &nums)
{
    int n = nums.size();

    // Temporary array functioning dynamically to track smallest possible tail elements
    vector<int> temp;

    // Initialize the tracking array with the very first sequence element
    temp.push_back(nums[0]);

    int length = 1;

    // Iterate sequentially through all the remaining elements inside the array
    for (int idx = 1; idx < n; idx++)
    {
        // If the element is strictly greater, simply extend the subsequence length directly
        if (nums[idx] > temp.back())
        {
            temp.push_back(nums[idx]);
            length++;
        }
        else
        {
            // Find the first tracking element greater than or equal to the current element
            int lower_bound_idx = lower_bound(temp.begin(), temp.end(), nums[idx]) - temp.begin();

            // Replace it to maintain a lower tail threshold for longer future subsequences
            temp[lower_bound_idx] = nums[idx];
        }
    }

    // The total length of the tracking array represents the max subsequence length
    return length;
}

int main()
{
    vector<int> nums = {10, 9, 2, 5, 3, 7, 101, 18};

    int lengthOfLIS = LIS(nums);

    cout << "The length of the LIS for the given array is: " << lengthOfLIS << endl;

    return 0;
}
