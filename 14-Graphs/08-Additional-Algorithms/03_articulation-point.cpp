// ==================================================
// PROBLEM
// - Given an undirected graph with V vertices and an adjacency list, find all articulation points (cut vertices) in ascending order. 
// - An articulation point is a vertex whose removal increases the number of connected components.
// - Return {-1} if no such vertex exists.
// ==================================================

#include <bits/stdc++.h>
using namespace std;

// ==================================================
// ARTICULATION POINTS IN GRAPH — TARJAN'S DFS ALGORITHM
//
// Idea:
// - Traverse the graph using DFS while tracking discoveryTime[u] and lowTime[u].
// - A vertex u is an articulation point if:
//      1. It is a non-root vertex and has a child subtree v such that lowTime[v] >= discoveryTime[u] (no back-edge to an ancestor of u).
//      2. It is the root of a DFS tree (parent == -1) and has more than 1 child subtree.
// - A hash/marked array is used to avoid duplicate recordings of the same vertex.
//
// Time Complexity: O(V + 2E) - Standard DFS traversal visiting every vertex and undirected edge.
// Space Complexity: O(V) - For discovery, low time, marked arrays, and recursion stack.
// ==================================================

void dfs(int u, int parentU, int &timer,
         vector<int> &discoveryTime,
         vector<int> &lowTime,
         const vector<vector<int>> &adj,
         vector<int> &marked)
{
    // Initialize discovery time and lowest reachable time with current timestamp
    discoveryTime[u] = lowTime[u] = ++timer;

    // Count of independent child subtrees in the DFS tree
    int child = 0;

    for (const auto &v : adj[u])
    {
        // Skip the edge leading directly back to the immediate DFS parent
        if (v == parentU)
            continue;

        // If the adjacent node has not been visited yet (tree edge)
        if (discoveryTime[v] == -1)
        {
            dfs(v, u, timer, discoveryTime, lowTime, adj, marked);

            // Update lowest reachable time for current node after child returns
            lowTime[u] = min(lowTime[u], lowTime[v]);

            // Articulation condition for non-root vertices: child cannot reach any ancestor of u
            if (lowTime[v] >= discoveryTime[u] && parentU != -1)
            {
                marked[u] = 1;
            }

            child++;
        }
        // If adjacent node is already visited and not parent (back edge)
        else
        {
            lowTime[u] = min(lowTime[u], discoveryTime[v]);
        }
    }

    // Articulation condition for the root of the DFS tree
    if (child > 1 && parentU == -1)
    {
        marked[u] = 1;
    }
}

vector<int> articulationPoints(int n, const vector<vector<int>> &adj)
{
    // discoveryTime tracks entry time (-1 denotes unvisited); lowTime tracks minimum reachable ancestor time
    vector<int> discoveryTime(n, -1), lowTime(n, 0);

    // marked array prevents recording the same articulation point multiple times
    vector<int> marked(n, 0);

    int timer = 0;

    // Traverse all components to handle disconnected graphs
    for (int i = 0; i < n; i++)
    {
        if (discoveryTime[i] == -1)
            dfs(i, -1, timer, discoveryTime, lowTime, adj, marked);
    }

    vector<int> ans;

    // Collect all unique articulation points in ascending order
    for (int i = 0; i < n; i++)
    {
        if (marked[i] == 1)
            ans.push_back(i);
    }

    // If no articulation points exist, return {-1}
    if (ans.size() == 0)
        return {-1};

    return ans;
}

int main()
{
    int V = 7;

    // Adjacency list representation of an undirected graph
    vector<vector<int>> adj = {
        {1, 2, 3},
        {0},
        {0, 3, 4, 5},
        {2, 0},
        {2, 6},
        {2, 6},
        {4, 5}};

    vector<int> nodes = articulationPoints(V, adj);

    for (auto node : nodes)
    {
        cout << node << " ";
    }
    cout << endl;
    return 0;
}
