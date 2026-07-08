// ========================== PROBLEM ==========================
// Given an integer array and a limit value, find the smallest positive divisor such that the sum of the ceiling values of all elements divided by this divisor is less than or equal to limit.
// ============================================================

#include <bits/stdc++.h>
using namespace std;

// ========================== HELPER FUNCTION ==========================
// Idea:
// Traverse the array and return the maximum element.
// The maximum element defines the upper bound for possible divisors.
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

// ========================== BRUTE FORCE APPROACH (LINEAR SEARCH) ==========================
// Idea:
// Try every possible divisor from 1 to the maximum array element.
// For each divisor, calculate the sum of ceiling divisions.
// Return the first divisor satisfying the given limit.
//
// Time Complexity: O(Max element of array * Size of array)
// Space Complexity: O(1)
// ==========================================================================================
// int smallestDivisor(vector<int> &nums, int limit)
// {
//     int size = nums.size();
//
//     int maxArrayElement = maxArrayElem(nums);
//
//     for (int i = 1; i <= maxArrayElement; i++)
//     {
//         int sum = 0;
//
//         for (int j = 0; j < size; j++)
//         {
//             sum += ceil((double)nums[j] / (double)i);
//         }
//
//         if (sum <= limit)
//             return i;
//     }
//
//     return -1;
// }

// ========================== OPTIMAL APPROACH (BINARY SEARCH) ==========================
// Idea:
// The required divisor lies between 1 and the maximum array element.
// Use binary search on this range.
// For each mid divisor, calculate the required sum:
// - If sum <= limit, try smaller divisors.
// - Otherwise, increase the divisor.
//
// Time Complexity: O(N * log(Max element of array))
// Space Complexity: O(1)
// =====================================================================================
int smallestDivisor(vector<int> &nums, int limit)
{
    int size = nums.size();

    // Minimum possible sum is equal to number of elements.
    // If elements are more than the limit, no divisor can satisfy the condition.
    if (size > limit)
        return -1;

    int low = 1, high = maxArrayElem(nums), ans = -1;

    while (low <= high)
    {
        int mid = low + ((high - low) / 2);

        int sum = 0;

        for (int i = 0; i < size; i++)
        {
            sum += ceil((double)nums[i] / (double)mid);
        }

        // Valid divisor found, search for a smaller one
        if (sum <= limit)
        {
            ans = mid;
            high = mid - 1;
        }
        // Divisor is too small, increase it
        else
        {
            low = mid + 1;
        }
    }

    return ans;
}

int main()
{
    vector<int> nums = {8, 4, 2, 3};

    int limit = 4;

    int ans = smallestDivisor(nums, limit);

    cout << ans;

    return 0;
}