// Problem:
// Given an array nums of size n containing distinct integers
// in the range [0, n], exactly one number is missing.
//
// Return the missing number from this range.

#include <bits/stdc++.h>
using namespace std;

// ===================================================
// BRUTE FORCE APPROACH
//
// Idea:
// For every number in the range [0, n], check whether it
// exists in the array using linear search.
//
// The first number not found in the array is the answer.
//
// Time Complexity: O(N^2)
// Space Complexity: O(1)
// ===================================================

// int missingNumber(vector<int> &nums)
// {
//     int N = nums.size() + 1;

//     for (int i = 0; i <= N; i++)
//     {
//         bool found = false;

//         for (int j = 0; j < nums.size(); j++)
//         {
//             if (nums[j] == i)
//             {
//                 found = true;
//                 break;
//             }
//         }

//         if (!found)
//             return i;
//     }

//     return -1;
// }

// ===================================================
// BETTER APPROACH (HASHING)
//
// Idea:
// Use a hash array (frequency array) to mark which numbers
// are present in nums.
//
// Traverse nums and mark hash[nums[i]] = 1.
// Then iterate over [0, n] and return the index which is
// not marked.
//
// Time Complexity: O(N)
// Space Complexity: O(N)
// ===================================================

// int missingNumber(vector<int> &nums)
// {
//     int N = nums.size() + 1;

//     vector<int> hash(N, 0);

//     for (int i = 0; i < nums.size(); i++)
//         hash[nums[i]] = 1;

//     for (int i = 0; i < N; i++)
//         if (hash[i] == 0)
//             return i;

//     return -1;
// }

// ===================================================
// OPTIMAL APPROACH 1 (SUM FORMULA)
//
// Idea:
// The sum of numbers from 0 to n is:
//   n * (n + 1) / 2
//
// Compute expected sum and subtract the actual sum
// of elements in the array. The difference is the
// missing number.
//
// Time Complexity: O(N)
// Space Complexity: O(1)
//
// NOTE: Be careful with integer overflow for large n.
// ===================================================

// int missingNumber(vector<int> &nums)
// {
//     int N = nums.size();

//     int sum1 = (N * (N + 1)) / 2;

//     int sum2 = 0;

//     for (auto it : nums)
//         sum2 += it;

//     return sum1 - sum2;
// }

// ===================================================
// OPTIMAL APPROACH 2 (XOR)
//
// Idea:
// Use XOR properties:
// • A ^ A = 0
// • A ^ 0 = A
//
// XOR all numbers from 1 to n and all elements in nums.
// The duplicates cancel out, leaving the missing number.
//
// Time Complexity: O(N)
// Space Complexity: O(1)
// ===================================================

int missingNumber(vector<int> &nums)
{
    int xor1 = 0, xor2 = 0;

    for (int i = 0; i < nums.size(); i++)
    {
        xor1 = xor1 ^ (i + 1); // XOR of 1..n
        xor2 = xor2 ^ nums[i]; // XOR of array elements
    }

    return xor1 ^ xor2;
}

int main()
{
    vector<int> nums = {0, 1, 2, 4, 5, 6};
    // vector<int> nums = {1, 3, 6, 4, 2, 5};

    int missing = missingNumber(nums);

    cout << "Missing number: " << missing;

    return 0;
}