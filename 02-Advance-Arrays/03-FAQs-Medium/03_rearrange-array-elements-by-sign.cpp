// Problem:
// Given an array containing an equal number of positive and negative integers,
// rearrange the elements such that:
//
// • Every adjacent pair has opposite signs
// • Relative order of positive numbers is preserved
// • Relative order of negative numbers is preserved
// • The resulting array starts with a positive number

#include <bits/stdc++.h>
using namespace std;

// ================================================================
// BRUTE FORCE APPROACH
//
// Idea:
// • Separate positive and negative numbers into two lists
// • Rebuild the array by alternately placing elements from both lists
//
// Time Complexity:  O(N)
// Space Complexity: O(N)
// ================================================================

// vector<int> rearrangeArray(vector<int> &nums)
// {
//     vector<int> positives, negatives;
//
//     for (int val : nums)
//     {
//         if (val > 0)
//             positives.push_back(val);
//         else
//             negatives.push_back(val);
//     }
//
//     for (int i = 0; i < nums.size() / 2; i++)
//     {
//         nums[2 * i] = positives[i];
//         nums[2 * i + 1] = negatives[i];
//     }
//
//     return nums;
// }

// ================================================================
// OPTIMAL APPROACH
//
// Key Observation:
// Since the array contains equal positives and negatives and
// the result must start with a positive number:
//
// • Positive numbers occupy even indices (0,2,4,...)
// • Negative numbers occupy odd indices (1,3,5,...)
//
// Maintain two pointers that move by 2 positions each time.
//
// Time Complexity:  O(N)
// Space Complexity: O(N)
// ================================================================

vector<int> rearrangeArray(vector<int> &nums)
{
    vector<int> ans(nums.size());

    int pos = 0; // next even index for positive numbers
    int neg = 1; // next odd index for negative numbers

    for (int val : nums)
    {
        if (val > 0)
        {
            ans[pos] = val;
            pos += 2;
        }
        else
        {
            ans[neg] = val;
            neg += 2;
        }
    }

    return ans;
}

int main()
{
    vector<int> nums = {1, -1, -3, -4, 2, 3};

    cout << "Before rearranging by sign: ";
    for (int val : nums)
        cout << val << " ";
    cout << endl;

    vector<int> rearrangedNums = rearrangeArray(nums);

    cout << "After rearranging by sign: ";
    for (int val : rearrangedNums)
        cout << val << " ";
    cout << endl;

    return 0;
}