// ==================================================
// PROBLEM
// - Given a 2D integer matrix representing an image, perform a "flood fill" starting from pixel (sr, sc).
// - Change the color of the starting pixel and all 4-directionally connected pixels of the same initial color to newColor.
// ==================================================

#include <bits/stdc++.h>
using namespace std;

// ==================================================
// FLOOD FILL — DFS & BFS APPROACHES
//
// Idea:
// - Identify the target color at the source pixel (sr, sc).
// - If target color matches newColor, return early.
// - Otherwise, traverse 4-directionally via DFS or BFS, recoloring valid matching pixels to prevent cycles and mark completion.
//
// Time Complexity: O(N * M) - In worst case, every pixel in the grid is visited.
// Space Complexity: O(N * M) - Recursion stack for DFS or queue space for BFS.
// ==================================================

// DFS traversal to recolor connected component recursively
void dfs(int sr, int sc,
         int n, int m,
         vector<vector<int>> &ans,
         int initialColor, int newColor,
         vector<int> &deltaRow, vector<int> &deltaCol)
{
    // Color the current pixel with newColor
    ans[sr][sc] = newColor;

    // Explore all 4 adjacent directions (up, right, down, left)
    for (int i = 0; i < 4; i++)
    {
        int nRow = sr + deltaRow[i];
        int nCol = sc + deltaCol[i];

        // Recurse only if neighbor is within bounds and matches initialColor
        if (nRow >= 0 &&
            nRow < n &&
            nCol >= 0 &&
            nCol < m &&
            ans[nRow][nCol] == initialColor)
        {
            ans[nRow][nCol] = newColor;
            dfs(nRow, nCol, n, m, ans, initialColor, newColor, deltaRow, deltaCol);
        }
    }
}

// BFS traversal to recolor connected component iteratively using a queue
void bfs(int sr, int sc,
         int n, int m,
         vector<vector<int>> &ans,
         int initialColor, int newColor,
         vector<int> &deltaRow, vector<int> &deltaCol)
{
    // Color starting pixel and enqueue its coordinates
    ans[sr][sc] = newColor;

    queue<pair<int, int>> q;

    q.push({sr, sc});

    // Process nodes level by level
    while (!q.empty())
    {
        auto pixelCoord = q.front();
        q.pop();

        // Check all 4 neighboring pixels
        for (int i = 0; i < 4; i++)
        {
            int nRow = pixelCoord.first + deltaRow[i];
            int nCol = pixelCoord.second + deltaCol[i];

            // If neighbor is valid and has the initial color, recolor and enqueue
            if (nRow >= 0 &&
                nRow < n &&
                nCol >= 0 &&
                nCol < m &&
                ans[nRow][nCol] == initialColor)
            {
                ans[nRow][nCol] = newColor;
                q.push({nRow, nCol});
            }
        }
    }
}

vector<vector<int>> floodFill(vector<vector<int>> &image,
                              int sr, int sc, int newColor)
{
    int n = image.size(), m = image[0].size();

    // Create a copy of original image matrix to store modified colors
    vector<vector<int>> ans = image;

    int initialColor = image[sr][sc];

    // Base condition: If starting pixel already has newColor, avoid infinite loops
    if (initialColor == newColor)
        return image;

    // Direction arrays for 4-directional traversal
    vector<int> deltaRow = {-1, 0, 1, 0};
    vector<int> deltaCol = {0, 1, 0, -1};

    // Both BFS and DFS are valid traversals for flood fill bfs(sr, sc, n, m, ans, initialColor, newColor, deltaRow, deltaCol);
    dfs(sr, sc, n, m, ans, initialColor, newColor, deltaRow, deltaCol);

    return ans;
}

int main()
{
    vector<vector<int>> image = {
        {1, 1, 1},
        {1, 1, 0},
        {1, 0, 1}};
    int sr = 1, sc = 1;
    int newColor = 2;

    int n = image.size();
    int m = image[0].size();

    vector<vector<int>> ans = floodFill(image, sr, sc, newColor);

    cout << "Image after performing flood fill algorithm: \n\n";

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