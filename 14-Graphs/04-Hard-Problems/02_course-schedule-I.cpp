// ==================================================
// PROBLEM
// - Given N tasks labeled 0 to N-1 and an array of prerequisites where arr[i] = [a, b] indicates task b must be completed before task a, determine if it is possible to finish all tasks.
// ==================================================

#include <bits/stdc++.h>
using namespace std;

// ==================================================
// COURSE SCHEDULE — DFS CYCLE DETECTION APPROACH
//
// Idea:
// - Model the tasks and prerequisites as a directed graph. 
// - The problem reduces to detecting a cycle in this directed graph. 
// - Use DFS with a path-visited array to track active recursive calls. 
// - If a cycle is found, tasks cannot be completed.
//
// Time Complexity: O(N + E) - Where E is the number of prerequisites. Every node and edge is visited at most once.
// Space Complexity: O(N + E) - For the adjacency list, visited arrays, and recursion stack.
// ==================================================

// Helper function to detect cycle in a directed graph using DFS
bool dfs(int node, vector<int> &vis, vector<int> &pathVis, vector<vector<int>> &adj)
{
    // Mark the current node as visited and add it to the current path
    vis[node] = 1;
    pathVis[node] = 1;

    // Traverse all dependent tasks (adjacent nodes)
    for (int adjNode : adj[node])
    {
        if (!vis[adjNode])
        {
            if (dfs(adjNode, vis, pathVis, adj) == true)
                return true;
        }
        // If the adjacent node is already in the current recursion path, a cycle exists
        else if (pathVis[adjNode])
        {
            return true;
        }
    }

    // Backtrack: remove node from the current path
    pathVis[node] = 0;

    return false;
}

bool dfsSolution(int N, const vector<vector<int>> &arr)
{
    // Create an adjacency list from the prerequisites array
    vector<vector<int>> adj(N);

    for (int i = 0; i < arr.size(); i++)
    {
        // Directed edge from prerequisite to dependent task
        adj[arr[i][1]].push_back(arr[i][0]);
    }

    vector<int> vis(N, 0);
    vector<int> pathVis(N, 0);

    // Check every node to ensure all disconnected components are covered
    for (int i = 0; i < N; i++)
    {
        if (!vis[i])
        {
            // If a cycle is detected, it's impossible to finish all tasks
            if (dfs(i, vis, pathVis, adj) == true)
                return false;
        }
    }

    return true;
}

// ==================================================
// COURSE SCHEDULE — BFS TOPOLOGICAL SORT APPROACH (KAHN'S ALGORITHM)
//
// Idea:
// - Represent tasks as a directed graph and calculate the in-degree of each node.
// - Process nodes with 0 in-degree (no prerequisites) using a queue. 
// - If the total number of processed nodes equals N, a valid topological sort exists (no cycles).
//
// Time Complexity: O(N + E) - Processing nodes and computing in-degrees takes linear time.
// Space Complexity: O(N + E) - For the adjacency list, in-degree array, and queue.
// ==================================================

bool bfsSolution(int N, const vector<vector<int>> &arr)
{
    vector<vector<int>> adj(N);

    // Build adjacency list
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

    // Enqueue all tasks that have no prerequisites
    for (int i = 0; i < N; i++)
    {
        if (indegree[i] == 0)
            q.push(i);
    }

    int counter = 0;

    // Process nodes level-by-level
    while (!q.empty())
    {
        int topNode = q.front();
        q.pop();

        counter++;

        // Reduce the in-degree of dependent tasks
        for (int adjNode : adj[topNode])
        {
            indegree[adjNode]--;

            // If a task has no more remaining prerequisites, add it to the queue
            if (indegree[adjNode] == 0)
                q.push(adjNode);
        }
    }

    // If all tasks were successfully processed, a valid topological ordering exists
    return (counter == N);
}

bool canFinish(int N, vector<vector<int>> arr)
{
    return dfsSolution(N, arr) && bfsSolution(N, arr);
}

int main()
{
    int N = 4;
    // Prerequisites array: [a, b] means b -> a
    vector<vector<int>> arr = {
        {1, 0},
        {2, 1},
        {3, 2}};

    bool ans = canFinish(N, arr);

    if (ans)
        cout << "All the tasks can be finished.";
    else
        cout << "All the tasks can not be finished.";

    return 0;
}
