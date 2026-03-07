// Given an integer array nums of even length consisting of an equal number of positive and negative integers.Return the answer array in such a way that the given conditions are met:

// - Every consecutive pair of integers have opposite signs.
// - For all integers with the same sign, the order in which they were present in nums is preserved.
// - The rearranged array begins with a positive integer.

#include <bits/stdc++.h>
using namespace std;

// ========== BRUTE FORCE (Store positives and negatives in separate lists) ==========
// vector<int> rearrangeArray(vector<int> &nums) // TC -> O(N^2), SC -> O(N)
// {
//     vector<int> positives, negatives;

//     for (int it : nums) // O(N)
//     {
//         if (it > 0)
//             positives.emplace_back(it);
//         else
//             negatives.emplace_back(it);
//     }

//     for (int i = 0; i < nums.size() / 2; i++) // O(N)
//     {
//         nums[2 * i] = positives[i];
//         nums[2 * i + 1] = negatives[i];
//     }

//     return nums;
// }

// ========== OPTIMAL (Store positives and negatives in a single list) ==========
vector<int> rearrangeArray(vector<int> &nums) // TC -> O(N), SC -> O(N)
{
    vector<int> ans(nums.size(), 0);

    int pos = 0, neg = 1;

    for (int it : nums)
    {
        if (it > 0)
        {
            ans[pos] = it;
            pos = pos + 2;
        }
        else
        {
            ans[neg] = it;
            neg = neg + 2;
        }
    }

    return ans;
}

int main()
{
    vector<int> nums = {1, -1, -3, -4, 2, 3};

    cout << "Before rearranging by sign: ";
    for (int it : nums)
        cout << it << " ";
    cout << endl;

    vector<int> rearrangedNums = rearrangeArray(nums);

    cout << "After rearranging by sign: ";
    for (int it : rearrangedNums)
        cout << it << " ";
    cout << endl;

    return 0;
}