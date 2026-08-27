// Problem:
// Represent a graph in C++ using an adjacency matrix or an adjacency list.
// The given examples represent an undirected graph, where each edge connects two vertices.

#include <bits/stdc++.h>
using namespace std;

// ==================================================
// ADJACENCY MATRIX
// Idea:
// - Use a 2D matrix where adj[u][v] indicates whether an edge exists between vertices u and v.
// - For an undirected graph, both adj[u][v] and adj[v][u] are set to 1.
//
// Time Complexity: O(1) to add an edge; O(1) to check whether an edge exists
// Space Complexity: O(V^2)
// ==================================================

// int main()
// {
//     int n, m;
//     cin >> n, m;

//     int adj[n+1][n+1];

//     for (int i = 0; i < m; i++)
//     {
//         int u, v;

//         cin >> u, v;

//         adj[u][v] = 1;
//         adj[v][u] = 1;
//     }

//     return 0;
// }

// ==================================================
// ADJACENCY LIST
// Idea:
// - Store a list of neighboring vertices for each vertex.
// - For an undirected graph, add each endpoint to the other's adjacency list.
// - This representation is generally more space-efficient for sparse graphs.
//
// Time Complexity: O(1) amortized to add an edge
// Space Complexity: O(V + E)
// ==================================================

int main()
{

    int n, m;
    cin >> n, m;

    vector<vector<int>> adj(n + 1);

    for (int i = 0; i < m; i++)
    {
        int u, v;

        cin >> u, v;

        adj[u].push_back(v);
        adj[v].push_back(u);
    }

    return 0;
}