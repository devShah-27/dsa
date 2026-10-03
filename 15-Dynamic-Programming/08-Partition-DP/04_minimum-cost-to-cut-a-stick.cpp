// ==================================================
// PROBLEM
// - Given a stick of length n and an array cuts of positions to cut at.
// - Cuts can be performed in any order.
// - The cost of one cut is the length of the stick being cut.
// - Return the minimum total cost of performing all the cuts.
// ==================================================

#include <bits/stdc++.h>
using namespace std;

// ==================================================
// RECURSIVE APPROACH
//
// Idea:
// - Pad cuts with 0 and n, so cuts[l] and cuts[r] mark the two ends of the current stick.
// - Try every cut idx between l and r as the first cut.
// - The first cut costs the full stick length cuts[r] - cuts[l].
// - This splits the stick into (l, idx) and (idx, r), which are solved independently.
// - Return the minimum total cost across all choices of idx.
//
// Time Complexity: O(2^m) roughly - Exponential branching, sub-sticks are recomputed (m = cuts.size() after padding).
// Space Complexity: O(m) - Auxiliary space required for the recursion stack.
// ==================================================

int helper(int l, int r, vector<int> &cuts)
{
    // Base case: No cut position exists strictly between l and r
    if (r - l < 2)
        return 0;

    int result = 1e9;

    // Try every cut between l and r as the first cut on this stick
    for (int idx = l + 1; idx <= r - 1; idx++)
    {
        // Cost of this cut = current stick length + cost of the left and right sub-sticks
        int cost = (cuts[r] - cuts[l]) +
                   helper(l, idx, cuts) +
                   helper(idx, r, cuts);

        result = min(result, cost);
    }

    return result;
}

int minCost(int n, vector<int> &cuts)
{
    // Pad both ends so the whole stick is represented as (0, m - 1)
    cuts.insert(cuts.begin(), 0);
    cuts.push_back(n);

    sort(cuts.begin(), cuts.end());

    int m = cuts.size();

    return helper(0, m - 1, cuts);
}

// ==================================================
// RECURSION + MEMOIZATION (TOP-DOWN DP)
//
// Idea:
// - The recursive solution repeatedly solves the same sub-sticks (l, r).
// - Cache each sub-stick result in a 2D table indexed by (l, r).
// - Return the stored answer immediately when a sub-stick is already solved.
// - Sort cuts after padding, so adjacent positions define valid sub-sticks.
//
// Time Complexity: O(m^3) - O(m^2) states, each iterating over O(m) cut choices.
// Space Complexity: O(m^2) for DP table + O(m) for recursion stack.
// ==================================================

int helper(int l, int r, vector<int> &cuts, vector<vector<int>> &dp)
{
    // Base case: No cut position exists strictly between l and r
    if (r - l < 2)
        return 0;

    // Return the stored result if this sub-stick is already solved
    if (dp[l][r] != -1)
        return dp[l][r];

    int result = 1e9;

    // Try every cut between l and r as the first cut on this stick
    for (int idx = l + 1; idx <= r - 1; idx++)
    {
        // Cost of this cut = current stick length + cost of the left and right sub-sticks
        int cost = (cuts[r] - cuts[l]) +
                   helper(l, idx, cuts, dp) +
                   helper(idx, r, cuts, dp);

        result = min(result, cost);
    }

    // Cache the minimum cost before returning
    return dp[l][r] = result;
}

int minCost(int n, vector<int> &cuts)
{
    // Pad both ends so the whole stick is represented as (0, m - 1)
    cuts.insert(cuts.begin(), 0);
    cuts.push_back(n);

    sort(cuts.begin(), cuts.end());

    int m = cuts.size();

    // Initialize the DP table with -1 to indicate uncomputed states
    vector<vector<int>> dp(m, vector<int>(m, -1));

    return helper(0, m - 1, cuts, dp);
}

// ==================================================
// TABULATION (BOTTOM-UP DP)
//
// Idea:
// - Convert the memoized recursion into iterative table filling.
// - State dp[l][r] stores the minimum cost to cut the stick (l, r).
// - Iterate l from bottom to top and r from left to right, so dp[l][idx] and dp[idx][r] are ready before use.
// - Sticks with no inner cut stay 0 from initialization.
//
// Time Complexity: O(m^3) - Three nested loops over l, r, and idx.
// Space Complexity: O(m^2) - Memory allocated for the 2D DP matrix.
// ==================================================

int minCost(int n, vector<int> &cuts)
{
    // Pad both ends so the whole stick is represented as (0, m - 1)
    cuts.insert(cuts.begin(), 0);
    cuts.push_back(n);

    sort(cuts.begin(), cuts.end());

    int m = cuts.size();

    // Initialize with 0, which also covers the base case of no inner cuts
    vector<vector<int>> dp(m, vector<int>(m, 0));

    // l moves from the last position down to the first
    for (int l = m - 1; l >= 0; l--)
    {
        for (int r = 0; r < m; r++)
        {
            // Skip invalid or trivial sticks, their value stays 0
            if (r - l < 2)
                continue;

            int result = 1e9;

            // Try every cut between l and r as the first cut on this stick
            for (int idx = l + 1; idx <= r - 1; idx++)
            {
                // Cost of this cut = current stick length + cost of the left and right sub-sticks
                int cost = (cuts[r] - cuts[l]) +
                           dp[l][idx] +
                           dp[idx][r];

                result = min(result, cost);
            }

            dp[l][r] = result;
        }
    }

    // Answer for the full stick from 0 to n
    return dp[0][m - 1];
}

int main()
{
    vector<int> cuts = {3, 5, 1, 4};

    int n = 7;

    cout << "The minimum cost incurred is: " << minCost(n, cuts) << endl;

    return 0;
}