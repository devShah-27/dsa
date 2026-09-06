// ==================================================
// PROBLEM
// - Given a weighted, directed graph with V vertices and E edges, find the shortest distance from source vertex S to all other vertices.
// - Unreachable vertices should have a distance of 10^9.
// - If the graph contains a negative weight cycle, return a list containing {-1}.
// ==================================================

#include <bits/stdc++.h>
using namespace std;

// ==================================================
// BELLMAN-FORD ALGORITHM — SHORTEST PATH & NEGATIVE CYCLE DETECTION
//
// Idea:
// - Initialize distances to 10^9 with dist[S] = 0.
// - Relax all E edges (V - 1) times, as the shortest path in a graph without negative cycles contains at most (V - 1) edges.
// - Perform a V-th relaxation cycle; if any distance continues to decrease, a negative cycle is present.
//
// Time Complexity: O(V * E) - Where V is the number of vertices and E is the number of edges.
// Space Complexity: O(V) - For the distance array.
// ==================================================

vector<int> bellman_ford(int V, const vector<vector<int>> &edges, int S)
{
    // Distance array initialized to 1e9 (infinity)
    vector<int> dist(V, 1e9);

    dist[S] = 0;

    // Step 1: Relax all edges (V - 1) times
    for (int i = 0; i < V - 1; i++)
    {
        for (const auto edge : edges)
        {
            int u = edge[0];
            int v = edge[1];
            int edgeWt = edge[2];

            // Relax edge if u is reachable and gives a shorter path to v
            if (dist[u] != 1e9 && dist[u] + edgeWt < dist[v])
                dist[v] = dist[u] + edgeWt;
        }
    }

    // Step 2: N-th relaxation to detect negative weight cycles
    for (const auto edge : edges)
    {
        int u = edge[0];
        int v = edge[1];
        int edgeWt = edge[2];

        // If distance reduces further on V-th iteration, a negative cycle exists
        if (dist[u] != 1e9 && dist[u] + edgeWt < dist[v])
            return {-1};
    }

    return dist;
}

int main()
{
    int V = 6, S = 0;

    // Directed edges format: {u, v, weight}
    vector<vector<int>> edges = {
        {3, 2, 6},
        {5, 3, 1},
        {0, 1, 5},
        {1, 5, -3},
        {1, 2, -2},
        {3, 4, -2},
        {2, 4, 3}};

    vector<int> ans = bellman_ford(V, edges, S);

    if (ans == vector<int>(1, -1))
        cout << "The graph contains negative cycle.";
    else
    {
        cout << "The shortest distance from source is: ";
        for (int i = 0; i < V; i++)
        {
            cout << ans[i] << " ";
        }
    }

    return 0;
}
