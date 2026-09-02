// ==================================================
// PROBLEM
// - Given N tasks labeled 0 to N-1 and an array of prerequisites where arr[i] = [a, b] indicates task b must be completed before task a, find a valid order to finish all tasks.
// - Return an empty array if impossible.
// ==================================================

#include <bits/stdc++.h>
using namespace std;

// ==================================================
// COURSE SCHEDULE II — DFS CYCLE DETECTION APPROACH
//
// Idea:
// - Model the tasks as a directed graph. 
// - Use DFS with a path-visited array to detect cycles. 
// - As DFS finishes for a node (all its dependents are explored), push it to a stack. 
// - If no cycle exists, the stack elements provide a valid topological ordering.
//
// Time Complexity: O(N + E) - Where E is the number of prerequisites. Every node and edge is visited at most once.
// Space Complexity: O(N + E) - For the adjacency list, visited arrays, and recursion stack.
// ==================================================

bool dfs(int node, vector<int> &vis, vector<int> &pathVis, vector<vector<int>> &adj, stack<int> &st)
{
    // Mark node as visited and actively in the current recursion path
    vis[node] = 1;
    pathVis[node] = 1;

    // Traverse all dependent tasks (adjacent nodes)
    for (int adjNode : adj[node])
    {
        if (!vis[adjNode])
        {
            if (dfs(adjNode, vis, pathVis, adj, st) == true)
                return true;
        }
        // If the adjacent node is already in the current path, a cycle is detected
        else if (pathVis[adjNode] == 1)
            return true;
    }

    // Backtrack: remove node from current path and push to topological sort stack
    pathVis[node] = 0;
    st.push(node);

    return false;
}

vector<int> findOrder(int N, const vector<vector<int>> &arr)
{
    vector<vector<int>> adj(N);

    // Build directed graph: prerequisite -> dependent task
    for (int i = 0; i < arr.size(); i++)
    {
        adj[arr[i][1]].push_back(arr[i][0]);
    }

    vector<int> vis(N, 0);
    vector<int> pathVis(N, 0);

    stack<int> st;

    // Traverse all components to ensure no disconnected tasks are missed
    for (int i = 0; i < N; i++)
    {
        if (!vis[i])
        {
            // If a cycle is found, a valid ordering is impossible
            if (dfs(i, vis, pathVis, adj, st) == true)
                return {};
        }
    }

    vector<int> result;

    // Transfer elements from stack to result array for the final ordering
    while (!st.empty())
    {
        result.push_back(st.top());
        st.pop();
    }

    return result;
}

// ==================================================
// COURSE SCHEDULE II — BFS TOPOLOGICAL SORT APPROACH (KAHN'S ALGORITHM)
//
// Idea:
// - Represent the tasks as a directed graph and compute the in-degree (number of prerequisites) for each node. 
// - Process nodes with 0 in-degree using a queue. 
// - If the resulting sequence contains all N tasks, return it; otherwise, a cycle exists, and an empty array is returned.
//
// Time Complexity: O(N + E) - Processing nodes and computing in-degrees takes linear time.
// Space Complexity: O(N + E) - For the adjacency list, in-degree array, queue, and result array.
// ==================================================

vector<int> findOrder(int N, const vector<vector<int>> &arr)
{
    vector<vector<int>> adj(N);

    // Build directed graph: prerequisite -> dependent task
    for (int i = 0; i < arr.size(); i++)
    {
        adj[arr[i][1]].push_back(arr[i][0]);
    }

    vector<int> indegree(N, 0);

    // Calculate in-degree (number of prerequisites) for each task
    for (int i = 0; i < N; i++)
    {
        for (int adjNode : adj[i])
        {
            indegree[adjNode]++;
        }
    }

    queue<int> q;

    // Enqueue all tasks that currently have no prerequisites
    for (int i = 0; i < N; i++)
    {
        if (indegree[i] == 0)
            q.push(i);
    }

    vector<int> result;

    // Process nodes level-by-level
    while (!q.empty())
    {
        int topNode = q.front();
        q.pop();

        // Append processed task to the topological ordering
        result.push_back(topNode);

        // Reduce the in-degree of all dependent tasks
        for (int adjNode : adj[topNode])
        {
            indegree[adjNode]--;

            // If a dependent task now has zero prerequisites, it's ready to be processed
            if (indegree[adjNode] == 0)
                q.push(adjNode);
        }
    }

    // If all tasks are successfully processed, return the ordering; else, cycle detected
    if (result.size() == N)
        return result;

    return {};
}

int main()
{
    int N = 4;

    // Prerequisites array: [a, b] means b -> a
    vector<vector<int>> arr = {
        {1, 0},
        {2, 1},
        {3, 2}};

    vector<int> ans = findOrder(N, arr);

    cout << "The order to perform tasks is:\n";

    for (int i = 0; i < ans.size(); i++)
    {
        cout << ans[i] << " ";
    }

    return 0;
}
