// Given an array of integers nums and an integer target. Return the indices(0 - indexed) of two elements in nums such that they add up to target.

// Each input will have exactly one solution, and the same element cannot be used twice. Return the answer in increasing order.

#include <bits/stdc++.h>
using namespace std;

// ======== BRUTE FORCE (For every element, iterate on remaining ones) ========
// vector<int> twoSum(vector<int> &nums, int target) // TC -> O(N^2), SC -> O(1)
// {
//     int n = nums.size();

//     vector<int> indices;

//     for (int i = 0; i < n; i++) // O(N)
//     {
//         for (int j = i + 1; j < n; j++) // O(N)
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

// ======== BETTER (Use a data structure like a map) (⚠️ For problems asking for indices, this is optimal) ========
vector<int> twoSum(vector<int> &nums, int target) // TC -> O(N*log(N)), SC -> O(N)
{
    int n = nums.size();
    vector<int> indices;

    map<int, int> mpp;

    for (int i = 0; i < n; i++) // O(N)
    {
        int otherInt = target - nums[i];

        if (mpp.count(otherInt)) // O(log(N))
        {
            indices.emplace_back(mpp[otherInt]);
            indices.emplace_back(i);
            return indices;
        }

        mpp[nums[i]] = i;
    }

    return indices;
}

// ======== OPTIMAL (⚠️ Only for problems that ask to return YES or NO) (Use 2 pointers) ========
// vector<int> twoSum(vector<int> &nums, int target) // TC -> O(N) + O(N*log(N)), SC -> O(1)
// {
//     int n = nums.size();
//     vector<int> indices;

//     vector<pair<int, int>> arr;

//     for (int i = 0; i < n; i++)
//         arr.push_back({nums[i], i});

//     sort(arr.begin(), arr.end()); // O(N*log(N))

//     int i = 0, j = n - 1;

//     while (i < j) // O(N)
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