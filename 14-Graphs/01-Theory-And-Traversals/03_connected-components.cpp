// Problem:
// Given an undirected graph with V vertices numbered from 0 to V-1 and E edges, find the number of connected components in the graph.
// Two vertices belong to the same component if there is a path between them.

#include <bits/stdc++.h>
using namespace std;

void bfs(int node, vector<int> &vis, vector<vector<int>> &adj)
{
    queue<int> q;

    q.push(node);

    vis[node] = 1;

    while (!q.empty())
    {
        int topNode = q.front();
        q.pop();

        for (auto it : adj[topNode])
        {
            if (!vis[it])
            {
                vis[it] = 1;
                q.push(it);
            }
        }
    }
}

void dfs(int node, vector<int> &vis, vector<vector<int>> &adj)
{
    for (auto it : adj[node])
    {
        if (!vis[it])
        {
            vis[it] = 1;
            dfs(it, vis, adj);
        }
    }
}

// ==================================================
// CONNECTED COMPONENTS — BFS / DFS APPROACH
//
// Idea:
// - Build an adjacency list and iterate through all vertices.
// - Every unvisited vertex represents a new connected component.
// - Run BFS or DFS from it to visit every vertex belonging to that component.
//
// Time Complexity: O(V + E)
// Space Complexity: O(V + E)
// ==================================================

int findNumberOfComponent(int V, vector<vector<int>> &edges)
{
    int n = edges.size();

    vector<vector<int>> adj(V);

    for (auto it : edges)
    {
        int u = it[0], v = it[1];

        adj[u].push_back(v);
        adj[v].push_back(u);
    }

    vector<int> vis(V, 0);

    int cnt = 0;

    for (int i = 0; i < V; i++)
    {
        if (!vis[i])
        {
            cnt++;

            bfs(i, vis, adj);
            // dfs(i, vis, adj);
        }
    }

    return cnt;
}

int main()
{
    int V = 4;
    vector<vector<int>> edges = {
        {0, 1},
        {1, 2}};

    int ans = findNumberOfComponent(V, edges);

    cout << "The number of components in the given graph is: " << ans;

    return 0;
}