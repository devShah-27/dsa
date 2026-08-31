// ==================================================
// PROBLEM
// - Given an undirected graph with V vertices and an edge list, determine if the graph is bipartite.
// - A graph is bipartite if its nodes can be colored using 2 colors such that no two adjacent nodes share the same color.
// ==================================================

#include <bits/stdc++.h>
using namespace std;

// ==================================================
// BIPARTITE GRAPH CHECK — BFS APPROACH
//
// Idea:
// - Build an adjacency list from the edge list.
// - Use a 2-color BFS traversal where each neighboring node is assigned the opposite color (!color[node]).
// - If an adjacent node already has the same color as the current node, the graph is not bipartite.
//
// Time Complexity: O(V + 2E) - Graph construction and BFS visit each vertex and edge once.
// Space Complexity: O(V + 2E) - For the adjacency list, color array, and BFS queue.
// ==================================================

bool checkUsingBFS(int srcNode, vector<vector<int>> &adj, vector<int> &color)
{
    color[srcNode] = 0;

    queue<int> q;

    q.push(srcNode);

    while (!q.empty())
    {
        int topNode = q.front();
        q.pop();

        for (int adjNode : adj[topNode])
        {
            // If adjacent node is uncolored, assign opposite color and enqueue
            if (color[adjNode] == -1)
            {
                color[adjNode] = !color[topNode];
                q.push(adjNode);
            }
            // If adjacent node has the same color, graph is not bipartite
            else if (color[adjNode] == color[topNode])
            {
                return false;
            }
        }
    }

    return true;
}

bool isBipartite(int V, vector<vector<int>> edges)
{
    vector<int> color(V, -1);

    vector<vector<int>> adj(V);

    // Build adjacency list representation
    for (auto it : edges)
    {
        int u = it[0];
        int v = it[1];

        adj[u].push_back(v);
        adj[v].push_back(u);
    }

    // Traverse all disconnected components
    for (int i = 0; i < V; i++)
    {
        if (color[i] == -1)
        {
            if (checkUsingBFS(i, adj, color) == false)
                return false;
        }
    }

    return true;
}

// ==================================================
// BIPARTITE GRAPH CHECK — DFS APPROACH
//
// Idea:
// - Build an adjacency list and color the graph recursively.
// - Assign alternate colors (0 and 1) to adjacent vertices during DFS.
// - If an adjacent vertex already has the same color as the current vertex, an odd-length cycle exists and the graph is not bipartite.
//
// Time Complexity: O(V + 2E) - Graph construction and DFS visit each vertex and edge once.
// Space Complexity: O(V + 2E) - For the adjacency list, color array, and recursion stack.
// ==================================================

bool checkUsingDFS(int node, int nodeColor, vector<vector<int>> &adj, vector<int> &color)
{
    color[node] = nodeColor;

    for (int adjNode : adj[node])
    {
        // If adjacent node is uncolored, recurse with opposite color
        if (color[adjNode] == -1)
        {
            if (checkUsingDFS(adjNode, !nodeColor, adj, color) == false)
                return false;
        }
        // Same color on adjacent vertices violates bipartite property
        else if (color[adjNode] == nodeColor)
        {
            return false;
        }
    }

    return true;
}

bool isBipartite(int V, vector<vector<int>> edges)
{
    // -1 denotes uncolored state; colors used are 0 and 1
    vector<int> color(V, -1);

    // Adjacency list representation
    vector<vector<int>> adj(V);

    for (auto it : edges)
    {
        int u = it[0];
        int v = it[1];

        adj[u].push_back(v);
        adj[v].push_back(u);
    }

    // Check all components in case of disconnected graph
    for (int i = 0; i < V; i++)
    {
        if (color[i] == -1)
        {
            if (checkUsingDFS(i, 0, adj, color) == false)
                return false;
        }
    }

    return true;
}

int main()
{
    int V = 4;

    vector<vector<int>> edges = {
        {0, 1},
        {1, 2},
        {2, 3},
        {3, 0}};

    bool ans = isBipartite(V, edges);

    if (ans)
        cout << "The given graph is a bipartite graph.";
    else
        cout << "The given graph is not a bipartite graph.";

    return 0;
}
