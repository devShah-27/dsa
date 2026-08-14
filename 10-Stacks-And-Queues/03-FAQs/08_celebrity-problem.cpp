// Problem:
// Given an N x N matrix where M[i][j] = 1 means person i knows person j, find the celebrity: a person known by everyone but who knows nobody.
// Return the celebrity's index, or -1 if no celebrity exists.

#include <bits/stdc++.h>
using namespace std;

// =============================================================
// BRUTE FORCE APPROACH
//
// Idea:
// Count how many people know each person and how many people each person knows.
// A celebrity must be known by exactly N-1 people and must know nobody.
//
// Time Complexity:
// O(N^2), for scanning the entire matrix, plus O(N) for verification.
//
// Space Complexity:
// O(2N), for storing the two count arrays.
//
// =============================================================

// int celebrity(vector<vector<int>> &M)
// {
//     int n = M.size();

//     vector<int> knowMe(n, 0), iKnow(n, 0);

//     for (int row = 0; row < n; row++)
//     {
//         for (int col = 0; col < n; col++)
//         {
//             if (M[row][col] == 1)
//             {
//                 knowMe[col]++;
//                 iKnow[row]++;
//             }
//         }
//     }

//     for (int i = 0; i < n; i++)
//     {
//         if (knowMe[i] == n - 1 && iKnow[i] == 0)
//             return i;
//     }

//     return -1;
// }

// =============================================================
// OPTIMAL APPROACH
//
// Idea:
// Use two pointers to eliminate non-celebrity candidates. If top knows down, top cannot be the celebrity; otherwise, down cannot be the celebrity.
// Continue until at most one candidate remains, then verify that candidate.
//
// Time Complexity:
// O(2N) -> O(N), one pass to find the candidate and one pass to verify it.
//
// Space Complexity:
// O(1), using only two pointers.
//
// =============================================================

int celebrity(vector<vector<int>> &M)
{
    int n = M.size();

    int top = 0, down = n - 1;

    // Eliminate candidates until only one possible celebrity remains.
    while (top < down)
    {
        if (M[top][down] == 1)
        {
            // top knows down, so top cannot be the celebrity.
            top++;
        }
        else if (M[down][top] == 1)
        {
            // down knows top, so down cannot be the celebrity.
            down--;
        }
        else
        {
            // Neither can be a celebrity because they do not satisfy the required relationship with each other.
            top++;
            down--;
        }
    }

    if (top > down)
        return -1;

    // Verify that the remaining candidate knows nobody and everyone knows them.
    for (int i = 0; i < n; i++)
    {
        if (i == top || (M[top][i] == 0 && M[i][top] == 1))
            continue;
        else
            return -1;
    }

    return top;
}

int main()
{
    vector<vector<int>> M = {
        {0, 1, 1, 0},
        {0, 0, 0, 0},
        {1, 1, 0, 0},
        {0, 1, 1, 0}};

    int ans = celebrity(M);

    cout << "The index of celebrity is: " << ans;

    return 0;
}