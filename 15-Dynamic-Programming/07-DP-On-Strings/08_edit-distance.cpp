// ==================================================
// PROBLEM
// - Given two strings start and target, determine the minimum number of operations required to convert start into target.
// - Allowed operations are inserting, deleting, or replacing a character.
// ==================================================

#include <bits/stdc++.h>
using namespace std;

// ==================================================
// RECURSION
//
// Idea:
// - Start by matching characters from the end of both strings.
// - If the current characters match perfectly, move both pointers backwards.
// - If they mismatch, recursively branch into three possible string operations: insertion, deletion, and replacement to find the minimal overall cost.
// - Return the absolute minimum cost evaluated among these three choices.
//
// Time Complexity: O(3^n) - Exponential branching evaluating three operations at mismatches.
// Space Complexity: O(n + m) - Maximum recursion stack depth for string traversal.
// ==================================================

int helper(int i, int j, const string &s, const string &t)
{
    // Base case: Target string exhausted. Delete all remaining start characters.
    if (j < 0)
        return i + 1;

    // Base case: Start string exhausted. Insert all remaining target characters.
    if (i < 0)
        return j + 1;

    // Characters match: no operation required, simply decrement both string pointers.
    if (s[i] == t[j])
        return helper(i - 1, j - 1, s, t);

    // Branch 1: Insert the required character (moves only the target pointer).
    int insertChar = helper(i, j - 1, s, t);

    // Branch 2: Delete the differing character (moves only the start pointer).
    int deleteChar = helper(i - 1, j, s, t);

    // Branch 3: Replace the differing character (moves both pointers simultaneously).
    int replaceChar = helper(i - 1, j - 1, s, t);

    // Add 1 for the current operation and find the minimal recursive cost.
    return 1 + min({insertChar, deleteChar, replaceChar});
}

int editDistance(string start, string target)
{
    int n = start.size(), m = target.size();

    // Trigger the recursive traversal starting from the last valid indices.
    return helper(n - 1, m - 1, start, target);
}

// ==================================================
// RECURSION + MEMOIZATION (TOP-DOWN DP)
//
// Idea:
// - Use a two-dimensional matrix to cache previously computed subproblem results to prevent redundant exponential branching during the deep recursive evaluation.
// - Shift the string indices to be strictly one-based so we can seamlessly manage the empty string base cases at zero.
//
// Time Complexity: O(n * m) - Each unique prefix combination is computed exactly once.
// Space Complexity: O(n * m) - Memory for DP matrix plus O(n + m) recursion stack.
// ==================================================

int helper(int i, int j, const string &s, const string &t, vector<vector<int>> &dp)
{
    // Base case: Target string is empty, meaning we must delete 'i' characters.
    if (j == 0)
        return i;

    // Base case: Start string is empty, meaning we must insert 'j' characters.
    if (i == 0)
        return j;

    // Return the dynamically cached result immediately if it was already evaluated.
    if (dp[i][j] != -1)
        return dp[i][j];

    // Note: Strings remain 0-indexed, so we access characters using i-1 and j-1.
    if (s[i - 1] == t[j - 1])
        return dp[i][j] = helper(i - 1, j - 1, s, t, dp);

    // Recursively compute the transformation cost for all three fundamental operations.
    int insertChar = helper(i, j - 1, s, t, dp);
    int deleteChar = helper(i - 1, j, s, t, dp);
    int replaceChar = helper(i - 1, j - 1, s, t, dp);

    // Cache the lowest valid operational cost securely before returning the result.
    return dp[i][j] = 1 + min({insertChar, deleteChar, replaceChar});
}

int editDistance(string start, string target)
{
    int n = start.size(), m = target.size();

    // Initialize the 2D memoization matrix strictly filled with -1 uncomputed states.
    vector<vector<int>> dp(n + 1, vector<int>(m + 1, -1));

    // Execute the top-down evaluation utilizing full 1-based string boundary lengths.
    return helper(n, m, start, target, dp);
}

