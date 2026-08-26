// ===================== PROBLEM =====================
// Given a sorted array of distinct integers nums and a target, return the index if the target is found.
//
// If not found, return the index where the target should be inserted to maintain sorted order.
// ===================================================

#include <bits/stdc++.h>
using namespace std;

// ===================================================
// BRUTE FORCE APPROACH (LINEAR SEARCH)
//
// Idea:
// Traverse the array and find the first index where nums[i] >= target.
//
// • If found → return i
// • If not found → target is greater than all elements,
//   so return n (insert at end)
//
// Time Complexity: O(N)
// Space Complexity: O(1)
// ===================================================

// int searchInsert(vector<int> &nums, int target)
// {
//     int n = nums.size();

//     for (int i = 0; i < n; i++)
//     {
//         if (nums[i] >= target)
//             return i;
//     }

//     return n;
// }

// ===================================================
// OPTIMAL APPROACH (BINARY SEARCH - LOWER BOUND)
//
// Idea:
// This problem is equivalent to finding the lower bound of the target (first index where nums[i] >= target).
//
// Use binary search to efficiently locate this position.
//
// Maintain an answer variable initialized to n:
// • If nums[mid] >= target → potential answer, search left
// • Else → search right
//
// Time Complexity: O(log N)
// Space Complexity: O(1)
// ===================================================

int searchInsert(vector<int> &nums, int target)
{
    int n = nums.size();

    int low = 0, high = n - 1;

    int ans = n;

    while (low <= high)
    {
        int mid = low + ((high - low) / 2);

        if (nums[mid] >= target)
        {
            ans = mid;
            high = mid - 1;
        }
        else
        {
            low = mid + 1;
        }
    }

    return ans;
}

int main()
{
    vector<int> nums = {1, 3, 5, 6};
    int target = 4;

    cout << "Array: ";
    for (int it : nums)
        cout << it << " ";
    cout << endl;

    int index = searchInsert(nums, target);

    cout << "Index found for " << target << ": " << index;

    return 0;
}