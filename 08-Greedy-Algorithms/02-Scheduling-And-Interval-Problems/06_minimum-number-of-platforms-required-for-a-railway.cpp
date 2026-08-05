// Problem:
// Given arrival and departure times of trains at a railway station, determine the minimum number of platforms required so that no train has to wait.
// A platform cannot be reused until the previous train has departed.

#include <bits/stdc++.h>
using namespace std;

// ==================================================
// BRUTE FORCE APPROACH
//
// Idea:
// For every train, count how many other trains are present at the station when the current train arrives. The maximum overlap found represents the minimum number of platforms required.
//
// Time Complexity: O(N^2)
// Space Complexity: O(1)
// ==================================================

// int findPlatform(vector<int> &Arrival, vector<int> &Departure)
// {
//     int n = Arrival.size();

//     int maxTrainCount = 0;

//     for (int i = 0; i < n; i++)
//     {
//         int trainCount = 1;

//         for (int j = 0; j < n; j++)
//         {
//             if (i != j)
//             {
//                 // Check if train j is present when train i arrives.
//                 if (Arrival[i] >= Arrival[j] && Departure[j] >= Arrival[i])
//                 {
//                     trainCount++;
//                 }
//             }
//         }

//         maxTrainCount = max(maxTrainCount, trainCount);
//     }

//     return maxTrainCount;
// }

// ==================================================
// OPTIMAL APPROACH
//
// Idea:
// Sort arrival and departure times separately and use two pointers.
// When a train arrives before the earliest departure, a new platform is needed.
// Otherwise, a platform is freed by a departing train.
//
// Time Complexity: O(N log N)
// Space Complexity: O(1)
// ==================================================

int findPlatform(vector<int> &Arrival, vector<int> &Departure)
{
    sort(Arrival.begin(), Arrival.end());
    sort(Departure.begin(), Departure.end());

    int n = Arrival.size();

    int i = 0, j = 0;

    int platformCount = 0, maxPlatformCount = 0;

    while (i < n)
    {
        if (Arrival[i] <= Departure[j])
        {
            platformCount++;
            i++;
        }
        else
        {
            platformCount--;
            j++;
        }

        maxPlatformCount = max(maxPlatformCount, platformCount);
    }

    return maxPlatformCount;
}

int main()
{
    vector<int> arr = {900, 945, 955, 1100, 1500, 1800};
    vector<int> dep = {920, 1200, 1130, 1150, 1900, 2000};

    int n = dep.size();

    int ans = findPlatform(arr, dep);

    cout << "Minimum number of Platforms required: " << ans << endl;

    return 0;
}