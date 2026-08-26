// Given an array of integers called nums, sort the array in non-decreasing order using the insertion sort algorithm and return the sorted array.

#include <bits/stdc++.h>
using namespace std;

vector<int> insertionSort(vector<int> &nums)
{
    int size = nums.size();

    for (int i = 0; i < size; i++)
    {
        int j = i;
        while (j > 0 && nums[j-1] > nums[j])
        {
            int temp = nums[j];
            nums[j] = nums[j - 1];
            nums[j - 1] = temp;

            j--;
        }
    }

    return nums;
}

int main()
{
    vector<int> nums = {13, 46, 24, 52, 8, 9};

    cout << "Before Bubble Sort: ";
    for (auto it : nums)
        cout << it << " ";
    cout << endl;

    vector<int> sortedNums = insertionSort(nums);

    cout << "After Bubble Sort: ";
    for (auto it : sortedNums)
        cout << it << " ";
    cout << endl;

    return 0;
}