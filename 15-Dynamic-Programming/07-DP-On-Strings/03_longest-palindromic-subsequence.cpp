// ==================================================
// PROBLEM
// - Given a string s, find the length of its longest palindromic subsequence.
// - A palindrome is a sequence that reads the same backward as forward.
// - A subsequence is derived by deleting zero or more characters without changing the order of remaining elements.
// ==================================================

#include <bits/stdc++.h>
using namespace std;

// ==================================================
// TABULATION (BOTTOM-UP DP)
//
// Idea:
// - Reduce the problem to Longest Common Subsequence by comparing the original string against a reversed copy of itself.
// - Build a 2D dynamic programming table iteratively by incrementing diagonal states on character matches or propagating adjacent maximums.
// - Return the maximum common subsequence length accumulated across the table.
//
// Time Complexity: O(n^2) - Nested loops traversing both strings of length n.
// Space Complexity: O(n^2) - Memory allocated for the 2D DP matrix.
// ==================================================

int lcs(string &s, string &t)
{
    int n = s.size(), m = t.size();

    // Shift indices by +1 so row 0 and column 0 represent empty prefix base cases
    vector<vector<int>> dp(n + 1, vector<int>(m + 1, 0));

    for (int i = 1; i <= n; i++)
    {
        for (int j = 1; j <= m; j++)
        {
            // Characters match: Extend the common subsequence from the previous diagonal state
            if (s[i - 1] == t[j - 1])
            {
                dp[i][j] = 1 + dp[i - 1][j - 1];
            }
            // Characters do not match: Carry forward the best length from skipping a character in either string
            else
            {
                dp[i][j] = max(dp[i - 1][j], dp[i][j - 1]);
            }
        }
    }

    return dp[n][m];
}

int longestPalinSubseq(string s)
{
    // Create a reversed copy of the input string
    string t = s;

    reverse(t.begin(), t.end());

    // The LCS of a string and its reverse equals its Longest Palindromic Subsequence
    return lcs(s, t);
}

// ==================================================
// 2-ROW SPACE OPTIMIZATION
//
// Idea:
// - Observe that computing any row in the LCS table strictly depends on values from the current and immediately preceding rows.
// - Replace the full two-dimensional matrix with two one-dimensional arrays to reduce memory overhead while comparing the reversed string.
// - Overwrite the previous row with the current row every iteration.
//
// Time Complexity: O(n^2) - Retains the exact same nested loop iteration count.
// Space Complexity: O(n) - Auxiliary space for two 1D arrays and the reversed string.
// ==================================================

int lcs(string &s, string &t)
{
    int n = s.size(), m = t.size();

    // Allocate two 1D arrays to represent the previous (i - 1) and current (i) rows
    vector<int> prev(m + 1, 0), curr(m + 1, 0);

    for (int i = 1; i <= n; i++)
    {
        for (int j = 1; j <= m; j++)
        {
            // Characters match: Increment the result from the previous row's diagonal state
            if (s[i - 1] == t[j - 1])
            {
                curr[j] = 1 + prev[j - 1];
            }
            // Characters do not match: Take the maximum from the top (prev[j]) or left (curr[j - 1]) state
            else
            {
                curr[j] = max(prev[j], curr[j - 1]);
            }
        }

        // Advance the state: Current row becomes the previous row for the next iteration
        prev = curr;
    }

    return prev[m];
}

int longestPalinSubseq(string s)
{
    // Create a reversed copy of the original string
    string t = s;

    reverse(t.begin(), t.end());

    // Compute the LCS between the original and reversed strings
    return lcs(s, t);
}

int main()
{
    string s = "bbabcbcab";

    cout << "The Length of Longest Palindromic Subsequence is " << longestPalinSubseq(s);

    return 0;
}
