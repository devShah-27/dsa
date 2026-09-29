// ==================================================
// PROBLEM
// - Given a string s, find the minimum number of insertions needed to make it a palindrome.
// - A palindrome is a sequence that reads the same backward as forward.
// - You can insert characters at any position in the string.
// ==================================================

#include <bits/stdc++.h>
using namespace std;

// ==================================================
// TABULATION (BOTTOM-UP DP)
//
// Idea:
// - Identify the longest palindromic subsequence to keep intact natively.
// - Any characters not part of this subsequence must be duplicated and inserted symmetrically to form a valid full palindrome string.
// - Calculate this by finding the longest common subsequence against reverse.
//
// Time Complexity: O(n^2) - Nested loops to process combinations of both string pointers.
// Space Complexity: O(n^2) - Allocates a full 2D dynamic programming matrix.
// ==================================================

int longestPalindromicSubsequence(const string &s, const string &t)
{
    int n = s.size();

    // Shift indices by +1 so row 0 and column 0 represent empty string base cases
    vector<vector<int>> dp(n + 1, vector<int>(n + 1, 0));

    for (int sPtr = 1; sPtr <= n; sPtr++)
    {
        for (int tPtr = 1; tPtr <= n; tPtr++)
        {
            // Characters match: Extend the common subsequence length from the diagonal
            if (s[sPtr - 1] == t[tPtr - 1])
                dp[sPtr][tPtr] = 1 + dp[sPtr - 1][tPtr - 1];
            // Characters do not match: Propagate the maximum subsequence length found so far
            else
                dp[sPtr][tPtr] = max(dp[sPtr - 1][tPtr], dp[sPtr][tPtr - 1]);
        }
    }

    return dp[n][n];
}

int minInsertion(const string &s)
{
    // Create a reversed copy to evaluate the longest common subsequence
    string t = s;

    reverse(t.begin(), t.end());

    // Minimum insertions equal total string length minus the longest palindromic subsequence
    return s.size() - longestPalindromicSubsequence(s, t);
}

// ==================================================
// 2-ROW SPACE OPTIMIZATION
//
// Idea:
// - Retain the identical longest common subsequence logic while reducing memory.
// - Instead of storing the entire two-dimensional dynamic programming table memory, maintain only the current and previous rows required for calculations.
// - The final difference yields the minimum number of necessary insertions.
//
// Time Complexity: O(n^2) - Maintains the exact same nested loop iteration count.
// Space Complexity: O(n) - Drastically reduced by utilizing just two one-dimensional arrays.
// ==================================================

int longestPalindromicSubsequence(const string &s, const string &t)
{
    int n = s.size();

    // Allocate two 1D arrays to manage state transitions across iterations
    vector<int> prev(n + 1, 0), curr(n + 1, 0);

    for (int sPtr = 1; sPtr <= n; sPtr++)
    {
        for (int tPtr = 1; tPtr <= n; tPtr++)
        {
            // Characters match: Increment based on the previous row's diagonal state
            if (s[sPtr - 1] == t[tPtr - 1])
                curr[tPtr] = 1 + prev[tPtr - 1];
            // Characters do not match: Carry forward the best result computed adjacently
            else
                curr[tPtr] = max(prev[tPtr], curr[tPtr - 1]);
        }

        // Advance the state: Update the previous row to become the current row
        prev = curr;
    }

    // The final answer rests at the end of the newly updated previous row
    return prev[n];
}

int minInsertion(const string &s)
{
    // Duplicate and reverse the target string
    string t = s;

    reverse(t.begin(), t.end());

    // Subtract the maximum palindromic preservation length from the total string length
    return s.size() - longestPalindromicSubsequence(s, t);
}

int main()
{
    string s = "abcaa";

    // Trigger the operation and display the optimal insertion count calculated
    cout << "The Minimum insertions required to make string palindrome: " << minInsertion(s);

    return 0;
}
