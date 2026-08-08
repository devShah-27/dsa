// Problem:
// Given a binary array nums and an integer k, flip at most k zeros to ones.
// Return the maximum length of a contiguous subarray containing only 1s after performing the flipping operation.

#include <bits/stdc++.h>
using namespace std;

// ==================================================
// BRUTE FORCE APPROACH
//
// Idea:
// Generate every possible subarray and count the number of zeros inside it.
// If the number of zeros is within the allowed limit k, update the maximum length.
// Stop expanding the current subarray once the zero count exceeds k.
//
// Time Complexity: O(N^2)
// Space Complexity: O(1)
// ==================================================

// int longestOnes(vector<int> &nums, int k)
// {
//     int n = nums.size();

//     int maxLength = 0;

//     for (int i = 0; i < n; i++)
//     {
//         int zeroCount = 0;

//         for (int j = i; j < n; j++)
//         {
//             if (nums[j] == 0)
//                 zeroCount++;

//             if (zeroCount > k)
//                 break;

//             maxLength = max(maxLength, j - i + 1);
//         }
//     }

//     return maxLength;
// }

// ==================================================
// BETTER APPROACH (SLIDING WINDOW)
//
// Idea:
// Maintain a window using two pointers and track the number of zeros inside it.
// Expand the window using the right pointer. If zeros exceed k, shrink the window from the left until the number of zeros becomes valid again.
//
// Time Complexity: O(2N)
// Space Complexity: O(1)
// ==================================================

// int longestOnes(vector<int> &nums, int k)
// {
//     int n = nums.size();

//     int zeroCount = 0, maxLength = 0;

//     int r = 0, l = 0;

//     while (r < n)
//     {
//         if (nums[r] == 0)
//             zeroCount++;

//         while (zeroCount > k)
//         {
//             if (nums[l] == 0)
//                 zeroCount--;

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
// Maintain a valid window containing at most k zeros.
// Move the right pointer to expand the window. When the zero count exceeds k, move the left pointer once to restore validity. Since the window only shrinks when necessary, each element is processed at most once.
//
// Time Complexity: O(N)
// Space Complexity: O(1)
// ==================================================

int longestOnes(vector<int> &nums, int k)
{
    int n = nums.size();

    int zeroCount = 0, maxLength = 0;

    int r = 0, l = 0;

    while (r < n)
    {
        if (nums[r] == 0)
            zeroCount++;

        if (zeroCount > k)
        {
            if (nums[l] == 0)
                zeroCount--;

            l++;
        }
        else
        {
            maxLength = max(maxLength, r - l + 1);
        }

        r++;
    }

    return maxLength;
}

int main()
{
    vector<int> input = {1, 1, 1, 1, 0, 1, 0, 1};
    int k = 2;

    int length = longestOnes(input, k);

    cout << "Length of longest substring with at most " << k << " zeros: " << length << endl;

    return 0;
}