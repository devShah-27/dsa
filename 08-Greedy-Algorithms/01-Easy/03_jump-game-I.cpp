// Given an array of integers nums, each element in the array represents the maximum jump length at that position. Initially starting at the first index of the array, determine if it is possible to reach the last index. Return true if the last index can be reached, otherwise return false.

#include <bits/stdc++.h>

using namespace std;

bool canJump(vector<int> &nums)
{
    int n = nums.size(), maxReachableIdx = 0;

    for (int i = 0; i < n; i++)
    {
        if (i > maxReachableIdx)
            return false;

        maxReachableIdx = max(maxReachableIdx, i + nums[i]);

        if (maxReachableIdx >= n)
            return true;
    }

    return true;
}

int main()
{
    vector<int> nums = {3, 2, 1, 0, 4};

    cout << "Array representing maximum jump from each index: ";
    for (int i = 0; i < nums.size(); i++)
    {
        cout << nums[i] << " ";
    }
    cout << endl;

    bool ans = canJump(nums);

    if (ans)
    {
        cout << "It is possible to reach the last index." << endl;
    }
    else
    {
        cout << "It is not possible to reach the last index." << endl;
    }

    return 0;
}