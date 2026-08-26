// ========================== PROBLEM ==========================
// Given an integer array and an integer k, split the array into
// exactly k non-empty contiguous subarrays such that the largest
// subarray sum is minimized. Return this minimum possible sum.
// ============================================================

#include <bits/stdc++.h>
using namespace std;

// ========================== HELPER FUNCTION ==========================
// Idea:
// Traverse the array and return the maximum element.
// Since every subarray must contain at least one element,
// the answer cannot be smaller than the largest array element.
//
// Time Complexity: O(N)
// Space Complexity: O(1)
// =====================================================================
int maximumElem(vector<int> &nums)
{
    int maxi = INT_MIN;

    for (int it : nums)
        maxi = max(maxi, it);

    return maxi;
}

// ========================== HELPER FUNCTION ==========================
// Idea:
// Compute the sum of all array elements.
// This represents the upper bound of the search space since the
// entire array can form a single subarray.
//
// Time Complexity: O(N)
// Space Complexity: O(1)
// =====================================================================
int sumOfAllElem(vector<int> &nums)
{
    int sum = 0;

    for (int it : nums)
        sum += it;

    return sum;
}

// ========================== HELPER FUNCTION ==========================
// Idea:
// Determine the minimum number of contiguous subarrays required
// if the maximum allowed subarray sum is 'allowedSplitCount'.
//
// Time Complexity: O(N)
// Space Complexity: O(1)
// =====================================================================
int calculateSectionCount(vector<int> &a, int allowedSplitCount)
{
    int sectionCount = 1, currentSectionSplitCount = 0;

    for (int i = 0; i < a.size(); i++)
    {
        if (currentSectionSplitCount + a[i] <= allowedSplitCount)
        {
            currentSectionSplitCount += a[i];
        }
        else
        {
            sectionCount++;
            currentSectionSplitCount = a[i];
        }
    }

    return sectionCount;
}

// ========================== BRUTE FORCE APPROACH (LINEAR SEARCH) ==========================
// Idea:
// Try every possible maximum subarray sum from the lower bound
// to the upper bound. Return the first value that requires
// at most k subarrays.
//
// NOTE: The lower bound should be the maximum array element, not the
// minimum element. Using the minimum element still works only when
// combined with the helper logic but performs unnecessary iterations.
//
// Time Complexity: O((Sum - Maximum element + 1) * N)
// Space Complexity: O(1)
// ==========================================================================================
// int largestSubarraySumMinimized(vector<int> &a, int k)
// {
//     int n = a.size();
//
//     if (k > n)
//         return -1;
//
//     int low = minimumElem(a), high = sumOfAllElem(a);
//
//     for (int i = low; i < high; i++)
//     {
//         int sectionCount = calculateSectionCount(a, i);
//
//         if (sectionCount <= k)
//             return i;
//     }
//
//     return -1;
// }

// ========================== OPTIMAL APPROACH (BINARY SEARCH) ==========================
// Idea:
// Binary search the answer between the largest element and the
// total array sum.
// - If the current maximum subarray sum requires at most k subarrays,
//   try reducing the allowed sum.
// - Otherwise, increase the allowed sum.
//
// NOTE: This problem is identical to the Book Allocation problem.
//
// NOTE: The lower bound should ideally be the maximum element instead
// of the minimum element for optimal efficiency.
//
// Time Complexity: O(N * log(Sum - Maximum element + 1))
// Space Complexity: O(1)
// ======================================================================================
int largestSubarraySumMinimized(vector<int> &a, int k)
{
    int n = a.size();

    if (k > n)
        return -1;

    int low = maximumElem(a), high = sumOfAllElem(a);

    while (low <= high)
    {
        int mid = low + ((high - low) / 2);

        int sectionCount = calculateSectionCount(a, mid);

        // Current maximum subarray sum is feasible
        if (sectionCount <= k)
            high = mid - 1;
        // Too many subarrays are required
        else
            low = mid + 1;
    }

    // 'low' stores the minimum feasible largest subarray sum
    return low;
}

int main()
{
    vector<int> a = {10, 20, 30, 40};
    int k = 2;

    int ans = largestSubarraySumMinimized(a, k);
    cout << "The answer is: " << ans << "\n";

    return 0;
}