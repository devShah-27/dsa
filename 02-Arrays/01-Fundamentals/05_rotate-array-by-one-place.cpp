// Given an integer array nums, rotate the array to the left by one.

// Note: There is no need to return anything, just modify the given array.

#include <bits/stdc++.h>
using namespace std;

void rotateArrayByOne(vector<int> &nums)
{
    int n = nums.size(), temp = nums[0];

    for (int i = 1; i < n; i++)
        nums[i - 1] = nums[i];

    nums[n - 1] = temp;
}

int main()
{
    int size;
    cin >> size;

    vector<int> nums(size);

    for (int i = 0; i < size; i++)
        cin >> nums[i];

    cout << "Before one rotation: ";
    for (int it : nums)
        cout << it << " ";
    cout << endl;

    rotateArrayByOne(nums);

    cout << "After one rotation: ";
    for (int it : nums)
        cout << it << " ";
    cout << endl;

    return 0;
}