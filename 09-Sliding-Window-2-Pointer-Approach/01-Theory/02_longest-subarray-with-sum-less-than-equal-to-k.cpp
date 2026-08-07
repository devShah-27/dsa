// Problem:
// Given an array of integers, find the length of the longest contiguous subarray whose sum is less than or equal to a given value K.
// Return the maximum length of such a subarray.

#include <bits/stdc++.h>
using namespace std;

// ==================================================
// BRUTE FORCE APPROACH
//
// Idea:
// Consider every possible subarray and calculate its sum.
// If the sum is within the limit K, update the maximum length.
// Stop extending a subarray once its sum exceeds K.
//
// Time Complexity: O(N^2)
// Space Complexity: O(1)
// ==================================================

// int longestSubarrayWithSum(vector<int> &arr, int K)
// {
//     int n = arr.size();

//     int maxLength = 0;

//     for (int i = 0; i < n; i++)
//     {
//         int sum = 0;

//         for (int j = i; j < n; j++)
//         {
//             sum += arr[j];

//             if (sum <= K)
//                 maxLength = max(maxLength, j - i + 1);

//             if (sum > K)
//                 break;
//         }
//     }

//     return maxLength;
// }

// ==================================================
// BETTER APPROACH (SLIDING WINDOW)
//
// Idea:
// Maintain a window using two pointers and track its current sum.
// Expand the window by moving the right pointer. If the sum exceeds K, shrink the window from the left until the condition becomes valid again.
//
// Time Complexity: O(2N)
// Space Complexity: O(1)
// ==================================================

// int longestSubarrayWithSum(vector<int> &arr, int K)
// {
//     int n = arr.size();

//     int l = 0, r = 0;

//     int sum = 0, maxLength = 0;

//     while (r < n)
//     {
//         sum += arr[r];

//         while (sum > K)
//         {
//             sum -= arr[l];
//             l++;
//         }

//         maxLength = max(maxLength, r - l + 1);

//         r++;
//     }

//     return maxLength;
// }

// ==================================================
// OPTIMAL APPROACH (SLIDING WINDOW)
//
// Idea:
// Use the sliding window technique where the right pointer expands the window.
// If the current sum exceeds K, remove the leftmost element once to restore the condition. Since the array contains positive integers, a single removal is sufficient for maintaining the optimal window movement.
//
// Time Complexity: O(N)
// Space Complexity: O(1)
// ==================================================

int longestSubarrayWithSum(vector<int> &arr, int K)
{
    int n = arr.size();

    int l = 0, r = 0;

    int sum = 0, maxLength = 0;

    while (r < n)
    {
        sum += arr[r];

        if (sum > K)
        {
            sum -= arr[l];
            l++;
        }

        maxLength = max(maxLength, r - l + 1);

        r++;
    }

    return maxLength;
}

int main()
{
    vector<int> arr = {2, 5, 1, 7, 10};
    int K = 14;

    int result = longestSubarrayWithSum(arr, K);

    cout << "The longest subarray length with sum <= " << K << " is: " << result << endl;

    return 0;
}