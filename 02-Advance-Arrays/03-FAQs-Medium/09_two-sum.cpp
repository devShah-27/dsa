// Problem:
// Given an integer array nums and an integer target,
// return the indices (0-indexed) of two elements such
// that their sum equals target.
//
// Each input has exactly one valid solution and the
// same element cannot be used twice.
// ===================================================

#include <bits/stdc++.h>
using namespace std;

// ===================================================
// BRUTE FORCE APPROACH
//
// Idea:
// Check every possible pair of elements in the array.
// For each index i, iterate through the remaining
// elements j > i and check whether:
//
// nums[i] + nums[j] == target
//
// As soon as such a pair is found, return their indices.
//
// Time Complexity: O(N^2)
// Space Complexity: O(1)
// ===================================================

// vector<int> twoSum(vector<int> &nums, int target)
// {
//     int n = nums.size();

//     vector<int> indices;

//     for (int i = 0; i < n; i++)
//     {
//         for (int j = i + 1; j < n; j++)
//         {
//             if (nums[i] + nums[j] == target)
//             {
//                 indices.emplace_back(i);
//                 indices.emplace_back(j);

//                 return indices;
//             }
//         }
//     }

//     return indices;
// }

// ===================================================
// BETTER APPROACH (HASH MAP)
//
// Idea:
// Traverse the array once while storing elements in
// a map where:
//
// key   -> array value
// value -> index of that value
//
// For every element nums[i], compute:
//
// otherInt = target - nums[i]
//
// If otherInt already exists in the map, we have found
// the required pair and can return the stored index
// along with i.
//
// This approach is commonly treated as the optimal
// solution when the problem asks for indices.
//
// Time Complexity: O(N log N) using map
// Space Complexity: O(N)
//
// NOTE: Using unordered_map would reduce the average
// time complexity to O(N).
// ===================================================

vector<int> twoSum(vector<int> &nums, int target)
{
    int n = nums.size();
    vector<int> indices;

    map<int, int> mpp;

    for (int i = 0; i < n; i++)
    {
        int otherInt = target - nums[i];

        if (mpp.count(otherInt))
        {
            indices.emplace_back(mpp[otherInt]);
            indices.emplace_back(i);
            return indices;
        }

        mpp[nums[i]] = i;
    }

    return indices;
}

// ===================================================
// OPTIMAL APPROACH (TWO POINTERS)
//
// Idea:
// Sort the array and then use the two-pointer technique to find two numbers whose sum equals target.
//
// Since sorting changes the original indices, we store elements as pairs: {value, original_index}. After sorting, apply two pointers from both ends.
//
// Move pointers based on the current sum:
//
// • sum < target → move left pointer
// • sum > target → move right pointer
//
// NOTE: This method modifies ordering due to sorting.
// It is typically used when the problem only asks whether such a pair exists (YES/NO) rather than returning indices directly.
//
// Time Complexity: O(N log N)
// Space Complexity: O(N)
// ===================================================

// vector<int> twoSum(vector<int> &nums, int target)
// {
//     int n = nums.size();
//     vector<int> indices;

//     vector<pair<int, int>> arr;

//     for (int i = 0; i < n; i++)
//         arr.push_back({nums[i], i});

//     sort(arr.begin(), arr.end());

//     int i = 0, j = n - 1;

//     while (i < j)
//     {
//         int sum = arr[i].first + arr[j].first;

//         if (sum == target)
//         {
//             indices.emplace_back(arr[i].second);
//             indices.emplace_back(arr[j].second);

//             return indices;
//         }
//         else if (sum < target)
//             i++;
//         else
//             j--;
//     }

//     return indices;
// }

int main()
{
    vector<int> input = {
        34, -21, 7, 18, -5, 42, 11, -9, 26, 3,
        -14, 8, 19, -30, 25, 16, -2, 41, -11, 6,
        13, -7, 29, -18, 22, 4, -25, 31, 10, -3,
        27, -15, 36, 2, -6, 21, -12, 38, 5, -8,
        14, 24, -4, 9, -16, 32, -10, 20, -13, 17};

    int target = 23;

    vector<int> ans = twoSum(input, target);

    cout << target << " is achieved by indices: ";

    for (int it : ans)
        cout << it << " ";

    return 0;
}