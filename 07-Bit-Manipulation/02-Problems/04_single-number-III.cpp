// Problem:
// Given an array where every element appears twice except for two elements.
// Find the two unique elements and return them in ascending order.

#include <bits/stdc++.h>
using namespace std;

// ==================================================
// BRUTE FORCE APPROACH
// Idea:
// Store the frequency of every element using a hash map.
// Collect the elements whose frequency is 1 and sort the result.
//
// Time Complexity: O(N)
// Space Complexity: O(N)
// ==================================================

// vector<int> singleNumber(vector<int> &nums)
// {
//     vector<int> ans;

//     unordered_map<int, int> mpp;

//     for (int it : nums)
//         mpp[it]++;

//     for (auto it : mpp)
//         if (it.second == 1)
//             ans.emplace_back(it.first);

//     sort(ans.begin(), ans.end());

//     return ans;
// }

// ==================================================
// OPTIMAL APPROACH
// Idea:
// XOR of all elements gives (unique1 ^ unique2) since duplicate elements cancel each other. Find the rightmost set bit in this XOR result to partition the array into two groups. Each group contains exactly one unique element, so XORing within each group isolates the answer.
//
// Time Complexity: O(N)
// Space Complexity: O(1)
// ==================================================

vector<int> singleNumber(vector<int> &nums)
{
    long XOR = 0;

    for (int it : nums)
        XOR ^= it;

    // Extract the rightmost set bit from (unique1 ^ unique2).
    // This bit differs between the two unique numbers.
    int rightmostSetBit = (XOR & (XOR - 1)) ^ XOR;

    int XOR1 = 0, XOR2 = 0;

    for (int it : nums)
    {
        if (it & rightmostSetBit)
            XOR1 ^= it;
        else
            XOR2 ^= it;
    }

    vector<int> ans = {XOR1, XOR2};

    sort(ans.begin(), ans.end());

    return ans;
}

int main()
{
    vector<int> nums = {1, 2, 1, 5, 8, 2};

    vector<int> ans = singleNumber(nums);

    cout << "The single numbers in given array are: " << ans[0] << " and " << ans[1];

    return 0;
}