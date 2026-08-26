// ===================== PROBLEM =====================
// Given a rotated sorted array (may contain duplicates) and a target k, return true if k exists in the array, otherwise return false.
//
// The rotation pivot is unknown.
// ===================================================

#include <bits/stdc++.h>
using namespace std;

// ===================================================
// BRUTE FORCE APPROACH (LINEAR SEARCH)
//
// Idea:
// Traverse the entire array and check if any element equals k.
//
// Time Complexity: O(N)
// Space Complexity: O(1)
// ===================================================

// bool searchInARotatedSortedArrayII(vector<int> &nums, int k)
// {
//     for (int it : nums)
//         if (it == k)
//             return true;

//     return false;
// }

// ===================================================
// OPTIMAL APPROACH (MODIFIED BINARY SEARCH WITH DUPLICATES)
//
// Idea:
// Similar to rotated sorted array search, but duplicates introduce ambiguity in identifying the sorted half.
//
// Steps:
// 1. If nums[mid] == k → return true
//
// 2. Handle duplicates:
//    If nums[low] == nums[mid] == nums[high],
//    shrink the search space (low++, high--)
//
// 3. Identify sorted half:
//    • If left half is sorted:
//        nums[low] <= nums[mid]
//    • Else right half is sorted
//
// 4. Check if k lies within the sorted half,
//    and adjust search space accordingly.
//
// NOTE:
// Worst-case time degrades to O(N) due to duplicate handling (e.g., when all elements are the same).
//
// Time Complexity: O(log N) average, O(N) worst case
// Space Complexity: O(1)
// ===================================================

bool searchInARotatedSortedArrayII(vector<int> &nums, int k)
{
    int n = nums.size();

    int low = 0, high = n - 1;

    while (low <= high)
    {
        int mid = low + ((high - low) / 2);

        if (nums[mid] == k)
            return true;

        // Handle ambiguity caused by duplicates
        if (nums[low] == nums[mid] && nums[mid] == nums[high])
        {
            low++, high--;
            continue;
        }

        // Case 1: Left half is sorted
        if (nums[low] <= nums[mid])
        {
            // Target lies within left sorted half
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
            // Target lies within right sorted half
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

    return false;
}

int main()
{
    vector<int> nums = {7, 8, 1, 2, 3, 3, 3, 4, 5, 6};
    int target = 3;

    cout << "Array: ";
    for (int it : nums)
        cout << it << " ";
    cout << endl;

    bool found = searchInARotatedSortedArrayII(nums, target);

    if (found)
        cout << target << " found";
    else
        cout << target << " not found";

    return 0;
}