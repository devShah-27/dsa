// ========================== PROBLEM ==========================
// Given two sorted arrays of sizes m and n, return the kth smallest
// element in the merged sorted order without explicitly merging
// the arrays.
// ============================================================

#include <bits/stdc++.h>
using namespace std;

// ========================== BRUTE FORCE APPROACH ==========================
// Idea:
// Merge both sorted arrays into a third array using the merge process.
// The kth element of the merged array is the required answer.
//
// Time Complexity: O(m + n)
// Space Complexity: O(m + n)
// ==========================================================================
// int kthElement(vector<int> &a, vector<int> &b, int k)
// {
//     int m = a.size(), n = b.size();
//
//     if (k > m + n)
//         return -1;
//
//     vector<int> c;
//
//     int leftPtr = 0, rightPtr = 0;
//
//     while (leftPtr < m && rightPtr < n)
//     {
//         if (a[leftPtr] <= b[rightPtr])
//             c.push_back(a[leftPtr++]);
//         else
//             c.push_back(b[rightPtr++]);
//     }
//
//     while (leftPtr < m)
//     {
//         c.push_back(a[leftPtr++]);
//     }
//
//     while (rightPtr < n)
//     {
//         c.push_back(b[rightPtr++]);
//     }
//
//     return c[k - 1];
// }

// ========================== BETTER APPROACH ==========================
// Idea:
// Simulate the merge process without creating a third array.
// Maintain a merged index and return immediately when the kth
// element is reached.
//
// Time Complexity: O(m + n)
// Space Complexity: O(1)
// =====================================================================
// int kthElement(vector<int> &a, vector<int> &b, int k)
// {
//     int m = a.size(), n = b.size();
//
//     if (k > m + n)
//         return -1;
//
//     int indexTracker = 0;
//
//     int leftPtr = 0, rightPtr = 0;
//
//     while (leftPtr < m && rightPtr < n)
//     {
//         if (a[leftPtr] <= b[rightPtr])
//         {
//             if (indexTracker == k - 1)
//                 return a[leftPtr];
//
//             indexTracker++;
//             leftPtr++;
//         }
//         else
//         {
//             if (indexTracker == k - 1)
//                 return b[rightPtr];
//
//             indexTracker++;
//             rightPtr++;
//         }
//     }
//
//     while (leftPtr < m)
//     {
//         if (indexTracker == k - 1)
//             return a[leftPtr];
//
//         indexTracker++;
//         leftPtr++;
//     }
//
//     while (rightPtr < n)
//     {
//         if (indexTracker == k - 1)
//             return b[rightPtr];
//
//         indexTracker++;
//         rightPtr++;
//     }
//
//     return -1;
// }

// ========================== OPTIMAL APPROACH (BINARY SEARCH) ==========================
// Idea:
// Partition both arrays such that the left partition contains exactly
// k elements. A valid partition satisfies:
// - Every element on the left <= every element on the right.
// Perform binary search only on the smaller array.
//
// Time Complexity: O(log(min(m, n)))
// Space Complexity: O(1)
// =======================================================================================
int kthElement(vector<int> &a, vector<int> &b, int k)
{
    int m = a.size(), n = b.size();

    if (k > m + n)
        return -1;

    // Always binary search on the smaller array
    if (m > n)
        return kthElement(b, a, k);

    // Number of elements taken from the first array
    int low = max(0, k - n), high = min(k, m);

    while (low <= high)
    {
        int mid1 = low + ((high - low) / 2);
        int mid2 = k - mid1;

        int l1 = INT_MIN, l2 = INT_MIN;
        int r1 = INT_MAX, r2 = INT_MAX;

        // First elements on the right partitions
        if (mid1 < m)
            r1 = a[mid1];
        if (mid2 < n)
            r2 = b[mid2];

        // Last elements on the left partitions
        if (mid1 > 0)
            l1 = a[mid1 - 1];
        if (mid2 > 0)
            l2 = b[mid2 - 1];

        // Correct partition found
        if (l1 <= r2 && l2 <= r1)
            return max(l1, l2);

        // Too many elements chosen from the first array
        if (l1 > r2)
            high = mid1 - 1;
        // Too few elements chosen from the first array
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

    int k = 39;

    int ans = kthElement(arr1, arr2, k);

    cout << ans;

    return 0;
}