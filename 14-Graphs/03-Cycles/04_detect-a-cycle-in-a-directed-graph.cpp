// ==================================================
// PROBLEM
// - Given a directed graph with V vertices labeled from 0 to V-1 represented using an adjacency list, determine if the graph contains any cycles.
// ==================================================

#include <bits/stdc++.h>
using namespace std;

// ==================================================
// CYCLE DETECTION IN DIRECTED GRAPH — DFS APPROACH
//
// Idea:
// - Traverse the graph using DFS while tracking the current recursion stack (path).
// - Use a single visited array with 3 states: 0 (unvisited), 1 (fully processed), and 2 (currently in the recursion path).
// - If we reach a node with state 2, a cycle exists.
//
// Time Complexity: O(V + E) - Every vertex and directed edge is visited at most once.
// Space Complexity: O(V) - For the state/visited array and recursion call stack.
// ==================================================

bool dfs(int node, vector<int> &vis, vector<int> adj[])
{
    // Mark node as visited and currently in the recursion path
    vis[node] = 2;

    for (int adjNode : adj[node])
    {
        if (vis[adjNode] == 0)
        {
            if (dfs(adjNode, vis, adj))
                return true;
        }
        // If the adjacent node is already in the current recursion path, a cycle is detected
        else if (vis[adjNode] == 2)
        {
            return true;
        }
    }

    // Mark node as fully processed (removed from current recursion path)
    vis[node] = 1;

    return false;
}

bool isCyclic(int N, vector<int> adj[])
{
    /*
        NOTE: This can also be done using two separate arrays (visited and pathVisited),
        marking all pathVisited nodes as 1 and unmarking them after backtracking.
    */

    vector<int> vis(N, 0);

    for (int i = 0; i < N; i++)
    {
        if (!vis[i])
        {
            if (dfs(i, vis, adj))
                return true;
        }
    }

    return false;
}

// ==================================================
// CYCLE DETECTION IN DIRECTED GRAPH — BFS (KAHN'S ALGORITHM)
//
// Idea:
// - Use Kahn's Algorithm for Topological Sorting. 
// - Since a valid topological sort is only possible for Directed Acyclic Graphs (DAGs), we count the processed nodes.
// - If the count does not equal V, it implies a cycle exists and the graph is not a DAG.
//
// Time Complexity: O(V + E) - Computes in-degrees and processes each vertex and edge once.
// Space Complexity: O(V) - For the in-degree array and queue.
// ==================================================

bool isCyclic(int N, vector<int> adj[])
{
    vector<int> indegree(N, 0);

    // Calculate in-degree (incoming edges count) for all vertices
    for (int i = 0; i < N; i++)
    {
        for (int adjNode : adj[i])
        {
            indegree[adjNode]++;
        }
    }

    queue<int> q;

    // Push all nodes with 0 in-degree as starting points
    for (int i = 0; i < N; i++)
    {
        if (indegree[i] == 0)
            q.push(i);
    }

    int counter = 0;

    // Process nodes level by level
    while (!q.empty())
    {
        int topNode = q.front();
        q.pop();

        // Increment count for every node successfully placed in the topological sort
        counter++;

        // Decrease the in-degree of adjacent nodes
        for (int adjNode : adj[topNode])
        {
            indegree[adjNode]--;

            if (indegree[adjNode] == 0)
                q.push(adjNode);
        }
    }

    // If topological sort does not include all N nodes, a cycle prevents it
    return !(counter == N);
}

int main()
{
    int V = 6;

    // Adjacency list representation of a directed graph
    vector<int> adj[V] = {
        {1},
        {2, 5},
        {3},
        {4},
        {1},
        {}};

    bool ans = isCyclic(V, adj);

    if (ans)
        cout << "The given directed graph contains a cycle.";
    else
        cout << "The given directed graph does not contain a cycle.";

    return 0;
}
