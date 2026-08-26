// Problem:
// Given an integer array nums of size n, return all elements that appear
// more than ⌊n/3⌋ times in the array.
//
// The result can contain at most two such elements because an element
// must appear more than n/3 times to qualify.

#include <bits/stdc++.h>
using namespace std;

// ================================================================
// BRUTE FORCE APPROACH
//
// Idea:
// For every element, count how many times it appears in the array.
// If its frequency is greater than n/3, add it to the result.
//
// Since at most two elements can appear more than n/3 times,
// stop early if two elements are found.
//
// Time Complexity:  O(N²)
// Space Complexity: O(1) extra (excluding output)
// ================================================================

// vector<int> majorityElementTwo(vector<int> &nums)
// {
//     int n = nums.size();
//     vector<int> ans;
//
//     for (int i = 0; i < n; i++)
//     {
//         if (ans.size() == 0 || ans[0] != nums[i])
//         {
//             int count = 0;
//
//             for (int j = 0; j < n; j++)
//             {
//                 if (nums[i] == nums[j])
//                     count++;
//             }
//
//             if (count > n / 3)
//                 ans.push_back(nums[i]);
//         }
//
//         if (ans.size() == 2)
//             break;
//     }
//
//     return ans;
// }

// ================================================================
// BETTER APPROACH (USING MAP)
//
// Idea:
// Use a map to store the frequency of each element while traversing
// the array once. When any element reaches frequency > n/3,
// add it to the result.
//
// Since at most two such elements can exist, stop when two are found.
//
// Time Complexity:  O(N log N)
// Space Complexity: O(N)
// ================================================================

// vector<int> majorityElementTwo(vector<int> &nums)
// {
//     int n = nums.size();
//
//     int minMajorityFreq = (n / 3) + 1;
//     map<int, int> freq;
//
//     vector<int> ans;
//
//     for (int num : nums)
//     {
//         freq[num]++;
//
//         if (freq[num] == minMajorityFreq)
//             ans.push_back(num);
//
//         if (ans.size() == 2)
//             break;
//     }
//
//     return ans;
// }

// ================================================================
// OPTIMAL APPROACH (MODIFIED MOORE'S VOTING ALGORITHM)
//
// Key Observation:
// At most two elements can appear more than n/3 times.
//
// Algorithm:
// 1. Maintain two candidate elements and their counts.
// 2. Traverse the array and update candidates using a voting process.
// 3. After selecting candidates, verify their actual frequencies.
//
// Time Complexity:  O(N)
// Space Complexity: O(1)
// ================================================================

vector<int> majorityElementTwo(vector<int> &nums)
{
    int n = nums.size();

    int count1 = 0, count2 = 0;

    int elem1 = INT_MIN, elem2 = INT_MIN;

    // Step 1: Find potential candidates
    for (int i = 0; i < n; i++)
    {
        if (count1 == 0 && elem2 != nums[i])
        {
            count1 = 1;
            elem1 = nums[i];
        }
        else if (count2 == 0 && elem1 != nums[i])
        {
            count2 = 1;
            elem2 = nums[i];
        }
        else if (nums[i] == elem1)
        {
            count1++;
        }
        else if (nums[i] == elem2)
        {
            count2++;
        }
        else
        {
            count1--;
            count2--;
        }
    }

    // Step 2: Verify candidates
    int minMajorityFreq = (n / 3) + 1;
    count1 = 0;
    count2 = 0;

    for (int i = 0; i < n; i++)
    {
        if (nums[i] == elem1)
            count1++;

        if (nums[i] == elem2)
            count2++;
    }

    vector<int> ans;

    if (count1 >= minMajorityFreq)
        ans.push_back(elem1);

    if (count2 >= minMajorityFreq)
        ans.push_back(elem2);

    return ans;
}

int main()
{
    vector<int> nums = {1, 1, 2, 2, 1, 1, 3, 2, 2, 3};

    cout << "Given array: ";
    for (int it : nums)
        cout << it << " ";
    cout << "\n";

    vector<int> majorityElements = majorityElementTwo(nums);

    cout << "Majority elements: ";
    for (int it : majorityElements)
        cout << it << " ";

    return 0;
}