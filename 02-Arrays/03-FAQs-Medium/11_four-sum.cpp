// Problem:
// Given an integer array nums and an integer target,
// return all unique quadruplets [a, b, c, d] such that:
//
// nums[a] + nums[b] + nums[c] + nums[d] == target
//
// Constraints:
// • All indices must be distinct
// • Quadruplets must be unique (no duplicates)
// • Order of output does not matter

#include <bits/stdc++.h>
using namespace std;

// ================================================================
// BRUTE FORCE APPROACH
// Try every possible combination of 4 indices using four loops.
//
// Idea:
// • Generate all quadruplets
// • Sort each quadruplet so duplicates look identical
// • Store in a set to automatically remove duplicates
//
// Time Complexity:  O(N^4 * log(unique_quadruplets))
// Space Complexity: O(unique_quadruplets)
// ================================================================

// vector<vector<int>> fourSum(vector<int> &nums, int target)
// {
//     int n = nums.size();
//     set<vector<int>> st;

//     for (int i = 0; i < n; i++)
//     {
//         for (int j = i + 1; j < n; j++)
//         {
//             for (int k = j + 1; k < n; k++)
//             {
//                 for (int l = k + 1; l < n; l++)
//                 {
//                     long long sum = nums[i] + nums[j] + nums[k] + nums[l];

//                     if (sum == target)
//                     {
//                         vector<int> temp = {nums[i], nums[j], nums[k], nums[l]};
//                         sort(temp.begin(), temp.end());
//                         st.insert(temp);
//                     }
//                 }
//             }
//         }
//     }

//     return vector<vector<int>>(st.begin(), st.end());
// }

// ================================================================
// BETTER APPROACH (HASHING)
//
// Idea:
// • Fix two elements (i, j)
// • Reduce problem to finding two numbers whose sum equals remaining target
// • Use a hash set to track previously seen elements
// • Store sorted quadruplets in a set to avoid duplicates
//
// Time Complexity:  O(N^3 * log(unique_quadruplets))
// Space Complexity: O(N) + O(unique_quadruplets)
// ================================================================

// vector<vector<int>> fourSum(vector<int> &nums, int target)
// {
//     int n = nums.size();
//     set<vector<int>> st;

//     for (int i = 0; i < n; i++)
//     {
//         for (int j = i + 1; j < n; j++)
//         {
//             set<long long> hashSet;

//             for (int k = j + 1; k < n; k++)
//             {
//                 long long sumOfThree = nums[i] + nums[j] + nums[k];
//                 long long fourth = target - sumOfThree;

//                 if (hashSet.find(fourth) != hashSet.end())
//                 {
//                     vector<int> temp = {nums[i], nums[j], nums[k], (int)fourth};
//                     sort(temp.begin(), temp.end());
//                     st.insert(temp);
//                 }

//                 hashSet.insert(nums[k]);
//             }
//         }
//     }

//     return vector<vector<int>>(st.begin(), st.end());
// }

// ================================================================
// OPTIMAL APPROACH (SORT + TWO POINTERS)
//
// Idea:
// • Sort the array
// • Fix first two numbers (i, j)
// • Use two pointers (k, l) to find remaining pair
// • Skip duplicates at every stage to ensure uniqueness
//
// Time Complexity:  O(N^3)
// Space Complexity: O(1) extra (excluding output)
// ================================================================

vector<vector<int>> fourSum(vector<int> &nums, int target)
{
    int n = nums.size();

    // Sorting allows two-pointer traversal and easy duplicate skipping
    sort(nums.begin(), nums.end());

    vector<vector<int>> ans;

    for (int i = 0; i < n; i++)
    {
        // Skip duplicate values for the first element
        if (i > 0 && nums[i] == nums[i - 1])
            continue;

        for (int j = i + 1; j < n; j++)
        {
            // Skip duplicate values for the second element
            if (j > i + 1 && nums[j] == nums[j - 1])
                continue;

            int k = j + 1;
            int l = n - 1;

            // Two-pointer search for remaining pair
            while (k < l)
            {
                long long sum = nums[i] + nums[j] + nums[k] + nums[l];

                if (sum < target)
                {
                    k++;
                }
                else if (sum > target)
                {
                    l--;
                }
                else
                {
                    ans.push_back({nums[i], nums[j], nums[k], nums[l]});

                    k++;
                    l--;

                    // Skip duplicate values for third element
                    while (k < l && nums[k] == nums[k - 1])
                        k++;

                    // Skip duplicate values for fourth element
                    while (k < l && nums[l] == nums[l + 1])
                        l--;
                }
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

    int target = 5;

    vector<vector<int>> ans = fourSum(nums, target);

    cout << "Quadruplets that add up to " << target << " are:\n";

    for (vector<int> lvl1Elem : ans)
    {
        for (int lvl2Elem : lvl1Elem)
            cout << lvl2Elem << " ";

        cout << endl;
    }

    return 0;
}