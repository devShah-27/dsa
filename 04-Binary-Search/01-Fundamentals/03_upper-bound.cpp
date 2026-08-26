// ===================== PROBLEM =====================
// Given a sorted array nums and an integer x, return the index of the first element that is greater than x (upper bound).
//
// If no such element exists, return nums.size().
// ===================================================

#include <bits/stdc++.h>
using namespace std;

// ===================================================
// BRUTE FORCE APPROACH (LINEAR SEARCH)
//
// Idea:
// Traverse the array from left to right and return the first index where nums[i] > x.
//
// If no such element is found, return n.
//
// Time Complexity: O(N)
// Space Complexity: O(1)
// ===================================================

// int upperBound(vector<int> &nums, int x)
// {
//     int n = nums.size();

//     for (int i = 0; i < n; i++)
//     {
//         if (nums[i] >= x)
//             return i;
//     }

//     return n;
// }

// ===================================================
// OPTIMAL APPROACH (BINARY SEARCH)
//
// Idea:
// Use binary search to efficiently find the first index
// where nums[index] > x.
//
// Maintain a variable `index` initialized to n (default case).
//
// For each mid:
// • If nums[mid] > x → possible answer, store it and
//   search in left half for a smaller index.
// • Else → search in right half.
//
// Time Complexity: O(log N)
// Space Complexity: O(1)
// ===================================================

int upperBound(vector<int> &nums, int x)
{
    int n = nums.size();

    int index = n;

    int low = 0, high = n - 1;

    while (low <= high)
    {
        int mid = low + ((high - low) / 2);

        if (nums[mid] > x)
        {
            index = mid;
            high = mid - 1;
        }
        else
        {
            low = mid + 1;
        }
    }

    return index;
}

int main()
{
    vector<int> nums = {3, 5, 8, 15, 19};
    int target = 5;

    cout << "Array: ";
    for (int it : nums)
        cout << it << " ";

    int foundIndex = upperBound(nums, target);

    cout << "\n"
         << target << "'s upper bound found at " << foundIndex;

    return 0;
}