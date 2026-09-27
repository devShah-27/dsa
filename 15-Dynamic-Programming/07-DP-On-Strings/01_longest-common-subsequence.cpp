// ==================================================
// PROBLEM
// - Given two strings str1 and str2, find the length of their longest common subsequence.
// - A subsequence appears in the same relative order, but is not necessarily contiguous.
// - A common subsequence is a subsequence that exists in both strings.
// ==================================================

#include <bits/stdc++.h>
using namespace std;

// ==================================================
// RECURSIVE APPROACH
//
// Idea:
// - Compare characters backward from the end of both strings using two pointers to track the current prefix lengths.
// - If characters match, increment the count and move both pointers backward; otherwise, branch by decrementing each pointer separately.
// - Return the maximum length found across all valid branches.
//
// Time Complexity: O(2^(n + m)) - Exponential branching when characters do not match.
// Space Complexity: O(n + m) - Auxiliary space required for the recursion stack.
// ==================================================

int helper(int ptr1, int ptr2, const string &str1, const string &str2)
{
    // Base case: If either pointer goes out of bounds, no common subsequence is possible
    if (ptr1 < 0 || ptr2 < 0)
        return 0;

    // Characters match: Include this character in the LCS and move both pointers backward
    if (str1[ptr1] == str2[ptr2])
        return 1 + helper(ptr1 - 1, ptr2 - 1, str1, str2);

    // Characters do not match: Branch by skipping the current character from either str1 or str2
    return max(helper(ptr1 - 1, ptr2, str1, str2), helper(ptr1, ptr2 - 1, str1, str2));
}

int lcs(const string &str1, const string &str2)
{
    int n = str1.size(), m = str2.size();

    // Start comparing from the last indices of both strings
    return helper(n - 1, m - 1, str1, str2);
}

// ==================================================
// RECURSION + MEMOIZATION (TOP-DOWN DP)
//
// Idea:
// - Optimize the naive exponential recursion by caching overlapping subproblem results dynamically inside a 2D memoization table.
// - The state is uniquely defined by the two indices representing the current prefix lengths of both input strings.
// - Retrieve cached answers immediately to bypass redundant recursive calls.
//
// Time Complexity: O(n * m) - Each unique pair of indices is computed at most once.
// Space Complexity: O(n * m) for DP table + O(n + m) for recursion stack.
// ==================================================

int helper(int ptr1, int ptr2, const string &str1, const string &str2, vector<vector<int>> &dp)
{
    // Base case: Exhausted either of the strings
    if (ptr1 < 0 || ptr2 < 0)
        return 0;

    // Immediately return the cached result if this state has already been computed
    if (dp[ptr1][ptr2] != -1)
        return dp[ptr1][ptr2];

    // Characters match: Cache and return 1 plus the result of the remaining prefixes
    if (str1[ptr1] == str2[ptr2])
        return dp[ptr1][ptr2] = 1 + helper(ptr1 - 1, ptr2 - 1, str1, str2, dp);

    // Characters do not match: Cache and return the maximum of both branching possibilities
    return dp[ptr1][ptr2] = max(helper(ptr1 - 1, ptr2, str1, str2, dp),
                                helper(ptr1, ptr2 - 1, str1, str2, dp));
}

int lcs(const string &str1, const string &str2)
{
    int n = str1.size(), m = str2.size();

    // Initialize a 2D DP matrix with -1 to represent uncomputed states
    vector<vector<int>> dp(n, vector<int>(m, -1));

    return helper(n - 1, m - 1, str1, str2, dp);
}

// ==================================================
// TABULATION (BOTTOM-UP DP)
//
// Idea:
// - Construct a bottom-up 2D dynamic programming table using 1-based indexing to handle empty string base cases cleanly.
// - Iterate through both strings and increment the diagonal value whenever the current characters at the shifted indices match.
// - Otherwise, carry forward the maximum length from adjacent states.
//
// Time Complexity: O(n * m) - Nested loops traversing the entire 2D DP table.
// Space Complexity: O(n * m) - Memory allocated solely for the 2D DP matrix.
// ==================================================

int lcs(const string &str1, const string &str2)
{
    int n = str1.size(), m = str2.size();

    // Shift indices by +1 so row 0 and column 0 naturally represent empty string base cases (initialized to 0)
    vector<vector<int>> dp(n + 1, vector<int>(m + 1, 0));

    // Build the DP table iteratively for all prefix combinations
    for (int ptr1 = 1; ptr1 <= n; ptr1++)
    {
        for (int ptr2 = 1; ptr2 <= m; ptr2++)
        {
            // Compare characters using 0-based string indices (ptr1 - 1 and ptr2 - 1)
            if (str1[ptr1 - 1] == str2[ptr2 - 1])
                dp[ptr1][ptr2] = 1 + dp[ptr1 - 1][ptr2 - 1];
            else
                dp[ptr1][ptr2] = max(dp[ptr1 - 1][ptr2], dp[ptr1][ptr2 - 1]);
        }
    }

    // The bottom-right cell holds the LCS length for the complete strings
    return dp[n][m];
}

// ==================================================
// 2-ROW SPACE OPTIMIZATION
//
// Idea:
// - Observe that computing any row in the tabulation matrix strictly requires values from the immediately preceding row and itself.
// - Replace the full two-dimensional table with two one-dimensional arrays to track only the previous and current rows.
// - Copy the current row into the previous row iteratively.
//
// Time Complexity: O(n * m) - Retains the exact same nested loop iteration count.
// Space Complexity: O(m) - Reduced memory footprint by utilizing two 1D arrays.
// ==================================================

int lcs(const string &str1, const string &str2)
{
    int n = str1.size(), m = str2.size();

    // Allocate two 1D arrays to represent the previous (ptr1 - 1) and current (ptr1) rows
    vector<int> prev(m + 1, 0), curr(m + 1, 0);

    for (int ptr1 = 1; ptr1 <= n; ptr1++)
    {
        for (int ptr2 = 1; ptr2 <= m; ptr2++)
        {
            // Characters match: Extend the LCS found in the previous row's diagonal state
            if (str1[ptr1 - 1] == str2[ptr2 - 1])
                curr[ptr2] = 1 + prev[ptr2 - 1];
            // Characters do not match: Take the best result from skipping a character in either string
            else
                curr[ptr2] = max(prev[ptr2], curr[ptr2 - 1]);
        }

        // Advance the state: Current row becomes the previous row for the next iteration
        prev = curr;
    }

    // Return the final LCS length stored at the end of the last processed row
    return prev[m];
}

int main()
{
    string s1 = "acd";
    string s2 = "ced";

    // Execute the LCS algorithm and output the result
    cout << "The Length of Longest Common Subsequence is " << lcs(s1, s2) << endl;

    return 0;
}
