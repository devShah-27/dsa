// ==================================================
// PROBLEM
// - Given a weighted, undirected graph with V vertices and an edge list where each edge is [u, v, weight], find the shortest distance from a given source vertex S to all other vertices.
// - If a vertex is unreachable, return 1e9 (10^9).
// ==================================================

#include <bits/stdc++.h>
using namespace std;

#define P pair<int, int>

// ==================================================
// DIJKSTRA'S ALGORITHM — MIN-HEAP (PRIORITY QUEUE) APPROACH
//
// Idea:
// - Use a min-priority queue to greedily pick the node with the minimum tentative distance.
// - Relax all adjacent edges; if a shorter path to a neighbor is found, update its distance and push the updated pair {dist, node} into the priority queue.
//
// Time Complexity: O(E * log(V)) - Each vertex and edge is processed, with heap operations taking logarithmic time.
// Space Complexity: O(V + E) - For the adjacency list, distance vector, and priority queue.
// ==================================================

vector<int> dijkstra(int V, const vector<vector<int>> &edges, int S)
{
    // Build adjacency list storing pairs of {destination, weight}
    vector<vector<P>> adj(V);

    for (int i = 0; i < edges.size(); i++)
    {
        int u = edges[i][0];
        int v = edges[i][1];
        int wt = edges[i][2];

        adj[u].push_back({v, wt});
        adj[v].push_back({u, wt});
    }

    // Min-heap stores {distance, node}
    priority_queue<P, vector<P>, greater<P>> pq;

    pq.push({0, S});

    // Distance array initialized to 1e9 (infinity)
    vector<int> dist(V, 1e9);

    dist[S] = 0;

    // Process nodes in order of shortest tentative distance
    while (!pq.empty())
    {
        int topWt = pq.top().first;
        int topNode = pq.top().second;

        pq.pop();

        // Relax adjacent neighbors
        for (P it : adj[topNode])
        {
            int adjNode = it.first;
            int edgeWt = it.second;

            if (topWt + edgeWt < dist[adjNode])
            {
                dist[adjNode] = topWt + edgeWt;
                pq.push({dist[adjNode], adjNode});
            }
        }
    }

    return dist;
}

// ==================================================
// DIJKSTRA'S ALGORITHM — SET APPROACH
//
// Idea:
// - Use an ordered set to maintain {distance, node} pairs in ascending order.
// - When a shorter path to an adjacent node is discovered, erase its existing outdated distance entry from the set before inserting the updated path, reducing redundant element traversals.
//
// Time Complexity: O(E * log(V)) - Logarithmic insertion and deletion per edge relaxation.
// Space Complexity: O(V + E) - For the adjacency list, distance vector, and set.
// ==================================================

vector<int> dijkstra(int V, const vector<vector<int>> &edges, int S)
{
    // Build adjacency list storing pairs of {destination, weight}
    vector<vector<P>> adj(V);

    for (int i = 0; i < edges.size(); i++)
    {
        int u = edges[i][0];
        int v = edges[i][1];
        int wt = edges[i][2];

        adj[u].push_back({v, wt});
        adj[v].push_back({u, wt});
    }

    // Set stores pairs of {distance, node} sorted automatically
    set<P> st;

    st.insert({0, S});

    // Distance array initialized to 1e9 (infinity)
    vector<int> dist(V, 1e9);

    dist[S] = 0;

    // Process nodes in increasing order of tentative distance
    while (!st.empty())
    {
        // Extract node with the smallest distance
        auto top = *(st.begin());
        int topWt = top.first;
        int topNode = top.second;

        st.erase(top);

        // Traverse and relax all adjacent edges
        for (P it : adj[topNode])
        {
            int adjNode = it.first;
            int edgeWt = it.second;

            if (topWt + edgeWt < dist[adjNode])
            {
                // Erase previous entry from set if it already exists to avoid redundant processing
                if (dist[adjNode] != 1e9)
                    st.erase({dist[adjNode], adjNode});

                dist[adjNode] = topWt + edgeWt;
                st.insert({dist[adjNode], adjNode});
            }
        }
    }

    return dist;
}

