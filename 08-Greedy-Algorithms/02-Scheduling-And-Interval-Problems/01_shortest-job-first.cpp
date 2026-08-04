// A software engineer is tasked with using the shortest job first (SJF) policy to calculate the average waiting time for each process. The shortest job first also known as shortest job next (SJN) scheduling policy selects the waiting process with the least execution time to run next.

// You are given an array of integers bt of size n representing the burst times (execution times) of n processes.

// Your task is to calculate the average waiting time for all processes when scheduled using the SJF policy. The waiting time of a process is the total time a process has to wait before its execution starts, which is the sum of burst times of all previously executed processes.

// Return the floor of the average waiting time, i.e., the largest whole number less than or equal to the actual average.

#include <bits/stdc++.h>
using namespace std;

long long solve(vector<int> &bt)
{
    long long n = bt.size();

    if (n <= 0)
        return -1;

    sort(bt.begin(), bt.end());

    long long timer = 0, waitTime = 0;

    for (int it : bt)
    {
        waitTime += timer;
        timer += it;
    }

    return (waitTime / n);
}

int main()
{
    vector<int> jobs = {1, 2, 3, 4};

    cout << "Array Representing Job Durations: ";
    for (int i = 0; i < jobs.size(); i++)
    {
        cout << jobs[i] << " ";
    }
    cout << endl;

    long long ans = solve(jobs);
    cout << "Total waiting time: " << ans << endl;

    return 0;
}