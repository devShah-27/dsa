// ==================================================
// PROBLEM
// - Given a weighted, undirected, and connected graph with V vertices represented as an adjacency list, find the sum of the edge weights in the Minimum Spanning Tree (MST) of the graph.
// ==================================================

#include <bits/stdc++.h>
using namespace std;
using P = pair<int, int>;

// ==================================================
// MINIMUM SPANNING TREE — PRIM'S ALGORITHM APPROACH
//
// Idea:
// - Start from an arbitrary node (0) and greedily select the edge with the minimum weight connecting a visited vertex to an unvisited vertex using a min-priority queue.
// - Mark vertices as visited upon extraction and accumulate the edge weights into the total MST sum.
//
// Time Complexity: O(E * log(E)) or O(E * log(V)) - Each edge is inserted into the min-heap at most once.
// Space Complexity: O(V + E) - For the min-priority queue and visited array.
// ==================================================

int spanningTree(int V, vector<vector<int>> adj[])
{
    // Min-heap storing pairs of {edgeWeight, node}
    priority_queue<P, vector<P>, greater<P>> pq;

    // Visited array to ensure each vertex is included in the MST exactly once
    vector<int> vis(V, 0);

    // Start traversal from node 0 with edge weight 0
    pq.push({0, 0});

    int sum = 0;

    // Greedily pick the minimum weight edge connecting to an unvisited vertex
    while (!pq.empty())
    {
        auto [currWt, currNode] = pq.top();
        pq.pop();

        // If the node is already part of the MST, skip it to prevent cycles
        if (vis[currNode])
            continue;

        // Include vertex in MST and add edge weight to total sum
        vis[currNode] = 1;
        sum += currWt;

        // Explore all adjacent unvisited vertices
        for (auto adjNode : adj[currNode])
        {
            int nNode = adjNode[0];
            int nEdgeWt = adjNode[1];

            if (!vis[nNode])
            {
                pq.push({nEdgeWt, nNode});
            }
        }
    }

    return sum;
}

// ==================================================
// MINIMUM SPANNING TREE — KRUSKAL'S ALGORITHM (DSU) APPROACH
//
// Idea:
// - Extract all edges from the adjacency list and sort them in non-decreasing order of their weights.
// - Iterate through the sorted edges and use a Disjoint Set Union (DSU) data structure.
// - If endpoints of an edge belong to different components, include the edge in the MST and union their sets.
//
// Time Complexity: O(E * log(E) + E * α(V)) - Sorting the edges dominates, where α is the Inverse Ackermann function.
// Space Complexity: O(V + E) - For the edge list and Disjoint Set parent and size vectors.
// ==================================================

class DisjointSet
{
    vector<int> parent, size;

public:
    // Initialize DSU for n elements (1-based indexing support)
    DisjointSet(int n)
    {
        size.resize(n + 1, 1);

        parent.resize(n + 1);

        for (int i = 0; i <= n; i++)
        {
            parent[i] = i;
        }
    }

    // Find the ultimate representative (root) with path compression
    int findUltimateParent(int node)
    {
        if (parent[node] == node)
            return node;

        return parent[node] = findUltimateParent(parent[node]);
    }

    // Merge two components based on the size heuristic
    void unionBySize(int u, int v)
    {
        int uRoot = findUltimateParent(u);
        int vRoot = findUltimateParent(v);

        // Already in the same connected component
        if (uRoot == vRoot)
            return;

        // Attach smaller subtree under larger subtree and aggregate sizes
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

int spanningTree(int V, vector<vector<int>> adj[])
{
    // List storing edges as {weight, {u, v}}
    vector<pair<int, P>> edges;

    for (int i = 0; i < V; i++)
    {
        for (auto it : adj[i])
        {
            int u = i;
            int v = it[0];
            int edgeWt = it[1];

            edges.push_back({edgeWt, {u, v}});
        }
    }

    // Sort all edges in non-decreasing order of weights
    sort(edges.begin(), edges.end());

    int sum = 0;

    DisjointSet ds(V);

    // Greedily pick edges that do not form a cycle
    for (auto edge : edges)
    {
        int edgeWt = edge.first;
        int u = edge.second.first;
        int v = edge.second.second;

        // If endpoints belong to different components, include edge in MST
        if (ds.findUltimateParent(u) != ds.findUltimateParent(v))
        {
            sum += edgeWt;
            ds.unionBySize(u, v);
        }
    }

    return sum;
}

int main()
{
    int V = 4;
    vector<vector<int>> edges = {
        {0, 1, 1},
        {1, 2, 2},
        {2, 3, 3},
        {0, 3, 4}};

    // Build adjacency list for an undirected weighted graph
    vector<vector<int>> adj[4];
    for (auto it : edges)
    {
        int u = it[0];
        int v = it[1];
        int wt = it[2];

        adj[u].push_back({v, wt});
        adj[v].push_back({u, wt});
    }

    int ans = spanningTree(V, adj);

    cout << "The sum of weights of edges in MST is: " << ans;

    return 0;
}
