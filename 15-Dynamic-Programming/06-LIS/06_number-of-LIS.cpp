// ==================================================
// PROBLEM
// - Given an integer array nums, find the total number of Longest Increasing Subsequences (LIS).
// - A subsequence is strictly increasing if every element is greater than the preceding one.
// - Return the count of all distinct subsequences that achieve the maximum possible length.
// ==================================================

#include <bits/stdc++.h>
using namespace std;

// ==================================================
// TABULATION (LIS VARIATION)
//
// Idea:
// - Maintain two DP arrays to track the maximum LIS length and the number of such subsequences ending at each index.
// - Inherit the predecessor's count when discovering a strictly longer subsequence, or accumulate the counts when matching the current maximum length.
// - Sum the counts across all indices achieving the global maximum.
//
// Time Complexity: O(n^2) - Nested loops evaluate all previous indices for each element.
// Space Complexity: O(n) - Two auxiliary arrays of size n track lengths and counts.
// ==================================================

int numberOfLIS(const vector<int> &nums)
{
    int n = nums.size();

    // len[idx] stores the length of the longest increasing subsequence ending at 'idx'
    // cnt[idx] stores the total number of such longest subsequences ending at 'idx'
    vector<int> len(n, 1), cnt(n, 1);

    // Track the global maximum LIS length found across the entire array
    int maxLen = 1;

    // Evaluate the optimal LIS length and frequency ending at each element
    for (int idx = 0; idx < n; idx++)
    {
        // Inspect all preceding elements to extend valid increasing subsequences
        for (int prevIdx = 0; prevIdx < idx; prevIdx++)
        {
            // Proceed only if the current element can strictly extend the previous subsequence
            if (nums[prevIdx] < nums[idx])
            {
                // Found a strictly longer subsequence ending at 'idx'
                if (len[idx] < len[prevIdx] + 1)
                {
                    len[idx] = len[prevIdx] + 1;
                    // Reset the count to match the number of ways to form the predecessor's LIS
                    cnt[idx] = cnt[prevIdx];
                }
                // Found another set of subsequences achieving the exact same maximum length at 'idx'
                else if (len[idx] == len[prevIdx] + 1)
                {
                    // Accumulate the additional ways from the current predecessor
                    cnt[idx] += cnt[prevIdx];
                }
            }
        }

        // Update the global maximum LIS length seen so far
        maxLen = max(maxLen, len[idx]);
    }

    int LISCnt = 0;

    // Sum the counts of all subsequences that achieved the global maximum length
    for (int idx = 0; idx < n; idx++)
    {
        if (len[idx] == maxLen)
            LISCnt += cnt[idx];
    }

    return LISCnt;
}

int main()
{
    vector<int> arr = {1, 3, 5, 4, 7};

    // Compute the total number of Longest Increasing Subsequences
    int ans = numberOfLIS(arr);

    cout << "The number of LIS present in the given array is: " << ans << endl;

    return 0;
}
