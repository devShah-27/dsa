// Problem:
// Given an integer array nums, return all "leaders".
//
// A leader is an element that is strictly greater than every element
// to its right. The rightmost element is always a leader.
//
// The result must preserve the order in which leaders appear
// in the original array.

#include <bits/stdc++.h>
using namespace std;

// ================================================================
// BRUTE FORCE APPROACH
//
// Idea:
// For each element, check every element to its right.
// If none of them are greater, the element is a leader.
//
// Time Complexity:  O(N²)
// Space Complexity: O(1) extra (excluding output)
// ================================================================

// vector<int> leaders(vector<int> &nums)
// {
//     int n = nums.size();
//     vector<int> ans;
//
//     for (int i = 0; i < n; i++)
//     {
//         bool isLeader = true;
//
//         for (int j = i + 1; j < n; j++)
//         {
//             if (nums[j] > nums[i])
//             {
//                 isLeader = false;
//                 break;
//             }
//         }
//
//         if (isLeader)
//             ans.push_back(nums[i]);
//     }
//
//     return ans;
// }

// ================================================================
// OPTIMAL APPROACH (RIGHT-TO-LEFT SCAN)
//
// Key Observation:
// While scanning from right to left, maintain the maximum element
// seen so far. If the current element is greater than this maximum,
// it must be a leader.
//
// Leaders are discovered in reverse order, so the result
// must be reversed before returning.
//
// Time Complexity:  O(N)
// Space Complexity: O(1) extra (excluding output)
// ================================================================

vector<int> leaders(vector<int> &nums)
{
    int n = nums.size();

    vector<int> ans;
    int maxRight = INT_MIN;

    // Traverse from rightmost element
    for (int i = n - 1; i >= 0; i--)
    {
        if (nums[i] > maxRight)
        {
            maxRight = nums[i];
            ans.push_back(nums[i]);
        }
    }

    // Reverse to restore original left-to-right order
    reverse(ans.begin(), ans.end());

    return ans;
}

int main()
{
    vector<int> nums = {10, 22, 12, 3, 0, 6};

    vector<int> ans = leaders(nums);

    cout << "Leaders in given array: ";
    for (int val : ans)
        cout << val << " ";

    return 0;
}