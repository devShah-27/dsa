// ==================================================
// PROBLEM
// - A ninja plans an n-day training schedule choosing one of three activities each day: running (0), stealth (1), or fighting (2).
// - The same activity cannot be performed on two consecutive days.
// - Given an n x 3 matrix where matrix[i][j] represents merit points earned on day i for activity j.
// - Return the maximum possible merit points the ninja can earn over n days.
// ==================================================

#include <bits/stdc++.h>
using namespace std;

// ==================================================
// BRUTE FORCE APPROACH — RECURSION
//
// Idea:
// - Recursively evaluate the maximum points achievable from day (n - 1) down to day 0.
// - For any given day, iterate through all three tasks and pick those that differ from 'lastTask'.
// - Transition: Add matrix[day][currTask] to the result of helper(day - 1, currTask).
// - Start the recursion from day (n - 1) with lastTask = 3 (representing no prior constraint).
//
// Time Complexity: O(3 * 2^(n-1)) = O(2^n) - Day (n - 1) has 3 branches; each preceding day branches into 2 choices.
// Space Complexity: O(n) - Maximum depth of the recursive call stack.
// ==================================================

int helper(int day, int lastTask, vector<vector<int>> &matrix)
{
    int maxPts = 0;

    // Explore all 3 possible tasks for the current day
    for (int currTask = 0; currTask < 3; currTask++)
    {
        // Avoid performing the same task as the consecutive day
        if (currTask != lastTask)
        {
            int currPts = matrix[day][currTask];

            // Recursively solve for the preceding days
            if (day > 0)
                currPts += helper(day - 1, currTask, matrix);

            maxPts = max(maxPts, currPts);
        }
    }

    return maxPts;
}

int ninjaTraining(vector<vector<int>> &matrix)
{
    int n = matrix.size();

    // 3 denotes that no task was performed on the subsequent day
    return helper(n - 1, 3, matrix);
}

// ==================================================
// BETTER APPROACH — MEMOIZATION (TOP-DOWN DP)
//
// Idea:
// - Optimize recursion by caching results in a 2D DP array: dp[day][lastTask].
// - 'day' ranges from 0 to (n - 1) and 'lastTask' ranges from 0 to 3 (3 represents no previous constraint).
// - If dp[day][lastTask] is already computed (!= -1), return the cached value to prevent redundant recursion.
//
// Time Complexity: O(n * 4 * 3) = O(n) - There are (n * 4) unique states, each evaluated in O(3) constant time.
// Space Complexity: O(n * 4) + O(n) = O(n) - For the 2D memoization table and the recursion call stack.
// ==================================================

int helper(int day, int lastTask, vector<vector<int>> &matrix, vector<vector<int>> &dp)
{
    // Return cached result if already computed
    if (dp[day][lastTask] != -1)
        return dp[day][lastTask];

    int maxPts = 0;

    // Try all valid task choices
    for (int currTask = 0; currTask < 3; currTask++)
    {
        if (currTask != lastTask)
        {
            int currPts = matrix[day][currTask];

            if (day > 0)
                currPts += helper(day - 1, currTask, matrix, dp);

            maxPts = max(maxPts, currPts);
        }
    }

    // Memoize and return the maximum points for state (day, lastTask)
    return dp[day][lastTask] = maxPts;
}

int ninjaTraining(vector<vector<int>> &matrix)
{
    int n = matrix.size();

    // dp[n][4] initialized to -1 to store states for all days and lastTask values
    vector<vector<int>> dp(n, vector<int>(4, -1));

    return helper(n - 1, 3, matrix, dp);
}

// ==================================================
// BETTER APPROACH — TABULATION (BOTTOM-UP DP)
//
// Idea:
// - Construct a 2D table dp[n][4] iteratively from day 0 up to day (n - 1).
// - Base case (day 0): dp[0][lastTask] stores the maximum point among all tasks where currTask != lastTask.
// - Transition for day 1 to n - 1: dp[day][lastTask] = max(matrix[day][currTask] + dp[day - 1][currTask]).
// - The final answer is stored in dp[n - 1][3].
//
// Time Complexity: O(n * 4 * 3) = O(n) - Nested loops for n days, 4 lastTask states, and 3 currTask options.
// Space Complexity: O(n * 4) = O(n) - 2D table of size n x 4 to store all intermediate states.
// ==================================================

