// ==================================================
// PROBLEM
// - Given an array of n integers, return the Longest Increasing Subsequence (LIS).
// - The returned subsequence must be Index-wise Lexicographically Smallest.
// - Prefer earlier array indices when resolving ties in subsequence lengths.
// ==================================================

#include <bits/stdc++.h>
using namespace std;

// ==================================================
// TABULATION WITH PATH RECONSTRUCTION (BOTTOM-UP DP)
//
// Idea:
// - Compute the LIS iteratively while keeping track of the parent indices to reliably reconstruct the exact sequence.
// - When length ties occur, update the parent index securely if the candidate index appears earlier in the original array.
// - Trace back from the optimal last index to safely build and extract the fully evaluated strictly increasing subsequence.
//
// Time Complexity: O(n^2) - Nested loops to evaluate all previous element choices.
// Space Complexity: O(n) - Auxiliary arrays for dynamic programming and parent tracking.
// ==================================================

vector<int> longestIncreasingSubsequence(vector<int> &arr)
{
    int n = arr.size();

    // DP array stores max LIS length ending at each specific index
    // Parent array dynamically tracks the optimal previous index for reconstruction
    vector<int> dp(n, 1), parent(n);

    // Track the globally maximum LIS length and its corresponding ending index
    int lastIdx = 0, maxLen = 1;

    // Iterate through each element to compute its optimal LIS ending there
    for (int i = 0; i < n; i++)
    {
        // Initialize the parent of the current element to itself forming a base case
        parent[i] = i;

        // Check all preceding elements to dynamically build strictly increasing subsequences
        for (int prevIdx = 0; prevIdx < i; prevIdx++)
        {
            // Proceed only if appending the current element maintains the strictly increasing property
            if (arr[prevIdx] < arr[i])
            {
                // Strictly longer subsequence found, update the maximum length and the parent index
                if (dp[i] < dp[prevIdx] + 1)
                {
                    dp[i] = dp[prevIdx] + 1;
                    parent[i] = prevIdx;
                }
                // Handle length ties by preferring the lexicographically earlier index for the parent
                else if (dp[i] == dp[prevIdx] + 1 && prevIdx < parent[i])
                {
                    parent[i] = prevIdx;
                }
            }
        }

        // Update the global maximum sequence length and its exact ending index efficiently
        if (dp[i] > maxLen)
        {
            maxLen = dp[i];
            lastIdx = i;
        }
    }

    // Start the traceback process securely from the optimal subsequence's terminating index
    int i = lastIdx;

    // Array to cleanly accumulate the final reconstructed strictly increasing subsequence
    vector<int> ans;

    // Traverse the recorded parent pointers backwards until the absolute base case is reached
    while (parent[i] != i)
    {
        // Append the current element safely directly to our newly reconstructed sequence
        ans.push_back(arr[i]);
        // Shift backward to carefully evaluate the immediately preceding element in the sequence
        i = parent[i];
    }

    // Append the very first element of the sequence which confidently points to itself
    ans.push_back(arr[i]);

    // Reverse the backward-traced sequence logically to restore the correct original chronological order
    reverse(ans.begin(), ans.end());

    // Return the final fully assembled array containing the optimal target sequence elements
    return ans;
}

int main()
{
    vector<int> arr = {10, 22, 9, 33, 21, 50, 41, 60, 80};

    // Trigger the dynamic programming tracking sequence to find the target optimized subsequence
    vector<int> ans = longestIncreasingSubsequence(arr);

    // Output the comprehensively evaluated final sequence reliably into the standard console
    cout << "The longest increasing subsequence for the given array is: ";

    for (auto x : ans)
        cout << x << " ";

    return 0;
}
