// ==================================================
// PROBLEM
// - Given an undirected graph with V vertices labeled from 0 to V-1 represented as an adjacency list, determine if the graph contains any cycle.
// - Self-loops are not present in the graph.
// ==================================================

#include <bits/stdc++.h>
using namespace std;

// ==================================================
// CYCLE DETECTION IN UNDIRECTED GRAPH — BFS APPROACH
//
// Idea:
// - Traverse the graph level-by-level using a queue storing {currentNode, parentNode}.
// - If an adjacent vertex is already visited and is not the parent of the current node, a cycle is detected.
//
// Time Complexity: O(V + 2E) - Every vertex and edge is explored once in BFS.
// Space Complexity: O(V) - For the visited array and BFS queue.
// ==================================================

bool detectCycleBFS(int srcNode, vector<int> adj[], vector<int> &vis)
{
    vis[srcNode] = 1;

    // Queue stores pairs of {currentNode, parentNode}
    queue<pair<int, int>> q;

    q.push({srcNode, -1});

    while (!q.empty())
    {
        auto topNode = q.front();
        q.pop();

        int node = topNode.first;
        int parentNode = topNode.second;

        // Iterate through all adjacent neighbors
        for (int adjNode : adj[node])
        {
            if (!vis[adjNode])
            {
                vis[adjNode] = 1;
                q.push({adjNode, node});
            }
            // Visited neighbor that is not the direct parent implies a cycle
            else if (adjNode != parentNode)
            {
                return true;
            }
        }
    }

    return false;
}

bool isCycle(int V, vector<int> adj[])
{
    // Visited array to handle disconnected components
    vector<int> vis(V, 0);

    for (int i = 0; i < V; i++)
    {
        if (!vis[i])
        {
            if (detectCycleBFS(i, adj, vis))
            {
                return true;
            }
        }
    }

    return false;
}

// ==================================================
// CYCLE DETECTION IN UNDIRECTED GRAPH — DFS APPROACH
//
// Idea:
// - Traverse the graph recursively passing the parent of the current node.
// - If an adjacent vertex is already visited and is not the parent, a back-edge exists, confirming a cycle.
//
// Time Complexity: O(V + 2E) - Every vertex and edge is traversed in DFS.
// Space Complexity: O(V) - For the visited array and recursion call stack.
// ==================================================

bool detectCycleDFS(int node, int parentNode, vector<int> adj[], vector<int> &vis)
{
    vis[node] = 1;

    // Explore all adjacent neighbors recursively
    for (int adjNode : adj[node])
    {
        if (!vis[adjNode])
        {
            if (detectCycleDFS(adjNode, node, adj, vis))
                return true;
        }
        // Visited neighbor that is not the parent indicates a cycle
        else if (adjNode != parentNode)
        {
            return true;
        }
    }

    return false;
}

bool isCycle(int V, vector<int> adj[])
{
    // Visited array to check all disconnected graph components
    vector<int> vis(V, 0);

    for (int i = 0; i < V; i++)
    {
        if (!vis[i])
        {
            if (detectCycleDFS(i, -1, adj, vis))
            {
                return true;
            }
        }
    }

    return false;
}

int main()
{
    int V = 6;

    vector<int> adj[V] = {
        {1, 3},
        {0, 2, 4},
        {1, 5},
        {0, 4},
        {1, 3, 5},
        {2, 4}};

    bool ans = isCycle(V, adj);

    if (ans)
        cout << "The given graph contains a cycle.";
    else
        cout << "The given graph does not contain a cycle.";

    return 0;
}
