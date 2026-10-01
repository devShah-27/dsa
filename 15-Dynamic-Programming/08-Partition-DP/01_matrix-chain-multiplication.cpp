// ==================================================
// PROBLEM
// - Given a chain of matrices A1, A2, ..., An, find the best way to parenthesize the multiplication.
// - Array nums of size n defines matrix Ai (0 < i < n) with dimension nums[i - 1] x nums[i].
// - Return the minimum number of scalar multiplications needed to multiply the entire chain.
// ==================================================

#include <bits/stdc++.h>
using namespace std;

// ==================================================
// RECURSIVE APPROACH
//
// Idea:
// - Try every possible partition point k between matrices i and j.
// - Splitting at k creates two independent sub-chains: (i..k) and (k+1..j).
// - Cost of one split equals the cost of the two sub-chains plus the cost of multiplying their two resulting matrices.
// - Return the minimum cost found across all partition points.
//
// Time Complexity: O(2^n) - Exponential branching, since sub-chains are recomputed repeatedly.
// Space Complexity: O(n) - Auxiliary space required for the recursion stack.
// ==================================================

int helper(int i, int j, vector<int> &nums)
{
    // Base case: A single matrix needs no multiplication
    if (i == j)
        return 0;

    int minOprCount = 1e9;

    for (int k = i; k < j; k++)
    {
        // Cost of multiplying the two resulting matrices: (nums[i-1] x nums[k]) * (nums[k] x nums[j])
        int currOprCount = nums[i - 1] * nums[k] * nums[j];

        // Total cost = current multiplication + cost of the left and right sub-chains
        int totalOprCount = currOprCount + helper(i, k, nums) + helper(k + 1, j, nums);

        minOprCount = min(minOprCount, totalOprCount);
    }

    return minOprCount;
}

int matrixMultiplication(vector<int> &nums)
{
    int n = nums.size();

    // The chain contains matrices A1 to A(n-1)
    return helper(1, n - 1, nums);
}

// ==================================================
// RECURSION + MEMOIZATION (TOP-DOWN DP)
//
// Idea:
// - The recursive solution repeatedly solves the same sub-chains (i, j).
// - Cache each sub-chain result in a 2D table indexed by (i, j).
// - Return the stored answer immediately when a state is already solved.
// - Each state still tries every partition point k once.
//
// Time Complexity: O(n^3) - O(n^2) states, each iterating over O(n) partition points.
// Space Complexity: O(n^2) for DP table + O(n) for recursion stack.
// ==================================================

int helper(int i, int j, vector<int> &nums, vector<vector<int>> &dp)
{
    // Base case: A single matrix needs no multiplication
    if (i == j)
        return 0;

    // Return the stored result if this sub-chain is already solved
    if (dp[i][j] != -1)
        return dp[i][j];

    int minOprCount = 1e9;

    for (int k = i; k < j; k++)
    {
        // Cost of multiplying the two resulting matrices
        int currOprCount = nums[i - 1] * nums[k] * nums[j];

        // Total cost = current multiplication + cost of the left and right sub-chains
        int totalOprCount = currOprCount + helper(i, k, nums, dp) + helper(k + 1, j, nums, dp);

        minOprCount = min(minOprCount, totalOprCount);
    }

    // Cache the minimum cost before returning
    return dp[i][j] = minOprCount;
}

int matrixMultiplication(vector<int> &nums)
{
    int n = nums.size();

    // Initialize the DP table with -1 to indicate uncomputed states
    vector<vector<int>> dp(n, vector<int>(n, -1));

    return helper(1, n - 1, nums, dp);
}

// ==================================================
// TABULATION (BOTTOM-UP DP)
//
// Idea:
// - Convert the memoized recursion into iterative table filling.
// - State dp[i][j] stores the minimum cost to multiply matrices i..j.
// - Iterate i from bottom to top and j from left to right, so dp[i][k] and dp[k+1][j] are ready before use.
// - Single-matrix states (i == j) stay 0 from initialization.
//
// Time Complexity: O(n^3) - Three nested loops over i, j, and k.
// Space Complexity: O(n^2) - Memory allocated for the 2D DP matrix.
// ==================================================

int matrixMultiplication(vector<int> &nums)
{
    int n = nums.size();

    // Initialize with 0, which also covers the base case dp[i][i] = 0
    vector<vector<int>> dp(n, vector<int>(n, 0));

    // i moves from the last matrix down to the first
    for (int i = n - 1; i >= 1; i--)
    {
        // j starts at i + 1 because i == j is the base case
        for (int j = i + 1; j < n; j++)
        {
            int minOprCount = 1e9;

            // Try every partition point between i and j
            for (int k = i; k < j; k++)
            {
                // Cost of multiplying the two resulting matrices
                int currOprCount = nums[i - 1] * nums[k] * nums[j];

                // Total cost = current multiplication + cost of the left and right sub-chains
                int totalOprCount = currOprCount + dp[i][k] + dp[k + 1][j];

                minOprCount = min(minOprCount, totalOprCount);
            }

            dp[i][j] = minOprCount;
        }
    }

    // Answer for the full chain A1..A(n-1)
    return dp[1][n - 1];
}

int main()
{
    vector<int> arr = {10, 20, 30, 40, 50};

    cout << "The minimum number of operations is " << matrixMultiplication(arr);

    return 0;
}