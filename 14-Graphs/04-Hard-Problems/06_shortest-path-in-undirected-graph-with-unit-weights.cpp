// ==================================================
// PROBLEM
// - Given an undirected graph with N vertices and M edges of unit weight, find the shortest path from the source vertex (0) to all other vertices.
// - If a vertex is unreachable from the source, return -1 for that vertex.
// ==================================================

#include <bits/stdc++.h>
using namespace std;

// ==================================================
// SHORTEST PATH IN UNDIRECTED GRAPH (UNIT WEIGHTS) — BFS APPROACH
//
// Idea:
// - Because all edges have uniform weight (1), Breadth-First Search (BFS) naturally explores vertices in increasing order of their distance from the source.
// - Initialize distances to infinity with dist[0] = 0.
// - Update neighbor distances level-by-level via a queue, and convert unreachable nodes (1e9) to -1.
//
// Time Complexity: O(N + 2M) - Each vertex and undirected edge is processed in BFS.
// Space Complexity: O(N + 2M) - For the adjacency list, distance array, and queue.
// ==================================================

vector<int> shortestPath(const vector<vector<int>> &edges, int N, int M)
{
    // Build adjacency list for the undirected graph
    vector<vector<int>> adj(N);

    for (int i = 0; i < M; i++)
    {
        int u = edges[i][0], v = edges[i][1];

        adj[u].push_back(v);
        adj[v].push_back(u);
    }

    // Distance array initialized to a large value representing infinity
    vector<int> dist(N, 1e9);

    // Source distance is 0
    dist[0] = 0;

    queue<int> q;

    q.push(0);

    // Standard BFS traversal to relax edges in a unit-weight graph
    while (!q.empty())
    {
        int node = q.front();
        q.pop();

        // Traverse all adjacent neighbors
        for (int adjNode : adj[node])
        {
            // If a shorter path is found, update distance and push to queue
            if (dist[node] + 1 < dist[adjNode])
            {
                dist[adjNode] = dist[node] + 1;
                q.push(adjNode);
            }
        }
    }

    // Unreachable nodes remaining at 1e9 should be mapped to -1
    for (int i = 0; i < N; i++)
    {
        if (dist[i] == 1e9)
            dist[i] = -1;
    }

    return dist;
}

int main()
{
    int N = 9, M = 10;

    vector<vector<int>> edges = {
        {0, 1}, {0, 3}, {3, 4}, {4, 5}, {5, 6}, {1, 2}, {2, 6}, {6, 7}, {7, 8}, {6, 8}};

    vector<int> ans = shortestPath(edges, N, M);

    cout << "The shortest distance of every node from source node is:\n";
    for (int i = 0; i < N; i++)
    {
        cout << ans[i] << " ";
    }

    return 0;
}
