// ========================== PROBLEM ==========================
// Given the positions of existing gas stations and k additional
// stations to place, minimize the maximum distance between any
// two adjacent gas stations after all insertions.
// ============================================================

#include <bits/stdc++.h>
using namespace std;

// ========================== BRUTE FORCE APPROACH (GREEDY) ==========================
// Idea:
// Repeatedly place each new gas station in the currently largest gap.
// Keep track of how many stations have been inserted into every gap,
// then compute the largest resulting section length.
//
// Time Complexity: O(k * N) + O(N)
// Space Complexity: O(N)
// ================================================================================
// long double minimiseMaxDistance(vector<int> &arr, int k)
// {
//     int n = arr.size();
//
//     vector<int> placedAt(n - 1, 0);
//
//     for (int gasStation = 1; gasStation <= k; gasStation++)
//     {
//         double maxSectionLength = -1;
//         int maxSectionIndex = -1;
//
//         for (int i = 0; i < n - 1; i++)
//         {
//             double difference = arr[i + 1] - arr[i];
//             double sectionLength = difference / (placedAt[i] + 1);
//
//             if (sectionLength > maxSectionLength)
//             {
//                 maxSectionLength = sectionLength;
//                 maxSectionIndex = i;
//             }
//         }
//
//         placedAt[maxSectionIndex]++;
//     }
//
//     long double minimizedMaxDist = -1;
//
//     for (int i = 0; i < n - 1; i++)
//     {
//         double difference = arr[i + 1] - arr[i];
//         long double sectionLength = (long double)(difference / (placedAt[i] + 1));
//
//         minimizedMaxDist = max(minimizedMaxDist, sectionLength);
//     }
//
//     return minimizedMaxDist;
// }

// ========================== BETTER APPROACH (MAX HEAP) ==========================
// Idea:
// Store every gap in a max heap.
// Always split the largest current section by placing one new station,
// then push the updated section length back into the heap.
//
// Time Complexity: O(k log N + N log N)
// Space Complexity: O(N)
// ================================================================================
// long double minimiseMaxDistance(vector<int> &arr, int k)
// {
//     int n = arr.size();
//
//     vector<int> placedAt(n - 1, 0);
//
//     priority_queue<pair<long double, int>> pq;
//
//     for (int i = 0; i < n - 1; i++)
//         pq.push({(long double)(arr[i + 1] - arr[i]), i});
//
//     for (int gasStation = 1; gasStation <= k; gasStation++)
//     {
//         auto currentMaxGap = pq.top();
//         pq.pop();
//
//         int maxSectionIndex = currentMaxGap.second;
//
//         placedAt[maxSectionIndex]++;
//
//         long double initialDifference = (long double)arr[maxSectionIndex + 1] - (long double)arr[maxSectionIndex];
//
//         long double newDifference = initialDifference / (long double)(placedAt[maxSectionIndex] + 1);
//
//         pq.push({newDifference, maxSectionIndex});
//     }
//
//     return pq.top().first;
// }

// ========================== HELPER FUNCTION ==========================
// Idea:
// Determine how many new gas stations are required so that every
// adjacent gap becomes less than or equal to 'allowedDistance'.
//
// Time Complexity: O(N)
// Space Complexity: O(1)
// =====================================================================
int possibleStationInsertions(vector<int> &arr, long double allowedDistance)
{
    int n = arr.size();

    int stationCounter = 0;

    for (int i = 0; i < n - 1; i++)
    {
        long double currentDistance = arr[i + 1] - arr[i];

        int maxPossibleStationCount = currentDistance / allowedDistance;

        // If the gap is exactly divisible, one fewer station is needed.
        if (currentDistance == (maxPossibleStationCount * allowedDistance))
            maxPossibleStationCount--;

        stationCounter += maxPossibleStationCount;
    }

    return stationCounter;
}

// ========================== OPTIMAL APPROACH (BINARY SEARCH) ==========================
// Idea:
// Binary search on the answer (maximum allowed adjacent distance).
// For each candidate distance, compute how many stations are required.
// - If more than k stations are needed, increase the allowed distance.
// - Otherwise, try a smaller allowed distance.
//
// Time Complexity: O(N * log(Answer Space))
// Space Complexity: O(1)
// ======================================================================================
long double minimiseMaxDistance(vector<int> &arr, int k)
{
    int n = arr.size();

    long double low = 0, high = -1;

    // Maximum existing gap is the upper bound of the answer
    for (int i = 0; i < n - 1; i++)
    {
        high = max(high, (long double)(arr[i + 1] - arr[i]));
    }

    // Continue until the required precision is achieved
    while ((high - low) > 1e-6)
    {
        long double mid = low + ((high - low) / 2.0);

        int counter = possibleStationInsertions(arr, mid);

        // Too many stations required → allowed distance is too small
        if (counter > k)
            low = mid;
        // Feasible → try reducing the maximum allowed distance
        else
            high = mid;
    }

    return high;
}

int main()
{
    vector<int> arr = {
        5, 18, 31, 49, 63, 82, 101, 117, 139, 158,
        176, 201, 223, 247, 269, 294, 319, 343, 370, 396,
        421, 448, 472, 501, 527, 556, 584, 611, 640, 668,
        699, 731, 764, 798, 833, 867, 904, 942, 981, 1023,
        1067, 1112, 1158, 1205, 1253, 1302, 1352, 1403, 1455, 1508};

    int k = 256;

    long double ans = minimiseMaxDistance(arr, k);

    cout << fixed << setprecision(6);
    cout << "The answer is: " << ans << '\n';

    return 0;
}