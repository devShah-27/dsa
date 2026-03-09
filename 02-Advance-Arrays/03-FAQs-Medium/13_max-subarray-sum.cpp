// Problem:
// Given an integer array nums, find the subarray with the largest sum
// and return the sum of the elements in that subarray.
//
// A subarray is a contiguous non-empty sequence of elements within the array.

#include <bits/stdc++.h>
using namespace std;

// ================================================================
// BRUTE FORCE APPROACH
//
// Idea:
// Generate every possible subarray and compute its sum.
// Keep track of the maximum sum encountered.
//
// Three nested loops are used:
// 1. First loop selects the starting index.
// 2. Second loop selects the ending index.
// 3. Third loop calculates the sum of that subarray.
//
// Time Complexity:  O(N³)
// Space Complexity: O(1)
// ================================================================

// int maxSubArray(vector<int> &nums)
// {
//     int n = nums.size();
//     int maxSum = INT_MIN;
//
//     for (int i = 0; i < n; i++)
//     {
//         for (int j = i; j < n; j++)
//         {
//             int sum = 0;
//
//             for (int k = i; k <= j; k++)
//             {
//                 sum += nums[k];
//             }
//
//             maxSum = max(maxSum, sum);
//         }
//     }
//
//     return maxSum;
// }

// ================================================================
// BETTER APPROACH
//
// Idea:
// Instead of recalculating the sum for every subarray, maintain a running sum while expanding the subarray.
//
// Fix a starting index i, then keep adding elements from i to the right and update the maximum sum.
//
// Time Complexity:  O(N²)
// Space Complexity: O(1)
// ================================================================

// int maxSubArray(vector<int> &nums)
// {
//     int n = nums.size();
//     int maxSum = INT_MIN;
//
//     for (int i = 0; i < n; i++)
//     {
//         int sum = 0;
//
//         for (int j = i; j < n; j++)
//         {
//             sum += nums[j];
//             maxSum = max(maxSum, sum);
//         }
//     }
//
//     return maxSum;
// }

// ================================================================
// OPTIMAL APPROACH (KADANE'S ALGORITHM)
//
// Key Observation:
// If the running sum becomes negative, it cannot contribute to a future maximum subarray. Therefore, reset it to 0.
//
// Algorithm:
// Traverse the array while maintaining a running sum.
// Update the maximum sum whenever the running sum increases.
//
// Time Complexity:  O(N)
// Space Complexity: O(1)
// ================================================================

// int maxSubArray(vector<int> &nums)
// {
//     int maxSum = INT_MIN;
//     int currentSum = 0;
//
//     for (int num : nums)
//     {
//         currentSum += num;
//         maxSum = max(maxSum, currentSum);
//
//         if (currentSum < 0)
//             currentSum = 0;
//     }
//
//     return maxSum;
// }

// ================================================================
// FOLLOW-UP: PRINT THE MAXIMUM SUM SUBARRAY
//
// In addition to Kadane's Algorithm, maintain indices to track where the maximum subarray starts and ends.
//
// start     -> potential starting index
// ansStart  -> start of best subarray
// ansEnd    -> end of best subarray
//
// Time Complexity:  O(N)
// Space Complexity: O(1)
// ================================================================

int maxSubArray(vector<int> &nums)
{
    int n = nums.size();

    int maxSum = INT_MIN;
    int currentSum = 0;

    int start = 0;
    int ansStart = -1;
    int ansEnd = -1;

    for (int i = 0; i < n; i++)
    {
        if (currentSum == 0)
            start = i;

        currentSum += nums[i];

        if (currentSum > maxSum)
        {
            maxSum = currentSum;
            ansStart = start;
            ansEnd = i;
        }

        if (currentSum < 0)
            currentSum = 0;
    }

    cout << "The subarray is: [";
    for (int i = ansStart; i <= ansEnd; i++)
    {
        cout << nums[i];
        if (i != ansEnd)
            cout << ", ";
    }
    cout << "]" << endl;

    return maxSum;
}

int main()
{
    vector<int> nums = {-50, -40, -30, -20, -10, 1, 2, 3, 4, 5, 6, 7, 8, 9, 10, -5, -4, -3, -2, -1, 10, 20, 30, 40, 50, -100, -90, -80, -70, -60, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, -10, -20, -30, 100, 200, 300, 400, 500, -1000, 50, 60, 70, 80, 90, 100, -10, -10, -10, 200, 300, 400, -500, 1000, 1000, 1000};

    int maxSubArraySum = maxSubArray(nums);

    cout << "Maximum subarray sum: " << maxSubArraySum;

    return 0;
}