// ==================================================
// PROBLEM
// - Given an n x m grid of 0s (empty), 1s (fresh), and 2s (rotten), find the minimum minutes required to rot all fresh oranges via 4-directional spreading.
// - If not all fresh oranges can rot, return -1.
// ==================================================

#include <bits/stdc++.h>
using namespace std;

// ==================================================
// ROTTING ORANGES — MULTI-SOURCE BFS APPROACH
//
// Idea:
// - Push all initially rotten oranges (cells with value 2) into a queue with time 0.
// - Perform multi-source BFS to rot adjacent fresh oranges layer-by-layer, updating time.
// - Finally, check if any fresh oranges remain unreached.
//
// Time Complexity: O(N * M)
// Space Complexity: O(N * M)
// ==================================================

int orangesRotting(vector<vector<int>> &grid)
{
    // Create a copy of grid to avoid modifying the input directly
    vector<vector<int>> gridCopy = grid;

    int n = gridCopy.size(), m = gridCopy[0].size();

    // Queue stores {{row, col}, time} for BFS
    queue<pair<pair<int, int>, int>> q;

    // Push all initially rotten oranges into the queue as starting sources
    for (int row = 0; row < n; row++)
    {
        for (int col = 0; col < m; col++)
        {
            if (gridCopy[row][col] == 2)
                q.push({{row, col}, 0});
        }
    }

    int maxTimer = 0;

    // 4-directional traversal offsets (up, right, down, left)
    vector<int> delRow = {-1, 0, 1, 0};
    vector<int> delCol = {0, 1, 0, -1};

    // Perform multi-source BFS
    while (!q.empty())
    {
        auto topElem = q.front();
        q.pop();

        for (int i = 0; i < 4; i++)
        {
            int nRow = topElem.first.first + delRow[i];
            int nCol = topElem.first.second + delCol[i];

            // If neighbor is within bounds and is a fresh orange, rot it
            if (nRow < n &&
                nRow >= 0 &&
                nCol < m &&
                nCol >= 0 &&
                gridCopy[nRow][nCol] == 1)
            {
                int currTimer = topElem.second + 1;

                gridCopy[nRow][nCol] = 2;

                q.push({{nRow, nCol}, currTimer});

                maxTimer = max(maxTimer, currTimer);
            }
        }
    }

    // Check if any fresh orange could not be reached
    for (int row = 0; row < n; row++)
    {
        for (int col = 0; col < m; col++)
        {
            if (gridCopy[row][col] == 1)
                return -1;
        }
    }

    return maxTimer;
}

int main()
{
    vector<vector<int>> grid = {
        {2, 1, 1},
        {1, 1, 0},
        {0, 1, 1}};

    int ans = orangesRotting(grid);

    cout << "The minimum number of minutes required for all oranges to rotten are: " << ans;
    return 0;
}
