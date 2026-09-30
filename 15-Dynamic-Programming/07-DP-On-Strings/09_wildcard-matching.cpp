// ==================================================
// PROBLEM
// - Given a string and a pattern containing special wildcard characters.
// - '?' matches any single character, and '*' matches any sequence.
// - Determine if the given pattern exactly matches the entire string.
// ==================================================

#include <bits/stdc++.h>
using namespace std;

// ==================================================
// RECURSION
//
// Idea:
// - Start matching characters from the end of both strings simultaneously moving backwards to check the remaining prefixes.
// - If characters match or the pattern has a question mark, move both pointers backwards to continue the matching sequence.
// - If an asterisk is found, branch to either skip a character in the string or skip the asterisk entirely.
// - Return true if any branching path successfully matches the strings.
//
// Time Complexity: O(2^(n+m)) - Exponential branching at every asterisk character encountered.
// Space Complexity: O(n + m) - Maximum depth of the auxiliary recursion stack.
// ==================================================

bool helper(int i, int j, const string &pat, const string &str)
{
    // Base case: Both the pattern and string are fully exhausted
    if (i < 0 && j < 0)
        return true;

    // Base case: Pattern is exhausted but string still has characters
    if (i < 0 && j >= 0)
        return false;

    // Base case: String exhausted, remaining pattern must only contain asterisks
    if (j < 0 && i >= 0)
    {
        for (int idx = 0; idx <= i; idx++)
        {
            if (pat[idx] != '*')
                return false;
        }

        return true;
    }

    // Direct match or single character wildcard allows moving both pointers safely
    if (pat[i] == str[j] || pat[i] == '?')
        return helper(i - 1, j - 1, pat, str);

    // Asterisk encountered: try treating it as empty (skip pattern) OR as matching a char (skip string)
    if (pat[i] == '*')
        return helper(i - 1, j, pat, str) | helper(i, j - 1, pat, str);

    // Characters do not match and no valid wildcard is present
    return false;
}

bool wildCard(const string &str, const string &pat)
{
    int n = str.size(), m = pat.size();

    // Trigger recursive validation from the last indices of both inputs
    return helper(m - 1, n - 1, pat, str);
}

// ==================================================
// RECURSION + MEMOIZATION (TOP-DOWN DP)
//
// Idea:
// - Use a two-dimensional matrix to cache previously computed recursive subproblems, preventing redundant overlapping exponential branches during the deep evaluation.
// - Shift the string indices to be strictly one-based inside the DP logic.
// - This allows us to cleanly handle empty string base cases at index zero without causing out of bounds array errors.
//
// Time Complexity: O(n * m) - Each unique index pair state is evaluated exactly once.
// Space Complexity: O(n * m) - Memory for the DP matrix plus recursion stack depth.
// ==================================================

bool helper(int i, int j, const string &pat, const string &str, vector<vector<int>> &dp)
{
    // Base case: Both strings are fully matched to their ends
    if (i == 0 && j == 0)
        return true;

    // Base case: Pattern exhausted but the target string is not
    if (i == 0 && j > 0)
        return false;

    // Base case: String exhausted, verify if remaining pattern is entirely asterisks
    if (j == 0 && i > 0)
    {
        for (int idx = 1; idx <= i; idx++)
        {
            if (pat[idx - 1] != '*')
                return false;
        }

        return true;
    }

    // Return the cached computation immediately if it already exists
    if (dp[i][j] != -1)
        return dp[i][j];

    // Access characters using i-1 and j-1 because state logic is 1-based
    if (pat[i - 1] == str[j - 1] || pat[i - 1] == '?')
        return dp[i][j] = helper(i - 1, j - 1, pat, str, dp);

    // Evaluate both wildcard branches and store the boolean result in the cache
    if (pat[i - 1] == '*')
        return dp[i][j] = helper(i - 1, j, pat, str, dp) | helper(i, j - 1, pat, str, dp);

    // Default to false for mismatched characters preventing the pattern completion
    return dp[i][j] = false;
}

bool wildCard(const string &str, const string &pat)
{
    int n = str.size(), m = pat.size();

    // Initialize DP matrix with -1 representing unvisited prefix combinations
    vector<vector<int>> dp(m + 1, vector<int>(n + 1, -1));

    return helper(m, n, pat, str, dp);
}

