// ==================================================
// PROBLEM
// - Given an n x m grid initially containing only water (0), process an array of k operations where each operation turns a cell into land (1). 
// - Return the total number of connected land components (islands) after each operation.
// ==================================================

#include <bits/stdc++.h>
using namespace std;

// ==================================================
// NUMBER OF ISLANDS II — DISJOINT SET UNION (DSU) APPROACH
//
// Idea:
// - Map 2D grid coordinates (row, col) to unique 1D identifiers (row * m + col).
// - For each operation, convert the cell to land and increment the island count.
// - Check all 4 adjacent neighbors; if a neighbor is already land and belongs to a different set, merge their sets via DSU and decrement the island count.
//
// Time Complexity: O(K * α(N * M)) - Where K is the number of operations and α is the Inverse Ackermann function.
// Space Complexity: O(N * M) - For the 2D grid and the DSU parent and size arrays.
// ==================================================

class DisjointSet
{
    vector<int> parent, size;

public:
    // Initialize DSU for n total cells
    DisjointSet(int n)
    {
        size.resize(n + 1, 1);
        parent.resize(n + 1);

        for (int i = 0; i <= n; i++)
        {
            parent[i] = i;
        }
    }

    // Finds the ultimate root of a node with path compression
    int findRoot(int node)
    {
        if (parent[node] == node)
            return node;

        return parent[node] = findRoot(parent[node]);
    }

    // Merges two components based on subtree size
    void unionBySize(int u, int v)
    {
        int uRoot = findRoot(u);
        int vRoot = findRoot(v);

        // Already in the same connected component
        if (uRoot == vRoot)
            return;

        // Attach smaller tree under larger tree and aggregate sizes
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

// Helper function to verify whether adjacent coordinates lie within grid boundaries
bool isValid(int n, int m, int nRow, int nCol)
{
    return (nRow >= 0 &&
            nRow < n &&
            nCol >= 0 &&
            nCol < m);
}

vector<int> numOfIslands(int n, int m, const vector<vector<int>> &A)
{
    // DSU instance to track connectivity across all n * m cells
    DisjointSet ds(n * m);

    // 2D grid to track land cells (1) and water cells (0)
    vector<vector<int>> island(n, vector<int>(m, 0));

    int cnt = 0;

    // 4-directional offsets (up, right, down, left)
    vector<int> delRow = {-1, 0, 1, 0};
    vector<int> delCol = {0, 1, 0, -1};

    vector<int> result;

    // Process each land-addition query dynamically
    for (const auto &operation : A)
    {
        int row = operation[0];
        int col = operation[1];

        // If the cell is already land, the number of islands does not change
        if (island[row][col] == 1)
        {
            result.push_back(cnt);
            continue;
        }

        // Convert current water cell to land
        island[row][col] = 1;
        cnt++;

        // Explore all 4 adjacent neighbors
        for (int i = 0; i < 4; i++)
        {
            int nRow = row + delRow[i];
            int nCol = col + delCol[i];

            // If neighbor is valid and is already land, check connectivity
            if (isValid(n, m, nRow, nCol) && island[nRow][nCol] == 1)
            {
                // Map 2D coordinates to 1D identifiers
                int nodeIdx = row * m + col;
                int nNodeIdx = nRow * m + nCol;

                // If cells belong to different components, merge them and reduce island count
                if (ds.findRoot(nodeIdx) != ds.findRoot(nNodeIdx))
                {
                    cnt--;
                    ds.unionBySize(nodeIdx, nNodeIdx);
                }
            }
        }

        result.push_back(cnt);
    }

    return result;
}

int main()
{
    int n = 4, m = 5, k = 4;

    // List of operations: [row, col] to convert to land
    vector<vector<int>> A = {
        {1, 1},
        {0, 1},
        {3, 3},
        {3, 4}};

    vector<int> ans = numOfIslands(n, m, A);

    cout << "The number of islands after each operations are: ";

    for (int i = 0; i < ans.size(); i++)
    {
        cout << ans[i] << " ";
    }

    return 0;
}
