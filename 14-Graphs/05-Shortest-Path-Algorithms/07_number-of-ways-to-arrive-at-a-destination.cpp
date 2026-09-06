// ==================================================
// PROBLEM
// - Given n intersections (0 to n-1) and bidirectional weighted roads, determine the number of distinct ways to travel from intersection 0 to intersection n-1 in the shortest time modulo 10^9 + 7.
// ==================================================

#include <bits/stdc++.h>
using namespace std;

#define P pair<long long, int>

// ==================================================
// NUMBER OF WAYS TO ARRIVE AT DESTINATION — DIJKSTRA'S ALGORITHM & DP
//
// Idea:
// - Use Dijkstra's algorithm with a min-priority queue to find the shortest travel time to all nodes while maintaining a 'ways' array. 
// - When a strictly shorter path is found, reset ways[v] = ways[u].
// - If an equal shortest path is found, add to ways[v]: ways[v] = (ways[v] + ways[u]) % MOD.
//
// Time Complexity: O(M * log(N)) - Where N is vertices and M is edges (roads).
// Space Complexity: O(N + M) - For the adjacency list, time & ways arrays, and priority queue.
// ==================================================

int countPaths(int n, const vector<vector<int>> &roads)
{
    // Build adjacency list storing pairs of {destination, travelTime}
    vector<vector<pair<int, int>>> adj(n);

    for (const auto road : roads)
    {
        int u = road[0];
        int v = road[1];
        int time = road[2];

        adj[u].push_back({v, time});
        adj[v].push_back({u, time});
    }

    // 'time' tracks the minimum time to reach each node; 'ways' counts paths of minimum time
    vector<long long> time(n, LLONG_MAX), ways(n, 0);

    time[0] = 0;
    ways[0] = 1;

    // Min-heap storing pairs of {timeTaken, currentNode}
    priority_queue<P, vector<P>, greater<P>> pq;

    // {time, node}
    pq.push({0, 0});

    int MOD = 1e9 + 7;

    while (!pq.empty())
    {
        auto [currTime, currNode] = pq.top();
        pq.pop();

        // Traverse all adjacent intersections
        for (auto adjNode : adj[currNode])
        {
            int nNode = adjNode.first;
            int nTime = adjNode.second;

            // Case 1: Found a strictly shorter path to neighbor
            if (currTime + nTime < time[nNode])
            {
                time[nNode] = currTime + nTime;
                pq.push({currTime + nTime, nNode});
                ways[nNode] = ways[currNode];
            }
            // Case 2: Found an additional path with the same minimal time
            else if (currTime + nTime == time[nNode])
            {
                ways[nNode] = (ways[nNode] + ways[currNode]) % MOD;
            }
        }
    }

    return ways[n - 1] % MOD;
}

int main()
{
    int n = 7, m = 20;

    // Bidirectional road network: [u, v, travelTime]
    vector<vector<int>> roads = {
        {0, 6, 7},
        {0, 1, 2},
        {1, 2, 3},
        {1, 3, 3},
        {6, 3, 3},
        {3, 5, 1},
        {6, 5, 1},
        {2, 5, 1},
        {0, 4, 5},
        {4, 6, 2}};

    int ans = countPaths(n, roads);

    cout << "The number of ways to arrive at destinations in shortest possible time is: " << ans;

    return 0;
}