int ninjaTraining(vector<vector<int>> &matrix)
{
    int n = matrix.size();

    vector<vector<int>> dp(n, vector<int>(4, -1));

    // Base condition for day 0 across all possible lastTask constraints
    for (int lastTask = 0; lastTask < 4; lastTask++)
    {
        for (int currTask = 0; currTask < 3; currTask++)
        {
            if (currTask != lastTask)
            {
                dp[0][lastTask] = max(dp[0][lastTask], matrix[0][currTask]);
            }
        }
    }

    // Iteratively build the DP table for subsequent days
    for (int day = 1; day < n; day++)
    {
        for (int lastTask = 0; lastTask < 4; lastTask++)
        {
            for (int currTask = 0; currTask < 3; currTask++)
            {
                if (currTask != lastTask)
                {
                    int currPts = matrix[day][currTask] + dp[day - 1][currTask];
                    dp[day][lastTask] = max(dp[day][lastTask], currPts);
                }
            }
        }
    }

    return dp[n - 1][3];
}

// ==================================================
// OPTIMAL APPROACH — SPACE-OPTIMIZED DP
//
// Idea:
// - Computing states for the current day requires only the DP values of the immediate previous day.
// - Replace the 2D DP table with a 1D array 'prev' of size 4.
// - For each day, compute state values in a temporary array 'temp' of size 4 and update 'prev = temp'.
// - The answer for the full schedule is stored in prev[3].
//
// Time Complexity: O(n * 4 * 3) = O(n) - Evaluates fixed transitions for each of the n days.
// Space Complexity: O(1) - Constant auxiliary space using fixed-size arrays of length 4.
// ==================================================

int ninjaTraining(vector<vector<int>> &matrix)
{
    int n = matrix.size();

    // Stores DP results of the previous day for each lastTask constraint (0 to 3)
    vector<int> prev(4, -1);

    // Initialize base values for day 0
    for (int lastTask = 0; lastTask < 4; lastTask++)
    {
        for (int currTask = 0; currTask < 3; currTask++)
        {
            if (currTask != lastTask)
            {
                prev[lastTask] = max(prev[lastTask], matrix[0][currTask]);
            }
        }
    }

    // Process remaining days by sliding the DP state vector forward
    for (int day = 1; day < n; day++)
    {
        vector<int> temp(4, -1);

        for (int lastTask = 0; lastTask < 4; lastTask++)
        {
            for (int currTask = 0; currTask < 3; currTask++)
            {
                if (currTask != lastTask)
                {
                    int currPts = matrix[day][currTask] + prev[currTask];
                    temp[lastTask] = max(temp[lastTask], currPts);
                }
            }
        }

        prev = temp;
    }

    return prev[3];
}

int main()
{
    vector<vector<int>> points = {
        {73, 12, 91},
        {44, 86, 27},
        {95, 31, 68},
        {17, 79, 53},
        {62, 24, 88},
        {39, 97, 14},
        {81, 45, 72},
        {26, 63, 99},
        {58, 11, 76},
        {92, 54, 33},

        {21, 89, 47},
        {67, 35, 94},
        {13, 76, 52},
        {84, 29, 61},
        {48, 93, 18},
        {71, 42, 87},
        {34, 68, 25},
        {99, 16, 57},
        {53, 82, 39},
        {28, 74, 96},

        {86, 37, 64},
        {15, 91, 43},
        {77, 28, 85},
        {41, 69, 12},
        {93, 55, 31},
        {36, 98, 67},
        {64, 23, 89},
        {19, 72, 46},
        {88, 34, 79},
        {52, 95, 17},

        {31, 61, 90},
        {79, 18, 54},
        {46, 87, 22},
        {97, 43, 71},
        {24, 66, 93},
        {68, 15, 82},
        {37, 99, 29},
        {83, 52, 11},
        {14, 78, 65},
        {91, 26, 48},

        {55, 84, 32},
        {23, 49, 97},
        {74, 13, 86},
        {42, 96, 35},
        {89, 57, 21},
        {16, 73, 92},
        {61, 38, 98},
        {35, 94, 44},
        {98, 27, 63},
        {47, 81, 19}};

    cout << ninjaTraining(points) << '\n';

    return 0;
}