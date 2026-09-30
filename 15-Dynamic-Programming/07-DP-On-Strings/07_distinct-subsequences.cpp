// ==================================================
// PROBLEM
// - Given string s and string t, count the number of distinct subsequences of s that equal string t.
// - Return the total count modulo 10^9 + 7.
// ==================================================

#include <bits/stdc++.h>
using namespace std;

// ==================================================
// RECURSION
//
// Idea:
// - Start matching characters from the end of both strings moving backwards to the beginning of the string prefixes.
// - If characters match, branch to either include the character or skip it to find other possible valid matches.
// - If they do not match, we must skip it.
//
// Time Complexity: O(2^n) - Exponential branching in the worst case.
// Space Complexity: O(n) - Auxiliary stack space for recursion depth.
// ==================================================

int helper(int i, int j, const string &s, const string &t, int MOD)
{
    // Base case: If string t is exhausted, we found a valid matching subsequence
    if (j < 0)
        return 1;

    // Base case: If string s is exhausted but t is not, no match is possible
    if (i < 0)
        return 0;

    // If characters match, we have two choices:
    // 1. Include this character in the subsequence (move both pointers)
    // 2. Skip this character in s to find other matches (move only i)
    if (s[i] == t[j])
        return (helper(i - 1, j - 1, s, t, MOD) + helper(i - 1, j, s, t, MOD)) % MOD;

    // If characters mismatch, we can only skip the current character in s
    return (helper(i - 1, j, s, t, MOD)) % MOD;
}

int distinctSubsequences(const string &s, const string &t)
{
    int n = s.size(), m = t.size();

    int MOD = 1e9 + 7;

    // Start evaluating combinations from the last characters of both strings (0-based indexing)
    return helper(n - 1, m - 1, s, t, MOD);
}

// ==================================================
// RECURSION + MEMOIZATION (TOP-DOWN DP)
//
// Idea:
// - Cache the results of overlapping subproblems in a matrix to prevent redundant calculations during the recursive branching phase.
// - Shift indices to be strictly one-based so we can cleanly represent the empty string base cases at zero.
//
// Time Complexity: O(n * m) - Each unique state is computed exactly once.
// Space Complexity: O(n * m) for DP table + O(n) for recursion stack.
// ==================================================

int helper(int i, int j, const string &s, const string &t, vector<vector<int>> &dp, int MOD)
{
    // Base case: Successfully matched all characters of string t
    if (j == 0)
        return 1;

    // Base case: Exhausted string s without completing string t
    if (i == 0)
        return 0;

    // Immediately return the cached result if this state was previously evaluated
    if (dp[i][j] != -1)
        return dp[i][j];

    // Note: We use i - 1 and j - 1 to access string characters because strings are 0-indexed,
    // but our DP states i and j are 1-indexed to accommodate the base case at 0.
    if (s[i - 1] == t[j - 1])
        return dp[i][j] = (helper(i - 1, j - 1, s, t, dp, MOD) +
                           helper(i - 1, j, s, t, dp, MOD)) %
                          MOD;

    // Cache and return the result of skipping the mismatched character
    return dp[i][j] = (helper(i - 1, j, s, t, dp, MOD)) % MOD;
}

int distinctSubsequences(const string &s, const string &t)
{
    int n = s.size(), m = t.size();

    // Initialize a 2D DP matrix filled with -1 to indicate uncomputed states
    vector<vector<int>> dp(n + 1, vector<int>(m + 1, -1));

    int MOD = 1e9 + 7;

    // Trigger the top-down DP starting from full string lengths
    return helper(n, m, s, t, dp, MOD);
}

// ==================================================
// TABULATION (BOTTOM-UP DP)
//
// Idea:
// - Build a two-dimensional dynamic programming table iteratively from the fundamental base cases up to the full string lengths.
// - The first column is initialized to one because an empty target string is a subsequence of any prefix.
//
// Time Complexity: O(n * m) - Nested loops traversing the lengths of s and t.
// Space Complexity: O(n * m) - Memory strictly allocated for the 2D DP matrix.
// ==================================================

