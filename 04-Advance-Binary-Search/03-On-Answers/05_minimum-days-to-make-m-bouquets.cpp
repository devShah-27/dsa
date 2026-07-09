// ========================== PROBLEM ==========================
// Given the bloom day of each rose, determine the minimum day
// required to make at least m bouquets, where each bouquet
// consists of exactly k adjacent bloomed roses.
// ============================================================

#include <bits/stdc++.h>
using namespace std;

// ========================== HELPER FUNCTION ==========================
// Idea:
// Traverse the array and return the minimum bloom day.
// This defines the lower bound of the binary search.
//
// Time Complexity: O(N)
// Space Complexity: O(1)
// =====================================================================
int minElem(vector<int> &nums)
{
    int mini = INT_MAX;

    for (int it : nums)
        mini = min(mini, it);

    return mini;
}

// ========================== HELPER FUNCTION ==========================
// Idea:
// Traverse the array and return the maximum bloom day.
// This defines the upper bound of the binary search.
//
// Time Complexity: O(N)
// Space Complexity: O(1)
// =====================================================================
int maxElem(vector<int> &nums)
{
    int maxi = INT_MIN;

    for (int it : nums)
        maxi = max(maxi, it);

    return maxi;
}

// ========================== HELPER FUNCTION ==========================
// Idea:
// Check whether it is possible to make at least m bouquets by
// 'dayCount'. Consecutive bloomed roses are grouped together,
// and every group contributes (groupSize / k) bouquets.
//
// Time Complexity: O(N)
// Space Complexity: O(1)
// =====================================================================
bool possibleDay(vector<int> &nums, int dayCount, int k, int m)
{
    int numberOfBouquetsPossible = 0, counter = 0;

    for (int i = 0; i < nums.size(); i++)
    {
        if (nums[i] <= dayCount)
        {
            counter++;
        }
        else
        {
            numberOfBouquetsPossible += counter / k;
            counter = 0;
        }
    }

    // Count bouquets from the final consecutive bloomed segment
    numberOfBouquetsPossible += counter / k;

    return numberOfBouquetsPossible >= m;
}

// ========================== BRUTE FORCE APPROACH (LINEAR SEARCH) ==========================
// Idea:
// Try every possible day from the earliest bloom day to the latest.
// Return the first day on which at least m bouquets can be formed.
//
// Time Complexity: O((Max bloom day - Min bloom day + 1) * N)
// Space Complexity: O(1)
// ==========================================================================================
// int roseGarden(int n, vector<int> nums, int k, int m)
// {
//     if (n < (m * 1LL * k * 1LL))
//         return -1;
//
//     int minimumElem = minElem(nums), maximumElem = maxElem(nums);
//
//     for (int i = minimumElem; i <= maximumElem; i++)
//     {
//         if (possibleDay(nums, i, k, m))
//             return i;
//     }
//
//     return -1;
// }

// ========================== OPTIMAL APPROACH (BINARY SEARCH) ==========================
// Idea:
// The answer lies between the minimum and maximum bloom day.
// Use binary search on this range.
// - If bouquets can be formed on the current day, search earlier days.
// - Otherwise, search later days.
//
// Time Complexity: O(N * log(Max bloom day - Min bloom day + 1))
// Space Complexity: O(1)
// =====================================================================================
int roseGarden(int n, vector<int> nums, int k, int m)
{
    // Impossible if total required roses exceed available roses
    if (n < (m * 1LL * k * 1LL))
        return -1;

    int low = minElem(nums), high = maxElem(nums);

    while (low <= high)
    {
        int mid = low + ((high - low) / 2);

        if (possibleDay(nums, mid, k, m))
            high = mid - 1;
        else
            low = mid + 1;
    }

    // 'low' stores the minimum feasible day
    return low;
}

int main()
{
    vector<int> bloomDays = {7, 7, 7, 7, 13, 11, 12, 7};

    int numberOfBouquetsRequired = 2, numberOfFlowersPerBouquet = 3;

    int ans = roseGarden(bloomDays.size(), bloomDays, numberOfFlowersPerBouquet, numberOfBouquetsRequired);

    cout << ans;

    return 0;
}