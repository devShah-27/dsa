// ==================================================
// PROBLEM
// - Given a graph with n vertices and m edges, find the minimum number of edge relocation operations required to make the graph connected.
// - If it is impossible (i.e., fewer than n - 1 total edges), return -1.
// ==================================================

#include <bits/stdc++.h>
using namespace std;

// ==================================================
// NUMBER OF OPERATIONS TO MAKE NETWORK CONNECTED — DISJOINT SET (DSU) APPROACH
//
// Idea:
// - Use Disjoint Set Union (DSU) to identify the number of connected components and count redundant edges (edges connecting nodes that already share a parent).
// - To connect C distinct components, exactly (C - 1) operations are needed.
// - If the count of extra edges is at least (C - 1), return (C - 1); otherwise, return -1.
//
// Time Complexity: O(E * α(V) + V) - Where E is edges, V is vertices, and α is the Inverse Ackermann function.
// Space Complexity: O(V) - For the DSU parent and size arrays.
// ==================================================

class DisjointSet
{
    vector<int> size;

public:
    vector<int> parent;

    // Initialize DSU for N vertices
    DisjointSet(int N)
    {
        size.resize(N + 1, 1);
        parent.resize(N + 1);

        // NOTE: The loop initializes up to N (exclusive). For 1-based indexing, resize/loop up to <= N.
        for (int i = 0; i < N; i++)
        {
            parent[i] = i;
        }
    }

    // Finds the ultimate parent (root) of a node with path compression
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

        // Already part of the same component
        if (uRoot == vRoot)
            return;

        // Attach smaller tree under larger tree
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

int solve(int n, const vector<vector<int>> &Edge)
{
    int size = Edge.size();

    if (size < n - 1)
        return -1;

    DisjointSet ds(n);

    int extraEdgeCnt = 0;

    for (const auto &edge : Edge)
    {
        int u = edge[0];
        int v = edge[1];

        // If nodes already share the same ultimate parent, this edge is redundant
        if (ds.findUltimateParent(u) == ds.findUltimateParent(v))
        {
            extraEdgeCnt++;
        }
        else
        {
            ds.unionBySize(u, v);
        }
    }

    int connectedComponentCnt = 0;

    // Count the number of independent components (nodes that are their own root)
    for (int i = 0; i < n; i++)
    {
        if (ds.parent[i] == i)
            connectedComponentCnt++;
    }

    // Check if we have enough redundant edges to connect all components
    if (extraEdgeCnt >= connectedComponentCnt - 1)
        return connectedComponentCnt - 1;

    return -1;
}

int main()
{
    int n = 4;

    // Edge list representation: [u, v]
    vector<vector<int>> Edge = {
        {0, 1},
        {0, 2},
        {1, 2}};

    int ans = solve(n, Edge);

    cout << "The number of operations to make network connected is: " << ans;

    return 0;
}
