// ========================== PROBLEM ==========================
// A monkey has multiple banana piles and can eat k bananas per hour
// from a single pile. Find the minimum eating speed k such that all
// bananas are consumed within h hours.
// ============================================================

#include <bits/stdc++.h>
using namespace std;

// ========================== HELPER FUNCTION ==========================
// Idea:
// Traverse the array and return the maximum element.
// The maximum pile size serves as the upper bound for the search space.
//
// Time Complexity: O(N)
// Space Complexity: O(1)
// =====================================================================
int maxArrayElem(vector<int> &nums)
{
    int maxElem = INT_MIN;

    for (int it : nums)
        maxElem = max(maxElem, it);

    return maxElem;
}

// ========================== HELPER FUNCTION ==========================
// Idea:
// Compute the total number of hours required to finish all piles
// if the monkey eats at a fixed rate of k bananas per hour.
//
// Time Complexity: O(N)
// Space Complexity: O(1)
// =====================================================================
int totalHoursForGivenRate(vector<int> &nums, int k)
{
    int ans = 0;

    for (int i = 0; i < nums.size(); i++)
    {
        ans += ceil((double)nums[i] / (double)k);
    }

    return ans;
}

// ========================== BRUTE FORCE APPROACH (LINEAR SEARCH) ==========================
// Idea:
// Try every possible eating speed from 1 to the maximum pile size.
// Return the first speed that allows the monkey to finish within h hours.
//
// Time Complexity: O(Max array element * Size of array)
// Space Complexity: O(1)
// ==========================================================================================
// int minimumRateToEatBananas(vector<int> &nums, int h)
// {
//     int maxElem = maxArrayElem(nums);
//
//     for (int i = 1; i <= maxElem; i++)
//     {
//         int totalHrs = totalHoursForGivenRate(nums, i);
//
//         if (totalHrs <= h)
//             return i;
//     }
//
//     return -1;
// }

// ========================== OPTIMAL APPROACH (BINARY SEARCH) ==========================
// Idea:
// The minimum eating speed lies between 1 and the largest pile size.
// Use binary search on this range.
// - If current speed finishes within h hours, try a smaller speed.
// - Otherwise, increase the speed.
//
// Time Complexity: O(N * log(Max array element))
// Space Complexity: O(1)
// =====================================================================================
int minimumRateToEatBananas(vector<int> &nums, int h)
{
    int low = 1, high = maxArrayElem(nums);

    while (low <= high)
    {
        int mid = low + ((high - low) / 2);

        int totalHrs = totalHoursForGivenRate(nums, mid);

        // Current speed is sufficient; search for a smaller valid speed
        if (totalHrs <= h)
            high = mid - 1;
        // Current speed is too slow; increase the eating rate
        else
            low = mid + 1;
    }

    // 'low' stores the minimum valid eating speed
    return low;
}

int main()
{
    vector<int> pile = {25, 12, 8, 14, 19};
    int h = 5;

    int ans = minimumRateToEatBananas(pile, h);

    cout << ans;

    return 0;
}