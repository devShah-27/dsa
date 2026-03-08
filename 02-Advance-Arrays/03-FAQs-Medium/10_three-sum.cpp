// Given an integer array nums. Return all triplets such that:
// - i != j, i != k, and j != k
// - nums[i] + nums[j] + nums[k] == 0.

// Notice that the solution set must not contain duplicate triplets. One element can be a part of multiple triplets. The output and the triplets can be returned in any order.

#include <bits/stdc++.h>
#include <chrono>
using namespace std;

// ====== BRUTE FORCE (Use 3 loops to identify triplets in O(N^3) time complexity) ======
// vector<vector<int>> threeSum(vector<int> &nums) // TC -> O(N^# * log(No. of unique triplets)), SC ->(2 * No. of unique triplets)
// {
//     int n = nums.size();

//     set<vector<int>> tripletSet;

//     for (int i = 0; i < n; i++) // O(N)
//     {
//         for (int j = i + 1; j < n; j++) // O(N)
//         {
//             for (int k = j + 1; k < n; k++) // O(N)
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

//     vector<vector<int>> ans(tripletSet.begin(), tripletSet.end());

//     return ans;
// }

// ====== BETTER (Use hashing to identify triplets in O(1) time complexity) ======
// vector<vector<int>> threeSum(vector<int> &nums) // TC -> O(N^2 * log(No. of unique triplets)), SC ->(2 * No. of unique triplets) + O(N)
// {
//     int n = nums.size();

//     set<vector<int>> tripletSet;

//     for (int i = 0; i < n; i++) // O(N)
//     {
//         set<int> hash;

//         for (int j = i + 1; j < n; j++) // O(N)
//         {
//             int k = -(nums[i] + nums[j]);

//             if (hash.find(k) != hash.end())
//             {
//                 vector<int> temp = {nums[i],
//                                     nums[j],
//                                     k};

//                 sort(temp.begin(), temp.end());

//                 tripletSet.insert(temp);
//             }

//             hash.insert(nums[j]);
//         }
//     }

//     vector<vector<int>> ans(tripletSet.begin(), tripletSet.end());

//     return ans;
// }

// ====== OPTIMAL (Use 2-pointer approach to identify triplets) ======
vector<vector<int>> threeSum(vector<int> &nums) // TC -> O(N^2) + O(N*log(N)), SC -> O(1)
{
    int n = nums.size();

    sort(nums.begin(), nums.end()); // O(N*log(N))

    vector<vector<int>> ans;

    for (int i = 0; i < n; i++) // O(N)
    {
        if (i > 0 && nums[i] == nums[i - 1])
            continue;

        int j = i + 1, k = n - 1;

        while (j < k) // O(N)
        {
            int sum = nums[i] + nums[j] + nums[k];

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
                vector<int> triplet = {nums[i], nums[j], nums[k]};
                ans.emplace_back(triplet);
                j++, k--;

                while (j < k && nums[j] == nums[j - 1])
                    j++;

                while (j < k && nums[k] == nums[k + 1])
                    k--;
            }
        }
    }

    return ans;
}

int main()
{
    // vector<int> nums = {
    //     -50, 23, -17, 9, -4, 15, -8, 42, -31, 7,
    //     13, -19, 28, -2, -11, 6, -7, 1, 3, -3,
    //     12, -12, 21, -21, 30, -30, 14, -14, 16, -16,
    //     5, -5, 18, -18, 24, -24, 27, -27, 33, -33,
    //     36, -36, 40, -40, 45, -45, 50, -50, 2, -2,
    //     4, -4, 6, -6, 8, -8, 10, -10, 11, -11,
    //     13, -13, 17, -17, 19, -19, 20, -20, 22, -22,
    //     25, -25, 26, -26, 29, -29, 31, -31, 34, -34,
    //     37, -37, 38, -38, 41, -41, 43, -43, 44, -44,
    //     46, -46, 47, -47, 48, -48, 49, -49, 0, 0};

    vector<int> nums = {-2, -2, -2, -1, -1, -1, 0, 0, 0, 2, 2, 2, 2};

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