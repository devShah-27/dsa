// ==================================================
// PROBLEM
// - Given an undirected connected graph with V vertices and E edges, find all bridges (critical connections) in the graph.
// - An edge is a bridge if its removal increases the number of connected components.
// ==================================================

#include <bits/stdc++.h>
using namespace std;

// ==================================================
// BRIDGES IN GRAPH — TARJAN'S ALGORITHM (DFS WITH DISCOVERY & LOW TIME)
//
// Idea:
// - Traverse the graph using DFS while tracking two values for each node:
//      1. discoveryTime[u]: The timestamp when node u is first visited.
//      2. lowTime[u]: The lowest discovery time reachable from node u via tree/back edges.
// - For any tree edge (u, v), if lowTime[v] > discoveryTime[u], it implies node v cannot reach u or any of u's ancestors without using edge (u, v), making it a bridge.
//
// Time Complexity: O(V + 2E) - Standard DFS traversal visiting every vertex and undirected edge.
// Space Complexity: O(V + 2E) - For the adjacency list, discovery/low time arrays, and recursion stack.
// ==================================================

void dfs(int u, int parentU, int &timer,
         vector<int> &discoveryTime,
         vector<int> &lowTime,
         const vector<vector<int>> &adj,
         vector<vector<int>> &bridges)
{
    // Initialize discovery time and lowest reachable time with current timestamp
    discoveryTime[u] = lowTime[u] = ++timer;

    // Explore all adjacent neighbors
    for (const auto &v : adj[u])
    {
        // Skip the edge leading back to the immediate parent in DFS tree
        if (v == parentU)
            continue;

        // If adjacent node is not yet visited (tree edge)
        if (discoveryTime[v] == -1)
        {
            dfs(v, u, timer, discoveryTime, lowTime, adj, bridges);

            // Update lowest reachable time for current node after child returns
            lowTime[u] = min(lowTime[u], lowTime[v]);

            // Bridge Condition: No back-edge from subtree of v reaches u or ancestors of u
            if (lowTime[v] > discoveryTime[u])
                bridges.push_back({u, v});
        }
        // If adjacent node is already visited and not parent (back edge)
        else
        {
            lowTime[u] = min(lowTime[u], discoveryTime[v]);
        }
    }
}

vector<vector<int>> criticalConnections(int V, const vector<vector<int>> &E)
{
    // Build adjacency list for the undirected graph
    vector<vector<int>> adj(V);

    for (const auto &edge : E)
    {
        int u = edge[0], v = edge[1];

        adj[u].push_back(v);
        adj[v].push_back(u);
    }

    int timer = 0;

    // discoveryTime tracks entry time (-1 denotes unvisited); lowTime tracks minimum reachable ancestor time
    vector<int> discoveryTime(V, -1), lowTime(V, 0);

    vector<vector<int>> bridges;

    // Iterate across all vertices to support disconnected components
    for (int i = 0; i < V; i++)
    {
        if (discoveryTime[i] == -1)
            dfs(i, -1, timer, discoveryTime, lowTime, adj, bridges);
    }

    return bridges;
}

int main()
{
    int V = 4;

    // List of undirected edges: [u, v]
    vector<vector<int>> E = {
        {0, 1},
        {1, 2},
        {2, 0},
        {1, 3}};

    vector<vector<int>> ans = criticalConnections(V, E);

    cout << "The critical connections in the given graph are:\n";

    for (int i = 0; i < ans.size(); i++)
    {
        cout << ans[i][0] << " " << ans[i][1] << endl;
    }

    return 0;
}
