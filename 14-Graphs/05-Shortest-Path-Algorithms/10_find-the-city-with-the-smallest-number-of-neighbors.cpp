// ==================================================
// PROBLEM
// - Given n cities and an array of weighted bidirectional edges, find the city with the smallest number of reachable cities within a given distance threshold.
// - If multiple such cities exist, return the city with the greatest index.
// ==================================================

#include <bits/stdc++.h>
using namespace std;

// ==================================================
// FIND CITY WITH SMALLEST NUMBER OF NEIGHBORS — FLOYD-WARSHALL APPROACH
//
// Idea:
// - Compute the shortest distance between all pairs of cities using the Floyd-Warshall algorithm. 
// - For each city, count the number of other cities reachable within distanceThreshold. 
// - Select the city with the minimum reachable count, breaking ties in favor of the greater city index.
//
// Time Complexity: O(N³) - For the three nested loops in Floyd-Warshall relaxation.
// Space Complexity: O(N²) - For the 2D distance matrix (adjMat).
// ==================================================

int findCity(int n, int m, const vector<vector<int>> &edges, int distanceThreshold)
{
    const int INF = 1e9;

    // Initialize distance matrix with infinity
    vector<vector<int>> adjMat(n, vector<int>(n, INF));

    for (const auto edge : edges)
    {
        int u = edge[0];
        int v = edge[1];
        int dist = edge[2];

        adjMat[u][v] = dist;
        adjMat[v][u] = dist;
    }

    // Distance from a city to itself is 0
    for (int row = 0; row < n; row++)
    {
        for (int col = 0; col < n; col++)
        {
            if (row == col)
                adjMat[row][col] = 0;
        }
    }

    // Floyd-Warshall: Try all intermediate cities (via) to find shortest paths
    for (int via = 0; via < n; via++)
    {
        for (int row = 0; row < n; row++)
        {
            for (int col = 0; col < n; col++)
            {
                if (adjMat[row][via] == INF || adjMat[via][col] == INF)
                    continue;

                adjMat[row][col] = min(adjMat[row][col], adjMat[row][via] + adjMat[via][col]);
            }
        }
    }

    int minPassingCityCnt = n;

    int minCity = -1;

    // Count reachable cities within threshold for each city
    for (int city = 0; city < n; city++)
    {
        int passingCityCnt = 0;

        for (int adjCity = 0; adjCity < n; adjCity++)
        {
            if (adjMat[city][adjCity] <= distanceThreshold)
                passingCityCnt++;
        }

        // Pick city with fewer reachable neighbors, or greater index on a tie
        if (passingCityCnt <= minPassingCityCnt)
        {
            minPassingCityCnt = passingCityCnt;
            minCity = city;
        }
    }

    return minCity;
}

int main()
{
    int N = 4, M = 4;

    // Bidirectional weighted edges: [from, to, weight]
    vector<vector<int>> edges = {{0, 1, 3}, {1, 2, 1}, {1, 3, 4}, {2, 3, 1}};

    int distanceThreshold = 4;

    int ans = findCity(N, M, edges, distanceThreshold);

    cout << "The city with smallest number of neighbors (with given threshold) is: " << ans;

    return 0;
}
