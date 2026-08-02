// Given an array nums of length n, every integer in the array appears twice except for two integers. Identify and return the two integers that appear only once in the array. Return the two numbers in ascending order.

// For example, if nums = [1, 2, 1, 3, 5, 2], the correct answer is [3, 5], not [5, 3].

#include <bits/stdc++.h>
using namespace std;

// BRUTE FORCE
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

// OPTIMAL
vector<int> singleNumber(vector<int> &nums)
{
    long XOR = 0;

    for (int it : nums)
        XOR ^= it;

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
