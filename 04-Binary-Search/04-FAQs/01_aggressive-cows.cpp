// ========================== PROBLEM ==========================
// Given the positions of stalls and k aggressive cows, place the
// cows in different stalls such that the minimum distance between
// any two cows is maximized. Return this maximum possible distance.
// ============================================================

#include <bits/stdc++.h>
using namespace std;

// ========================== HELPER FUNCTION ==========================
// Idea:
// Greedily place the first cow in the first stall. Then place each
// subsequent cow in the leftmost stall that is at least 'minDistance'
// away from the previously placed cow.
//
// Time Complexity: O(N)
// Space Complexity: O(1)
// =====================================================================
bool canPlace(vector<int> &stalls, int cowCount, int minDistance)
{
    int placedCowsCount = 1, lastCowCoordinate = stalls[0];

    for (int i = 1; i < stalls.size(); i++)
    {
        if (stalls[i] - lastCowCoordinate >= minDistance)
        {
            placedCowsCount++;
            lastCowCoordinate = stalls[i];
        }

        if (placedCowsCount >= cowCount)
            return true;
    }

    return false;
}

// ========================== BRUTE FORCE APPROACH (LINEAR SEARCH) ==========================
// Idea:
// Sort the stall positions and try every possible minimum distance
// from 1 up to the maximum possible distance. Return the largest
// distance for which all cows can still be placed.
//
// Time Complexity: O((Maximum distance) * N) + O(N log N)
// Space Complexity: O(1)
// ==========================================================================================
// int aggressiveCows(vector<int> &nums, int k)
// {
//     int n = nums.size();
//
//     if (k > n)
//         return -1;
//
//     sort(nums.begin(), nums.end());
//
//     int min = 1, max = nums[n - 1];
//
//     for (int i = 1; i <= max - min + 1; i++)
//     {
//         if (canPlace(nums, k, i))
//             continue;
//         else
//             return (i - 1);
//     }
//
//     return -1;
// }

// ========================== OPTIMAL APPROACH (BINARY SEARCH) ==========================
// Idea:
// The answer lies between 1 and the maximum possible distance between
// the first and last stall. Use binary search on this range.
// - If cows can be placed with the current distance, try a larger distance.
// - Otherwise, reduce the distance.
//
// Time Complexity: O(N log N) + O(N * log(Maximum distance))
// Space Complexity: O(1)
// ======================================================================================
int aggressiveCows(vector<int> &nums, int k)
{
    int n = nums.size();

    if (k > n)
        return -1;

    // Sort stalls to enable greedy placement
    sort(nums.begin(), nums.end());

    int low = 1, high = nums[n - 1] - nums[0];

    while (low <= high)
    {
        int mid = low + ((high - low) / 2);

        // Current minimum distance is feasible; try increasing it
        if (canPlace(nums, k, mid))
            low = mid + 1;
        // Current minimum distance is too large
        else
            high = mid - 1;
    }

    // 'high' stores the largest feasible minimum distance
    return high;
}

int main()
{
    vector<int> stalls = {10, 1, 2, 7, 5};

    int cowCount = 3;

    int ans = aggressiveCows(stalls, cowCount);

    cout << ans;

    return 0;
}