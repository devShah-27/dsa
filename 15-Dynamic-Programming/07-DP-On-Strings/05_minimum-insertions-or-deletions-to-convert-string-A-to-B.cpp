// ==================================================
// PROBLEM
// - Given two strings str1 and str2.
// - Find the minimum number of insertions and deletions required to transform str1 into str2.
// - Operations can occur at any position in the string.
// ==================================================

#include <bits/stdc++.h>
using namespace std;

// ==================================================
// TABULATION (BOTTOM-UP DP)
//
// Idea:
// - The minimum operations can be found by subtracting the longest common subsequence length from both string lengths.
// - Use a 2D dynamic programming table to compute the length of the LCS iteratively from the bottom up.
//
// Time Complexity: O(n * m) - Nested loops to process every character pair of str1 and str2.
// Space Complexity: O(n * m) - A 2D DP matrix to store intermediate LCS lengths.
// ==================================================

int LCS(const string &s, const string &t)
{
    int n = s.size(), m = t.size();

    // Initialize a 2D DP matrix to store the lengths
    // of common subsequences for all prefix combinations.
    vector<vector<int>> dp(n + 1, vector<int>(m + 1, 0));

    // Iterate through the characters of both strings systematically
    for (int sPtr = 1; sPtr <= n; sPtr++)
    {
        for (int tPtr = 1; tPtr <= m; tPtr++)
        {
            // If characters match, extend the LCS length from the previous diagonal state
            if (s[sPtr - 1] == t[tPtr - 1])
                dp[sPtr][tPtr] = 1 + dp[sPtr - 1][tPtr - 1];
            // If characters differ, take the maximum LCS found by skipping one character
            else
                dp[sPtr][tPtr] = max(dp[sPtr - 1][tPtr], dp[sPtr][tPtr - 1]);
        }
    }

    // Extract the final Longest Common Subsequence length from the bottom-right cell
    return dp[n][m];
}

int minOperations(const string &str1, const string &str2)
{
    int n = str1.size(), m = str2.size();

    // Deletions = n - LCS, Insertions = m - LCS
    // Total operations = (n - LCS) + (m - LCS) = n + m - 2 * LCS
    return (n + m - (2 * LCS(str1, str2)));
}

// ==================================================
// SPACE OPTIMIZED (1D DP)
//
// Idea:
// - Computing the current row of the LCS DP table only strictly requires values from the previous row.
// - We can reduce the space footprint by maintaining just two one-dimensional arrays representing previous and current states.
//
// Time Complexity: O(n * m) - Retains the identical nested iteration bounds as tabulation.
// Space Complexity: O(m) - Uses only two 1D arrays of size m + 1 instead of a full matrix.
// ==================================================

int LCS(const string &s, const string &t)
{
    int n = s.size(), m = t.size();

    // Allocate two 1D arrays to track the previous and current row states
    vector<int> prev(m + 1, 0), curr(m + 1, 0);

    // Process each character of the first string one row at a time
    for (int sPtr = 1; sPtr <= n; sPtr++)
    {
        for (int tPtr = 1; tPtr <= m; tPtr++)
        {
            // Characters match: add 1 to the top-left diagonal equivalent
            if (s[sPtr - 1] == t[tPtr - 1])
                curr[tPtr] = 1 + prev[tPtr - 1];
            // Characters mismatch: inherit the best result from top or left adjacent cells
            else
                curr[tPtr] = max(prev[tPtr], curr[tPtr - 1]);
        }

        // Shift the completed current row state to become the previous row state
        prev = curr;
    }

    // Return the max length accumulated at the end of the arrays
    return prev[m];
}

int minOperations(const string &str1, const string &str2)
{
    int n = str1.size(), m = str2.size();

    // Reusing the mathematical formula mapping LCS length to required transformations
    return (n + m - (2 * LCS(str1, str2)));
}

int main()
{
    string str1 = "abcd";
    string str2 = "anc";

    // Compute and display the minimum number of required structural modifications
    cout << "The Minimum operations required to convert str1 to str2: " << minOperations(str1, str2);

    return 0;
}
