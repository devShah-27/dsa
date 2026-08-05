// Problem:
// Given a sorted list of non-overlapping intervals and a new interval, insert the new interval into the list while preserving the sorted order.
// Merge any overlapping intervals and return the updated list.

#include <bits/stdc++.h>
using namespace std;

// ==================================================
// GREEDY APPROACH
//
// Idea:
// Traverse the intervals in three phases:
// 1. Add all intervals that lie completely before the new interval.
// 2. Merge all intervals that overlap with the new interval.
// 3. Append the merged interval, followed by the remaining intervals.
//
// Time Complexity: O(N)
// Space Complexity: O(N)
// ==================================================

vector<vector<int>> insertNewInterval(vector<vector<int>> &Intervals, vector<int> &newInterval)
{
    int n = Intervals.size();

    int i = 0;

    vector<vector<int>> result;

    // Add intervals that end before the new interval begins.
    while (i < n && Intervals[i][1] < newInterval[0])
    {
        result.emplace_back(Intervals[i]);
        i++;
    }

    // Merge all overlapping intervals into newInterval.
    while (i < n && Intervals[i][0] <= newInterval[1])
    {
        newInterval[0] = min(newInterval[0], Intervals[i][0]);
        newInterval[1] = max(newInterval[1], Intervals[i][1]);
        i++;
    }

    // Insert the merged interval.
    result.emplace_back(newInterval);

    // Append all remaining intervals.
    while (i < n)
    {
        result.emplace_back(Intervals[i]);
        i++;
    }

    return result;
}

int main()
{
    vector<vector<int>> intervals = {{1, 2}, {3, 4}, {6, 7}, {8, 10}, {12, 16}};

    cout << "Intervals Array: ";

    for (auto interval : intervals)
    {
        cout << "[" << interval[0] << ", " << interval[1] << "], ";
    }
    cout << endl;

    vector<int> newInterval = {5, 8};

    cout << "New Interval to be Inserted: ";
    cout << "[" << newInterval[0] << ", " << newInterval[1] << "]" << endl;

    vector<vector<int>> result = insertNewInterval(intervals, newInterval);

    for (auto interval : result)
    {
        cout << "[" << interval[0] << ", " << interval[1] << "], ";
    }
    cout << endl;

    return 0;
}