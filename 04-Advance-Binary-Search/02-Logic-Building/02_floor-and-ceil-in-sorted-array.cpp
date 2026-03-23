// ===================== PROBLEM =====================
// Given a sorted array nums and an integer x, find the floor and ceil of x.
//
// • Floor: largest element <= x
// • Ceil : smallest element >= x
//
// If floor or ceil does not exist, return -1 for that value.
// ===================================================

#include <bits/stdc++.h>
using namespace std;

// ===================================================
// BRUTE FORCE APPROACH (LINEAR SEARCH)
//
// Idea:
// Traverse the entire array and track:
// • Maximum element <= x → floor
// • Minimum element >= x → ceil
//
// Initialize floor = -1 and ceil = INT_MAX.
// Update them while iterating.
//
// Time Complexity: O(N)
// Space Complexity: O(1)
// ===================================================

// vector<int> getFloorAndCeil(vector<int> nums, int x)
// {
//     int n = nums.size();

//     vector<int> ans = {-1, INT_MAX};

//     for (int i = 0; i < n; i++)
//     {
//         if (nums[i] <= x && nums[i] > ans[0])
//             ans[0] = nums[i];

//         if (nums[i] >= x && nums[i] < ans[1])
//             ans[1] = nums[i];
//     }

//     if (ans[1] == INT_MAX)
//         ans[1] = -1;

//     return ans;
// }

// ===================================================
// OPTIMAL APPROACH (BINARY SEARCH)
//
// Idea:
// Use two separate binary searches:
//
// 1. Floor:
//    Find the largest element <= target
//    → move right when nums[mid] <= target
//
// 2. Ceil:
//    Find the smallest element >= target
//    → move left when nums[mid] >= target
//
// This leverages the sorted nature of the array.
//
// Time Complexity: O(log N)
// Space Complexity: O(1)
// ===================================================

int findFloor(vector<int> &nums, int n, int target)
{
    int low = 0, high = n - 1;

    int floor = -1;

    while (low <= high)
    {
        int mid = low + ((high - low) / 2);

        if (nums[mid] <= target)
        {
            floor = nums[mid]; // possible answer
            low = mid + 1;     // try to find larger valid value
        }
        else
        {
            high = mid - 1;
        }
    }

    return floor;
}

int findCeil(vector<int> &nums, int n, int target)
{
    int low = 0, high = n - 1;

    int ceil = -1;

    while (low <= high)
    {
        int mid = low + ((high - low) / 2);

        if (nums[mid] >= target)
        {
            ceil = nums[mid]; // possible answer
            high = mid - 1;   // try to find smaller valid value
        }
        else
        {
            low = mid + 1;
        }
    }

    return ceil;
}

vector<int> getFloorAndCeil(vector<int> nums, int x)
{
    int n = nums.size();

    return {findFloor(nums, n, x), findCeil(nums, n, x)};
}

int main()
{
    vector<int> nums = {1, 3, 5, 6};
    int target = 4;

    cout << "Array: ";
    for (int it : nums)
        cout << it << " ";
    cout << endl;

    vector<int> floorAndCeil = getFloorAndCeil(nums, target);

    cout << "Floor of " << target << ": " << floorAndCeil[0];

    cout << endl;

    cout << "Ceil of " << target << ": " << floorAndCeil[1];

    return 0;
}