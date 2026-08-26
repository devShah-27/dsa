// Given an array of integers called nums, sort the array in non-decreasing order using the quick sort algorithm and return the sorted array.

#include <bits/stdc++.h>
using namespace std;

int getPartitionIndex(vector<int> &nums, int low, int high)
{
    int pivot = low, smallPtr = low, largePtr = high;

    while (smallPtr < largePtr)
    {
        while (nums[smallPtr] <= nums[pivot] && smallPtr < high)
            smallPtr++;

        while (nums[largePtr] > nums[pivot] && largePtr > low)
            largePtr--;

        if (smallPtr < largePtr)
            swap(nums[smallPtr], nums[largePtr]);
    }

    swap(nums[pivot], nums[largePtr]);

    return largePtr;
}

void recursiveQuickSort(vector<int> &nums, int low, int high)
{
    if (low < high)
    {
        int partitionIndex = getPartitionIndex(nums, low, high);
        recursiveQuickSort(nums, low, partitionIndex - 1);
        recursiveQuickSort(nums, partitionIndex + 1, high);
    }
}

vector<int> quickSort(vector<int> &nums)
{
    recursiveQuickSort(nums, 0, nums.size() - 1);
    return nums;
}

int main()
{
    vector<int> nums = {13, 46, 24, 52, 8, 9, 8};

    cout << "Before Quick Sort: ";
    for (auto it : nums)
        cout << it << " ";
    cout << endl;

    vector<int> sortedNums = quickSort(nums);

    cout << "After Quick Sort: ";
    for (auto it : sortedNums)
        cout << it << " ";
    cout << endl;

    return 0;
}