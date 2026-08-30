// ==================================================
// PROBLEM
// - Given an N x M binary grid, find the distance of the nearest 1 for each cell.
// - The distance between two cells (i1, j1) and (i2, j2) is the Manhattan distance: |i1 - i2| + |j1 - j2|.
// ==================================================

#include <bits/stdc++.h>
using namespace std;

// ==================================================
// DISTANCE OF NEAREST 1 — MULTI-SOURCE BFS APPROACH
//
// Idea:
// - Push all cells containing 1 into a queue with step count 0 and mark them visited.
// - Run multi-source BFS to expand outward level-by-level in 4 directions to find the shortest Manhattan distance to every remaining cell.
//
// Time Complexity: O(N * M) - Each cell is visited at most once.
// Space Complexity: O(N * M) - For the visited matrix, distance matrix, and queue.
// ==================================================

vector<vector<int>> nearest(const vector<vector<int>> &grid)
{
    int n = grid.size(), m = grid[0].size();

    // 2D visited array to track processed cells
    vector<vector<int>> vis(n, vector<int>(m, 0));

    // Matrix to store the shortest distance to the nearest 1
    vector<vector<int>> distMatrix(n, vector<int>(m, 0));

    // Queue stores {{row, col}, stepCount}
    queue<pair<pair<int, int>, int>> q;

    // Enqueue all sources (cells with value 1) with an initial distance of 0
    for (int row = 0; row < n; row++)
    {
        for (int col = 0; col < m; col++)
        {
            if (grid[row][col] == 1)
            {
                q.push({{row, col}, 0});
                vis[row][col] = 1;
            }
        }
    }

    // 4-directional traversal offsets (up, right, down, left)
    vector<int> delRow = {-1, 0, 1, 0};
    vector<int> delCol = {0, 1, 0, -1};

    // Perform multi-source BFS traversal
    while (!q.empty())
    {
        auto topElem = q.front();
        q.pop();

        int row = topElem.first.first;
        int col = topElem.first.second;

        int stepCnt = topElem.second;

        distMatrix[row][col] = stepCnt;

        // Traverse all 4 adjacent neighbors
        for (int i = 0; i < 4; i++)
        {
            int nRow = row + delRow[i];
            int nCol = col + delCol[i];

            // If neighbor is within bounds, is a 0 cell, and is unvisited, enqueue it
            if (nRow < n &&
                nRow >= 0 &&
                nCol < m &&
                nCol >= 0 &&
                grid[nRow][nCol] == 0 &&
                !vis[nRow][nCol])
            {
                vis[nRow][nCol] = 1;

                q.push({{nRow, nCol}, stepCnt + 1});
            }
        }
    }

    return distMatrix;
}

int main()
{
    vector<vector<int>> grid = {
        {0, 1, 1, 0},
        {1, 1, 0, 0},
        {0, 0, 1, 1}};

    vector<vector<int>> ans = nearest(grid);

    int n = ans.size();
    int m = ans[0].size();

    cout << "The distance of the nearest 1 in the grid for each cell is: " << endl;
    for (int i = 0; i < n; i++)
    {
        for (int j = 0; j < m; j++)
        {
            cout << ans[i][j] << " ";
        }
        cout << endl;
    }

    return 0;
}
