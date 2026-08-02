// Problem:
// Given an array where every element appears twice except one element.
// Find the element that appears only once.

#include <bits/stdc++.h>
using namespace std;

// ==================================================
// BRUTE FORCE APPROACH
// Idea:
// Store the frequency of every element using a hash map.
// Traverse the frequency map to find the element whose count is 1.
//
// Time Complexity: O(N)
// Space Complexity: O(N)
// ==================================================

// int singleNumber(vector<int> &nums)
// {
//     unordered_map<int, int> mpp;

//     for (int it : nums)
//     {
//         mpp[it]++;
//     }

//     for (auto it : mpp)
//     {
//         if (it.second == 1)
//             return it.first;
//     }

//     return -1;
// }

// ==================================================
// OPTIMAL APPROACH
// Idea:
// Use XOR properties to cancel out duplicate elements.
// Since x ^ x = 0 and 0 ^ x = x, all pairs cancel each other, leaving only the element that appears once.
//
// Time Complexity: O(N)
// Space Complexity: O(1)
// ==================================================

int singleNumber(vector<int> &nums)
{
    int ans = 0;

    for (int it : nums)
    {
        ans ^= it;
    }

    return ans;
}

int main()
{
    vector<int> nums = {1, 2, 2, 4, 3, 1, 4};

    int ans = singleNumber(nums);

    cout << "The single number in given array is: " << ans;

    return 0;
}