// Given an array of integers nums and an integer target, find the smallest index (0 based indexing) where the target appears in the array. If the target is not found in the array, return -1.

#include <bits/stdc++.h>
using namespace std;

int linearSearch(vector<int> &nums, int target)
{
    for (int i = 0; i < nums.size(); i++)
    {
        if (nums[i] == target)
            return i;
    }

    return -1;
}

int main()
{
    int size;
    cin >> size;

    vector<int> nums(size);

    for (int i = 0; i < size; i++)
        cin >> nums[i];

    int query;
    cin >> query;

    int index = linearSearch(nums, query);

    if (index == -1)
        cout << query << " was not found";
    else
        cout << query << " was found at index " << index;

    return 0;
}