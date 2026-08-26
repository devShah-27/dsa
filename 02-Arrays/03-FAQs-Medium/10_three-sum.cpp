// Problem:
// Given an integer array nums, return all unique triplets [a, b, c] such that:
//
// nums[a] + nums[b] + nums[c] == 0
//
// Constraints:
// • All indices must be distinct
// • Triplets must be unique (no duplicates)
// • Order of output does not matter

#include <bits/stdc++.h>
#include <chrono>
using namespace std;

// ================================================================
// BRUTE FORCE APPROACH
//
// Idea:
// • Try every combination of three indices
// • If their sum is zero, store the triplet
// • Sort each triplet so duplicates look identical
// • Use a set to automatically remove duplicates
//
// Time Complexity:  O(N³ * log(unique_triplets))
// Space Complexity: O(unique_triplets)
// ================================================================

// vector<vector<int>> threeSum(vector<int> &nums)
// {
//     int n = nums.size();
//     set<vector<int>> tripletSet;

//     for (int i = 0; i < n; i++)
//     {
//         for (int j = i + 1; j < n; j++)
//         {
//             for (int k = j + 1; k < n; k++)
//             {
//                 if (nums[i] + nums[j] + nums[k] == 0)
//                 {
//                     vector<int> temp = {nums[i], nums[j], nums[k]};
//                     sort(temp.begin(), temp.end());
//                     tripletSet.insert(temp);
//                 }
//             }
//         }
//     }

//     return vector<vector<int>>(tripletSet.begin(), tripletSet.end());
// }

// ================================================================
// BETTER APPROACH (HASHING)
//
// Idea:
// • Fix the first element (i)
// • Reduce the problem to finding two numbers whose sum equals -nums[i]
// • Use a hash set to track previously seen elements
// • Store sorted triplets in a set to avoid duplicates
//
// Time Complexity:  O(N² * log(unique_triplets))
// Space Complexity: O(N) + O(unique_triplets)
// ================================================================

// vector<vector<int>> threeSum(vector<int> &nums)
// {
//     int n = nums.size();
//     set<vector<int>> tripletSet;

//     for (int i = 0; i < n; i++)
//     {
//         set<int> hash;

//         for (int j = i + 1; j < n; j++)
//         {
//             int third = -(nums[i] + nums[j]);

//             if (hash.find(third) != hash.end())
//             {
//                 vector<int> temp = {nums[i], nums[j], third};
//                 sort(temp.begin(), temp.end());
//                 tripletSet.insert(temp);
//             }

//             hash.insert(nums[j]);
//         }
//     }

//     return vector<vector<int>>(tripletSet.begin(), tripletSet.end());
// }

// ================================================================
// OPTIMAL APPROACH (SORT + TWO POINTERS)
//
// Idea:
// • Sort the array
// • Fix one element (i)
// • Use two pointers (j, k) to find the remaining pair
// • Skip duplicates to ensure unique triplets
//
// Time Complexity:  O(N²)
// Space Complexity: O(1) extra (excluding output)
// ================================================================

vector<vector<int>> threeSum(vector<int> &nums)
{
    int n = nums.size();

    // Sorting enables two-pointer traversal and easy duplicate handling
    sort(nums.begin(), nums.end());

    vector<vector<int>> ans;

    for (int i = 0; i < n; i++)
    {
        // Skip duplicate values for the first element
        if (i > 0 && nums[i] == nums[i - 1])
            continue;

        int j = i + 1;
        int k = n - 1;

        while (j < k)
        {
            // Use long long to avoid integer overflow
            long long sum = (long long)nums[i] + nums[j] + nums[k];

            if (sum < 0)
            {
                j++;
            }
            else if (sum > 0)
            {
                k--;
            }
            else
            {
                ans.emplace_back(vector<int>{nums[i], nums[j], nums[k]});

                j++;
                k--;

                // Skip duplicate values for second element
                while (j < k && nums[j] == nums[j - 1])
                    j++;

                // Skip duplicate values for third element
                while (j < k && nums[k] == nums[k + 1])
                    k--;
            }
        }
    }

    return ans;
}

int main()
{
    vector<int> nums = {
        -50, 23, -17, 9, -4, 15, -8, 42, -31, 7,
        13, -19, 28, -2, -11, 6, -7, 1, 3, -3,
        12, -12, 21, -21, 30, -30, 14, -14, 16, -16,
        5, -5, 18, -18, 24, -24, 27, -27, 33, -33,
        36, -36, 40, -40, 45, -45, 50, -50, 2, -2,
        4, -4, 6, -6, 8, -8, 10, -10, 11, -11,
        13, -13, 17, -17, 19, -19, 20, -20, 22, -22,
        25, -25, 26, -26, 29, -29, 31, -31, 34, -34,
        37, -37, 38, -38, 41, -41, 43, -43, 44, -44,
        46, -46, 47, -47, 48, -48, 49, -49, 0, 0};

    auto start = chrono::steady_clock::now();

    vector<vector<int>> ans = threeSum(nums);

    auto end = chrono::steady_clock::now();

    auto duration = chrono::duration_cast<chrono::nanoseconds>(end - start);

    cout << "Execution time: " << duration.count() << " ns\n";

    cout << "Triplets that add up to 0 are:\n";

    for (vector<int> lvl1Elem : ans)
    {
        for (int lvl2Elem : lvl1Elem)
            cout << lvl2Elem << " ";

        cout << endl;
    }

    return 0;
}