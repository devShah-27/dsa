// ========================== PROBLEM ==========================
// Given a sorted array where every element appears exactly twice
// except one element that appears once, find that single element.
// ============================================================

#include <bits/stdc++.h>
using namespace std;

// ========================== BRUTE FORCE APPROACH - 1 ==========================
// Idea:
// Traverse each element and compare it with its neighbors.
// The element which is not equal to both its adjacent elements is the single non-duplicate element.
//
// Time Complexity: O(N)
// Space Complexity: O(1)
// =================================================================================
// int singleNonDuplicate(vector<int> &nums)
// {
//     int n = nums.size();
//
//     if (n == 1)
//         return nums[0];
//
//     for (int i = 0; i < n; i++)
//     {
//         if (i == 0)
//         {
//             if (nums[i] != nums[i + 1])
//                 return nums[i];
//         }
//         else if (i == (n - 1))
//         {
//             if (nums[n - 1] != nums[n - 2])
//                 return nums[n - 1];
//         }
//         else
//         {
//             if ((nums[i] != nums[i - 1]) && (nums[i] != nums[i + 1]))
//                 return nums[i];
//         }
//     }
//
//     return -1;
// }

// ========================== BRUTE FORCE APPROACH - 2 (XOR) ==========================
// Idea:
// XOR of identical numbers cancels out to 0, and XOR with 0 gives the number itself.
// Applying XOR on all elements leaves only the unique element.
//
// NOTE: Does not use the sorted property of the array.
//
// Time Complexity: O(N)
// Space Complexity: O(1)
// ====================================================================================
// int singleNonDuplicate(vector<int> &nums)
// {
//     int n = nums.size();
//
//     if (n == 1)
//         return nums[0];
//
//     int ans = 0;
//
//     for (int it : nums)
//     {
//         ans ^= it;
//     }
//
//     return ans;
// }

// ========================== OPTIMAL APPROACH (BINARY SEARCH) ==========================
// Idea:
// In a sorted array with pairs, elements before the single element follow (even, odd) indexing pattern, and after it follow (odd, even).
// Use binary search to detect the disruption in this pattern.
//
// Key Insight:
// - If mid is even and nums[mid] == nums[mid+1], single lies on right.
// - If mid is odd and nums[mid] == nums[mid-1], single lies on right.
// Otherwise, it lies on the left side.
//
// Time Complexity: O(log N)
// Space Complexity: O(1)
// ======================================================================================
int singleNonDuplicate(vector<int> &nums)
{
    int n = nums.size();

    if (n == 1)
        return nums[0];

    // Edge cases: single element at boundaries
    if (nums[0] != nums[1])
        return nums[0];

    if (nums[n - 1] != nums[n - 2])
        return nums[n - 1];

    int low = 1, high = n - 2;

    while (low <= high)
    {
        int mid = low + ((high - low) / 2);

        // Check if mid itself is the single element
        if (nums[mid - 1] != nums[mid] && nums[mid] != nums[mid + 1])
        {
            return nums[mid];
        }

        // If pairing pattern is correct, eliminate left half
        if ((mid % 2 == 1 && nums[mid - 1] == nums[mid]) ||
            (mid % 2 == 0 && nums[mid] == nums[mid + 1]))
        {
            low = mid + 1;
        }
        // Otherwise, eliminate right half
        else
        {
            high = mid - 1;
        }
    }

    // NOTE: Given constraints guarantee one unique element, so this is fallback
    return -1;
}

int main()
{
    vector<int> nums = {1, 1, 2, 2, 3, 3, 4, 4, 5, 6, 6, 7, 7};

    cout << "Array: ";
    for (int it : nums)
        cout << it << " ";
    cout << endl;

    int nonDuplicate = singleNonDuplicate(nums);

    cout << "Non Duplicate: " << nonDuplicate;

    return 0;
}