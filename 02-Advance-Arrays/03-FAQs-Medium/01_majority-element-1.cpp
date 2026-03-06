// Given an integer array nums of size n, return the majority element of the array.

// The majority element of an array is an element that appears more than n/2 times in the array. The array is guaranteed to have a majority element.

#include <bits/stdc++.h>
using namespace std;

// ============= BRUTE FORCE (Count occurance of every element) =============
// int majorityElement(vector<int> &nums) // TC -> O(N^2), SC -> O(1)
// {
//     int n = nums.size();

//     for (int val : nums) // O(N)
//     {
//         int count = 0;

//         for (int el : nums) // O(N)
//             if (val == el)
//                 count++;

//         if (count > (n / 2))
//             return val;
//     }

//     return -1;
// }

// ============= BETTER (Use something like map to store frequencies) =============
// int majorityElement(vector<int> &nums) // TC -> O(N), SC -> O(N)
// {
//     int n = nums.size();

//     map<int, int> mpp;

//     for (int it : nums) // O(N)
//         mpp[it]++;

//     for (auto it : mpp) // O(N)
//         if (it.second > (n / 2))
//             return it.first;

//     return -1;
// }

// ============= OPTIMAL (Use Moore's Voting Algorithm) =============
int majorityElement(vector<int> &nums) // TC -> O(N), SC -> O(1)
{
    int n = nums.size();

    int candidate = -1, vote = 0;

    for (int i = 0; i < n; i++)
    {
        if (vote == 0)
            candidate = nums[i];

        if (candidate == nums[i])
            vote++;
        else
            vote--;
    }

    // ========== Perform below only if array is not guaranteed to have a majority element ==========
    int freq = 0;

    for (int it : nums)
        if (it == candidate)
            freq++;

    if (freq > (n / 2))
        return candidate;

    return -1;
}

int main()
{
    vector<int> nums = {1, 1, 1, 2, 1, 2};

    cout << "Majority element: " << majorityElement(nums);

    return 0;
}
