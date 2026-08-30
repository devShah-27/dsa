// ==================================================
// PROBLEM
// - Given an N x M binary matrix grid of 0s (sea) and 1s (land), find the number of land cells (enclaves) from which we cannot walk off the boundary of the grid by moving 4-directionally through adjacent land cells.
// ==================================================

#include <bits/stdc++.h>
using namespace std;

// ==================================================
// NUMBER OF ENCLAVES — BOUNDARY BFS APPROACH
//
// Idea:
// - Any land cell connected to the grid boundary can reach outside.
// - Enqueue all boundary land cells and run multi-source BFS to mark all boundary-connected land components as visited.
// - The remaining unvisited land cells are enclaves.
//
// Time Complexity: O(N * M) - Every cell is processed at most once during traversal.
// Space Complexity: O(N * M) - For the visited matrix and BFS queue storage.
// ==================================================

// Enqueue and mark all unvisited land cells located on the grid boundaries
void markBoundaryElements(vector<vector<int>> &grid,
                          int n, int m,
                          vector<vector<int>> &vis,
                          queue<pair<int, int>> &q)
{
    // Check top and bottom boundaries
    for (int col = 0; col < m; col++)
    {
        if (grid[0][col] == 1 && !vis[0][col])
        {
            q.push({0, col});
            vis[0][col] = 1;
        }

        if (grid[n - 1][col] == 1 && !vis[n - 1][col])
        {
            q.push({n - 1, col});
            vis[n - 1][col] = 1;
        }
    }

    // Check left and right boundaries
    for (int row = 0; row < n; row++)
    {
        if (grid[row][0] == 1 && !vis[row][0])
        {
            q.push({row, 0});
            vis[row][0] = 1;
        }

        if (grid[row][m - 1] == 1 && !vis[row][m - 1])
        {
            q.push({row, m - 1});
            vis[row][m - 1] = 1;
        }
    }
}

// Multi-source BFS to traverse all land cells reachable from the boundaries
void bfs(vector<vector<int>> &grid,
         vector<vector<int>> &vis,
         queue<pair<int, int>> &q)
{
    int n = grid.size(), m = grid[0].size();

    // 4-directional offsets (up, right, down, left)
    vector<int> delRow = {-1, 0, 1, 0};
    vector<int> delCol = {0, 1, 0, -1};

    while (!q.empty())
    {
        auto topElem = q.front();
        q.pop();

        for (int i = 0; i < 4; i++)
        {
            int nRow = topElem.first + delRow[i];
            int nCol = topElem.second + delCol[i];

            // Traverse valid unvisited neighboring land cells
            if (nRow < n &&
                nRow >= 0 &&
                nCol < m &&
                nCol >= 0 &&
                grid[nRow][nCol] == 1 &&
                !vis[nRow][nCol])
            {
                vis[nRow][nCol] = 1;
                q.push({nRow, nCol});
            }
        }
    }
}

int numberOfEnclaves(vector<vector<int>> &grid)
{
    int n = grid.size(), m = grid[0].size();

    // 2D array to track visited land cells connected to the boundary
    vector<vector<int>> vis(n, vector<int>(m, 0));

    queue<pair<int, int>> q;

    // Collect all boundary entry points
    markBoundaryElements(grid, n, m, vis, q);

    // Mark all land connected to boundaries
    bfs(grid, vis, q);

    int count = 0;

    // Count interior land cells that cannot reach any boundary
    for (int row = 1; row < n - 1; row++)
    {
        for (int col = 1; col < m - 1; col++)
        {
            if (grid[row][col] == 1 && !vis[row][col])
                count++;
        }
    }

    return count;
}

int main()
{
    vector<vector<int>> grid = {
        {0, 0, 0, 1},
        {1, 0, 1, 0},
        {0, 0, 1, 0},
        {0, 0, 0, 0}};

    int ans = numberOfEnclaves(grid);

    cout << "The number of enclaves in given grid are: " << ans;
    return 0;
}
