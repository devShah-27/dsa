// Given a binary array nums, return the maximum number of consecutive 1s in the array.

// A binary array is an array that contains only 0s and 1s.

#include <bits/stdc++.h>
using namespace std;

int findMaxConsecutiveOnes(vector<int> &nums)
{
    int maxCount = 0, currCount = 0;

    for (int i = 0; i < nums.size(); i++)
    {
        if (nums[i] == 1)
            currCount++;
        else if (nums[i] == 0)
            currCount = 0;

        if (currCount > maxCount)
            maxCount = currCount;
    }

    return maxCount;
}

int main()
{
    int size;
    cin >> size;

    vector<int> nums(size);

    for (int i = 0; i < size; i++)
        cin >> nums[i];

    int maxConsecutiveOnes = findMaxConsecutiveOnes(nums);

    cout << "Max. Consecutive ones: " << maxConsecutiveOnes;

    return 0;
}