int distinctSubsequences(const string &s, const string &t)
{
    int n = s.size(), m = t.size();

    // Initialize the full DP table with 0 configurations
    vector<vector<int>> dp(n + 1, vector<int>(m + 1, 0));

    int MOD = 1e9 + 7;

    // Base Case initialization: An empty string t can be formed exactly 1 way
    // by deleting all characters from any prefix of string s.
    for (int i = 0; i <= n; i++)
        dp[i][0] = 1;

    // Iteratively build up the solution for remaining lengths
    for (int i = 1; i <= n; i++)
    {
        for (int j = 1; j <= m; j++)
        {
            // If the characters align, accumulate possibilities from taking or dropping it
            if (s[i - 1] == t[j - 1])
                dp[i][j] = (dp[i - 1][j - 1] + dp[i - 1][j]) % MOD;
            // Otherwise, inherit the number of ways from dropping the current character of s
            else
                dp[i][j] = (dp[i - 1][j]) % MOD;
        }
    }

    // Extract the final total matching count from the bottom-right coordinate
    return dp[n][m];
}

// ==================================================
// 2-ROW SPACE OPTIMIZATION
//
// Idea:
// - The current row in the dynamic programming table only relies directly on the immediately preceding calculated row values.
// - Replace the full matrix with just two one-dimensional arrays to track the previous and current states, saving memory.
//
// Time Complexity: O(n * m) - Iterates identically to the standard tabulation approach.
// Space Complexity: O(m) - Drastically reduced by utilizing just two 1D arrays.
// ==================================================

int distinctSubsequences(const string &s, const string &t)
{
    int n = s.size(), m = t.size();

    // Allocate arrays to manage state transitions between consecutive prefix lengths
    vector<int> prev(m + 1, 0), curr(m + 1, 0);

    int MOD = 1e9 + 7;

    // Initialize the base case for an empty string t (at j = 0)
    prev[0] = curr[0] = 1;

    for (int i = 1; i <= n; i++)
    {
        for (int j = 1; j <= m; j++)
        {
            // Characters match: sum the counts of including and skipping
            if (s[i - 1] == t[j - 1])
                curr[j] = (prev[j - 1] + prev[j]) % MOD;
            // Mismatch: carry forward the previous valid sequence count
            else
                curr[j] = (prev[j]) % MOD;
        }

        // Shift the computed row downwards to prepare for the next prefix iteration
        prev = curr;
    }

    // The maximum accumulated count rests at the final requested capacity index
    return prev[m];
}

// ==================================================
// 1-ROW SPACE OPTIMIZATION
//
// Idea:
// - Optimize memory further by using a single one-dimensional array.
// - Iterate backwards through the inner loop to ensure that we use the previous row values before they are completely overwritten by the current row calculation updates internally.
//
// Time Complexity: O(n * m) - Maintains identical iteration bounds.
// Space Complexity: O(m) - Achieves the absolute minimum memory using just one array.
// ==================================================

int distinctSubsequences(const string &s, const string &t)
{
    int n = s.size(), m = t.size();

    // Utilize a single dimensional array to maintain state transitions in place
    vector<int> prev(m + 1, 0);

    int MOD = 1e9 + 7;

    // Base case setup for the empty target string
    prev[0] = 1;

    // Process every character of string s
    for (int i = 1; i <= n; i++)
    {
        // NOTE: Iterating right-to-left is critical here.
        // It ensures prev[j - 1] still holds the unaltered value from the *previous* row (i - 1),
        // preventing the current row from accidentally reusing updated values.
        for (int j = m; j >= 1; j--)
        {
            // If matched, we add the un-updated prev[j-1] to the existing prev[j]
            if (s[i - 1] == t[j - 1])
                prev[j] = (prev[j - 1] + prev[j]) % MOD;

            // NOTE: If they do NOT match, the logic implicitly demands curr[j] = prev[j].
            // Because we are operating in-place on a single array, prev[j] already
            // holds the correct value, so the `else` block is beautifully bypassed.
        }
    }

    // Return the final counted combinations stored at the end of the array
    return prev[m];
}

int main()
{
    string s1 = "babgbag";
    string s2 = "bag";

    cout << "The Count of Distinct Subsequences is " << distinctSubsequences(s1, s2);

    return 0;
}
