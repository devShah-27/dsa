// ==================================================
// PROBLEM
// - Two robots start at top-left and top-right of a matrix and move downwards.
// - If both land on the same cell, they pick its cherries only once.
// - Find the maximum total cherries both robots can collect reaching the bottom.
// ==================================================

#include <bits/stdc++.h>
using namespace std;

// ==================================================
// RECURSIVE APPROACH
//
// Idea:
// - Simulate all possible move combinations for both robots simultaneously.
// - From each cell, a robot can take three downward moves.
// - If both land on the same cell, add cherries once.
// - Recursively maximize the sum of cherries collected from paths.
//
// Time Complexity: O(3^n * 3^n) - Each robot makes 3 choices per row step.
// Space Complexity: O(n) - Auxiliary recursion stack space for n rows.
// ==================================================

int helper(int row, int r1Col, int r2Col, int n, int m, vector<vector<int>> &matrix)
{
    // Base case: If either robot steps outside the grid boundaries
    if (r1Col < 0 || r1Col >= m || r2Col < 0 || r2Col >= m)
        return 0;

    // Base case: Both robots have reached the final row
    if (row == n - 1)
    {
        // If they land on the same cell, collect cherries only once
        if (r1Col == r2Col)
            return matrix[row][r1Col];
        else
            return matrix[row][r1Col] + matrix[row][r2Col];
    }

    int maxSum = INT_MIN;

    // Robot 1 explores all 3 possible downward directions (left-diag, straight, right-diag)
    for (int delCol1 = -1; delCol1 <= 1; delCol1++)
    {
        // Robot 2 explores all 3 possible downward directions simultaneously
        for (int delCol2 = -1; delCol2 <= 1; delCol2++)
        {
            // Collect Robot 1's current cell and recursively calculate the future path
            int currMaxSum = matrix[row][r1Col] + helper(row + 1, r1Col + delCol1, r2Col + delCol2, n, m, matrix);

            // Add Robot 2's current cell cherries if they are on different cells
            if (r1Col != r2Col)
                currMaxSum += matrix[row][r2Col];

            // Update the maximum possible cherries for the current state
            maxSum = max(maxSum, currMaxSum);
        }
    }

    return maxSum;
}

int cherryPickup(vector<vector<int>> &matrix)
{
    int n = matrix.size(), m = matrix[0].size();

    // Start from row 0: Robot 1 at top-left (0), Robot 2 at top-right (m-1)
    return helper(0, 0, m - 1, n, m, matrix);
}

// ==================================================
// RECURSION + MEMOIZATION (TOP-DOWN DP)
//
// Idea:
// - Store results of overlapping subproblems in a 3D DP array.
// - The state is defined by the current row and both columns.
// - If a state has been computed, return the cached value.
// - This prunes the recursion tree and avoids redundant calculations.
//
// Time Complexity: O(n * m * m * 9) - Total unique states times 9 transitions.
// Space Complexity: O(n * m * m) for DP array + O(n) for recursion stack.
// ==================================================

int helper(int row, int r1Col, int r2Col, int n, int m,
           vector<vector<int>> &matrix,
           vector<vector<vector<int>>> &dp)
{
    // Base case: Out of bounds check
    if (r1Col < 0 || r1Col >= m || r2Col < 0 || r2Col >= m)
        return 0;

    // Return the cached result if this state has already been computed
    if (dp[row][r1Col][r2Col] != -1)
        return dp[row][r1Col][r2Col];

    // Base case: Reached the last row
    if (row == n - 1)
    {
        if (r1Col == r2Col)
            return matrix[row][r1Col];
        else
            return matrix[row][r1Col] + matrix[row][r2Col];
    }

    int maxSum = INT_MIN;

    // Explore all 9 combinations of moves for Robot 1 and Robot 2
    for (int delCol1 = -1; delCol1 <= 1; delCol1++)
    {
        for (int delCol2 = -1; delCol2 <= 1; delCol2++)
        {
            int currMaxSum = matrix[row][r1Col] + helper(row + 1, r1Col + delCol1, r2Col + delCol2, n, m, matrix, dp);

            if (r1Col != r2Col)
                currMaxSum += matrix[row][r2Col];

            maxSum = max(maxSum, currMaxSum);
        }
    }

    // Save the computed maximum to the DP table before returning
    return dp[row][r1Col][r2Col] = maxSum;
}

int cherryPickup(vector<vector<int>> &matrix)
{
    int n = matrix.size(), m = matrix[0].size();

    // Initialize a 3D DP table with -1 to indicate uncomputed states
    vector<vector<vector<int>>> dp(n, vector<vector<int>>(m, vector<int>(m, -1)));

    return helper(0, 0, m - 1, n, m, matrix, dp);
}

// ==================================================
// TABULATION (BOTTOM-UP DP)
//
// Idea:
// - Build a 3D DP table starting from the bottom row.
// - Iteratively compute max cherries for each state moving upwards.
// - Calculate transitions for all 9 combinations of downward moves.
// - Eliminates recursion stack overhead while preserving valid state transitions.
//
// Time Complexity: O(n * m * m * 9) - 3 nested loops and 9 transitions.
// Space Complexity: O(n * m * m) - For storing the 3D DP table.
// ==================================================

