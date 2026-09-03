// ==================================================
// PROBLEM
// - Given a Directed Acyclic Graph (DAG) with N vertices and M weighted edges, find the shortest path from the source vertex (0) to all other vertices.
// - If a vertex is unreachable, return -1 for that vertex.
// ==================================================

#include <bits/stdc++.h>
using namespace std;

// ==================================================
// SHORTEST PATH IN DAG — TOPOLOGICAL SORT & RELAXATION
//
// Idea:
// - First, find the topological ordering of the DAG using DFS.
// - Then, initialize distances with infinity and set the source distance to 0.
// - Pop nodes from the topological stack and relax their outgoing edges.
// - Processing in topological order guarantees that a node's shortest path is finalized before exploring it.
//
// Time Complexity: O(N + M) - O(N + M) for topological sort and O(N + M) for edge relaxation.
// Space Complexity: O(N + M) - For the adjacency list, visited array, distance array, and recursion stack.
// ==================================================

void topoSort(int node, vector<int> &vis, vector<vector<pair<int, int>>> &adj, stack<int> &st)
{
    vis[node] = 1;

    for (auto adjNode : adj[node])
    {
        if (!vis[adjNode.first])
            topoSort(adjNode.first, vis, adj, st);
    }

    st.push(node);
}

vector<int> shortestPath(int N, int M, const vector<vector<int>> &edges)
{
    // Build adjacency list containing pairs of {destination, weight}
    vector<vector<pair<int, int>>> adj(N);

    for (int i = 0; i < M; i++)
    {
        int u = edges[i][0];
        int v = edges[i][1];
        int weight = edges[i][2];

        adj[u].push_back({v, weight});
    }

    // Step 1: Find the Topological Sort using DFS
    stack<int> st;
    vector<int> vis(N, 0);

    for (int i = 0; i < N; i++)
    {
        if (!vis[i])
            topoSort(i, vis, adj, st);
    }

    // Step 2: Initialize distance array with a large value representing infinity
    vector<int> dist(N, INT_MAX);

    // Source node is implicitly assumed to be 0 based on the problem description
    dist[0] = 0;

    // Step 3: Process nodes in topological order and relax their edges
    while (!st.empty())
    {
        int node = st.top();
        st.pop();

        // Relax adjacent edges only if the current node is reachable from the source
        for (auto adjNode : adj[node])
        {
            int nextNode = adjNode.first;
            int weight = adjNode.second;

            if (dist[node] != INT_MAX)
            {
                if (dist[node] + weight < dist[nextNode])
                    dist[nextNode] = dist[node] + weight;
            }
        }
    }

    // Convert any remaining unreachable nodes (still INT_MAX) to -1
    for (int i = 0; i < N; i++)
    {
        if (dist[i] == INT_MAX)
            dist[i] = -1;
    }

    return dist;
}

int main()
{
    int N = 4, M = 2;

    vector<vector<int>> edges = {
        {0, 1, 2}, {0, 2, 1}};

    vector<int> ans = shortestPath(N, M, edges);

    cout << "The shortest distance of every node from source node is:\n";
    for (int i = 0; i < N; i++)
    {
        cout << ans[i] << " ";
    }

    return 0;
}
