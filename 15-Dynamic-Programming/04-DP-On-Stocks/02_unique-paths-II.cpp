// ==================================================
// PROBLEM
// - Given an m x n binary matrix where 1 denotes an obstacle and 0 denotes an open cell.
// - A robot starts at matrix[0][0] and moves to matrix[m-1][n-1].
// - Movement is allowed only downward or rightward from any non-blocked cell.
// - Return total unique paths to reach the bottom-right cell without obstacles.
// ==================================================

#include <bits/stdc++.h>
using namespace std;

// ==================================================
// BRUTE FORCE APPROACH — RECURSION
//
// Idea:
// - Start from destination (m - 1, n - 1) and recursively move toward (0, 0).
// - At cell (row, col), return 0 if out of bounds or blocked.
// - Base case: Return 1 when successfully reaching the start cell (0, 0).
// - Sum valid paths coming from the cell above and the left cell.
//
// Time Complexity: O(2^(m + n)) - Branches exponentially across all possible recursive path choices.
// Space Complexity: O(m + n) - Maximum depth of the recursive call stack.
// ==================================================

int helper(int row, int col, vector<vector<int>> &matrix)
{
    // Base case: Out of bounds or current cell contains an obstacle
    if (row < 0 || col < 0 || matrix[row][col] == 1)
        return 0;

    // Base case: Successfully reached the starting cell (0, 0)
    if (row == 0 && col == 0)
        return 1;

    // Explore path from the cell directly above the current position
    int up = helper(row - 1, col, matrix);

    // Explore path from the cell directly left of the current position
    int left = helper(row, col - 1, matrix);

    return (up + left);
}

int uniquePathsWithObstacles(vector<vector<int>> &matrix)
{
    int m = matrix.size(), n = matrix[0].size();

    return helper(m - 1, n - 1, matrix);
}

// ==================================================
// BETTER APPROACH — MEMOIZATION (TOP-DOWN DP)
//
// Idea:
// - Store computed subproblem results in a 2D DP table initialized to -1.
// - If state dp[row][col] is already computed, return it immediately.
// - Return 0 for invalid bounds or cells containing an obstacle.
// - Recursively evaluate transitions, cache their sum, and return the optimal count.
//
// Time Complexity: O(m * n) - Each state is evaluated and cached exactly once.
// Space Complexity: O(m * n) + O(m + n) = O(m * n) - For the DP table and recursion stack.
// ==================================================

int helper(int row, int col, vector<vector<int>> &matrix, vector<vector<int>> &dp)
{
    // Return 0 if out of bounds or on an obstacle cell
    if (row < 0 || col < 0 || matrix[row][col] == 1)
        return 0;

    // Base case: Reached start cell
    if (row == 0 && col == 0)
        return 1;

    // Return cached result if already computed for this grid cell
    if (dp[row][col] != -1)
        return dp[row][col];

    int up = helper(row - 1, col, matrix, dp);

    int left = helper(row, col - 1, matrix, dp);

    // Cache and return total unique paths to cell (row, col)
    return dp[row][col] = (up + left);
}

int uniquePathsWithObstacles(vector<vector<int>> &matrix)
{
    int m = matrix.size(), n = matrix[0].size();

    // Table to memoize solutions for all grid cells from (0, 0)
    vector<vector<int>> dp(m, vector<int>(n, -1));

    return helper(m - 1, n - 1, matrix, dp);
}

// ==================================================
// BETTER APPROACH — TABULATION (BOTTOM-UP DP)
//
// Idea:
// - Iteratively compute unique paths to each cell from (0, 0) upward.
// - Set dp[row][col] = 0 if matrix[row][col] is an obstacle.
// - Initialize base condition dp[0][0] = 1 if starting cell is open.
// - Transition: dp[row][col] = (up paths) + (left paths) for valid open cells.
//
// Time Complexity: O(m * n) - Nested loops traversing every cell in the grid.
// Space Complexity: O(m * n) - 2D array storing intermediate cell path counts.
// ==================================================

int uniquePathsWithObstacles(vector<vector<int>> &matrix)
{
    int m = matrix.size(), n = matrix[0].size();

    // dp[row][col] stores unique paths from (0, 0) to (row, col)
    vector<vector<int>> dp(m, vector<int>(n, -1));

    for (int row = 0; row < m; row++)
    {
        for (int col = 0; col < n; col++)
        {
            // Obstacle cells cannot be traversed
            if (matrix[row][col] == 1)
            {
                dp[row][col] = 0;
            }
            // Base condition for starting cell
            else if (row == 0 && col == 0)
            {
                dp[row][col] = 1;
            }
            else
            {
                int up = row > 0 ? dp[row - 1][col] : 0;

                int left = col > 0 ? dp[row][col - 1] : 0;

                dp[row][col] = up + left;
            }
        }
    }

    return dp[m - 1][n - 1];
}

// ==================================================
// OPTIMAL APPROACH — SPACE-OPTIMIZED DP
//
// Idea:
// - Computing current row cells depends only on previous and current row values.
// - Maintain 1D vector 'prev' for previous row and 'cur' for current.
// - Handle obstacle cells by resetting cur[col] to 0 during iteration.
// - Slide the state forward by setting prev = cur after each row.
//
// Time Complexity: O(m * n) - Linear iteration across all m rows and n columns.
// Space Complexity: O(n) - Two 1D vectors of size n for rows.
// ==================================================

int uniquePathsWithObstacles(vector<vector<int>> &matrix)
{
    int m = matrix.size(), n = matrix[0].size();

    // Stores path counts for the previous row of the grid
    vector<int> prev(n, -1);

    for (int row = 0; row < m; row++)
    {
        // Stores path counts for the current row of the grid
        vector<int> cur(n, -1);

        for (int col = 0; col < n; col++)
        {
            // Blocked cell has zero paths
            if (matrix[row][col] == 1)
            {
                cur[col] = 0;
            }
            // Base condition for top-left cell
            else if (row == 0 && col == 0)
            {
                cur[col] = 1;
            }
            else
            {
                int up = row > 0 ? prev[col] : 0;

                int left = col > 0 ? cur[col - 1] : 0;

                cur[col] = up + left;
            }
        }

        // Slide the row state downward
        prev = cur;
    }

    return prev[n - 1];
}

int main()
{
    vector<vector<int>> maze{
        {0, 0, 0},
        {0, 1, 0},
        {0, 0, 0}};

    cout << "Number of paths with obstacles: " << uniquePathsWithObstacles(maze) << endl;

    return 0;
}
