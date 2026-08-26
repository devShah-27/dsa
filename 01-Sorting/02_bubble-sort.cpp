// Given an array of integers called nums,sort the array in non-decreasing order using the bubble sort algorithm and return the sorted array.

#include <bits/stdc++.h>
using namespace std;

vector<int> bubbleSort(vector<int> &nums)
{
    int size = nums.size();

    for (int i = 0; i < size; i++)
    {
        int didSwap = 0;

        for (int j = 0; j < size - i - 1; j++)
        {
            if (nums[j] > nums[j + 1])
            {
                int temp = nums[j];
                nums[j] = nums[j + 1];
                nums[j + 1] = temp;

                didSwap = 1;
            }
        }

        if (didSwap == 0)
            break;
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

    vector<int> sortedNums = bubbleSort(nums);

    cout << "After Bubble Sort: ";
    for (auto it : sortedNums)
        cout << it << " ";
    cout << endl;

    return 0;
}