int cherryPickup(vector<vector<int>> &matrix)
{
    int n = matrix.size(), m = matrix[0].size();

    // DP table storing the maximum cherries from (row) down to the bottom
    vector<vector<vector<int>>> dp(n, vector<vector<int>>(m, vector<int>(m, -1)));

    // Base case initialization for the last row
    for (int r1Col = 0; r1Col < m; r1Col++)
    {
        for (int r2Col = 0; r2Col < m; r2Col++)
        {
            dp[n - 1][r1Col][r2Col] = matrix[n - 1][r1Col];

            // Add cherries for Robot 2 only if it is on a different cell
            if (r1Col != r2Col)
                dp[n - 1][r1Col][r2Col] += matrix[n - 1][r2Col];
        }
    }

    // Process from the second-to-last row upwards to the first row
    for (int row = n - 2; row >= 0; row--)
    {
        for (int r1Col = 0; r1Col < m; r1Col++)
        {
            for (int r2Col = 0; r2Col < m; r2Col++)
            {
                int maxSum = INT_MIN;

                // Try all 9 possible transition pairs from the row below
                for (int delCol1 = -1; delCol1 <= 1; delCol1++)
                {
                    for (int delCol2 = -1; delCol2 <= 1; delCol2++)
                    {
                        // Use a highly negative baseline to disregard out-of-bound paths
                        int currMaxSum = -1e8;

                        // Ensure both robots' next moves stay within grid limits
                        if (r1Col + delCol1 >= 0 &&
                            r1Col + delCol1 < m &&
                            r2Col + delCol2 >= 0 &&
                            r2Col + delCol2 < m)
                        {
                            // Add current cell(s) cherries to the best path from the row below
                            currMaxSum = matrix[row][r1Col] + dp[row + 1][r1Col + delCol1][r2Col + delCol2];

                            if (r1Col != r2Col)
                                currMaxSum += matrix[row][r2Col];
                        }

                        maxSum = max(maxSum, currMaxSum);

                        // Store the maximum found for this state
                        dp[row][r1Col][r2Col] = maxSum;
                    }
                }
            }
        }
    }

    // Return the result starting from the initial positions at row 0
    return dp[0][0][m - 1];
}

// ==================================================
// SPACE OPTIMIZED DP
//
// Idea:
// - The current row only depends on the immediate next row.
// - Replace the 3D DP array with two 2D arrays.
// - Keep track of previous row results to compute current row.
// - Reduces memory usage while maintaining the optimal time complexity.
//
// Time Complexity: O(n * m * m * 9) - Same state transitions as tabulation.
// Space Complexity: O(m * m) - Uses two 2D arrays of size m x m.
// ==================================================

int cherryPickup(vector<vector<int>> &matrix)
{
    int n = matrix.size(), m = matrix[0].size();

    // prev array holds the optimal results for the row directly below the current one
    vector<vector<int>> prev(m, vector<int>(m, 0));

    // Base case initialization for the last row
    for (int r1Col = 0; r1Col < m; r1Col++)
    {
        for (int r2Col = 0; r2Col < m; r2Col++)
        {
            prev[r1Col][r2Col] = matrix[n - 1][r1Col];

            if (r1Col != r2Col)
                prev[r1Col][r2Col] += matrix[n - 1][r2Col];
        }
    }

    // Traverse upwards from the second-to-last row
    for (int row = n - 2; row >= 0; row--)
    {
        // curr array builds the optimal results for the current row
        vector<vector<int>> curr(m, vector<int>(m, 0));

        for (int r1Col = 0; r1Col < m; r1Col++)
        {
            for (int r2Col = 0; r2Col < m; r2Col++)
            {
                int maxSum = INT_MIN;

                for (int delCol1 = -1; delCol1 <= 1; delCol1++)
                {
                    for (int delCol2 = -1; delCol2 <= 1; delCol2++)
                    {
                        int currMaxSum = -1e8;

                        if (r1Col + delCol1 >= 0 &&
                            r1Col + delCol1 < m &&
                            r2Col + delCol2 >= 0 &&
                            r2Col + delCol2 < m)
                        {
                            // Retrieve the overlapping subproblem result from the 'prev' array
                            currMaxSum = matrix[row][r1Col] + prev[r1Col + delCol1][r2Col + delCol2];

                            if (r1Col != r2Col)
                                currMaxSum += matrix[row][r2Col];
                        }

                        maxSum = max(maxSum, currMaxSum);

                        curr[r1Col][r2Col] = maxSum;
                    }
                }
            }
        }

        // Shift current row results into 'prev' for the next iteration step upwards
        prev = curr;
    }

    // Final answer is stored in 'prev' representing row 0
    return prev[0][m - 1];
}

int main()
{
    vector<vector<int>> matrix{
        {2, 3, 1, 2},
        {3, 4, 2, 2},
        {5, 6, 3, 5},
    };

    cout << cherryPickup(matrix);

    return 0;
}
