// ==================================================
// PROBLEM
// - A frog starts at step 0 of an array 'heights' of size n and wants to reach step (n - 1).
// - From step i, the frog can jump to any step in the range [i + 1, min(i + k, n - 1)].
// - Each jump incurs an energy cost equal to |heights[i] - heights[j]|.
// - Return the minimum energy required to reach the last step.
// ==================================================

#include <bits/stdc++.h>
using namespace std;

// ==================================================
// BRUTE FORCE APPROACH — RECURSION
//
// Idea:
// - Express the problem recursively from target index (n - 1) down to index 0.
// - At index idx, evaluate all valid jumps from the preceding k steps (idx - 1 to idx - k).
// - Base case: At step 0, 0 energy is required since the frog starts there.
// - Compute and return the minimum energy across all possible jump origins.
//
// Time Complexity: O(k^n) - Each state branches into up to k recursive calls.
// Space Complexity: O(n) - Maximum depth of the recursive call stack.
// ==================================================

int helper(int idx, vector<int> &heights, int k)
{
    // Base case: Starting step requires 0 energy
    if (idx == 0)
        return 0;

    int minStepEnergy = INT_MAX;

    // Try all possible jump lengths from 1 to k
    for (int i = 1; i <= k; i++)
    {
        if (idx - i >= 0)
        {
            int stepEnergy = helper(idx - i, heights, k) + abs(heights[idx] - heights[idx - i]);
            minStepEnergy = min(minStepEnergy, stepEnergy);
        }
    }

    return minStepEnergy;
}

int frogJump(vector<int> &heights, int k)
{
    int n = heights.size();

    return helper(n - 1, heights, k);
}

// ==================================================
// BETTER APPROACH — MEMOIZATION (TOP-DOWN DP)
//
// Idea:
// - Avoid redundant subproblem computations by caching results in a DP array initialized to -1.
// - If the result for index idx has already been computed (dp[idx] != -1), return it directly.
// - Otherwise, iterate over all k previous steps, store the minimum energy in dp[idx], and return it.
//
// Time Complexity: O(n * k) - Each of the n states evaluates up to k transitions once.
// Space Complexity: O(n) - O(n) for the memoization array + O(n) for the recursion call stack.
// ==================================================

int helper(int idx, vector<int> &heights, int k, vector<int> &dp)
{
    // Base case: Starting position requires 0 energy
    if (idx == 0)
        return 0;

    // Return cached result if already computed
    if (dp[idx] != -1)
        return dp[idx];

    int minStepEnergy = INT_MAX;

    // Explore all valid previous k steps
    for (int i = 1; i <= k; i++)
    {
        if (idx - i >= 0)
        {
            int stepEnergy = helper(idx - i, heights, k, dp) + abs(heights[idx] - heights[idx - i]);
            minStepEnergy = min(minStepEnergy, stepEnergy);
        }
    }

    // Cache and return the minimum energy to reach step idx
    return dp[idx] = minStepEnergy;
}

int frogJump(vector<int> &heights, int k)
{
    int n = heights.size();

    // Table to memoize solutions from step 0 to (n - 1)
    vector<int> dp(n + 1, -1);

    return helper(n - 1, heights, k, dp);
}

// ==================================================
// BETTER APPROACH — TABULATION (BOTTOM-UP DP)
//
// Idea:
// - Iteratively compute the minimum energy for each step from 0 up to (n - 1).
// - Base case: dp[0] = 0 (no energy needed at step 0).
// - Transition state: For each step idx, dp[idx] = min(dp[idx - i] + |heights[idx] - heights[idx - i]|) for 1 <= i <= k.
//
// Time Complexity: O(n * k) - Outer loop runs n times, with an inner loop executing up to k times.
// Space Complexity: O(n) - 1D array of size n storing the minimum energy for each step.
// ==================================================

int frogJump(vector<int> &heights, int k)
{
    int n = heights.size();

    // dp[idx] stores the minimum energy required to reach step idx
    vector<int> dp(n, -1);

    // Base condition
    dp[0] = 0;

    // Iteratively compute minimum energy for every step from 1 to n - 1
    for (int idx = 1; idx < n; idx++)
    {
        int minStepEnergy = INT_MAX;

        for (int i = 1; i <= k; i++)
        {
            if (idx - i >= 0)
            {
                int stepEnergy = dp[idx - i] + abs(heights[idx] - heights[idx - i]);
                minStepEnergy = min(minStepEnergy, stepEnergy);
            }
        }

        dp[idx] = minStepEnergy;
    }

    return dp[n - 1];
}

// ==================================================
// OPTIMAL APPROACH — SPACE-OPTIMIZED DP (CIRCULAR BUFFER)
//
// Idea:
// - Computing dp[idx] only requires results from the preceding k steps.
// - Maintain a circular buffer of size k using modulo arithmetic: index idx maps to (idx % k).
// - Overwrite older states that are no longer reachable within a k-step window.
//
// Time Complexity: O(n * k) - Evaluates k transitions for each of the n steps.
// Space Complexity: O(k) - Circular DP array of size k storing only the most recent k states.
// ================================================== 

int frogJump(vector<int> &heights, int k)
{
    int n = heights.size();

    // Circular buffer of size k to store the most recent k DP states
    vector<int> dp(k, 0);

    for (int idx = 1; idx < n; idx++)
    {
        int minStepEnergy = INT_MAX;

        for (int i = 1; i <= k; i++)
        {
            if (idx - i >= 0)
            {
                // Map previous step index into the circular buffer
                int prevIdx = (idx - i) % k;

                int stepEnergy = dp[prevIdx] + abs(heights[idx] - heights[idx - i]);
                minStepEnergy = min(minStepEnergy, stepEnergy);
            }
        }

        // Overwrite the current step result into the circular buffer
        dp[idx % k] = minStepEnergy;
    }

    return dp[(n - 1) % k];
}

int main()
{
    vector<int> height{15, 4, 1, 14, 15};

    int k = 3;

    cout << "Minimum energy : " << frogJump(height, k) << endl;

    return 0;
}
