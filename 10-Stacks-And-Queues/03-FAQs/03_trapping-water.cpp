// Problem:
// Given an elevation map represented by an array of heights, calculate the
// amount of rainwater that can be trapped between the bars.

#include <bits/stdc++.h>
using namespace std;

// =============================================================
// OPTIMAL APPROACH - 1
//
// Idea:
// For every index, find the maximum height on its left and right side.
// The trapped water at an index is determined by the smaller of these two boundaries minus the current height.
//
// Time Complexity:
// O(3N) -> O(N), where N is the size of the array.
//
// Space Complexity:
// O(2N) -> O(N), for storing prefix and suffix maximum arrays.
//
// =============================================================

// void findPrefixAndSuffixMax(vector<int> &height, int n, vector<int> &prefixMax, vector<int> &suffixMax)
// {
//     prefixMax[0] = height[0];

//     for (int i = 1; i < n; i++)
//         prefixMax[i] = max(prefixMax[i - 1], height[i]);

//     suffixMax[n - 1] = height[n - 1];

//     for (int i = n - 2; i >= 0; i--)
//         suffixMax[i] = max(suffixMax[i + 1], height[i]);
// }

// int trap(vector<int> &height)
// {
//     int n = height.size();

//     int totalWater = 0;

//     vector<int> prefixMax(n), suffixMax(n);

//     findPrefixAndSuffixMax(height, n, prefixMax, suffixMax);

//     for (int i = 0; i < n; i++)
//     {
//         int leftMax = prefixMax[i];
//         int rightMax = suffixMax[i];

//         if (height[i] < leftMax && height[i] < rightMax)
//             totalWater += min(leftMax, rightMax) - height[i];
//     }

//     return totalWater;
// }

// =============================================================
// OPTIMAL APPROACH - 2
//
// Idea:
// Use two pointers to avoid storing prefix and suffix maximum arrays.
// Maintain the maximum height seen from both ends. The side with the smaller maximum determines the amount of water that can be trapped at that pointer.
//
// Time Complexity:
// O(N), where N is the size of the array.
//
// Space Complexity:
// O(1), as no additional data structures are used.
//
// =============================================================

int trap(vector<int> &height)
{
    int n = height.size();

    int l = 0, r = n - 1;
    int lmax = 0, rmax = 0;

    int ans = 0;

    while (l < r)
    {
        lmax = max(lmax, height[l]);
        rmax = max(rmax, height[r]);

        if (lmax < rmax)
        {
            ans += (lmax - height[l]);
            l++;
        }
        else
        {
            ans += (rmax - height[r]);
            r--;
        }
    }

    return ans;
}

int main()
{
    vector<int> heights = {4, 2, 0, 3, 2, 5};

    int ans = trap(heights);

    cout << "The trapped rainwater is: " << ans;

    return 0;
}