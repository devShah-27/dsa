// Given an array nums of n integers, return true if the array nums is sorted in non-decreasing order or else false.

#include <bits/stdc++.h>
using namespace std;

bool recursiveCheckSorted(vector<int> &arr, int N, int i)
{
    if (i >= N - 1)
        return true;

    if (arr[i] > arr[i + 1])
        return false;

    return recursiveCheckSorted(arr, N, i + 1);
}

bool isSorted(vector<int> &nums)
{
    return recursiveCheckSorted(nums, nums.size(), 0);
}

int main()
{
    vector<int> input = {1, 2, 4, 3, 5};

    bool sorted = isSorted(input);

    if (sorted)
        cout << "Given array is sorted";
    else
        cout << "Given array is not sorted";

    return 0;
}