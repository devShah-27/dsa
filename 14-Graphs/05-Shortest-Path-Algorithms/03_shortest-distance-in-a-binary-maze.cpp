// ==================================================
// PROBLEM
// - Given an n x m binary matrix grid where each cell contains 0 or 1, ind the shortest distance from a source cell to a destination cell.
// - Movement is restricted to adjacent 4-directional cells containing 1.
// - Return -1 if the destination is unreachable.
// ==================================================

#include <bits/stdc++.h>
using namespace std;

// ==================================================
// SHORTEST PATH IN BINARY MAZE — BFS APPROACH
//
// Idea:
// - Since all valid moves have unit weight (1), Breadth-First Search (BFS) finds the shortest path level-by-level.
// - Use a 2D distance matrix initialized to infinity and a queue storing {row, col}.
// - Update distances and return immediately upon first reaching the destination cell.
//
// Time Complexity: O(N * M) - In the worst case, every cell is visited once.
// Space Complexity: O(N * M) - For the 2D distance grid and the BFS queue.
// ==================================================

bool isValid(int nRow, int n, int nCol, int m, int currDist,
             const vector<vector<int>> &grid,
             const vector<vector<int>> &distGrid)
{
    return nRow >= 0 &&
           nRow < n &&
           nCol >= 0 &&
           nCol < m &&
           grid[nRow][nCol] == 1 &&
           currDist + 1 < distGrid[nRow][nCol];
}

int shortestPath(const vector<vector<int>> &grid, const pair<int, int> &source, const pair<int, int> &destination)
{
    // Base case: If source or destination is blocked (value 0), path cannot exist
    if (grid[source.first][source.second] == 0 ||
        grid[destination.first][destination.second] == 0)
        return -1;

    // Base case: If starting cell is already the destination
    if (source == destination)
        return 0;

    // Queue stores {row, col}
    queue<pair<int, int>> q;

    int n = grid.size(), m = grid[0].size();

    // 2D distance array initialized to infinity (1e9)
    vector<vector<int>> distGrid(n, vector<int>(m, 1e9));

    // Distance to source cell is 0
    distGrid[source.first][source.second] = 0;

    q.push({source.first, source.second});

    // 4-directional traversal offsets (up, right, down, left)
    vector<int> delRow = {-1, 0, 1, 0};
    vector<int> delCol = {0, 1, 0, -1};

    // Perform BFS traversal
    while (!q.empty())
    {
        auto topPair = q.front();
        q.pop();

        int currRow = topPair.first;
        int currCol = topPair.second;

        int currDist = distGrid[currRow][currCol];

        // Explore all 4 adjacent neighbors
        for (int i = 0; i < 4; i++)
        {
            int nRow = currRow + delRow[i];
            int nCol = currCol + delCol[i];

            if (isValid(nRow, n, nCol, m, currDist, grid, distGrid))
            {
                // Early exit: First time destination is reached guarantees the shortest path
                if (nRow == destination.first && nCol == destination.second)
                    return currDist + 1;

                distGrid[nRow][nCol] = currDist + 1;

                q.push({nRow, nCol});
            }
        }
    }

    return -1;
}

int main()
{
    pair<int, int> source, destination;
    source.first = 0;
    source.second = 1;
    destination.first = 2;
    destination.second = 2;

    // 2D grid containing obstacles (0) and open paths (1)
    vector<vector<int>> grid = {
        {1, 1, 1, 1},
        {1, 1, 0, 1},
        {1, 1, 1, 1},
        {1, 1, 0, 0},
        {1, 0, 0, 1}};

    int ans = shortestPath(grid, source, destination);

    cout << "The shortest distance from the source to destination is: " << ans;

    return 0;
}
