// ==================================================
// PROBLEM
// - Given an array of n integers, find the longest bitonic sequence length.
// - A sequence is bitonic if it first increases and then decreases.
// - The sequence elements do not need to be contiguous.
// ==================================================

#include <bits/stdc++.h>
using namespace std;

// ==================================================
// TABULATION (LIS VARIATION)
//
// Idea:
// - Treat a bitonic sequence as an increasing subsequence merged with a decreasing subsequence at a single shared peak index.
// - Precompute Longest Increasing Subsequence lengths from left-to-right and right-to-left.
// - Maximize the combined directional lengths at each index while subtracting one to avoid double-counting the overlapping peak element.
//
// Time Complexity: O(n^2) - Two separate nested loops for prefix and suffix DP tables.
// Space Complexity: O(n) - Two auxiliary arrays used to store directional LIS states.
// ==================================================

int LongestBitonicSequence(const vector<int> &arr)
{
    int n = arr.size();

    // prefixDP[idx] stores the length of the Longest Increasing Subsequence ending at 'idx'
    vector<int> prefixDP(n, 1);

    // Compute standard LIS from left to right (increasing part of the bitonic sequence)
    for (int idx = 0; idx < n; idx++)
    {
        for (int prevIdx = 0; prevIdx < idx; prevIdx++)
        {
            // Extend the increasing subsequence if the previous element is strictly smaller
            if (arr[prevIdx] < arr[idx] && prefixDP[idx] < prefixDP[prevIdx] + 1)
                prefixDP[idx] = prefixDP[prevIdx] + 1;
        }
    }

    // suffixDP[idx] stores the length of the Longest Decreasing Subsequence starting at 'idx'
    // (equivalent to computing LIS from right to left ending at 'idx')
    vector<int> suffixDP(n, 1);

    // Compute LIS from right to left (decreasing part of the bitonic sequence)
    for (int idx = n - 1; idx >= 0; idx--)
    {
        for (int prevIdx = n - 1; prevIdx > idx; prevIdx--)
        {
            // Extend the reverse increasing subsequence if the right-side element is strictly smaller
            if (arr[prevIdx] < arr[idx] && suffixDP[idx] < suffixDP[prevIdx] + 1)
                suffixDP[idx] = suffixDP[prevIdx] + 1;
        }
    }

    int bitonicLength = INT_MIN;

    // Evaluate each index 'i' as the potential peak of the bitonic subsequence
    for (int i = 0; i < n; i++)
    {
        // Combine the increasing length up to 'i' and decreasing length from 'i'
        // Subtract 1 because the peak element arr[i] is counted in both DP arrays
        // If both parts must be non-empty, guard the update with: if (prefixDP[i] > 1 && suffixDP[i] > 1)
        if (prefixDP[i] > 1 && suffixDP[i] > 1)
            bitonicLength = max(bitonicLength, prefixDP[i] + suffixDP[i] - 1);
    }

    return bitonicLength;
}

int main()
{
    vector<int> arr = {5, 1, 4, 2, 3, 6, 8, 7};

    // Compute the maximum length of a valid bitonic subsequence
    int lengthOfLongestBitonicSequence = LongestBitonicSequence(arr);

    cout << "The length of the Longest Bitonic Sequence is: " << lengthOfLongestBitonicSequence << endl;

    return 0;
}
