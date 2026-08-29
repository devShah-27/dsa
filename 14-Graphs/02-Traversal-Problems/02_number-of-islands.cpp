// ==================================================
// PROBLEM
// - Given an N x M grid consisting of '0's (water) and '1's (land), find the total number of islands.
// - An island is formed by connecting adjacent land cells in all 8 directions (horizontally, vertically, or diagonally).
// ==================================================

#include <bits/stdc++.h>
using namespace std;

// ==================================================
// NUMBER OF ISLANDS — 8-DIRECTIONAL DFS APPROACH
//
// Idea:
// - Traverse the grid cell by cell.
// - When an unvisited land cell ('1') is found, increment the island count and initiate DFS to explore and mark all connected land cells in all 8 directions as visited.
//
// Time Complexity: O(N * M)
// Space Complexity: O(N * M)
// ==================================================

void dfs(int row, int col, int n, int m, vector<vector<char>> &grid, vector<vector<int>> &vis)
{
    vis[row][col] = 1;

    // Explore all 8 adjacent neighbors (horizontal, vertical, diagonal)
    for (int deltaRow = -1; deltaRow <= 1; deltaRow++)
    {
        for (int deltaCol = -1; deltaCol <= 1; deltaCol++)
        {
            int neighborRow = row + deltaRow;
            int neighborCol = col + deltaCol;

            // Check boundary limits, land status, and visited state
            if (neighborRow >= 0 &&
                neighborRow < n &&
                neighborCol >= 0 &&
                neighborCol < m &&
                grid[neighborRow][neighborCol] == '1' &&
                !vis[neighborRow][neighborCol])
            {
                dfs(neighborRow, neighborCol, n, m, grid, vis);
            }
        }
    }
}

int numIslands(vector<vector<char>> &grid)
{
    int n = grid.size(), m = grid[0].size();

    // 2D visited array to prevent reprocessing cells
    vector<vector<int>> vis(n, vector<int>(m, 0));

    int cnt = 0;

    // Iterate over every cell in the grid
    for (int row = 0; row < n; row++)
    {
        for (int col = 0; col < m; col++)
        {
            // If an unvisited land cell is found, a new island starts
            if (grid[row][col] == '1' && !vis[row][col])
            {
                cnt++;
                dfs(row, col, n, m, grid, vis);
            }
        }
    }

    return cnt;
}

int main()
{
    vector<vector<char>> grid = {
        {'1', '1', '1', '0', '1'},
        {'1', '0', '0', '0', '0'},
        {'1', '1', '1', '0', '1'},
        {'0', '0', '0', '1', '1'}};

    int ans = numIslands(grid);

    cout << "The total islands in given grids are: " << ans << endl;

    return 0;
}