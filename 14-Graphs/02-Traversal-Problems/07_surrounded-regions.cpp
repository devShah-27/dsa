// ==================================================
// PROBLEM
// - Given an N x M matrix where cells are 'X' or 'O', replace all 'O's completely surrounded by 'X's with 'X'. 
// - A region of 4-directionally connected 'O's is not surrounded if it touches any border of the matrix.
// ==================================================

#include <bits/stdc++.h>
using namespace std;

// ==================================================
// SURROUNDED REGIONS — BOUNDARY DFS APPROACH
//
// Idea:
// - Any 'O' connected to the boundary cannot be surrounded. 
// - Traverse all boundary 'O' cells and perform DFS to mark all reachable 'O's as visited (safe).
// - Finally, convert all unvisited 'O' cells into 'X'.
//
// Time Complexity: O(N * M) - Every cell is processed at most once.
// Space Complexity: O(N * M) - For the visited matrix and recursion call stack.
// ==================================================

void dfs(int row, int col, int n, int m,
         vector<vector<char>> &mat,
         vector<vector<int>> &vis,
         vector<int> &delRow,
         vector<int> &delCol)
{
    // Mark current cell as visited/safe
    vis[row][col] = 1;

    // Explore 4 adjacent neighbors (up, right, down, left)
    for (int i = 0; i < 4; i++)
    {
        int nRow = row + delRow[i];
        int nCol = col + delCol[i];

        // Recurse on unvisited 'O' neighbors within grid boundaries
        if (nRow >= 0 &&
            nRow < n &&
            nCol >= 0 &&
            nCol < m &&
            mat[nRow][nCol] == 'O' &&
            !vis[nRow][nCol])
        {
            vis[nRow][nCol] = 1;
            dfs(nRow, nCol, n, m, mat, vis, delRow, delCol);
        }
    }
}

vector<vector<char>> fill(vector<vector<char>> mat)
{
    int n = mat.size(), m = mat[0].size();

    // 2D array to track 'O' cells connected to the boundary
    vector<vector<int>> vis(n, vector<int>(m, 0));

    // 4-directional offsets (up, right, down, left)
    vector<int> delRow = {-1, 0, 1, 0};
    vector<int> delCol = {0, 1, 0, -1};

    // Trigger DFS for all 'O' cells located on the matrix boundary
    for (int row = 0; row < n; row++)
    {
        for (int col = 0; col < m; col++)
        {
            if ((row == 0 || row == n - 1 || col == 0 || col == m - 1) && mat[row][col] == 'O')
                dfs(row, col, n, m, mat, vis, delRow, delCol);
        }
    }

    // Flip all surrounded 'O' cells (those not connected to the boundary) to 'X'
    for (int row = 0; row < n; row++)
    {
        for (int col = 0; col < m; col++)
        {
            if (mat[row][col] == 'O' && !vis[row][col])
                mat[row][col] = 'X';
        }
    }

    return mat;
}

int main()
{
    vector<vector<char>> mat = {
        {'X', 'X', 'X', 'X'},
        {'X', 'O', 'O', 'X'},
        {'X', 'X', 'O', 'X'},
        {'X', 'O', 'X', 'X'}};

    vector<vector<char>> ans = fill(mat);

    int n = ans.size();
    int m = ans[0].size();

    cout << "The updated matrix is: " << endl;
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
