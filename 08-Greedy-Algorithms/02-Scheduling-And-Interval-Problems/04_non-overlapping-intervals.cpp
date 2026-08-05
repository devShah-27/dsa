// Problem:
// Given a set of intervals, remove the minimum number of intervals so that the remaining intervals are pairwise non-overlapping.
// Intervals that only touch at their endpoints are considered non-overlapping.

#include <bits/stdc++.h>
using namespace std;

bool comparator(vector<int> &i1, vector<int> &i2)
{
    return i1[1] < i2[1];
}

// ==================================================
// GREEDY APPROACH
//
// Idea:
// Sort the intervals by their ending times and greedily keep the interval that finishes earliest. This maximizes the number of non-overlapping intervals that can be retained. The answer is the total number of intervals minus the maximum number that can be kept.
//
// Time Complexity: O(N log N)
// Space Complexity: O(1) (excluding sorting overhead)
// ==================================================

int MaximumNonOverlappingIntervals(vector<vector<int>> &Intervals)
{
    int n = Intervals.size();

    // NOTE: Assumes the input contains at least one interval.
    sort(Intervals.begin(), Intervals.end(), comparator);

    int count = 1, lastEndTime = Intervals[0][1];

    for (int i = 1; i < n; i++)
    {
        if (Intervals[i][0] >= lastEndTime)
        {
            count++;
            lastEndTime = Intervals[i][1];
        }
    }

    return n - count;
}

int main()
{
    vector<vector<int>> intervals = {{0, 5}, {3, 4}, {1, 2}, {5, 9}, {7, 9}};

    int ans = MaximumNonOverlappingIntervals(intervals);

    cout << "Maximum Non-Overlapping Intervals: " << ans << endl;

    return 0;
}