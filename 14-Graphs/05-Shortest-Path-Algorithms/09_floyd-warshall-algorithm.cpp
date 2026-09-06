// ==================================================
// PROBLEM
// - Given an n x n adjacency matrix representing a weighted directed graph with V vertices, find the shortest distances between every pair of vertices.
// - If there is no edge from vertex i to vertex j, matrix[i][j] is -1.
// ==================================================

#include <bits/stdc++.h>
using namespace std;

// ==================================================
// FLOYD-WARSHALL ALGORITHM — ALL-PAIRS SHORTEST PATH APPROACH
//
// Idea:
// - Use dynamic programming to find shortest paths between all pairs of nodes.
// - Iterate through every intermediate node 'k' and relax the path between every pair (i, j) by checking if routing through 'k' offers a shorter route: matrix[i][j] = min(matrix[i][j], matrix[i][k] + matrix[k][j]).
//
// Time Complexity: O(N³) - Three nested loops iterating from 0 to N-1.
// Space Complexity: O(1) - Modifies the adjacency matrix in-place without extra auxiliary space.
// ==================================================

void shortestDistance(vector<vector<int>> &matrix)
{
    const int INF = 1e9;

    int n = matrix.size();

    // Step 1: Pre-process the matrix (replace -1 with infinity 1e9, set diagonal to 0)
    for (int row = 0; row < n; row++)
    {
        for (int col = 0; col < n; col++)
        {
            if (matrix[row][col] == -1)
                matrix[row][col] = INF;

            if (row == col)
                matrix[row][col] = 0;
        }
    }

    // Step 2: Floyd-Warshall core DP relaxation via every intermediate node
    for (int interimNode = 0; interimNode < n; interimNode++)
    {
        for (int row = 0; row < n; row++)
        {
            for (int col = 0; col < n; col++)
            {
                if (matrix[row][interimNode] == INF || matrix[interimNode][col] == INF)
                    continue;

                matrix[row][col] = min(matrix[row][col], (matrix[row][interimNode] + matrix[interimNode][col]));
            }
        }
    }

    // Step 3: Post-process the matrix (convert unreachable 1e9 values back to -1)
    for (int row = 0; row < n; row++)
    {
        for (int col = 0; col < n; col++)
        {
            if (matrix[row][col] == INF)
                matrix[row][col] = -1;
        }
    }
}

int main()
{
    // Adjacency matrix representation (-1 indicates no direct edge)
    vector<vector<int>> matrix = {
        {0, 2, -1, -1},
        {1, 0, 3, -1},
        {-1, -1, 0, 1},
        {3, 5, 4, 0}};

    shortestDistance(matrix);

    int n = matrix.size();

    cout << "The shortest distance matrix is:\n";

    for (int i = 0; i < n; i++)
    {
        for (int j = 0; j < n; j++)
        {
            cout << matrix[i][j] << " ";
        }
        cout << endl;
    }

    return 0;
}
