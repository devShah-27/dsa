// ==================================================
// PROBLEM
// - Given a Directed Acyclic Graph (DAG) with V vertices represented as an adjacency list, find any valid Topological Sorting.
// - In a topological sort, for every directed edge u -> v, vertex u must appear before v.
// ==================================================

#include <bits/stdc++.h>
using namespace std;

// ==================================================
// TOPOLOGICAL SORT — DFS APPROACH
//
// Idea:
// - Traverse the graph using Depth-First Search.
// - When a node has no unvisited adjacent nodes (its recursive calls finish), push it onto a stack.
// - Popping all elements from the stack at the end yields a valid topological ordering.
//
// Time Complexity: O(V + E) - Visits every vertex and edge exactly once.
// Space Complexity: O(V) - For the visited array, recursion stack, and result stack.
// ==================================================

void dfs(int node, vector<int> adj[], vector<int> &vis, stack<int> &st)
{
    vis[node] = 1;

    // Explore all outgoing edges recursively
    for (int adjNode : adj[node])
    {
        if (!vis[adjNode])
            dfs(adjNode, adj, vis, st);
    }

    // Push node to stack only after all its dependencies are processed
    st.push(node);
}

vector<int> topoSort(int V, vector<int> adj[])
{
    vector<int> vis(V, 0);

    stack<int> st;

    for (int i = 0; i < V; i++)
    {
        if (!vis[i])
            dfs(i, adj, vis, st);
    }

    vector<int> ans;

    // The stack elements represent the valid topological sequence
    while (!st.empty())
    {
        ans.push_back(st.top());
        st.pop();
    }

    return ans;
}

// ==================================================
// TOPOLOGICAL SORT — BFS APPROACH (KAHN'S ALGORITHM)
//
// Idea:
// - Calculate the in-degree (number of incoming edges) for all vertices.
// - Enqueue all vertices with 0 in-degree.
// - Process nodes by removing them, appending to the result, and decrementing the in-degree of their neighbors.
// - Enqueue neighbors when their in-degree drops to 0.
//
// Time Complexity: O(V + E) - Computes in-degrees and processes each vertex and edge once.
// Space Complexity: O(V) - For the in-degree array, queue, and result array.
// ==================================================

vector<int> topoSort(int V, vector<int> adj[])
{
    vector<int> indegree(V, 0);

    // Calculate in-degree (incoming edges count) for all vertices
    for (int node = 0; node < V; node++)
    {
        for (int adjNode : adj[node])
        {
            indegree[adjNode]++;
        }
    }

    queue<int> q;

    // Vertices with 0 in-degree have no prerequisites and act as starting points
    for (int i = 0; i < V; i++)
    {
        if (indegree[i] == 0)
            q.push(i);
    }

    vector<int> ans;

    // Process nodes level by level
    while (!q.empty())
    {
        int topNode = q.front();
        q.pop();

        // Append nodes to the topological sort sequence as they are processed
        ans.push_back(topNode);

        // Decrease the in-degree of adjacent nodes, simulating the removal of the current node
        for (int adjNode : adj[topNode])
        {
            indegree[adjNode]--;

            // If a node's in-degree reaches 0, all its prerequisites are met
            if (indegree[adjNode] == 0)
                q.push(adjNode);
        }
    }

    return ans;
}

int main()
{
    int V = 6;

    // Adjacency list representation of a Directed Acyclic Graph (DAG)
    vector<int> adj[V] = {
        {},
        {},
        {3},
        {1},
        {0, 1},
        {0, 2}};

    vector<int> ans = topoSort(V, adj);

    cout << "The topological sorting of the given graph is: \n";
    for (int i = 0; i < V; i++)
    {
        cout << ans[i] << " ";
    }

    return 0;
}
