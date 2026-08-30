// ==================================================
// PROBLEM
// - Given an N x M binary grid, find the number of distinct islands formed by 4-directionally connected 1s.
// - Two islands are considered the same if their shapes match identically without rotation or reflection.
// ==================================================

#include <bits/stdc++.h>
using namespace std;

// ==================================================
// BRUTE FORCE APPROACH — DFS WITH SET OF COORDINATE VECTORS
//
// Idea:
// - Traverse the grid using DFS to explore each island.
// - Record each cell's relative coordinate (row - baseRow, col - baseCol) into a vector and insert the vector into an ordered set to filter out duplicate island shapes.
//
// Time Complexity: O(N * M * log(N * M) + N * M) - DFS visits all cells; inserting island coordinate vectors of length K into set takes O(K * log(total_islands)).
// Space Complexity: O(N * M) - For the visited array, recursion stack, and set storage.
// ==================================================

// void dfs(int row, int col, int n, int m,
//          vector<vector<int>> &grid,
//          vector<vector<int>> &vis,
//          vector<pair<int, int>> &vec,
//          int baseRow, int baseCol,
//          vector<int> &delRow,
//          vector<int> &delCol)
// {
//     vis[row][col] = 1;

//     // Store relative coordinate from the starting base cell
//     vec.push_back({row - baseRow, col - baseCol});

//     // Explore 4 adjacent neighbors (up, right, down, left)
//     for (int i = 0; i < 4; i++)
//     {
//         int nRow = row + delRow[i];
//         int nCol = col + delCol[i];

//         if (nRow >= 0 &&
//             nRow < n &&
//             nCol >= 0 &&
//             nCol < m &&
//             grid[nRow][nCol] == 1 &&
//             !vis[nRow][nCol])
//         {
//             dfs(nRow, nCol, n, m, grid, vis, vec, baseRow, baseCol, delRow, delCol);
//         }
//     }
// }

// int countDistinctIslands(vector<vector<int>> &grid)
// {
//     int n = grid.size(), m = grid[0].size();

//     vector<vector<int>> vis(n, vector<int>(m, 0));

//     // Ordered set stores unique island coordinate patterns
//     set<vector<pair<int, int>>> st;

//     vector<int> delRow = {-1, 0, 1, 0};
//     vector<int> delCol = {0, 1, 0, -1};

//     for (int row = 0; row < n; row++)
//     {
//         for (int col = 0; col < m; col++)
//         {
//             if (grid[row][col] == 1 && !vis[row][col])
//             {
//                 vector<pair<int, int>> vec;
//                 dfs(row, col, n, m, grid, vis, vec, row, col, delRow, delCol);
//                 st.emplace(vec);
//             }
//         }
//     }

//     return st.size();
// }

// ==================================================
// OPTIMAL APPROACH — DFS WITH STRING SERIALIZATION & UNORDERED SET
//
// Idea:
// - Serialize the relative coordinates of each island into a unique formatted string during DFS traversal.
// - Store the serialized representations in an unordered_set to achieve O(1) average-time lookups and insertions.
//
// Time Complexity: O(N * M) - O(N * M) for grid traversal and O(K) average insertion into unordered_set where K is island size.
// Space Complexity: O(N * M) - For the visited matrix, recursion stack, and unordered_set storage.
// ==================================================

void dfs(int row, int col, int n, int m,
         vector<vector<int>> &grid,
         vector<vector<int>> &vis,
         string &temp,
         int baseRow, int baseCol,
         vector<int> &delRow,
         vector<int> &delCol)
{
    vis[row][col] = 1;

    // Append relative coordinates as a serialized string token
    temp += to_string(row - baseRow) + "," + to_string(col - baseCol) + " ";

    // Explore 4 adjacent neighbors (up, right, down, left)
    for (int i = 0; i < 4; i++)
    {
        int nRow = row + delRow[i];
        int nCol = col + delCol[i];

        if (nRow >= 0 &&
            nRow < n &&
            nCol >= 0 &&
            nCol < m &&
            grid[nRow][nCol] == 1 &&
            !vis[nRow][nCol])
        {
            dfs(nRow, nCol, n, m, grid, vis, temp, baseRow, baseCol, delRow, delCol);
        }
    }
}

int countDistinctIslands(vector<vector<int>> &grid)
{
    int n = grid.size(), m = grid[0].size();

    vector<vector<int>> vis(n, vector<int>(m, 0));

    // Hash set stores serialized string patterns of unique shapes
    unordered_set<string> st;

    vector<int> delRow = {-1, 0, 1, 0};
    vector<int> delCol = {0, 1, 0, -1};

    for (int row = 0; row < n; row++)
    {
        for (int col = 0; col < m; col++)
        {
            if (grid[row][col] == 1 && !vis[row][col])
            {
                string temp = "";
                dfs(row, col, n, m, grid, vis, temp, row, col, delRow, delCol);
                st.emplace(temp);
            }
        }
    }

    return st.size();
}

int main()
{
    vector<vector<int>> grid = {
        {1, 1, 0, 1, 1},
        {1, 0, 0, 0, 0},
        {0, 0, 0, 0, 1},
        {1, 1, 0, 1, 1}};

    int ans = countDistinctIslands(grid);

    cout << "The count of distinct islands in the given grid is: " << ans << endl;

    return 0;
}
