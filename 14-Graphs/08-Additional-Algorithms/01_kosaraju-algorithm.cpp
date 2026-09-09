// ==================================================
// PROBLEM
// - Given a directed graph with V vertices numbered 0 to V - 1 and its adjacency list, find the total number of Strongly Connected Components (SCCs).
// - A strongly connected component is a maximal subgraph where every vertex is reachable from every other vertex in that subgraph.
// ==================================================

#include <bits/stdc++.h>
using namespace std;

// ==================================================
// STRONGLY CONNECTED COMPONENTS — KOSARAJU'S ALGORITHM
//
// Idea:
// 1. Perform DFS on the original graph to order vertices by their finish times (store finish order on a stack).
// 2. Reverse (transpose) all directed edges in the graph.
// 3. Pop vertices from the stack and run DFS on the reversed graph. 
//    - Each complete traversal from an unvisited vertex discovers one distinct SCC.
//
// Time Complexity: O(V + E) - Performs two DFS passes and one graph reversal pass.
// Space Complexity: O(V + E) - For the stack, visited array, recursion stack, and reversed adjacency list.
// ==================================================

// Helper DFS to order vertices by finish time (Step 1)
void dfs(int node, vector<int> &vis, stack<int> &st, const vector<vector<int>> &adj)
{
    vis[node] = 1;

    // Explore all adjacent unvisited vertices
    for (const auto &adjNode : adj[node])
    {
        if (!vis[adjNode])
            dfs(adjNode, vis, st, adj);
    }

    // Push the vertex to stack after exploring all its reachable paths
    st.push(node);
}

// Helper DFS to traverse components on the transposed graph (Step 3)
void transposeDfs(int node, vector<int> &vis, const vector<vector<int>> &transposeAdj)
{
    vis[node] = 1;

    // Traverse all reachable vertices in the reversed component
    for (const auto &adjNode : transposeAdj[node])
    {
        if (!vis[adjNode])
            transposeDfs(adjNode, vis, transposeAdj);
    }
}

int kosaraju(int V, const vector<vector<int>> &adj)
{
    // STEP 1: Sort the vertices in decreasing order of finish time
    vector<int> vis(V, 0);
    stack<int> st;

    for (int i = 0; i < V; i++)
    {
        if (!vis[i])
            dfs(i, vis, st, adj);
    }

    // STEP 2: Create the transposed (reversed) graph and reset the visited array
    vector<vector<int>> transposeAdj(V);
    for (int i = 0; i < V; i++)
    {
        vis[i] = 0; // Reusing the visited array for the second DFS pass

        for (const auto &adjNode : adj[i])
        {
            // Reverse edge direction: i -> adjNode becomes adjNode -> i
            transposeAdj[adjNode].push_back(i);
        }
    }

    // STEP 3: DFS traversal on reversed graph according to finish time order
    int sccCount = 0;

    while (!st.empty())
    {
        int node = st.top();
        st.pop();

        // Each unvisited node popped from the stack starts a new SCC
        if (!vis[node])
        {
            sccCount++;
            transposeDfs(node, vis, transposeAdj);
        }
    }

    return sccCount;
}

int main()
{
    int n = 5;

    // Directed edge list: [u, v] meaning u -> v
    int edges[5][2] = {{1, 0}, {0, 2}, {2, 1}, {0, 3}, {3, 4}};

    vector<vector<int>> adj(n);

    for (int i = 0; i < n; i++)
    {
        adj[edges[i][0]].push_back(edges[i][1]);
    }

    int ans = kosaraju(n, adj);

    cout << "The number of strongly connected components is: " << ans << endl;
    return 0;
}
