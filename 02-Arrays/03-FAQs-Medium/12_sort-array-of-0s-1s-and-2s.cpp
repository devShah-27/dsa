// Problem:
// Given an array nums consisting only of 0s, 1s, and 2s, sort the array in non-decreasing order.

// The sorting must be done in-place without using extra space.

#include <bits/stdc++.h>
using namespace std;

// ================================================================
// BRUTE FORCE APPROACH (USE BUILT-IN SORT)
//
// Idea:
// Simply use the built-in sorting function.
// Since the array contains only integers, the STL sort will correctly arrange them in non-decreasing order.
//
// Time Complexity:  O(N log N)
// Space Complexity: O(1)
// ================================================================

// void sortZeroOneTwo(vector<int> &nums)
// {
//     sort(nums.begin(), nums.end());
// }

// ================================================================
// BETTER APPROACH (COUNTING METHOD)
//
// Idea:
// Count the number of 0s, 1s, and 2s in the array.
// Then overwrite the array with:
//   - all 0s first
//   - then all 1s
//   - then all 2s
//
// Time Complexity:  O(N)
// Space Complexity: O(1)
// ================================================================

// void sortZeroOneTwo(vector<int> &nums)
// {
//     int n = nums.size();
//
//     int count0 = 0;
//     int count1 = 0;
//     int count2 = 0;
//
//     // Count occurrences
//     for (int num : nums)
//     {
//         if (num == 0)
//             count0++;
//         else if (num == 1)
//             count1++;
//         else
//             count2++;
//     }
//
//     // Overwrite array with sorted values
//     int index = 0;
//
//     for (int i = 0; i < count0; i++)
//         nums[index++] = 0;
//
//     for (int i = 0; i < count1; i++)
//         nums[index++] = 1;
//
//     for (int i = 0; i < count2; i++)
//         nums[index++] = 2;
// }

// ================================================================
// OPTIMAL APPROACH (DUTCH NATIONAL FLAG ALGORITHM)
//
// Key Observation:
// Maintain three regions in the array:
//
//   [0 ... low-1]   -> all 0s
//   [low ... mid-1] -> all 1s
//   [mid ... high]  -> unknown elements
//   [high+1 ... n-1]-> all 2s
//
// Traverse the array using 'mid' and place elements in the correct region using swaps.
//
// Time Complexity:  O(N)
// Space Complexity: O(1)
// ================================================================

void sortZeroOneTwo(vector<int> &nums)
{
    int n = nums.size();

    int low = 0;
    int mid = 0;
    int high = n - 1;

    while (mid <= high)
    {
        if (nums[mid] == 0)
        {
            swap(nums[low], nums[mid]);
            low++;
            mid++;
        }
        else if (nums[mid] == 1)
        {
            mid++;
        }
        else
        {
            swap(nums[mid], nums[high]);
            high--;
        }
    }
}

int main()
{
    int n = 1000;
    vector<int> nums(n);

    // Generate random values (0, 1, or 2)
    for (int i = 0; i < n; i++)
        nums[i] = rand() % 3;

    cout << "Before sorting 0's, 1's, and 2's: ";
    for (int val : nums)
        cout << val << " ";
    cout << endl;

    sortZeroOneTwo(nums);

    cout << "\nAfter sorting 0's, 1's, and 2's: ";
    for (int val : nums)
        cout << val << " ";
    cout << endl;

    return 0;
}