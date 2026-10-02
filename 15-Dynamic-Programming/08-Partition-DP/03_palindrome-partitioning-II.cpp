// ==================================================
// PROBLEM
// - Given a string s, partition it so every substring is a palindrome.
// - Return the minimum number of cuts needed for such a partition.
// ==================================================

#include <bits/stdc++.h>
using namespace std;

// Two-pointer check: returns true if s[i..j] reads the same forwards and backwards
// Time Complexity: O(j - i + 1), Space Complexity: O(1)
bool isPalindrome(int i, int j, string &s)
{
    while (i < j)
    {
        if (s[i] != s[j])
            return false;

        i++;
        j--;
    }

    return true;
}

// ==================================================
// RECURSIVE APPROACH
//
// Idea:
// - Starting at index i, try every end index j for the next substring s[i..j].
// - Recurse on the remaining suffix only when s[i..j] is a palindrome.
// - Each valid choice adds one partition to the suffix result.
// - Return the minimum partitions found across all valid choices.
//
// Time Complexity: O(2^n * n) - Each gap may be cut or not, plus an O(n) palindrome check.
// Space Complexity: O(n) - Auxiliary space required for the recursion stack.
// ==================================================

int helper(int i, int n, string &s)
{
    // Base case: Reached the end of the string, no more partitions needed
    if (i == n)
        return 0;

    int minPartitionCnt = 1e9;

    // Try every end index j for the substring starting at i
    for (int j = i; j < n; j++)
    {
        // Only partition here if the current substring is a palindrome
        if (isPalindrome(i, j, s))
        {
            // One partition for s[i..j] + best partitions for the remaining suffix
            int currPartitionCnt = 1 + helper(j + 1, n, s);
            minPartitionCnt = min(minPartitionCnt, currPartitionCnt);
        }
    }

    return minPartitionCnt;
}

int minCut(string s)
{
    int n = s.size();

    // Partitions minus 1 gives cuts, since k partitions need k - 1 cuts
    return helper(0, n, s) - 1;
}

// ==================================================
// RECURSION + MEMOIZATION (TOP-DOWN DP)
//
// Idea:
// - The recursive solution repeatedly solves the same suffixes starting at i.
// - Cache the minimum partitions for each suffix in a 1D table indexed by i.
// - Return the stored answer immediately when a suffix is already solved.
// - Each suffix still tries every palindromic prefix once.
//
// Time Complexity: O(n^3) - O(n) states, each trying O(n) ends with an O(n) palindrome check.
// Space Complexity: O(n) for DP table + O(n) for recursion stack.
// ==================================================

int helper(int i, int n, string &s, vector<int> &dp)
{
    // Base case: Reached the end of the string, no more partitions needed
    if (i == n)
        return 0;

    // Return the stored result if this suffix is already solved
    if (dp[i] != -1)
        return dp[i];

    int minPartitionCnt = 1e9;

    // Try every end index j for the substring starting at i
    for (int j = i; j < n; j++)
    {
        // Only partition here if the current substring is a palindrome
        if (isPalindrome(i, j, s))
        {
            // One partition for s[i..j] + best partitions for the remaining suffix
            int currPartitionCnt = 1 + helper(j + 1, n, s, dp);
            minPartitionCnt = min(minPartitionCnt, currPartitionCnt);
        }
    }

    // Cache the minimum partitions before returning
    return dp[i] = minPartitionCnt;
}

int minCut(string s)
{
    int n = s.size();

    // Initialize the DP table with -1 to indicate uncomputed states
    vector<int> dp(n, -1);

    // Partitions minus 1 gives cuts
    return helper(0, n, s, dp) - 1;
}

// ==================================================
// TABULATION (BOTTOM-UP DP)
//
// Idea:
// - Convert the memoized recursion into iterative table filling.
// - State dp[i] stores the minimum partitions for the suffix s[i..n-1].
// - Iterate i from right to left, so dp[j + 1] is ready before use.
// - The empty suffix dp[n] stays 0 from initialization.
//
// Time Complexity: O(n^3) - Two nested loops plus an O(n) palindrome check.
// Space Complexity: O(n) - Memory allocated for the 1D DP array.
// ==================================================

int minCut(string s)
{
    int n = s.size();

    // Initialize with 0, which also covers the base case dp[n] = 0
    vector<int> dp(n + 1, 0);

    // i moves from the last character down to the first
    for (int i = n - 1; i >= 0; i--)
    {
        int minPartitionCnt = INT_MAX;

        // Try every end index j for the substring starting at i
        for (int j = i; j < n; j++)
        {
            // Only partition here if the current substring is a palindrome
            if (isPalindrome(i, j, s))
            {
                // One partition for s[i..j] + best partitions for the remaining suffix
                int currPartitionCnt = 1 + dp[j + 1];
                minPartitionCnt = min(minPartitionCnt, currPartitionCnt);
            }
        }

        dp[i] = minPartitionCnt;
    }

    // Partitions for the full string minus 1 gives cuts
    return dp[0] - 1;
}

int main()
{
    string str = "BABABCBADCEDE";

    cout << "The minimum number of partitions: " << minCut(str) << "\n";

    return 0;
}