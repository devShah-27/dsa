// ==================================================
// PROBLEM
// - Given a 2D integer array 'triangle' with n rows.
// - The first row has 1 element, and each subsequent row has one additional element.
// - Find the minimum path sum from the apex (0, 0) to the bottom row.
// - Allowed moves from cell (row, col) are to (row + 1, col) or (row + 1, col + 1).
// ==================================================

#include <bits/stdc++.h>
using namespace std;

// ==================================================
// BRUTE FORCE APPROACH — RECURSION
//
// Idea:
// - Start at the top cell (0, 0) and explore both valid moves recursively.
// - From cell (row, col), move to either (row + 1, col) or (row + 1, col + 1).
// - Base case: When reaching the last row, return the value triangle[row][col].
// - Return the minimum path sum between the two possible paths.
//
// Time Complexity: O(2^n) - Each cell branches into two recursive calls down to depth n.
// Space Complexity: O(n) - Maximum depth of the recursive call stack.
// ==================================================

int helper(int row, int col, int n, vector<vector<int>> &triangle)
{
    // Base case: Reached the bottom row
    if (row == n - 1)
        return triangle[row][col];

    // Transition 1: Move to directly bottom cell
    int bottom = triangle[row][col] + helper(row + 1, col, n, triangle);

    // Transition 2: Move to bottom-right adjacent cell
    int bottom_right = triangle[row][col] + helper(row + 1, col + 1, n, triangle);

    return min(bottom, bottom_right);
}

int minTriangleSum(vector<vector<int>> &triangle)
{
    int n = triangle.size();

    return helper(0, 0, n, triangle);
}

// ==================================================
// BETTER APPROACH — MEMOIZATION (TOP-DOWN DP)
//
// Idea:
// - Optimize recursion by caching results in a 2D DP array initialized to -1.
// - If the subproblem state for (row, col) is already calculated, return it directly.
// - Recursively evaluate bottom and bottom-right transitions, memoize the minimum sum, and return.
//
// Time Complexity: O(n^2) - Total of n*(n + 1)/2 unique states, each evaluated once.
// Space Complexity: O(n^2) - O(n^2) for the memoization table plus O(n) recursion call stack depth.
// ==================================================

int helper(int row, int col, int n, vector<vector<int>> &triangle, vector<vector<int>> &dp)
{
    // Base case: Reached the bottom row
    if (row == n - 1)
        return triangle[row][col];

    // Return cached result if already computed
    if (dp[row][col] != INT_MAX)
        return dp[row][col];

    int bottom = triangle[row][col] + helper(row + 1, col, n, triangle, dp);

    int bottom_right = triangle[row][col] + helper(row + 1, col + 1, n, triangle, dp);

    // Cache and return optimal minimum sum
    return dp[row][col] = min(bottom, bottom_right);
}

int minTriangleSum(vector<vector<int>> &triangle)
{
    int n = triangle.size();

    // Table to memoize solutions for all triangle cells
    vector<vector<int>> dp(n, vector<int>(n, INT_MAX));

    return helper(0, 0, n, triangle, dp);
}

// ==================================================
// BETTER APPROACH — TABULATION (BOTTOM-UP DP)
//
// Idea:
// - Iteratively compute path sums in bottom-up fashion from row (n - 2) to 0.
// - Base condition: Initialize dp[n - 1][col] with the values of the last row.
// - State transition: dp[row][col] = triangle[row][col] + min(dp[row + 1][col], dp[row + 1][col + 1]).
// - The final minimum sum is stored in the apex cell dp[0][0].
//
// Time Complexity: O(n^2) - Nested loops traversing all n*(n + 1)/2 cells in the triangle.
// Space Complexity: O(n^2) - 2D table of size n x n to store intermediate states.
// ==================================================

int minTriangleSum(vector<vector<int>> &triangle)
{
    int n = triangle.size();

    // dp[row][col] stores minimum path sum from (row, col) to the bottom row
    vector<vector<int>> dp(n, vector<int>(n, 0));

    // Base condition: Initialize bottom row states
    for (int col = 0; col < n; col++)
    {
        dp[n - 1][col] = triangle[n - 1][col];
    }

    // Iteratively build the solution upward to the top cell
    for (int row = n - 2; row >= 0; row--)
    {
        for (int col = 0; col <= row; col++)
        {
            int bottom = triangle[row][col] + dp[row + 1][col];

            int bottom_right = triangle[row][col] + dp[row + 1][col + 1];

            dp[row][col] = min(bottom, bottom_right);
        }
    }

    return dp[0][0];
}

// ==================================================
// OPTIMAL APPROACH — SPACE-OPTIMIZED DP
//
// Idea:
// - Notice that computing states for row depends only on row (row + 1).
// - Maintain a 1D vector 'prev' representing the bottom row's state.
// - Iteratively update 'curr' for the current row and set 'prev = curr'.
// - The final minimum path sum is stored in prev[0].
//
// Time Complexity: O(n^2) - Evaluates transitions for all n*(n + 1)/2 elements.
// Space Complexity: O(n) - Uses two 1D vectors of size n for row-level state transitions.
// ==================================================

int minTriangleSum(vector<vector<int>> &triangle)
{
    int n = triangle.size();

    // Stores path sums for the row directly below
    vector<int> prev(n, 0);

    // Initialize base values for the bottom row
    for (int col = 0; col < n; col++)
    {
        prev[col] = triangle[n - 1][col];
    }

    // Iteratively compute minimum sums upward
    for (int row = n - 2; row >= 0; row--)
    {
        vector<int> curr(n, 0);

        for (int col = 0; col <= row; col++)
        {
            int bottom = triangle[row][col] + prev[col];

            int bottom_right = triangle[row][col] + prev[col + 1];

            curr[col] = min(bottom, bottom_right);
        }

        // Slide current row values to previous
        prev = curr;
    }

    return prev[0];
}

int main()
{
    vector<vector<int>> triangle = {{3},
                                    {-1, 3},
                                    {-3, 2, 4},
                                    {8, 8, 1, -4}};

    cout << minTriangleSum(triangle);

    return 0;
}
