// ==================================================
// PROBLEM
// - Given an n x m grid 'heights', find the minimum effort required to travel from the top-left cell (0, 0) to the bottom-right cell (n-1, m-1).
// - A route's effort is the maximum absolute difference in heights between consecutive cells along the path.
// ==================================================

#include <bits/stdc++.h>
using namespace std;

// ==================================================
// PATH WITH MINIMUM EFFORT — DIJKSTRA'S ALGORITHM APPROACH
//
// Idea:
// - Use a min-priority queue to greedily explore paths with the smallest maximum step-effort so far. 
// - For each adjacent cell, compute the transition effort as max(currentPathEffort, heightDifference). 
// - If this yields a smaller effort to reach that neighbor, update the effort matrix and enqueue the cell.
//
// Time Complexity: O(N * M * log(N * M)) - With at most 4 * N * M edges, Dijkstra runs in logarithmic time per relaxation.
// Space Complexity: O(N * M) - For the 2D effort matrix and priority queue.
// ==================================================

#define P pair<int, pair<int, int>>

bool isValid(int nRow, int n, int nCol, int m)
{
    return (nRow >= 0 &&
            nRow < n &&
            nCol >= 0 &&
            nCol < m);
}

int MinimumEffort(const vector<vector<int>> &heights)
{
    int n = heights.size(), m = heights[0].size();

    // Base case: Already at destination
    if (n == 1 && m == 1)
        return 0;

    // 2D matrix to track the minimum effort required to reach each cell
    vector<vector<int>> effort(n, vector<int>(m, 1e9));

    // Min-heap stores pairs of {effort, {row, col}}
    priority_queue<P, vector<P>, greater<P>> pq;

    pq.push({0, {0, 0}});

    effort[0][0] = 0;

    // 4-directional traversal offsets (up, right, down, left)
    vector<int> delRow = {-1, 0, 1, 0};
    vector<int> delCol = {0, 1, 0, -1};

    // Perform Dijkstra's algorithm traversal
    while (!pq.empty())
    {
        auto topPair = pq.top();
        pq.pop();

        int currEffort = topPair.first;

        int currRow = topPair.second.first;
        int currCol = topPair.second.second;

        // Destination reached: First time popping (n-1, m-1) guarantees the minimum effort
        if (currRow == n - 1 && currCol == m - 1)
            return currEffort;

        // Explore all 4 adjacent neighbors
        for (int i = 0; i < 4; i++)
        {
            int nRow = currRow + delRow[i];
            int nCol = currCol + delCol[i];

            if (isValid(nRow, n, nCol, m))
            {
                // Absolute height difference between consecutive cells
                int nEffort = abs(heights[currRow][currCol] - heights[nRow][nCol]);

                // The effort for the route is the maximum step difference encountered so far
                if (max(currEffort, nEffort) < effort[nRow][nCol])
                {
                    effort[nRow][nCol] = max(currEffort, nEffort);
                    pq.push({max(currEffort, nEffort), {nRow, nCol}});
                }
            }
        }
    }

    return -1;
}

int main()
{
    // 2D grid representing heights
    vector<vector<int>> heights = {
        {1, 2, 2},
        {3, 8, 2},
        {5, 3, 5}};

    int ans = MinimumEffort(heights);

    cout << "The minimum efforts required to go from cell (0,0) to cell (row-1, col-1) is: " << ans;

    return 0;
}
