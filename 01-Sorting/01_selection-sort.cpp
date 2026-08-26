// Given an array of integers nums, sort the array in non-decreasing order using the selection sort algorithm and return the sorted array.

#include <bits/stdc++.h>
using namespace std;

vector<int> selectionSort(vector<int> &nums)
{
    int arrSize = nums.size();
    for (int i = 0; i < arrSize - 1; i++)
    {
        int min = i;

        for (int j = i + 1; j < arrSize; j++)
        {
            if (nums[j] < nums[min])
                min = j;
        }

        int temp = nums[min];
        nums[min] = nums[i];
        nums[i] = temp;
    }

    return nums;
}

int main()
{
    vector<int> nums = {13, 46, 24, 52, 8, 9};

    cout << "Before Selection Sort: ";
    for (auto it : nums)
        cout << it << " ";
    cout << endl;

    vector<int> sortedNums = selectionSort(nums);

    cout << "After Selection Sort: ";
    for (auto it : sortedNums)
        cout << it << " ";
    cout << endl;

    return 0;
}