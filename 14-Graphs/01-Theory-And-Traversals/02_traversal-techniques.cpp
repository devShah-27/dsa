// ==================================================
// PROBLEM
// Given an undirected connected graph with V vertices numbered from 0 to V-1, implement DFS and BFS traversals starting from vertex 0.
// The graph is given as an edge list, where each edge [u, v] represents an undirected connection between vertices u and v.
// ==================================================

#include <bits/stdc++.h>
using namespace std;

// ==================================================
// DFS APPROACH
//
// Idea:
// - Build an adjacency list from the given edge list.
// - Use recursive DFS to visit each unvisited neighbor and record the traversal.
// - Mark a vertex visited before the recursive call to avoid revisiting it.
//
// Time Complexity: O(V + E)
// Space Complexity: O(V + E)
// ==================================================

void dfsHelper(vector<int> &dfs, vector<vector<int>> &adj, vector<int> &vis, int node)
{
    dfs.push_back(node);

    for (auto it : adj[node])
    {
        if (!vis[it])
        {
            vis[it] = 1;
            dfsHelper(dfs, adj, vis, it);
        }
    }
}

vector<int> dfsOfGraph(int V, vector<vector<int>> edges)
{
    vector<vector<int>> adj(V);

    for (auto it : edges)
    {
        int u = it[0];
        int v = it[1];

        adj[u].push_back(v);
        adj[v].push_back(u);
    }

    vector<int> vis(V, 0);

    vis[0] = 1;

    vector<int> dfs;

    dfsHelper(dfs, adj, vis, 0);

    return dfs;
}

// ==================================================
// BFS APPROACH
//
// Idea:
// - Build an adjacency list from the given edge list.
// - Use a queue to process vertices level by level starting from vertex 0.
// - Mark a vertex visited when it is added to the queue to avoid duplicates.
//
// Time Complexity: O(V + E)
// Space Complexity: O(V + E)
// ==================================================

vector<int> bfsOfGraph(int V, vector<vector<int>> edges)
{
    vector<vector<int>> adj(V);

    for (int i = 0; i < edges.size(); i++)
    {
        int u = edges[i][0];
        int v = edges[i][1];

        adj[u].push_back(v);
        adj[v].push_back(u);
    }

    vector<int> bfs;

    vector<int> vis(V, 0);

    vis[0] = 1;

    queue<int> q;

    q.push(0);

    while (!q.empty())
    {
        int currNode = q.front();
        q.pop();

        bfs.push_back(currNode);

        for (auto it : adj[currNode])
        {
            if (!vis[it])
            {
                vis[it] = 1;
                q.push(it);
            }
        }
    }

    return bfs;
}

int main()
{
    int V = 5;
    vector<vector<int>> edges = {
        {0, 1},
        {0, 2},
        {0, 3},
        {2, 4}};

    vector<int> bfs = bfsOfGraph(V, edges);

    vector<int> dfs = dfsOfGraph(V, edges);

    cout << "The BFS traversal of the given graph is: ";
    for (int i = 0; i < bfs.size(); i++)
    {
        cout << bfs[i] << " ";
    }

    cout << "\nThe DFS traversal of the given graph is: ";
    for (int i = 0; i < dfs.size(); i++)
    {
        cout << dfs[i] << " ";
    }

    return 0;
}