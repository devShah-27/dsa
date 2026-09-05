// ==================================================
// PROBLEM
// - Given n cities connected by flights with given costs, find the cheapest price from src to dst with at most K intermediate stops.
// - If no such route exists, return -1.
// ==================================================

#include <bits/stdc++.h>
using namespace std;

#define P pair<int, pair<int, int>>

// ==================================================
// CHEAPEST FLIGHTS WITHIN K STOPS — BFS / LEVEL-ORDER APPROACH
//
// Idea:
// - Model the cities and flight costs as a directed weighted graph.
// - Use a BFS queue tracking {currentCost, {stops, currentNode}} to explore paths level-by-level, ensuring we do not exceed K stops.
// - Relax adjacent edges whenever a lower cost is found for a reachable city.
//
// Time Complexity: O(K * E) - Where E is the number of flights and K is the maximum stops allowed.
// Space Complexity: O(V + E) - For the adjacency list, distance array, and BFS queue.
// ==================================================

int CheapestFlight(int n, const vector<vector<int>> &flights, int src, int dst, int K)
{
    // Build adjacency list: u -> {v, cost}
    vector<vector<pair<int, int>>> adj(n);

    for (const auto flight : flights)
    {
        int u = flight[0];
        int v = flight[1];
        int cost = flight[2];

        adj[u].push_back({v, cost});
    }

    // Array to store the minimum cost to reach each city
    vector<int> minCost(n, 1e9);

    minCost[src] = 0;

    // Queue stores {currentCost, {stopsTaken, currentNode}}
    queue<P> q;

    q.push({0, {0, src}});

    // Perform BFS level-order traversal
    while (!q.empty())
    {
        auto [currCost, state] = q.front();
        q.pop();

        int stops = state.first;
        int currNode = state.second;

        // Skip further expansion if the number of stops exceeds the limit K
        if (stops > K)
            continue;

        // Explore all outgoing flights from the current city
        for (auto [nNode, nCost] : adj[currNode])
        {
            int totalCost = currCost + nCost;

            // If a cheaper route to the destination city is found within stop limits
            if (totalCost < minCost[nNode])
            {
                minCost[nNode] = totalCost;
                q.push({totalCost, {stops + 1, nNode}});
            }
        }
    }

    return minCost[dst] == 1e9 ? -1 : minCost[dst];
}

int main()
{
    int n = 4;

    // Flight list: [from, to, price]
    vector<vector<int>> flights = {
        {0, 1, 100},
        {1, 2, 100},
        {2, 0, 100},
        {1, 3, 600},
        {2, 3, 200}};

    int src = 0, dst = 3, k = 1;

    int ans = CheapestFlight(n, flights, src, dst, k);

    cout << "The cheapest flight from source to destination within K stops is: " << ans;

    return 0;
}