int main()
{
    // ------------------------------------------------------------
    // Comprehensive Test Case
    //
    // Vertices: 0 to 14
    // Source: 0
    //
    // Reachable component:
    // 0 - 1 - 2 - 3 - 4 - 5 - 6 - 7 - 8 - 9 - 10
    //
    // Disconnected component:
    // 11 - 12 - 13 - 14
    //
    // The graph contains:
    // - Multiple competing paths
    // - Cycles
    // - Parallel edges
    // - Equal-weight paths
    // - Self-loop
    // - Large edge weights
    // - Disconnected vertices
    // ------------------------------------------------------------

    int V = 15;
    int S = 0;

    vector<vector<int>> edges =
        {
            // --------------------------------------------------------
            // Main reachable component
            // --------------------------------------------------------

            // Basic connections
            {0, 1, 10},
            {0, 2, 3},
            {1, 2, 1},
            {1, 3, 2},
            {2, 3, 8},
            {2, 4, 2},
            {3, 4, 7},
            {3, 5, 4},
            {4, 5, 1},
            {4, 6, 5},
            {5, 6, 2},
            {5, 7, 6},
            {6, 7, 1},
            {6, 8, 7},
            {7, 8, 2},
            {7, 9, 3},
            {8, 9, 1},
            {8, 10, 5},
            {9, 10, 2},

            // --------------------------------------------------------
            // Additional competing paths
            // --------------------------------------------------------

            {0, 3, 20},
            {0, 4, 50},
            {0, 5, 100},
            {1, 5, 20},
            {2, 5, 15},
            {2, 6, 25},
            {3, 6, 10},
            {3, 7, 30},
            {4, 7, 10},
            {4, 8, 20},
            {5, 8, 10},
            {5, 9, 25},
            {6, 9, 8},
            {6, 10, 20},
            {7, 10, 10},

            // --------------------------------------------------------
            // Parallel / duplicate edges
            // --------------------------------------------------------

            // The first edge gives distance 10, but the second gives 5.
            {0, 1, 5},

            // The first edge gives 3, but this parallel edge is worse.
            {0, 2, 100},

            // Multiple edges between 4 and 5.
            {4, 5, 10},
            {4, 5, 1},

            // Multiple edges between 8 and 9.
            {8, 9, 20},
            {8, 9, 1},

            // --------------------------------------------------------
            // Equal-weight alternative paths
            // --------------------------------------------------------

            // 0 -> 2 -> 4 -> 5
            // 0 -> 1 -> 3 -> 5
            // Additional paths intentionally create ties.
            {2, 4, 2},
            {1, 3, 2},

            // --------------------------------------------------------
            // Cycles
            // --------------------------------------------------------

            {1, 4, 12},
            {2, 5, 9},
            {3, 5, 4},
            {4, 6, 5},
            {5, 7, 6},
            {6, 8, 7},
            {7, 9, 3},

            // --------------------------------------------------------
            // Self-loop
            // --------------------------------------------------------

            {5, 5, 0},

            // --------------------------------------------------------
            // Very large edge weight
            // --------------------------------------------------------

            {0, 10, 100000000},

            // --------------------------------------------------------
            // Disconnected component
            // --------------------------------------------------------

            {11, 12, 4},
            {12, 13, 7},
            {13, 14, 2},
            {11, 14, 20},
            {12, 14, 10}};

    // NOTE: Call may be ambiguous or fail to compile due to identical function signatures above.
    vector<int> ans = dijkstra(V, edges, S);

    cout << "The shortest distance of nodes from the source node is: ";

    for (int i = 0; i < V; i++)
    {
        cout << ans[i] << " ";
    }

    cout << "\n";

    return 0;
}
