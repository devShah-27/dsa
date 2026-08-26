// Problem:
// Given an integer array nums of size n, return the majority element.
//
// The majority element is the element that appears more than n/2 times
// in the array. It is guaranteed that the array contains a majority element.

#include <bits/stdc++.h>
using namespace std;

// ================================================================
// BRUTE FORCE APPROACH
//
// Idea:
// For each element, count how many times it appears in the array.
// If the count of any element becomes greater than n/2,
// that element is the majority element.
//
// Time Complexity:  O(N²)
// Space Complexity: O(1)
// ================================================================

// int majorityElement(vector<int> &nums)
// {
//     int n = nums.size();
//
//     for (int val : nums)
//     {
//         int count = 0;
//
//         for (int el : nums)
//         {
//             if (el == val)
//                 count++;
//         }
//
//         if (count > n / 2)
//             return val;
//     }
//
//     return -1;
// }

// ================================================================
// BETTER APPROACH (USING MAP)
//
// Idea:
// Store the frequency of each element using a map.
// Then check which element has a frequency greater than n/2.
//
// Time Complexity:  O(N log N)  (map operations)
// Space Complexity: O(N)
// ================================================================

// int majorityElement(vector<int> &nums)
// {
//     int n = nums.size();
//
//     map<int, int> freq;
//
//     // Count frequencies
//     for (int num : nums)
//         freq[num]++;
//
//     // Check for majority element
//     for (auto it : freq)
//     {
//         if (it.second > n / 2)
//             return it.first;
//     }
//
//     return -1;
// }

// ================================================================
// OPTIMAL APPROACH (MOORE'S VOTING ALGORITHM)
//
// Key Observation:
// If we cancel out different elements from the array,
// the majority element will always remain because it appears
// more than n/2 times.
//
// Algorithm:
// 1. Traverse the array and maintain a candidate and vote count.
// 2. If vote becomes 0, select the current element as the new candidate.
// 3. If the current element equals the candidate, increase vote.
// 4. Otherwise, decrease vote.
//
// Since the problem guarantees a majority element,
// the final candidate will be the answer.
//
// Time Complexity:  O(N)
// Space Complexity: O(1)
// ================================================================

int majorityElement(vector<int> &nums)
{
    int n = nums.size();

    int candidate = -1;
    int vote = 0;

    for (int i = 0; i < n; i++)
    {
        if (vote == 0)
            candidate = nums[i];

        if (nums[i] == candidate)
            vote++;
        else
            vote--;
    }

    return candidate;
}

int main()
{
    vector<int> nums = {1, 1, 1, 2, 1, 2};

    cout << "Majority element: " << majorityElement(nums);

    return 0;
}