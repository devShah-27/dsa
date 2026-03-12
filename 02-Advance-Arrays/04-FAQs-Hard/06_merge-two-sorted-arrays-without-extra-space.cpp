// ===================== PROBLEM =====================
// Given two sorted integer arrays nums1 and nums2 (sorted in non-decreasing order),
// merge nums2 into nums1 so that nums1 becomes a single sorted array.
//
// nums1 has size m + n where the first m elements are valid values and the
// remaining n positions are placeholders (0s) to accommodate nums2.
// The merge must be performed in-place inside nums1.
// ===================================================

#include <bits/stdc++.h>
using namespace std;

// ===================================================
// BRUTE FORCE APPROACH
//
// Idea:
// Use the standard merge step of merge sort. Traverse both arrays using
// two pointers and construct a third temporary array containing elements
// in sorted order. Finally copy the merged result back into nums1.
//
// This approach is straightforward but violates the in-place requirement
// since it uses an auxiliary array.
//
// Time Complexity: O(m + n)
// Space Complexity: O(m + n)
// ===================================================

// void merge(vector<int> &nums1, int m, vector<int> &nums2, int n)
// {
//     int left = 0, right = 0;

//     vector<int> temp(m + n, 0);

//     int tempIndex = 0;

//     while (left < m && right < n)
//     {
//         if (nums1[left] < nums2[right])
//             temp[tempIndex++] = nums1[left++];
//         else
//             temp[tempIndex++] = nums2[right++];
//     }

//     while (left < m)
//     {
//         temp[tempIndex++] = nums1[left++];
//     }

//     while (right < n)
//     {
//         temp[tempIndex++] = nums2[right++];
//     }

//     for (int i = 0; i < m + n; i++)
//     {
//         nums1[i] = temp[i];
//     }
// }

// ===================================================
// OPTIMAL APPROACH 1
//
// Idea:
// Use two pointers:
// • left  → last valid element of nums1
// • right → first element of nums2
//
// Swap elements when nums1[left] > nums2[right]. This ensures smaller
// elements stay in nums1 and larger ones move to nums2.
//
// After swaps, both arrays may become unsorted internally, so we sort
// each array individually and then append nums2 to nums1.
//
// NOTE: Although called "optimal", this approach still performs sorting
// operations, which makes it slower than the true optimal solution.
//
// Time Complexity: O(min(m,n)) + O(m log m) + O(n log n)
// Space Complexity: O(1)
// ===================================================

// void merge(vector<int> &nums1, int m, vector<int> &nums2, int n)
// {
//     int left = m - 1, right = 0;

//     while (left >= 0 && right < n)
//     {
//         if (nums1[left] > nums2[right])
//         {
//             swap(nums1[left], nums2[right]);
//             left--, right++;
//         }
//         else
//             break;
//     }

//     sort(nums1.begin(), nums1.begin() + m);

//     sort(nums2.begin(), nums2.end());

//     for (int i = 0; i < n; i++)
//     {
//         nums1[m + i] = nums2[i];
//     }
// }

// ===================================================
// OPTIMAL APPROACH 2 (GAP METHOD - Shell Sort Inspired)
//
// Idea:
// Treat both arrays as a single combined array of length (m + n).
// Compare elements that are 'gap' distance apart and swap them if
// they are out of order. Gradually reduce the gap similar to Shell
// Sort until the gap becomes 1.
//
// This allows elements to move closer to their correct positions
// without using extra space.
//
// Time Complexity: O((m + n) * log₂(m + n))
// Space Complexity: O(1)
// ===================================================

// void swapGreater(vector<int> &nums1, int index1, vector<int> &nums2, int index2)
// {
//     if (nums1[index1] > nums2[index2])
//         swap(nums1[index1], nums2[index2]);
// }

// void merge(vector<int> &nums1, int m, vector<int> &nums2, int n)
// {
//     int length = m + n;
//     int gap = (length / 2) + (length % 2); // Ceiling(length / 2)

//     while (gap > 0)
//     {
//         int left = 0;
//         int right = left + gap;

//         while (right < length)
//         {
//             // Compare element from nums1 with element from nums2
//             if (left < m && right >= m)
//             {
//                 swapGreater(nums1, left, nums2, right - m);
//             }
//             // Compare elements inside nums2
//             else if (left >= m)
//             {
//                 swapGreater(nums2, left - m, nums2, right - m);
//             }
//             // Compare elements inside nums1
//             else
//             {
//                 swapGreater(nums1, left, nums1, right);
//             }

//             left++, right++;
//         }

//         if (gap == 1)
//             break;

//         gap = (gap / 2) + (gap % 2);
//     }

//     for (int i = 0; i < n; i++)
//     {
//         nums1[m + i] = nums2[i];
//     }
// }

// ===================================================
// OPTIMAL APPROACH 3 (TRUE IN-PLACE MERGE)
//
// Idea:
// Since nums1 has extra space at the end, fill it from the back.
// Start comparing the largest elements of both arrays:
//
// • left  → last valid element in nums1
// • right → last element in nums2
// • availableIndex → last index of nums1
//
// Place the larger element at availableIndex and move pointers
// accordingly. This avoids overwriting valid elements in nums1.
//
// Time Complexity: O(m + n)
// Space Complexity: O(1)
// ===================================================

void merge(vector<int> &nums1, int m, vector<int> &nums2, int n)
{
    int left = m - 1, right = n - 1;

    int availableIndex = nums1.size() - 1;

    while (left >= 0 && right >= 0)
    {
        if (nums1[left] > nums2[right])
        {
            nums1[availableIndex--] = nums1[left--];
        }
        else
        {
            nums1[availableIndex--] = nums2[right--];
        }
    }

    // If elements remain in nums2, copy them to nums1
    while (right >= 0)
    {
        nums1[availableIndex--] = nums2[right--];
    }
}

int main()
{
    vector<int> nums1 = {
        -100, -95, -90, -85, -80, -75, -70, -65, -60, -55,
        -50, -45, -40, -35, -30, -25, -20, -15, -10, -5,
        0, 5, 10, 15, 20, 25, 30, 35, 40, 45,
        50, 55, 60, 65, 70, 75, 80, 85, 90, 95,

        // placeholders
        0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
        0, 0, 0, 0, 0, 0, 0, 0, 0, 0};

    vector<int> nums2 = {
        -110, -92, -88, -72, -68,
        -50, -33, -17, -3, 2,
        7, 13, 26, 39, 44,
        58, 73, 91, 102, 120};

    cout << "Nums1 before merge:\n";
    for (int x : nums1)
        cout << x << " ";
    cout << endl;

    cout << "\nNums2 before merge:\n";
    for (int x : nums2)
        cout << x << " ";
    cout << endl;

    int n = nums2.size();
    int m = nums1.size() - n;

    merge(nums1, m, nums2, n);

    cout << "\n\nNums1 after merge:\n";
    for (int x : nums1)
        cout << x << " ";

    return 0;
}