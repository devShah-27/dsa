// Problem:
// Given an integer array nums and an integer k,
// return the total number of subarrays whose XOR equals k.
//
// A subarray is a contiguous sequence of elements.

#include <bits/stdc++.h>
using namespace std;

// ===================================================
// BRUTE FORCE APPROACH
//
// Idea:
// Generate all possible subarrays using three nested loops.
// For each subarray [i..j], compute XOR using a third loop.
// If XOR equals k, increment the count.
//
// Time Complexity: O(N^3)
// Space Complexity: O(1)
// ===================================================

// int subarraysWithXorK(vector<int> &nums, int k)
// {
//     int n = nums.size();

//     int count = 0;

//     for (int i = 0; i < n; i++)
//     {
//         for (int j = i; j < n; j++)
//         {
//             int XOR = 0;

//             for (int k = i; k <= j; k++)
//             {
//                 XOR ^= nums[k];
//             }

//             if (XOR == k)
//                 count++;
//         }
//     }

//     return count;
// }

// ===================================================
// IMPROVED BRUTE FORCE
//
// Idea:
// Eliminate the innermost loop by maintaining a running XOR.
// For each starting index i, keep XORing nums[j] as j expands.
//
// This avoids recomputing XOR for overlapping subarrays.
//
// Time Complexity: O(N^2)
// Space Complexity: O(1)
// ===================================================

// int subarraysWithXorK(vector<int> &nums, int k)
// {
//     int n = nums.size();

//     int count = 0;

//     for (int i = 0; i < n; i++)
//     {
//         int XOR = 0;

//         for (int j = i; j < n; j++)
//         {
//             XOR ^= nums[j];

//             if (XOR == k)
//                 count++;
//         }
//     }

//     return count;
// }

// ===================================================
// OPTIMAL APPROACH (PREFIX XOR + HASH MAP)
//
// Idea:
// Maintain prefix XOR while traversing the array.
//
// Let prefixXOR[i] = XOR of elements from 0 to i.
// For current XOR, we want to find number of previous
// prefix XORs such that:
//
// previousXOR ^ currentXOR = k
// → previousXOR = currentXOR ^ k
//
// Use a hashmap to store frequency of prefix XORs.
//
// Initialize map with {0:1} to handle subarrays starting
// from index 0.
//
// Time Complexity: O(N)
// Space Complexity: O(N)
// ===================================================

int subarraysWithXorK(vector<int> &nums, int k)
{
    int n = nums.size(), count = 0, XOR = 0;

    unordered_map<int, int> preXOR; // {prefixXOR -> frequency}

    preXOR[XOR] = 1; // Base case: XOR = 0 seen once

    for (int i = 0; i < n; i++)
    {
        XOR = XOR ^ nums[i];

        int x = XOR ^ k;

        if (preXOR.find(x) != preXOR.end())
            count += preXOR[x];

        // Increment frequency of current prefix XOR
        preXOR[XOR]++;
    }

    return count;
}

int main()
{
    vector<int> nums = {5, 2, 9};

    int target = 7;

    cout << "Array: ";
    for (int it : nums)
        cout << it << " ";
    cout << endl;

    int subarrayCount = subarraysWithXorK(nums, target);

    cout << "No. of Subarrays with XOR " << target << ": " << subarrayCount;

    return 0;
}