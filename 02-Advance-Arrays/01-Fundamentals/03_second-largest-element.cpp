// ========================== PROBLEM ==========================
// Given an integer array, return the second-largest distinct
// element. If no such element exists (e.g., all elements equal
// or size < 2), return -1.
// ============================================================

#include <bits/stdc++.h>
using namespace std;

// ========================== BRUTE FORCE APPROACH (SORTING) ==========================
// Idea:
// Sort the array and identify the largest element.
// Traverse backwards to find the first element strictly smaller
// than the largest — that will be the second-largest distinct value.
//
// NOTE: This modifies the original array.
//
// Time Complexity: O(N log N)
// Space Complexity: O(1) (ignoring sort recursion stack)
// ====================================================================================
// int secondLargestElement(vector<int> &nums)
// {
//     int n = nums.size();
//
//     if (n < 2)
//         return -1;
//
//     sort(nums.begin(), nums.end());
//
//     int largest = nums[n - 1];
//
//     for (int i = n - 2; i >= 0; i--)
//     {
//         if (nums[i] < largest)
//             return nums[i];
//     }
//
//     return -1;
// }

// ========================== BETTER APPROACH (TWO PASSES) ==========================
// Idea:
// First pass: find the maximum element.
// Second pass: find the largest element strictly less than the maximum.
// This avoids sorting and keeps logic simple.
//
// Time Complexity: O(N)
// Space Complexity: O(1)
// =================================================================================
// int secondLargestElement(vector<int> &nums)
// {
//     int n = nums.size();
//
//     if (n < 2)
//         return -1;
//
//     int largest = INT_MIN, secondLargest = INT_MIN;
//
//     for (int i = 0; i < n; i++)
//     {
//         if (nums[i] > largest)
//             largest = nums[i];
//     }
//
//     for (int i = 0; i < n; i++)
//     {
//         if (nums[i] > secondLargest && nums[i] != largest)
//             secondLargest = nums[i];
//     }
//
//     if (secondLargest == INT_MIN)
//         return -1;
//
//     return secondLargest;
// }

// ========================== OPTIMAL APPROACH (SINGLE PASS) ==========================
// Idea:
// Traverse the array once while maintaining two variables:
// - largest: the maximum element seen so far
// - secondLargest: the maximum element smaller than 'largest'
// Update both values dynamically in a single traversal.
//
// Time Complexity: O(N)
// Space Complexity: O(1)
// ====================================================================================
int secondLargestElement(vector<int> &nums)
{
    int n = nums.size();

    if (n < 2)
        return -1;

    int largest = INT_MIN, secondLargest = INT_MIN;

    for (int i = 0; i < n; i++)
    {
        if (nums[i] > largest)
        {
            secondLargest = largest;
            largest = nums[i];
        }
        else if (nums[i] > secondLargest && nums[i] != largest)
        {
            secondLargest = nums[i];
        }
    }

    // If secondLargest was never updated, no valid answer exists
    if (secondLargest == INT_MIN)
        return -1;

    return secondLargest;
}

int main()
{
    int size;
    cin >> size;

    vector<int> nums(size);

    // Input array elements
    for (int i = 0; i < size; i++)
        cin >> nums[i];

    int secondLargestElem = secondLargestElement(nums);

    cout << "Second Largest Element in given array: " << secondLargestElem;

    return 0;
}