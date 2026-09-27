// ==================================================
// PROBLEM
// - Given an n x m matrix consisting of integer values.
// - Find the minimum path sum starting at any cell in the first row and ending at any cell in the last row.
// - Movement is allowed only to the bottom, bottom-left, or bottom-right adjacent cells.
// ==================================================

#include <bits/stdc++.h>
using namespace std;

// ==================================================
// BRUTE FORCE APPROACH — RECURSION
//
// Idea:
// - Recursively evaluate paths from the last row up to the first row.
// - From cell (row, col), explore all three valid previous cells: up, up-left, and up-right.
// - Return infinity (1e9) for out-of-bounds columns, and matrix[0][col] for row 0.
// - Iterate over all columns in the last row to find the overall minimum.
//
// Time Complexity: O(m * 3^n) - Each path branches into 3 choices across n rows for m starting columns.
// Space Complexity: O(n) - Maximum depth of the recursive call stack.
// ==================================================

int helper(int row, int col, int n, int m, vector<vector<int>> &matrix)
{
    // Base case: Out of column boundaries
    if (col < 0 || col >= m)
        return 1e9;

    // Base case: Reached the top row
    if (row == 0)
        return matrix[row][col];

    // Transition 1: Move directly upward
    int up = matrix[row][col] + helper(row - 1, col, n, m, matrix);

    // Transition 2: Move diagonally up-left
    int up_left = matrix[row][col] + helper(row - 1, col - 1, n, m, matrix);

    // Transition 3: Move diagonally up-right
    int up_right = matrix[row][col] + helper(row - 1, col + 1, n, m, matrix);

    // Return minimum among all three paths
    return min({up, up_left, up_right});
}

int minFallingPathSum(vector<vector<int>> &matrix)
{
    int n = matrix.size(), m = matrix[0].size();

    int mini = 1e9;

    // Try all possible ending column cells in the bottom row
    for (int col = 0; col < m; col++)
    {
        int colMin = helper(n - 1, col, n, m, matrix);

        mini = min(mini, colMin);
    }

    return mini;
}

// ==================================================
// BETTER APPROACH — MEMOIZATION (TOP-DOWN DP)
//
// Idea:
// - Store computed minimum path sums in a 2D DP array initialized to -1.
// - If state (row, col) is already computed, return it directly to avoid recomputation.
// - Recursively compute transitions for up, up-left, and up-right, caching the minimum value.
// - Take the minimum over all columns in the bottom row.
//
// Time Complexity: O(n * m) - Each cell state is computed and memoized once.
// Space Complexity: O(n * m) - O(n * m) for the DP table plus O(n) recursion call stack.
// ==================================================

int helper(int row, int col, int n, int m, vector<vector<int>> &matrix, vector<vector<int>> &dp)
{
    // Base case: Out of column boundaries
    if (col < 0 || col >= m)
        return 1e9;

    // Base case: Reached the top row
    if (row == 0)
        return matrix[row][col];

    // Return cached result if already calculated
    if (dp[row][col] != -1)
        return dp[row][col];

    // Compute all three possible directional transitions
    int up = matrix[row][col] + helper(row - 1, col, n, m, matrix, dp);

    int up_left = matrix[row][col] + helper(row - 1, col - 1, n, m, matrix, dp);

    int up_right = matrix[row][col] + helper(row - 1, col + 1, n, m, matrix, dp);

    // Cache and return optimal minimum sum
    return dp[row][col] = min({up, up_left, up_right});
}

int minFallingPathSum(vector<vector<int>> &matrix)
{
    int n = matrix.size(), m = matrix[0].size();

    // Table to memoize solutions for all cells
    vector<vector<int>> dp(n, vector<int>(m, -1));

    int mini = 1e9;

    // Evaluate minimum across all ending columns
    for (int col = 0; col < m; col++)
    {
        int colMin = helper(n - 1, col, n, m, matrix, dp);

        mini = min(mini, colMin);
    }

    return mini;
}

// ==================================================
// BETTER APPROACH — TABULATION (BOTTOM-UP DP)
//
// Idea:
// - Iteratively calculate the minimum path sum from row 0 down to row (n - 1).
// - Base case: dp[0][col] = matrix[0][col] for all columns in the first row.
// - Transition: dp[row][col] is matrix[row][col] plus the minimum of dp[row-1][col], dp[row-1][col-1], and dp[row-1][col+1].
// - Return the minimum value found across the last row dp[n - 1].
//
// Time Complexity: O(n * m) - Nested loops iterate over all n rows and m columns.
// Space Complexity: O(n * m) - 2D table storing answers for all subproblems.
// ==================================================

int minFallingPathSum(vector<vector<int>> &matrix)
{
    int n = matrix.size(), m = matrix[0].size();

    // dp[row][col] stores minimum path sum to reach cell (row, col)
    vector<vector<int>> dp(n, vector<int>(m, -1));

    // Base condition: Initialize first row with matrix values
    for (int col = 0; col < m; col++)
    {
        dp[0][col] = matrix[0][col];
    }

    // Iteratively compute minimum path sum for subsequent rows
    for (int row = 1; row < n; row++)
    {
        for (int col = 0; col < m; col++)
        {
            int up = matrix[row][col] + dp[row - 1][col];

            // Handle boundary checks for diagonal moves
            int up_left = col - 1 >= 0 ? matrix[row][col] + dp[row - 1][col - 1] : 1e9;

            int up_right = col + 1 < m ? matrix[row][col] + dp[row - 1][col + 1] : 1e9;

            dp[row][col] = min({up, up_left, up_right});
        }
    }

    int mini = 1e9;

    // Find minimum path sum in last row
    for (int col = 0; col < m; col++)
    {
        mini = min(mini, dp[n - 1][col]);
    }

    return mini;
}

// ==================================================
// OPTIMAL APPROACH — SPACE-OPTIMIZED DP
//
// Idea:
// - Current row values only depend on the previous row's results.
// - Maintain a 1D vector 'prev' representing the previous row and compute 'curr' for the current row.
// - Update prev = curr after processing each row to reduce auxiliary space.
//
// Time Complexity: O(n * m) - Traverses each matrix element once with O(1) transitions.
// Space Complexity: O(m) - Uses two 1D vectors of size m for state transitions.
// ==================================================

int minFallingPathSum(vector<vector<int>> &matrix)
{
    int n = matrix.size(), m = matrix[0].size();

    // Stores minimum path sums for the previous row
    vector<int> prev(m, -1);

    // Initialize base values for the first row
    for (int col = 0; col < m; col++)
    {
        prev[col] = matrix[0][col];
    }

    for (int row = 1; row < n; row++)
    {
        // Stores path sums for current row
        vector<int> curr(m, -1);

        for (int col = 0; col < m; col++)
        {
            int up = matrix[row][col] + prev[col];

            // Boundary checks for diagonal previous transitions
            int up_left = col - 1 >= 0 ? matrix[row][col] + prev[col - 1] : 1e9;

            int up_right = col + 1 < m ? matrix[row][col] + prev[col + 1] : 1e9;

            curr[col] = min({up, up_left, up_right});
        }

        // Slide current row results to previous
        prev = curr;
    }

    int mini = 1e9;

    // Find minimum among all ending columns
    for (int col = 0; col < m; col++)
    {
        mini = min(mini, prev[col]);
    }

    return mini;
}

int main()
{
    vector<vector<int>> matrix{{1, 2, 10, 4}, {100, 3, 2, 1}, {1, 1, 20, 2}, {1, 2, 2, 1}};

    cout << minFallingPathSum(matrix) << endl;

    return 0;
}
