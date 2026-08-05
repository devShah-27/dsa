// Problem:
// Given the start and end times of N meetings and a single meeting room, determine the maximum number of non-overlapping meetings that can be scheduled.
// A meeting can be selected only if its start time is strictly greater than the previous meeting's end time.

#include <bits/stdc++.h>
using namespace std;

bool comparator(vector<int> &m1, vector<int> &m2)
{
    return m1[1] < m2[1];
}

// ==================================================
// GREEDY APPROACH
//
// Idea:
// Pair each meeting's start time, end time, and original index, then sort the meetings by their finishing times. Always pick the meeting that finishes earliest, as it leaves the maximum remaining time available for scheduling future meetings.
//
// Time Complexity: O(N log N)
// Space Complexity: O(N)
// ==================================================

int maxMeetings(vector<int> &start, vector<int> &end)
{
    int n = start.size();

    vector<vector<int>> meetings(n);

    for (int i = 0; i < n; i++)
    {
        meetings[i] = {start[i], end[i], i + 1};
    }

    sort(meetings.begin(), meetings.end(), comparator);

    // NOTE: Assumes the input contains at least one meeting.
    int count = 1, lastFinishTime = meetings[0][1];

    vector<int> order;

    order.emplace_back(meetings[0][2]);

    for (int i = 1; i < n; i++)
    {
        if (meetings[i][0] > lastFinishTime)
        {
            count++;
            lastFinishTime = meetings[i][1];
            order.emplace_back(meetings[i][2]);
        }
    }

    return count;
}

int main()
{
    vector<int> start = {1, 3, 0, 5, 5, 8, 2, 4, 6, 8, 9, 11, 12, 13, 14};
    vector<int> end = {2, 4, 6, 7, 9, 9, 3, 5, 8, 10, 11, 12, 13, 14, 15};

    int maxMeetingsNum = maxMeetings(start, end);

    cout << "Maximum number of meetings: " << maxMeetingsNum << endl;

    return 0;
}