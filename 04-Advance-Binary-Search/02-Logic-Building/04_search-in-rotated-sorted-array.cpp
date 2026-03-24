// ===================== PROBLEM =====================
// Given a rotated sorted array (distinct elements) and a target k, return the index of k if present.
//
// If k is not present, return -1.
// ===================================================

#include <bits/stdc++.h>
using namespace std;

// ===================================================
// BRUTE FORCE APPROACH (LINEAR SEARCH)
//
// Idea:
// Traverse the array and check each element.
// Return index if nums[i] == k, else return -1.
//
// Time Complexity: O(N)
// Space Complexity: O(1)
// ===================================================

// int search(vector<int> &nums, int k)
// {
//     int n = nums.size();

//     for (int i = 0; i < n; i++)
//     {
//         if (nums[i] == k)
//             return i;
//     }

//     return -1;
// }

// ===================================================
// OPTIMAL APPROACH (MODIFIED BINARY SEARCH)
//
// Idea:
// Even after rotation, at least one half (left or right) of the array is always sorted.
//
// At each step:
// • Identify which half is sorted
// • Check if target lies within that sorted half
// • Narrow the search space accordingly
//
// Cases:
// 1. Left half sorted:
//    nums[low] <= nums[mid]
//    → check if k lies in [nums[low], nums[mid]]
//
// 2. Right half sorted:
//    otherwise
//    → check if k lies in [nums[mid], nums[high]]
//
// Time Complexity: O(log N)
// Space Complexity: O(1)
// ===================================================

int search(vector<int> &nums, int k)
{
    int n = nums.size();

    int low = 0, high = n - 1;

    while (low <= high)
    {
        int mid = low + ((high - low) / 2);

        if (nums[mid] == k)
            return mid;

        // Case 1: Left half is sorted
        if (nums[low] <= nums[mid])
        {
            // Target lies within left sorted portion
            if (nums[low] <= k && k <= nums[mid])
            {
                high = mid - 1;
            }
            else
            {
                low = mid + 1;
            }
        }
        // Case 2: Right half is sorted
        else
        {
            // Target lies within right sorted portion
            if (nums[mid] <= k && k <= nums[high])
            {
                low = mid + 1;
            }
            else
            {
                high = mid - 1;
            }
        }
    }

    return -1;
}

int main()
{
    vector<int> nums = {4, 5, 6, 7, 0, 1, 2};
    int target = 7;

    cout << "Array: ";
    for (int it : nums)
        cout << it << " ";
    cout << endl;

    int index = search(nums, target);

    cout << target << " found at index " << index;

    return 0;
}