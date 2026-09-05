// ==================================================
// PROBLEM
// - Given a start number, an end number, and an array of integers 'arr', find the minimum multiplications (each step modulo 100000) needed to reach 'end' from 'start'.
// - Return -1 if unreachable.
// ==================================================

#include <bits/stdc++.h>
using namespace std;

// ==================================================
// MINIMUM MULTIPLICATIONS TO REACH END — BFS APPROACH
//
// Idea:
// - Treat each value modulo 100000 as a node in a graph of size 10^5.
// - Since each multiplication has a uniform edge weight of 1, apply Breadth-First Search (BFS) starting from 'start' to find the shortest path level-by-level.
//
// Time Complexity: O(10^5 * N) - Where 10^5 is the state space (MOD) and N is the size of arr.
// Space Complexity: O(10^5) - For the steps array and BFS queue.
// ==================================================

int minimumMultiplications(const vector<int> &arr, int start, int end)
{
    // Base case: Already at destination
    if (start == end)
        return 0;

    const int MOD = 100000;

    // Array to track the minimum steps to reach each value (0 to 99999)
    vector<int> steps(MOD, 1e9);

    steps[start] = 0;

    // Queue stores pairs of {stepsTaken, currentNode}
    queue<pair<int, int>> q;

    q.push({0, start});

    while (!q.empty())
    {
        auto [currSteps, currNode] = q.front();
        q.pop();

        // Destination reached: First time popping 'end' guarantees minimum steps
        if (currNode == end)
            return currSteps;

        // Try multiplying with every number in the array
        for (auto num : arr)
        {
            int nMultiple = (currNode * num) % MOD;

            // If this node has not been reached before, assign its distance and enqueue it.
            if (currSteps + 1 < steps[nMultiple])
            {
                steps[nMultiple] = currSteps + 1;
                q.push({currSteps + 1, nMultiple});
            }
        }
    }

    return -1;
}

int main()
{
    int start = 3, end = 30;

    // Array of multipliers
    vector<int> arr = {2, 5, 7};

    int ans = minimumMultiplications(arr, start, end);

    cout << "The minimum multiplications to reach end is: " << ans;

    return 0;
}
