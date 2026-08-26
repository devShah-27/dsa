// Problem:
// Given an undirected graph with N vertices and M available colors, determine whether the graph can be colored such that no two adjacent vertices have the same color.
// Return true if a valid coloring exists, otherwise return false.

#include <bits/stdc++.h>
using namespace std;

// ============================================================================
// BACKTRACKING APPROACH
//
// Idea:
// Assign colors to vertices one by one using recursion.
// For every vertex, try all available colors and choose a color only if it does not conflict with any already-colored adjacent vertex.
// Backtrack whenever a coloring choice leads to an invalid state.
//
// Time Complexity: O(M^N) where M is the number of colors and N is vertices
// Space Complexity: O(N) for color array and recursion stack
// ============================================================================

// Checks whether assigning currColor to a node is valid.
bool isColorPossible(int node, vector<int> &colors, vector<vector<int>> &adj, int currColor)
{
    vector<int> adjacentNodes = adj[node];

    // Check all adjacent vertices for color conflicts.
    for (int i = 0; i < adjacentNodes.size(); i++)
    {
        if (colors[adjacentNodes[i]] == currColor)
            return false;
    }

    return true;
}

bool recursiveGraphColoring(int node, int colorCount, int nodeCount, vector<int> &colors, vector<vector<int>> &adj)
{
    // All vertices have been assigned a valid color.
    if (node == nodeCount)
        return true;

    // Try assigning every available color to the current vertex.
    for (int i = 1; i <= colorCount; i++)
    {
        if (isColorPossible(node, colors, adj, i))
        {
            // Assign the current color.
            colors[node] = i;

            // Continue coloring the remaining vertices.
            if (recursiveGraphColoring(node + 1, colorCount, nodeCount, colors, adj))
                return true;

            // Backtrack if this color assignment does not lead to a solution.
            colors[node] = 0;
        }
    }

    return false;
}

bool graphColoring(vector<vector<int>> &edges, int colorCount, int nodeCount)
{
    // Build adjacency list representation of the graph.
    vector<vector<int>> adj(nodeCount);

    for (int i = 0; i < edges.size(); i++)
    {
        adj[edges[i][0]].push_back(edges[i][1]);
        adj[edges[i][1]].push_back(edges[i][0]);
    }

    // 0 represents that the vertex is not colored yet.
    vector<int> colors(nodeCount, 0);

    return recursiveGraphColoring(0, colorCount, nodeCount, colors, adj);
}

int main()
{
    vector<vector<int>> edges = {
        {0, 1}, {0, 2}, {0, 3}, {0, 4}, {0, 5}, {1, 2}, {1, 3}, {1, 4}, {1, 5}, {2, 3}, {2, 4}, {2, 5}, {3, 4}, {3, 5}, {4, 5}};

    int m = 5;
    int n = 6;

    if (graphColoring(edges, m, n))
    {
        cout << "The graph can be colored with " << m << " colors." << endl;
    }
    else
    {
        cout << "The graph cannot be colored with " << m << " colors." << endl;
    }

    return 0;
}