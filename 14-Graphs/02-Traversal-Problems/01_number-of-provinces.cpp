// ==================================================
// PROBLEM
// - Given an undirected graph with V vertices, find the number of provinces.
// - The graph is represented by an n x n adjacency matrix where adj[i][j] = 1 if cities i and j are directly connected, and 0 otherwise.
// ==================================================

#include <bits/stdc++.h>
using namespace std;

// ==================================================
// PROVINCE COUNT — DFS APPROACH
//
// Idea:
// - Treat each city as a vertex and the adjacency matrix as the graph representation.
// - Every unvisited city starts a new province; DFS visits all cities connected to it.
// - Continue until all cities have been visited.
//
// Time Complexity: O(V²)
// Space Complexity: O(V)
// ==================================================

void dfs(int node, vector<vector<int>> &adj, vector<int> &vis)
{
    vis[node] = 1;

    for (int i = 0; i < adj.size(); i++)
    {
        // If an edge exists and the neighboring city is not visited, traverse it
        if (adj[node][i] == 1 && !vis[i])
        {
            dfs(i, adj, vis);
        }
    }
}

int numProvinces(vector<vector<int>> adj)
{
    int n = adj.size();

    // Track visited status of each city
    vector<int> vis(n, 0);

    int cnt = 0;

    // Check each city; unvisited cities indicate a new connected component (province)
    for (int i = 0; i < n; i++)
    {
        if (!vis[i])
        {
            cnt++;
            dfs(i, adj, vis);
        }
    }

    return cnt;
}

int main()
{
    vector<vector<int>> adj = {
        {1, 0, 0, 1},
        {0, 1, 1, 0},
        {0, 1, 1, 0},
        {1, 0, 0, 1}};

    int ans = numProvinces(adj);

    cout << "The number of provinces in the given graph is: " << ans;

    return 0;
}