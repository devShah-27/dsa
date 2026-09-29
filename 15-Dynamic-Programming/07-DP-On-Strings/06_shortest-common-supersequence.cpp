// ==================================================
// PROBLEM
// - Given two strings str1 and str2.
// - Find the shortest common supersequence string that contains both str1 and str2 as exact subsequences.
// ==================================================

#include <bits/stdc++.h>
using namespace std;

// ==================================================
// TABULATION (BOTTOM-UP DP) & BACKTRACKING
//
// Idea:
// - First, compute the Longest Common Subsequence (LCS) matrix using bottom-up dynamic programming tabulation to identify shared characters.
// - Then, backtrack from the bottom-right corner of the DP matrix to incrementally construct the shortest common supersequence string.
// - Include matching characters exactly once to avoid unnecessary duplication.
// - For mismatched characters, trace back toward the maximum LCS value, safely appending the character from the skipped string.
// - Finally, reverse the assembled string to restore chronological order.
//
// Time Complexity: O(n * m) - For DP matrix population, plus O(n + m) for backtracking.
// Space Complexity: O(n * m) - For the 2D DP matrix used to trace the LCS.
// ==================================================

string shortestCommonSupersequence(const string &str1, const string &str2)
{
    // Extract the exact sizes of both input strings
    int n = str1.size(), m = str2.size();

    // Initialize a 2D DP matrix to calculate Longest Common Subsequence lengths
    vector<vector<int>> dp(n + 1, vector<int>(m + 1, 0));

    // Systematically build the LCS DP table from the bottom up
    for (int i = 1; i <= n; i++)
    {
        for (int j = 1; j <= m; j++)
        {
            // If the characters match, extend the known sequence length
            if (str1[i - 1] == str2[j - 1])
                dp[i][j] = 1 + dp[i - 1][j - 1];
            // If they mismatch, carry forward the maximum sequence found so far
            else
                dp[i][j] = max(dp[i - 1][j], dp[i][j - 1]);
        }
    }

    // Allocate a string to accumulate the shortest supersequence characters backwards
    string ans = "";

    // Start the backtracking process from the bottom-right corner
    int i = n, j = m;

    // Traverse the matrix backwards until one string is fully exhausted
    while (i > 0 && j > 0)
    {
        // Matching character found: include it once and move diagonally
        if (str1[i - 1] == str2[j - 1])
        {
            ans += str1[i - 1];
            i--;
            j--;
        }
        // Mismatch: move up if the cell above had a strictly greater LCS value,
        // which means the current character of str1 is not part of the LCS
        else if (dp[i - 1][j] > dp[i][j - 1])
        {
            ans += str1[i - 1];
            i--;
        }
        // Mismatch: move left otherwise, appending the current character of str2
        else
        {
            ans += str2[j - 1];
            j--;
        }
    }

    // Exhaust remaining characters from the first string, if any
    while (i > 0)
    {
        ans += str1[i - 1];
        i--;
    }

    // Exhaust remaining characters from the second string, if any
    while (j > 0)
    {
        ans += str2[j - 1];
        j--;
    }

    // Reverse the string to correct the backwards traversal accumulation
    reverse(ans.begin(), ans.end());

    // Return the final formatted shortest common supersequence
    return ans;
}

int main()
{
    string s1 = "brute";
    string s2 = "groot";

    // Trigger the computation and display the evaluated supersequence
    cout << "The Longest Common Supersequence is " << shortestCommonSupersequence(s1, s2);

    return 0;
}
