// Given an 2D array Jobs of size Nx3, where Jobs[i][0] represents JobID , Jobs[i][1] represents Deadline , Jobs[i][2] represents Profit associated with that job. Each Job takes 1 unit of time to complete and only one job can be scheduled at a time.

// The profit associated with a job is earned only if it is completed by its deadline. Find the number of jobs and maximum profit.

#include <bits/stdc++.h>
using namespace std;

bool comparator(vector<int> Job1, vector<int> Job2)
{
    return Job1[2] > Job2[2];
}

vector<int> JobScheduling(vector<vector<int>> &Jobs)
{
    sort(Jobs.begin(), Jobs.end(), comparator);

    int maxDeadline = INT_MIN;

    for (auto it : Jobs)
    {
        maxDeadline = max(maxDeadline, it[1]);
    }

    vector<int> days(maxDeadline + 1, -1);

    int profit = 0, count = 0;

    for (int i = 0; i < Jobs.size(); i++)
    {
        for (int j = Jobs[i][1]; j > 0; j--)
        {
            if (days[j] == -1)
            {
                days[j] = Jobs[i][0];
                count++;
                profit += Jobs[i][2];
                break;
            }
        }
    }

    return {count, profit};
}

int main()
{
    vector<vector<int>> jobs = {
        {1, 4, 20},
        {2, 1, 10},
        {3, 1, 40},
        {4, 1, 30}};

    vector<int> result = JobScheduling(jobs);

    cout << "Number of Jobs: " << result[0] << endl;
    cout << "Maximum Profit: " << result[1] << endl;

    return 0;
}