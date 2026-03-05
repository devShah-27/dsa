// Given an integer array of size n containing distinct values in the range from 0 to n (inclusive), return the only number missing from the array within this range.

#include <bits/stdc++.h>
using namespace std;

// ============= BRUTE FORCE (2 loop approach) =============
// int missingNumber(vector<int> &nums)
// {
//     int N = nums.size() + 1;

//     for (int i = 0; i <= N; i++)
//     {
//         bool found = false;

//         for (int j = 0; j < nums.size(); j++)
//         {
//             if (nums[j] == i)
//             {
//                 found = true;
//                 break;
//             }
//         }

//         if (!found)
//             return i;
//     }

//     return -1;
// }

// ============= BETTER (Use Hashing) =============
// int missingNumber(vector<int> &nums)
// {
//     int N = nums.size() + 1;

//     vector<int> hash(N, 0);

//     for (int i = 0; i < nums.size(); i++)
//         hash[nums[i]] = 1;

//     for (int i = 0; i < N; i++)
//         if (hash[i] == 0)
//             return i;

//     return -1;
// }

// ============= OPTIMAL-1 (Use sum of N numbers formula) =============
// int missingNumber(vector<int> &nums)
// {
//     int N = nums.size(); // 0 inclusive so use nums.size directly. if 0 was not included, use nums.size()+1;

//     int sum1 = (N * (N + 1)) / 2;

//     int sum2 = 0;

//     for (auto it : nums)
//         sum2 = sum2 + it;

//     return sum1 - sum2;
// }

// ============= OPTIMAL-2 (Use XOR) =============

int missingNumber(vector<int> &nums)
{
    int xor1 = 0, xor2 = 0;

    for (int i = 0; i < nums.size(); i++)
    {
        xor1 = xor1 ^ (i + 1);
        xor2 = xor2 ^ nums[i];
    }

    return xor1 ^ xor2;
}

int main()
{
    vector<int> nums = {0, 1, 2, 4, 5, 6};
    // vector<int> nums = {1, 3, 6, 4, 2, 5};

    int missing = missingNumber(nums);

    cout << "Missing number: " << missing;

    return 0;
}