// ========================== PROBLEM ==========================
// Given two sorted arrays of sizes m and n, find the median of the
// combined sorted array without explicitly merging them.
// ============================================================

#include <bits/stdc++.h>
using namespace std;

// ========================== BRUTE FORCE APPROACH ==========================
// Idea:
// Merge both sorted arrays into a third sorted array using the
// standard merge process. The median is then obtained directly
// from the merged array.
//
// Time Complexity: O(m + n)
// Space Complexity: O(m + n)
// ==========================================================================
// double median(vector<int> &arr1, vector<int> &arr2)
// {
//     vector<int> arr3;
//
//     int m = arr1.size(), n = arr2.size();
//
//     int i = 0, j = 0;
//
//     while (i < m && j < n)
//     {
//         if (arr1[i] <= arr2[j])
//             arr3.push_back(arr1[i++]);
//         else
//             arr3.push_back(arr2[j++]);
//     }
//
//     while (i < m)
//     {
//         arr3.push_back(arr1[i++]);
//     }
//
//     while (j < n)
//     {
//         arr3.push_back(arr2[j++]);
//     }
//
//     int x = (m + n);
//
//     if (x % 2 == 1)
//         return arr3[x / 2];
//
//     return (double)(arr3[x / 2] + arr3[(x / 2) - 1]) / 2.0;
// }

// ========================== BETTER APPROACH ==========================
// Idea:
// Simulate the merge process without creating an extra array.
// Track only the elements required to compute the median.
//
// Time Complexity: O(m + n)
// Space Complexity: O(1)
// =====================================================================
// double median(vector<int> &arr1, vector<int> &arr2)
// {
//     int m = arr1.size(), n = arr2.size();
//
//     int x = (m + n);
//
//     int indexTracker = 0;
//
//     int medianElem1 = -1, medianElem2 = -1;
//
//     int medianIndex1 = x / 2, medianIndex2 = (x / 2) - 1;
//
//     int i = 0, j = 0;
//
//     while (i < m && j < n)
//     {
//         if (arr1[i] < arr2[j])
//         {
//             if (indexTracker == medianIndex1)
//                 medianElem1 = arr1[i];
//             if (indexTracker == medianIndex2)
//                 medianElem2 = arr1[i];
//
//             indexTracker++;
//             i++;
//         }
//         else
//         {
//             if (indexTracker == medianIndex1)
//                 medianElem1 = arr2[j];
//             if (indexTracker == medianIndex2)
//                 medianElem2 = arr2[j];
//
//             indexTracker++;
//             j++;
//         }
//     }
//
//     while (i < m)
//     {
//         if (indexTracker == medianIndex1)
//             medianElem1 = arr1[i];
//         if (indexTracker == medianIndex2)
//             medianElem2 = arr1[i];
//
//         indexTracker++;
//         i++;
//     }
//
//     while (j < n)
//     {
//         if (indexTracker == medianIndex1)
//             medianElem1 = arr2[j];
//         if (indexTracker == medianIndex2)
//             medianElem2 = arr2[j];
//
//         indexTracker++;
//         j++;
//     }
//
//     if (x % 2 == 1)
//         return medianElem1;
//
//     return (double)(medianElem1 + medianElem2) / 2.0;
// }

// ========================== OPTIMAL APPROACH (BINARY SEARCH) ==========================
// Idea:
// Partition both arrays such that:
// - Left partition contains half of the total elements.
// - Every element on the left is <= every element on the right.
// Perform binary search only on the smaller array to achieve
// logarithmic complexity.
//
// Time Complexity: O(log(min(m, n)))
// Space Complexity: O(1)
// =======================================================================================
double median(vector<int> &arr1, vector<int> &arr2)
{
    int m = arr1.size(), n = arr2.size();

    // Always perform binary search on the smaller array
    if (n < m)
        return median(arr2, arr1);

    int low = 0, high = m;

    int left = (m + n + 1) / 2;
    int totalElements = m + n;

    while (low <= high)
    {
        int mid1 = low + ((high - low) / 2); // Partition index in arr1
        int mid2 = left - mid1;              // Corresponding partition in arr2

        int l1 = INT_MIN, l2 = INT_MIN;
        int r1 = INT_MAX, r2 = INT_MAX;

        // Elements immediately to the right of both partitions
        if (mid1 < m)
            r1 = arr1[mid1];
        if (mid2 < n)
            r2 = arr2[mid2];

        // Elements immediately to the left of both partitions
        if (mid1 > 0)
            l1 = arr1[mid1 - 1];
        if (mid2 > 0)
            l2 = arr2[mid2 - 1];

        // Correct partition found
        if (l1 <= r2 && l2 <= r1)
        {
            if (totalElements % 2 == 1)
                return max(l1, l2);

            return (max(l1, l2) / 2.0) + (min(r1, r2) / 2.0);
        }

        // Too many elements taken from arr1
        if (l1 > r2)
            high = mid1 - 1;
        // Too few elements taken from arr1
        else
            low = mid1 + 1;
    }

    // NOTE: This line should never be reached for valid sorted inputs.
    return 0;
}

int main()
{
    vector<int> arr1 = {
        1, 4, 7, 10, 13, 16, 19, 22, 25, 28,
        31, 34, 37, 40, 43, 46, 49, 52, 55, 58,
        61, 64, 67, 70, 73, 76, 79, 82, 85, 88};

    vector<int> arr2 = {
        2, 3, 5, 6, 8, 9, 11, 12, 14, 15,
        17, 18, 20, 21, 23, 24, 26, 27, 29, 30,
        32, 33, 35, 36, 38, 39, 41, 42, 44, 45,
        47, 48, 50, 51, 53, 54, 56, 57, 59, 60,
        62, 63, 65, 66, 68, 69, 71, 72, 74, 75,
        77, 78, 80, 81, 83, 84, 86, 87, 89, 90};

    double ans = median(arr1, arr2);

    cout << ans;

    return 0;
}