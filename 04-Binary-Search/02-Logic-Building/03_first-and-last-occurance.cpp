// ===================== PROBLEM =====================
// Given a sorted array nums and a target value, return the starting and ending index of the target.
//
// If the target is not present, return {-1, -1}.
// ===================================================

#include <bits/stdc++.h>
using namespace std;

// ===================================================
// BRUTE FORCE APPROACH (LINEAR SEARCH)
//
// Idea:
// Traverse the array and track:
// • First occurrence → first index where nums[i] == target
// • Last occurrence  → keep updating whenever target is found
//
// Time Complexity: O(N)
// Space Complexity: O(1)
// ===================================================

// vector<int> searchRange(vector<int> &nums, int target)
// {
//     int n = nums.size();

//     int first = -1, last = -1;

//     for (int i = 0; i < n; i++)
//     {
//         if (nums[i] == target)
//         {
//             if (first == -1)
//                 first = i;

//             last = i;
//         }
//     }

//     return {first, last};
// }

// ===================================================
// USING LOWER & UPPER BOUND
//
// Idea:
// • Lower Bound → first index where nums[i] >= target
// • Upper Bound → first index where nums[i] > target
//
// If target exists:
// • First occurrence = lower bound
// • Last occurrence  = upper bound - 1
//
// Time Complexity: O(log N)
// Space Complexity: O(1)
// ===================================================

// int lowerBound(vector<int> &nums, int target)
// {
//     int n = nums.size();

//     int low = 0, high = n - 1;

//     int ans = -1;

//     while (low <= high)
//     {
//         int mid = low + ((high - low) / 2);

//         if (nums[mid] >= target)
//         {
//             ans = mid;
//             high = mid - 1;
//         }
//         else
//         {
//             low = mid + 1;
//         }
//     }

//     return ans;
// }

// int upperBound(vector<int> &nums, int target)
// {
//     int n = nums.size();

//     int low = 0, high = n - 1;

//     int ans = -1;

//     while (low <= high)
//     {
//         int mid = low + ((high - low) / 2);

//         if (nums[mid] > target)
//         {
//             ans = mid;
//             high = mid - 1;
//         }
//         else
//         {
//             low = mid + 1;
//         }
//     }

//     return ans;
// }

// vector<int> searchRange(vector<int> &nums, int target)
// {
//     int n = nums.size();

//     int lb = lowerBound(nums, target);

//     if (lb == n || nums[lb] != target)
//         return {-1, -1};

//     int ub = upperBound(nums, target);

//     return {lb, ub - 1};
// }

// ===================================================
// OPTIMAL APPROACH (BINARY SEARCH)
//
// Idea:
// Perform two binary searches:
//
// 1. First Occurrence:
//    • When nums[mid] == target → store index and move left
//
// 2. Last Occurrence:
//    • When nums[mid] == target → store index and move right
//
// This ensures finding the extreme positions efficiently.
//
// Time Complexity: O(log N)
// Space Complexity: O(1)
// ===================================================

int firstOccurance(vector<int> &nums, int target)
{
    int n = nums.size();

    int low = 0, high = n - 1;

    int firstOccurance = -1;

    while (low <= high)
    {
        int mid = low + ((high - low) / 2);

        if (nums[mid] == target)
        {
            firstOccurance = mid;
            high = mid - 1; // continue searching left
        }
        else if (nums[mid] < target)
        {
            low = mid + 1;
        }
        else
        {
            high = mid - 1;
        }
    }

    return firstOccurance;
}

int lastOccurance(vector<int> &nums, int target)
{
    int n = nums.size();

    int low = 0, high = n - 1;

    int lastOccurance = -1;

    while (low <= high)
    {
        int mid = low + ((high - low) / 2);

        if (nums[mid] == target)
        {
            lastOccurance = mid;
            low = mid + 1; // continue searching right
        }
        else if (nums[mid] < target)
        {
            low = mid + 1;
        }
        else
        {
            high = mid - 1;
        }
    }

    return lastOccurance;
}

vector<int> searchRange(vector<int> &nums, int target)
{
    int n = nums.size();

    int first = firstOccurance(nums, target);

    if (first == -1)
        return {-1, -1};

    int last = lastOccurance(nums, target);

    return {first, last};
}

int main()
{
    vector<int> nums = {5, 7, 7, 8, 8, 8, 8, 8, 10};
    int target = 8;

    cout << "Array: ";
    for (int it : nums)
        cout << it << " ";
    cout << endl;

    vector<int> firstAndLastOccurance = searchRange(nums, target);

    cout << "\nFirst occurance of " << target << ": " << firstAndLastOccurance[0];

    cout << "\nLast occurance of " << target << ": " << firstAndLastOccurance[1];

    return 0;
}