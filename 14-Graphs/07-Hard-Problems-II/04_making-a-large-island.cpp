// ==================================================
// PROBLEM
// - Given an n x n binary matrix grid, you are allowed to change at most one 0 to 1. 
// - An island is a 4-directionally connected group of 1s.
// - Return the size of the largest island possible after applying this operation.
// ==================================================

#include <bits/stdc++.h>
using namespace std;

// ==================================================
// MAKING A LARGE ISLAND — DISJOINT SET UNION (DSU) APPROACH
//
// Idea:
// - Group all existing adjacent 1s into connected components using Disjoint Set Union (DSU) by mapping 2D coordinates (row, col) to 1D indices (row * n + col).
// - Then, evaluate every 0 cell by checking its 4 adjacent neighbors, summing the sizes of unique neighboring components, and adding 1 for the flipped cell.
// - Finally, account for the edge case where the grid is already entirely 1s.
//
// Time Complexity: O(N² * α(N²)) - Where N x N is the grid size and α is the Inverse Ackermann function.
// Space Complexity: O(N²) - For the DSU parent and size arrays, and the neighbor component set.
// ==================================================

class DisjointSet
{
    vector<int> parent;

public:
    vector<int> size;

    // Initialize DSU for total elements (n * n cells)
    DisjointSet(int n)
    {
        size.resize(n + 1, 1);
        parent.resize(n + 1);

        for (int i = 0; i <= n; i++)
        {
            parent[i] = i;
        }
    }

    // Finds the ultimate representative (root) with path compression
    int findUltimateParent(int node)
    {
        if (parent[node] == node)
            return node;

        return parent[node] = findUltimateParent(parent[node]);
    }

    // Merges two components based on subtree size
    void unionBySize(int u, int v)
    {
        int uRoot = findUltimateParent(u);
        int vRoot = findUltimateParent(v);

        // Already part of the same island component
        if (uRoot == vRoot)
            return;

        // Attach smaller component under larger component and aggregate size
        if (size[uRoot] < size[vRoot])
        {
            parent[uRoot] = vRoot;
            size[vRoot] += size[uRoot];
        }
        else
        {
            parent[vRoot] = uRoot;
            size[uRoot] += size[vRoot];
        }
    }
};

// Helper function to check if the given cell coordinates lie within grid boundaries
bool isValid(int n, int nRow, int nCol)
{
    return (nRow >= 0 &&
            nRow < n &&
            nCol >= 0 &&
            nCol < n);
}

int largestIsland(const vector<vector<int>> &grid)
{
    int n = grid.size();

    // Base case: 1x1 or empty grid
    if (n <= 1)
        return n;

    // DSU instance to track n * n cells (mapped from 0 to n * n - 1)
    DisjointSet ds(n * n);

    // 4-directional traversal offsets (up, right, down, left)
    vector<int> delRow = {-1, 0, 1, 0};
    vector<int> delCol = {0, 1, 0, -1};

    // Step 1: Connect all existing adjacent 1s into disjoint components
    for (int row = 0; row < n; row++)
    {
        for (int col = 0; col < n; col++)
        {
            if (grid[row][col] == 0)
                continue;

            for (int i = 0; i < 4; i++)
            {
                int nRow = row + delRow[i];
                int nCol = col + delCol[i];

                if (isValid(n, nRow, nCol) && grid[nRow][nCol] == 1)
                {
                    // Map 2D coordinates to 1D index
                    int coord = (row * n) + col;
                    int nCoord = (nRow * n) + nCol;

                    ds.unionBySize(coord, nCoord);
                }
            }
        }
    }

    int maxSize = 0;

    // Step 2: Try flipping each 0 to 1 and calculate the resulting island size
    for (int row = 0; row < n; row++)
    {
        for (int col = 0; col < n; col++)
        {
            if (grid[row][col] == 1)
                continue;

            // Set to store unique adjacent component root parents
            unordered_set<int> componentSt;

            int currSize = 0;

            // Check all 4 adjacent neighbors of the current 0 cell
            for (int i = 0; i < 4; i++)
            {
                int nRow = row + delRow[i];
                int nCol = col + delCol[i];

                if (isValid(n, nRow, nCol) && grid[nRow][nCol] == 1)
                {
                    int nCoord = (nRow * n) + nCol;
                    componentSt.insert(ds.findUltimateParent(nCoord));
                }
            }

            // Sum the sizes of all distinct adjacent island components
            for (const auto &component : componentSt)
            {
                currSize += ds.size[component];
            }

            // Include +1 for the newly converted cell itself
            maxSize = max(maxSize, currSize + 1);
        }
    }

    // Step 3: Handle edge case where the grid is already entirely 1s (no 0s flipped)
    for (int currNode = 0; currNode < n * n; currNode++)
    {
        int currSize = ds.size[ds.findUltimateParent(currNode)];

        maxSize = max(maxSize, currSize);
    }

    return maxSize;
}

int main()
{
    // Binary grid
    vector<vector<int>> grid = {
        {1, 0},
        {0, 1}};

    int ans = largestIsland(grid);

    cout << "The size of the largest island is: " << ans;

    return 0;
}