// ==================================================
// TABULATION (BOTTOM-UP DP)
//
// Idea:
// - Construct a bottom-up boolean dynamic programming table iteratively from scratch.
// - Initialize the base cases for matching against an empty string, which only matches a pattern of pure asterisks.
// - Iteratively process the remaining prefixes by inheriting optimal previous states, where asterisks inherit truth values from either top or left.
//
// Time Complexity: O(n * m) - Nested loops systematically process all pattern and string characters.
// Space Complexity: O(n * m) - Memory strictly allocated for the full 2D boolean matrix.
// ==================================================

bool wildCard(const string &str, const string &pat)
{
    int n = str.size(), m = pat.size();

    // dp[i][j] represents if pattern prefix 'i' matches string prefix 'j'
    vector<vector<bool>> dp(m + 1, vector<bool>(n + 1, false));

    // Base case: Empty pattern successfully matches an empty string
    dp[0][0] = true;

    // Base case: Fill the first column handling an empty target string
    for (int i = 1; i <= m; i++)
    {
        bool flag = true;

        // An empty string only matches if the pattern prefix consists entirely of '*'
        for (int idx = 1; idx <= i; idx++)
        {
            if (pat[idx - 1] != '*')
            {
                flag = false;
                break;
            }
        }

        dp[i][0] = flag;
    }

    // Process all character combinations filling the DP table bottom-up
    for (int i = 1; i <= m; i++)
    {
        for (int j = 1; j <= n; j++)
        {
            // Characters match or we have a wildcard '?', inherit diagonal value
            if (pat[i - 1] == str[j - 1] || pat[i - 1] == '?')
                dp[i][j] = dp[i - 1][j - 1];

            // Asterisk acts as empty sequence (dp[i-1][j]) OR valid sequence (dp[i][j-1])
            else if (pat[i - 1] == '*')
                dp[i][j] = dp[i - 1][j] | dp[i][j - 1];

            // Direct mismatch with no usable wildcards means false
            else
                dp[i][j] = false;
        }
    }

    // The final result lies at the extreme bottom right coordinate
    return dp[m][n];
}

// ==================================================
// SPACE OPTIMIZATION
//
// Idea:
// - Computing the current row in the dynamic programming matrix strictly requires data from only the immediately preceding calculated row state.
// - Replace the large two-dimensional matrix with just two compact arrays that continuously track the previous and current state transitions.
// - This vastly reduces the overall memory footprint of the algorithm.
//
// Time Complexity: O(n * m) - Retains the exact same nested loop iterations as tabulation.
// Space Complexity: O(n) - Memory usage is drastically minimized to two 1D arrays.
// ==================================================

bool wildCard(const string &str, const string &pat)
{
    int n = str.size(), m = pat.size();

    // Track matching states using compact arrays sequentially replacing the 2D matrix
    vector<bool> prev(n + 1, false), curr(n + 1, false);

    // Initialize base condition for matching double empty strings
    prev[0] = true;

    // Iterate through every character prefix in the pattern string
    for (int i = 1; i <= m; i++)
    {
        bool flag = true;

        // Verify if the current pattern prefix is exclusively asterisks
        for (int idx = 1; idx <= i; idx++)
        {
            if (pat[idx - 1] != '*')
            {
                flag = false;
                break;
            }
        }

        // Apply empty string base condition strictly to the current iteration array
        curr[0] = flag;

        // Iterate through all characters of the target evaluation string
        for (int j = 1; j <= n; j++)
        {
            // Pass forward valid matches using previous stored prefix boundaries
            if (pat[i - 1] == str[j - 1] || pat[i - 1] == '?')
                curr[j] = prev[j - 1];

            // Calculate asterisk permutations relying on adjacent stored state booleans
            else if (pat[i - 1] == '*')
                curr[j] = prev[j] | curr[j - 1];

            // Mismatch invalidates the prefix sequence forcing a false closure
            else
                curr[j] = false;
        }

        // Overwrite previous state transferring the fully verified current array
        prev = curr;
    }

    // Final logical answer is captured dynamically in the ultimate array slot
    return prev[n];
}

int main()
{
    string S1 = "ab*cd";
    string S2 = "abdefcd";

    // Initiate sequence matching and output the processed boolean validation
    if (wildCard(S2, S1))
        cout << "String S1 and S2 do match";
    else
        cout << "String S1 and S2 do not match";

    return 0;
}
