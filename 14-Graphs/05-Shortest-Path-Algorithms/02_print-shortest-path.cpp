// ==================================================
// PROBLEM
// - Given a weighted, undirected graph of n vertices (1 to n) and m edges, find the shortest path between vertex 1 and vertex n.
// - Return a list whose first element is the total path weight followed by the sequence of nodes.
// - If no path exists, return {-1}.
// ==================================================

#include <bits/stdc++.h>
using namespace std;

#define P pair<int, int>

// ==================================================
// SHORTEST PATH WITH PATH RECONSTRUCTION — DIJKSTRA'S ALGORITHM (MIN-HEAP)
//
// Idea:
// - Use Dijkstra's algorithm with a min-priority queue to find the shortest distances from source vertex 1.
// - Maintain a parent array to record the predecessor of each node whenever its distance is relaxed.
// - Backtrack from vertex n to vertex 1 using the parent array to reconstruct the exact path.
//
// Time Complexity: O(M * log(N)) - Where N is vertices and M is edges.
// Space Complexity: O(N + M) - For the adjacency list, distance array, parent array, and priority queue.
// ==================================================

vector<int> shortestPath(int n, int m, const vector<vector<int>> &edges)
{
    // 1-based indexed adjacency list storing {neighbor, weight}
    vector<vector<P>> adj(n + 1);

    for (const auto &it : edges)
    {
        int u = it[0], v = it[1], wt = it[2];

        adj[u].push_back({v, wt});
        adj[v].push_back({u, wt});
    }

    // Min-heap stores pairs of {distance, node}
    priority_queue<P, vector<P>, greater<P>> pq;

    pq.push({0, 1});

    // Initialize distance array with infinity and parent array for path reconstruction
    vector<int> dist(n + 1, 1e9), parent(n + 1);

    for (int i = 0; i < parent.size(); i++)
    {
        parent[i] = i;
    }

    dist[1] = 0;

    // Standard Dijkstra traversal
    while (!pq.empty())
    {
        P topPair = pq.top();
        pq.pop();

        int node = topPair.second;
        int currDist = topPair.first;

        // Traverse all adjacent vertices
        for (P adjPair : adj[node])
        {
            int adjNode = adjPair.first;
            int edgeWt = adjPair.second;

            // Relaxation step: update shortest distance and track predecessor
            if (currDist + edgeWt < dist[adjNode])
            {
                dist[adjNode] = currDist + edgeWt;
                pq.push({dist[adjNode], adjNode});
                parent[adjNode] = node;
            }
        }
    }

    // If destination node n is unreachable
    if (dist[n] == 1e9)
        return {-1};

    vector<int> res;

    int node = n;

    // Backtrack from destination to source using the parent pointers
    while (parent[node] != node)
    {
        res.push_back(node);
        node = parent[node];
    }

    res.push_back(1);
    res.push_back(dist[n]); // Add the total path weight

    // Reverse to get [totalWeight, 1, ..., n]
    reverse(res.begin(), res.end());

    return res;
}

int main()
{
    int n = 5, m = 6;

    // Edge list: {u, v, weight}
    vector<vector<int>> edges = {{1, 2, 2}, {2, 5, 5}, {2, 3, 4}, {1, 4, 1}, {4, 3, 3}, {3, 5, 1}};

    vector<int> ans = shortestPath(n, m, edges);

    cout << "The resulting path weight is: " << ans[0] << endl;

    cout << "The path is: " << endl;

    for (int i = 1; i < ans.size(); i++)
    {
        cout << ans[i] << " ";
    }

    return 0;
}