// ==================================================
// TABULATION (BOTTOM-UP DP)
//
// Idea:
// - Build a bottom-up two-dimensional dynamic programming table iteratively from scratch.
// - Initialize the first row and column to sequentially represent the base costs of transforming to or from fully empty strings.
// - Process remaining string segments iteratively by inheriting optimal previous states.
//
// Time Complexity: O(n * m) - Nested loops to systematically process all character combinations.
// Space Complexity: O(n * m) - Memory allocated strictly for the full 2D matrix.
// ==================================================

int editDistance(string s, string t)
{
    int n = s.size(), m = t.size();

    // Allocate the comprehensive DP matrix uniformly initialized with zero costs.
    vector<vector<int>> dp(n + 1, vector<int>(m + 1, 0));

    // Populate the first column: deleting 'i' characters to reach an empty target.
    for (int i = 0; i <= n; i++)
        dp[i][0] = i;

    // Populate the first row: inserting 'j' characters to build the target.
    for (int j = 1; j <= m; j++)
        dp[0][j] = j;

    // Iteratively scan through every possible prefix combination of both strings.
    for (int i = 1; i <= n; i++)
    {
        for (int j = 1; j <= m; j++)
        {
            // Characters match identically, directly inherit the diagonal operational cost.
            if (s[i - 1] == t[j - 1])
            {
                dp[i][j] = dp[i - 1][j - 1];
            }
            // Characters mismatch, compute the absolute minimum required structural alterations.
            else
            {
                int insertChar = dp[i][j - 1];      // Left cell represents insertion
                int deleteChar = dp[i - 1][j];      // Top cell represents deletion
                int replaceChar = dp[i - 1][j - 1]; // Diagonal cell represents replacement

                // Apply the optimal transformation and increment the cumulative operational count.
                dp[i][j] = 1 + min({insertChar, deleteChar, replaceChar});
            }
        }
    }

    // Extract the final total minimum operational distance from the bottom-right corner.
    return dp[n][m];
}

// ==================================================
// SPACE OPTIMIZATION
//
// Idea:
// - Notice that computing the current row in the DP table strictly requires data from only the immediately preceding computed row.
// - Replace the full two-dimensional matrix with just two compact arrays to track the previous and current state transitions continuously.
//
// Time Complexity: O(n * m) - Retains the identical iteration limits as the tabulation approach.
// Space Complexity: O(m) - Memory usage vastly reduced by strictly utilizing two arrays.
// ==================================================

int editDistance(string s, string t)
{
    int n = s.size(), m = t.size();

    // Construct arrays to maintain state sequentially rather than retaining entire matrices.
    vector<int> prev(m + 1, 0), curr(m + 1, 0);

    // Initialize the previous array corresponding to an empty start string scenario.
    for (int j = 1; j <= m; j++)
        prev[j] = j;

    // Incrementally process characters of the starting string one by one.
    for (int i = 1; i <= n; i++)
    {
        // Define the base condition for the current row when target is empty.
        curr[0] = i;

        for (int j = 1; j <= m; j++)
        {
            // Match discovered: replicate the stored value from the previous diagonal safely.
            if (s[i - 1] == t[j - 1])
            {
                curr[j] = prev[j - 1];
            }
            // Mismatch encountered: deduce optimal combination utilizing previously stored boundary constraints.
            else
            {
                int insertChar = curr[j - 1];
                int deleteChar = prev[j];
                int replaceChar = prev[j - 1];

                // Consolidate the lowest valid cumulative sum into the current state tracker.
                curr[j] = 1 + min({insertChar, deleteChar, replaceChar});
            }
        }

        // Overwrite the prior state by completely shifting the computed current state.
        prev = curr;
    }

    // Return the minimum aggregated alterations located at the maximum target index.
    return prev[m];
}

int main()
{
    string s1 = "horse";
    string s2 = "ros";

    cout << "The minimum number of operations required is: " << editDistance(s1, s2);

    return 0;
}
