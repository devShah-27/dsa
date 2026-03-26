// ========================== PROBLEM ==========================
// Given a sorted array (distinct elements) that has been right rotated k times, find the value of k.
// Note: The index of the minimum element equals the rotation count.
// ============================================================

#include <bits/stdc++.h>
using namespace std;

// ========================== BRUTE FORCE APPROACH ==========================
// Idea:
// The minimum element in a rotated sorted array indicates the rotation count.
// Linearly scan the array to find the smallest element and return its index.
//
// Time Complexity: O(N)
// Space Complexity: O(1)
// =========================================================================
// int findKRotation(vector<int> &nums)
// {
//     int n = nums.size();
//
//     int mini = nums[0], index = 0;
//
//     for (int i = 0; i < n; i++)
//     {
//         if (nums[i] < mini)
//         {
//             mini = nums[i];
//             index = i;
//         }
//     }
//
//     return index;
// }

// ========================== OPTIMAL APPROACH (BINARY SEARCH) ==========================
// Idea:
// Use binary search to locate the minimum element efficiently.
// At any step, one half of the array is guaranteed to be sorted.
// Compare boundaries to decide which half may contain the minimum.
// Track the smallest value and its index during the process.
//
// Time Complexity: O(log N)
// Space Complexity: O(1)
// =====================================================================================
int findKRotation(vector<int> &nums)
{
    int n = nums.size();

    int mini = nums[0], index = 0;

    int low = 0, high = n - 1;

    while (low <= high)
    {
        int mid = low + ((high - low) / 2);

        // If current segment is already sorted,
        // the smallest element lies at 'low'
        if (nums[low] <= nums[high])
        {
            if (nums[low] <= mini)
            {
                mini = nums[low];
                index = low;
            }
            break;
        }

        // Left half is sorted → minimum cannot be inside this sorted part
        if (nums[low] <= nums[mid])
        {
            if (nums[low] <= mini)
            {
                mini = nums[low];
                index = low;
            }
            low = mid + 1;
        }
        // Right half is sorted → minimum lies in left half including mid
        else
        {
            if (nums[mid] <= mini)
            {
                mini = nums[mid];
                index = mid;
            }
            high = mid - 1;
        }
    }

    return index;
}

int main()
{
    vector<int> nums = {4, 5, 6, 7, -7, 1, 2, 3};

    cout << "Array: ";
    for (int it : nums)
        cout << it << " ";
    cout << endl;

    int rotationCount = findKRotation(nums);

    cout << "\nNo. of rotations: " << rotationCount;

    return 0;
}