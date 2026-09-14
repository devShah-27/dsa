// ==================================================
// PROBLEM
// - Given two integers m and n representing the dimensions of an m x n matrix.
// - A robot starts at the top-left cell (matrix[0][0]) and aims to reach the bottom-right cell (matrix[m-1][n-1]).
// - Movement is permitted only downward or rightward from any cell.
// - Return the total number of unique paths to reach the destination.
// ==================================================

#include <bits/stdc++.h>
using namespace std;

// ==================================================
// BRUTE FORCE APPROACH — RECURSION
//
// Idea:
// - Start at destination cell (m - 1, n - 1) and recursively navigate backward toward the origin (0, 0).
// - From cell (row, col), move either upward to (row - 1, col) or leftward to (row, col - 1).
// - Base cases: Return 1 when cell (0, 0) is reached, and 0 for any out-of-bounds coordinates.
// - The total number of paths equals the sum of valid paths coming from the top and left cells.
//
// Time Complexity: O(2^(m + n)) - Exponential exploration of all path combinations.
// Space Complexity: O(m + n) - Maximum depth of the recursive call stack.
// ==================================================

int helper(int row, int col)
{
    // Base case: Successfully reached the start cell
    if (row == 0 && col == 0)
        return 1;

    // Base case: Out-of-bounds boundary check
    if (row < 0 || col < 0)
        return 0;

    // Explore path from the cell directly above
    int up = helper(row - 1, col);

    // Explore path from the cell directly to the left
    int left = helper(row, col - 1);

    return (up + left);
}

int uniquePaths(int m, int n)
{
    return helper(m - 1, n - 1);
}

// ==================================================
// BETTER APPROACH — MEMOIZATION (TOP-DOWN DP)
//
// Idea:
// - Store computed results in a 2D DP table of size m x n initialized to -1.
// - If state dp[row][col] has already been calculated, return it directly to avoid duplicate recursion.
// - Recursively compute the sum of paths from (row - 1, col) and (row, col - 1), cache it, and return.
//
// Time Complexity: O(m * n) - Each unique cell state (row, col) is evaluated and memoized once.
// Space Complexity: O(m * n) + O(m + n) = O(m * n) - 2D DP table plus recursion call stack depth.
// ==================================================

int helper(int row, int col, vector<vector<int>> &dp)
{
    // Base cases
    if (row == 0 && col == 0)
        return 1;

    if (row < 0 || col < 0)
        return 0;

    // Return cached result if already computed
    if (dp[row][col] != -1)
        return dp[row][col];

    int up = helper(row - 1, col, dp);

    int left = helper(row, col - 1, dp);

    // Cache and return total unique paths to (row, col)
    return dp[row][col] = (up + left);
}

int uniquePaths(int m, int n)
{
    // DP table to memoize solutions for all cells
    vector<vector<int>> dp(m, vector<int>(n, -1));

    return helper(m - 1, n - 1, dp);
}

// ==================================================
// BETTER APPROACH — TABULATION (BOTTOM-UP DP)
//
// Idea:
// - Iteratively compute the total unique paths to each cell from (0, 0) up to (m - 1, n - 1).
// - Base case: dp[0][0] = 1 (1 way to be at the starting point).
// - State transition: dp[row][col] = (row > 0 ? dp[row - 1][col] : 0) + (col > 0 ? dp[row][col - 1] : 0).
//
// Time Complexity: O(m * n) - Nested loops traversing every cell in the m x n grid.
// Space Complexity: O(m * n) - 2D array of size m x n to store intermediate path counts.
// ==================================================

int uniquePaths(int m, int n)
{
    // dp[row][col] stores total unique paths from (0, 0) to (row, col)
    vector<vector<int>> dp(m, vector<int>(n, -1));

    // Base condition
    dp[0][0] = 1;

    // Iteratively build table from top-left to bottom-right
    for (int row = 0; row < m; row++)
    {
        for (int col = 0; col < n; col++)
        {
            if (row == 0 && col == 0)
                continue;

            int up = row > 0 ? dp[row - 1][col] : 0;

            int left = col > 0 ? dp[row][col - 1] : 0;

            dp[row][col] = up + left;
        }
    }

    return dp[m - 1][n - 1];
}

// ==================================================
// OPTIMAL APPROACH — SPACE-OPTIMIZED DP
//
// Idea:
// - Computing paths for the current row depends only on the previous row's state and the current row's left cell.
// - Maintain a 1D vector 'dp' representing the previous row and 'temp' representing the current row.
// - Update 'dp = temp' after completing each row to achieve O(n) auxiliary space.
//
// Time Complexity: O(m * n) - Linear iteration over all m rows and n columns.
// Space Complexity: O(n) - Two 1D vectors of size n for row-level state tracking.
// ==================================================

int uniquePaths(int m, int n)
{
    // Stores path counts for the previous row
    vector<int> dp(n, -1);

    for (int row = 0; row < m; row++)
    {
        // Stores path counts for the current row
        vector<int> temp(n, -1);

        for (int col = 0; col < n; col++)
        {
            if (row == 0 && col == 0)
            {
                temp[col] = 1;
            }
            else
            {
                int up = row > 0 ? dp[col] : 0;

                int left = col > 0 ? temp[col - 1] : 0;

                temp[col] = up + left;
            }
        }

        // Slide the row state down
        dp = temp;
    }

    return dp[n - 1];
}

int main()
{
    int m = 3;
    int n = 2;

    cout << "Number of ways: " << uniquePaths(m, n) << endl;

    return 0;
}
