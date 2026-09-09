// ==================================================
// PROBLEM
// - Given n stones on a 2D plane where stones[i] = [xi, yi], a stone can be removed if it shares the same row or column with another remaining stone.
// - Return the maximum possible number of stones that can be removed.
// ==================================================

#include <bits/stdc++.h>
using namespace std;

class DisjointSet
{
    vector<int> size;

public:
    vector<int> parent;

    // Initialize DSU for elements up to n
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

        // Already in the same connected component
        if (uRoot == vRoot)
            return;

        // Attach smaller subtree under larger subtree and aggregate size
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

// ==================================================
// MOST STONES REMOVED — PAIRWISE DSU APPROACH
//
// Idea:
// - Treat each stone as a node.
// - Check every pair of stones; if they share the same row or column, union their indices.
// - In each connected component of size K, we can remove (K - 1) stones, leaving 1 stone intact.
// - Total stones removed is (Total Stones - Number of Connected Components).
//
// Time Complexity: O(N² * α(N)) - Where N is the number of stones and α is the Inverse Ackermann function.
// Space Complexity: O(N) - For the DSU parent and size arrays.
// ==================================================

int maxRemove(const vector<vector<int>> &stones, int n)
{
    DisjointSet ds(n);

    // Pairwise comparison to connect stones sharing the same row or column
    for (int i = 0; i < n; i++)
    {
        for (int j = i + 1; j < n; j++)
        {
            if (stones[i][0] == stones[j][0] ||
                stones[i][1] == stones[j][1])
            {
                ds.unionBySize(i, j);
            }
        }
    }

    int independentCompCount = 0;

    // Count the number of independent stone components
    for (int i = 0; i < n; i++)
    {
        if (ds.parent[i] == i)
            independentCompCount++;
    }

    // Maximum stones removed = Total stones - Number of independent components
    return n - independentCompCount;
}

// ==================================================
// MOST STONES REMOVED — ROW & COLUMN COORDINATE DSU APPROACH
//
// Idea:
// - Treat every unique row and column coordinate as a separate node in DSU.
// - For a stone at (r, c), create an edge between node 'r' and node '(c + offset)' (where offset = maxRow + 1 to avoid coordinate collisions).
// - The number of independent components formed by these active coordinates determines how many stones must remain.
//
// Time Complexity: O(N * α(maxRow + maxCol)) - Where N is the number of stones.
// Space Complexity: O(maxRow + maxCol) - For the DSU structure and hash map.
// ==================================================

int maxRemove(const vector<vector<int>> &stones, int n)
{
    int maxRow = 0, maxCol = 0;

    // Determine coordinate boundaries to size the DSU correctly
    for (const auto &stone : stones)
    {
        maxRow = max(maxRow, stone[0]);
        maxCol = max(maxCol, stone[1]);
    }

    // Total elements needed: (maxRow + 1) rows + (maxCol + 1) columns
    DisjointSet ds(maxRow + maxCol + 1);

    int offset = maxRow + 1;

    // Map to track all row and column nodes that contain at least one stone
    unordered_map<int, int> nodeHavingStone;

    for (const auto &stone : stones)
    {
        int rowCoord = stone[0];
        int colCoord = stone[1] + offset; // Shift column index to prevent collision with row indices

        // Connect the row component and column component
        ds.unionBySize(rowCoord, colCoord);

        nodeHavingStone[rowCoord] = 1;
        nodeHavingStone[colCoord] = 1;
    }

    int independentCompCount = 0;

    // Count unique ultimate parents among all active row and column nodes
    for (const auto &node : nodeHavingStone)
    {
        if (ds.findUltimateParent(node.first) == node.first)
            independentCompCount++;
    }

    // Maximum stones removed = Total stones - Number of independent connected components
    return n - independentCompCount;
}

int main()
{
    int n = 6;

    // Coordinates of stones: [row, col]
    vector<vector<int>> stones = {{0, 0}, {0, 1}, {1, 0}, {1, 2}, {2, 1}, {2, 2}};

    // NOTE: Rename or comment out one of the 'maxRemove' functions above to resolve redefinition error.
    int ans = maxRemove(stones, n);

    // NOTE: Output message text in original code refers to "largest island" instead of "maximum stones removed".
    cout << "The maximum number of stones that can be removed is: " << ans;

    return 0;
}
