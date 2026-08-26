// ===================== PROBLEM =====================
// Given a sorted array nums (0-based indexing) and a target value,
// return the index of the target if found.
//
// If the target does not exist in the array, return -1.
// ===================================================

#include <bits/stdc++.h>
using namespace std;

// ===================================================
// ITERATIVE BINARY SEARCH
//
// Idea:
// Use two pointers (low, high) to represent the current search range.
// Repeatedly compute the middle index and compare it with the target:
//
// • If nums[mid] == target → return mid
// • If nums[mid] > target → search left half
// • If nums[mid] < target → search right half
//
// Continue until the search space becomes empty.
//
// Time Complexity: O(log N)
// Space Complexity: O(1)
// ===================================================

// int search(vector<int> &nums, int target)
// {
//     int n = nums.size();

//     int low = 0, high = n - 1;

//     while (low <= high)
//     {
//         int mid = low + ((high - low) / 2);

//         if (nums[mid] == target)
//             return mid;

//         else if (nums[mid] > target)
//             high = mid - 1;

//         else
//             low = mid + 1;
//     }

//     return -1;
// }

// ===================================================
// RECURSIVE BINARY SEARCH
//
// Idea:
// Apply binary search recursively by dividing the search
// space into halves.
//
// Base Case:
// • If low > high → target not found → return -1
//
// Recursive Steps:
// • Compute mid
// • If nums[mid] == target → return mid
// • If nums[mid] > target → search left half
// • Else → search right half
//
// Time Complexity: O(log N)
// Space Complexity: O(log N) (due to recursion stack)
// ===================================================

int recursiveBinarySearch(vector<int> &nums, int target, int low, int high)
{
    if (low > high)
        return -1;

    int index;

    int mid = low + ((high - low) / 2);

    if (nums[mid] == target)
        index = mid;

    else if (nums[mid] > target)
        index = recursiveBinarySearch(nums, target, low, mid - 1);

    else
        index = recursiveBinarySearch(nums, target, mid + 1, high);

    return index;
}

int search(vector<int> &nums, int target)
{
    return recursiveBinarySearch(nums, target, 0, nums.size() - 1);
}

int main()
{
    vector<int> nums = {-1, 0, 3, 5, 9, 12};
    int target = 9;

    cout << "Array: ";
    for (int it : nums)
        cout << it << " ";

    int foundIndex = search(nums, target);

    cout << "\n"
         << target << " found at " << foundIndex;

    return 0;
}