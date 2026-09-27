// ==================================================
// PROBLEM
// - Given two strings str1 and str2, find the length of their longest common substring.
// - A substring is a contiguous sequence of characters within a string.
// ==================================================

#include <bits/stdc++.h>
using namespace std;

// ==================================================
// TABULATION (BOTTOM-UP DP)
//
// Idea:
// - Build a 2D dynamic programming table where each cell represents the length of the common substring ending at those indices.
// - If the characters match, extend the contiguous match length from the previous diagonal state; otherwise, reset the current state to zero.
// - Track the maximum length encountered across the entire table.
//
// Time Complexity: O(n * m) - Nested loops traversing all character pairs.
// Space Complexity: O(n * m) - Memory allocated for the 2D DP matrix.
// ==================================================

int longestCommonSubstr(const string &str1, const string &str2)
{
    int n = str1.size(), m = str2.size();

    // Shift indices by +1 so row 0 and column 0 naturally represent empty string base cases
    vector<vector<int>> dp(n + 1, vector<int>(m + 1, 0));

    // Tracks the maximum length of a common substring found anywhere in the table
    int maxLen = 0;

    for (int ptr1 = 1; ptr1 <= n; ptr1++)
    {
        for (int ptr2 = 1; ptr2 <= m; ptr2++)
        {
            // Characters match: Extend the contiguous substring from the previous diagonal state
            if (str1[ptr1 - 1] == str2[ptr2 - 1])
            {
                dp[ptr1][ptr2] = 1 + dp[ptr1 - 1][ptr2 - 1];
                maxLen = max(maxLen, dp[ptr1][ptr2]);
            }
            // Characters do not match: Contiguity is broken, so reset the current length to 0
            else
            {
                dp[ptr1][ptr2] = 0;
            }
        }
    }

    return maxLen;
}

// ==================================================
// 2-ROW SPACE OPTIMIZATION
//
// Idea:
// - Observe that computing the current row strictly requires diagonal values from the immediately preceding row in the dynamic programming table.
// - Replace the full two-dimensional matrix with two one-dimensional arrays to track only the previous and current row states.
// - Update the global maximum length whenever matching characters are found.
//
// Time Complexity: O(n * m) - Retains the exact same nested loop iteration count.
// Space Complexity: O(m) - Reduced memory footprint by utilizing two 1D arrays.
// ==================================================

int longestCommonSubstr(const string &str1, const string &str2)
{
    int n = str1.size(), m = str2.size();

    // Allocate two 1D arrays to represent the previous (ptr1 - 1) and current (ptr1) rows
    vector<int> prev(m + 1, 0), curr(m + 1, 0);

    int maxLen = 0;

    for (int ptr1 = 1; ptr1 <= n; ptr1++)
    {
        for (int ptr2 = 1; ptr2 <= m; ptr2++)
        {
            // Characters match: Extend the contiguous substring using the previous row's diagonal value
            if (str1[ptr1 - 1] == str2[ptr2 - 1])
            {
                curr[ptr2] = 1 + prev[ptr2 - 1];
                maxLen = max(maxLen, curr[ptr2]);
            }
            // Characters do not match: Reset current state to 0 to enforce contiguity
            else
            {
                curr[ptr2] = 0;
            }
        }

        // Advance the state: Current row becomes the previous row for the next iteration
        prev = curr;
    }

    return maxLen;
}

int main()
{
    string s1 = "abcjklp";
    string s2 = "acjkp";

    // Execute the algorithm and output the maximum contiguous substring length
    cout << "The Length of Longest Common Substring is " << longestCommonSubstr(s1, s2) << endl;

    return 0;
}
