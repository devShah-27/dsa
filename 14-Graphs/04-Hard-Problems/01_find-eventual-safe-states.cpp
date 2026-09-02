// ==================================================
// PROBLEM
// - Given a directed graph with V vertices, return an array of all safe nodes in ascending order.
// - A node is a safe node if every possible path starting from that node leads to a terminal node (it cannot reach any cycle).
// ==================================================

#include <bits/stdc++.h>
using namespace std;

// ==================================================
// EVENTUAL SAFE NODES — DFS CYCLE DETECTION APPROACH
//
// Idea:
// - Use DFS to detect cycles in a directed graph using a path visited array.
// - Any node that is part of a cycle or has a path to a cycle is unsafe.
// - Mark nodes as safe ('checked') only if they lead solely to terminal nodes.
//
// Time Complexity: O(V + E) - Every vertex and edge is visited at most once.
// Space Complexity: O(V) - For the vis, pathVis, checked arrays, and recursion stack.
// ==================================================

bool dfs(int node, vector<int> adj[], vector<int> &vis, vector<int> &pathVis, vector<int> &checked)
{
    // Mark node as visited and actively in the current recursion path
    vis[node] = 1;
    pathVis[node] = 1;
    checked[node] = 0; // Assume unsafe until proven otherwise

    // Traverse all outgoing edges
    for (int adjNode : adj[node])
    {
        if (!vis[adjNode])
        {
            if (dfs(adjNode, adj, vis, pathVis, checked) == true)
                return true;
        }
        // If an adjacent node is already in the current traversal path, a cycle exists
        else if (pathVis[adjNode] == 1)
        {
            return true;
        }
    }

    // Backtrack: remove node from the current path as it finishes its outgoing edges
    pathVis[node] = 0;
    // Mark as safe because no cycle was detected from this node
    checked[node] = 1;

    return false;
}

vector<int> eventualSafeNodes(int V, vector<int> adj[])
{
    vector<int> vis(V, 0);
    vector<int> pathVis(V, 0);
    vector<int> checked(V, 0);

    for (int i = 0; i < V; i++)
    {
        if (!vis[i])
            dfs(i, adj, vis, pathVis, checked);
    }

    vector<int> result;

    // Collect all nodes that have been verified as safe
    for (int i = 0; i < checked.size(); i++)
    {
        if (checked[i] == 1)
            result.push_back(i);
    }

    return result;
}

// ==================================================
// EVENTUAL SAFE NODES — BFS TOPOLOGICAL SORT APPROACH (KAHN'S ALGORITHM)
//
// Idea:
// - Reverse all edges of the graph.
// - Terminal nodes now have an in-degree of 0.
// - Apply Kahn's Algorithm (BFS) to process nodes level-by-level.
// - Any node processed by the algorithm is safe because it can only be reached from terminal-bound paths.
//
// Time Complexity: O(V + E + V log V) - Processing the reversed graph and BFS takes O(V + E). Sorting the result takes O(V log V).
// Space Complexity: O(V + E) - For the reversed adjacency list, queue, and in-degree array.
// ==================================================

vector<int> eventualSafeNodes(int V, vector<int> adj[])
{
    // Adjacency list for the graph with reversed edges
    vector<vector<int>> revAdj(V);

    // Array to track incoming edges in the reversed graph
    vector<int> revIndegree(V);

    // Populate reversed graph and in-degrees based on the original directed edges
    for (int i = 0; i < V; i++)
    {
        for (int adjNode : adj[i])
        {
            revAdj[adjNode].push_back(i);
            revIndegree[i]++;
        }
    }

    queue<int> q;

    // Nodes with 0 in-degree in the reversed graph were terminal nodes in the original
    for (int i = 0; i < V; i++)
    {
        if (revIndegree[i] == 0)
            q.push(i);
    }

    vector<int> safeNodes;

    // Perform BFS traversal (Kahn's Algorithm)
    while (!q.empty())
    {
        int topNode = q.front();
        q.pop();

        // Any node entering the queue is verified as safe
        safeNodes.push_back(topNode);

        // Reduce the in-degree of adjacent nodes, simulating edge removal
        for (int adjNode : revAdj[topNode])
        {
            revIndegree[adjNode]--;

            if (revIndegree[adjNode] == 0)
                q.push(adjNode);
        }
    }

    // Sort the output array to meet the ascending order requirement
    sort(safeNodes.begin(), safeNodes.end());

    return safeNodes;
}

int main()
{
    int V = 7;

    vector<int> adj[V] = {
        {1, 2},
        {2, 3},
        {5},
        {0},
        {5},
        {},
        {}};

    vector<int> ans = eventualSafeNodes(V, adj);

    cout << "The eventually safe nodes in the graph are:\n";
    for (int i = 0; i < ans.size(); i++)
    {
        cout << ans[i] << " ";
    }

    return 0;
}
