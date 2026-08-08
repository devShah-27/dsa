// Problem:
// Given an array where fruits[i] represents the type of fruit on the ith tree, find the maximum number of fruits that can be collected from a contiguous range containing at most two distinct fruit types.

#include <bits/stdc++.h>
using namespace std;

// ==================================================
// BRUTE FORCE APPROACH
//
// Idea:
// Generate every possible subarray and store the distinct fruit types present.
// If the number of distinct types exceeds two, stop expanding the current range.
// Track the maximum valid subarray length.
//
// Time Complexity: O(N^2)
// Space Complexity: O(1)
// ==================================================

// int totalFruits(vector<int> &fruits)
// {
//     int n = fruits.size(), maxLength = 0;

//     for (int i = 0; i < n; i++)
//     {
//         unordered_set<int> st;

//         for (int j = i; j < n; j++)
//         {
//             st.emplace(fruits[j]);

//             if (st.size() > 2)
//                 break;

//             maxLength = max(maxLength, j - i + 1);
//         }
//     }

//     return maxLength;
// }

// ==================================================
// BETTER APPROACH (SLIDING WINDOW)
//
// Idea:
// Maintain a sliding window containing at most two distinct fruit types.
// Expand the window using the right pointer. If the number of fruit types exceeds two, shrink the window from the left until the condition becomes valid again.
//
// Time Complexity: O(2N)
// Space Complexity: O(1)
// ==================================================

// int totalFruits(vector<int> &fruits)
// {
//     int n = fruits.size(), maxLength = 0;

//     int l = 0, r = 0;

//     unordered_map<int, int> mpp;

//     while (r < n)
//     {
//         mpp[fruits[r]]++;

//         while (mpp.size() > 2)
//         {
//             mpp[fruits[l]]--;

//             if (mpp[fruits[l]] == 0)
//                 mpp.erase(fruits[l]);

//             l++;
//         }

//         maxLength = max(maxLength, r - l + 1);

//         r++;
//     }

//     return maxLength;
// }

// ==================================================
// OPTIMAL APPROACH (SLIDING WINDOW)
//
// Idea:
// Maintain a window with at most two distinct fruit types using two pointers.
// When a third fruit type appears, remove the leftmost fruits until only two types remain. Since both pointers move only forward, each element is processed once.
//
// Time Complexity: O(N)
// Space Complexity: O(1)
// ==================================================

int totalFruits(vector<int> &fruits)
{
    int n = fruits.size(), maxLength = 0;

    int l = 0, r = 0;

    unordered_map<int, int> mpp;

    while (r < n)
    {
        mpp[fruits[r]]++;

        if (mpp.size() > 2)
        {
            mpp[fruits[l]]--;

            if (mpp[fruits[l]] == 0)
                mpp.erase(fruits[l]);

            l++;
        }

        if (mpp.size() <= 2)
        {
            maxLength = max(maxLength, r - l + 1);
        }

        r++;
    }

    return maxLength;
}

int main()
{
    vector<int> input = {3, 3, 3, 1, 2, 1, 1, 2, 3, 3, 4};

    int length = totalFruits(input);

    cout << "Maximum fruits in the basket is: " << length << endl;

    return 0;
}