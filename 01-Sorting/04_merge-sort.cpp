// Given an array of integers, nums,sort the array in non-decreasing order using the merge sort algorithm. Return the sorted array.

#include <bits/stdc++.h>
using namespace std;

void merge(vector<int> &arr, int low, int mid, int high)
{
    vector<int> temp;

    int left = low, right = mid + 1;

    while (left <= mid && right <= high)
    {
        if (arr[left] <= arr[right])
        {
            temp.emplace_back(arr[left]);
            left++;
        }
        else
        {
            temp.emplace_back(arr[right]);
            right++;
        }
    }

    while (left <= mid)
    {
        temp.emplace_back(arr[left]);
        left++;
    }

    while (right <= high)
    {
        temp.emplace_back(arr[right]);
        right++;
    }

    for (int i = low; i <= high; i++)
    {
        arr[i] = temp[i - low];
    }
}

void recursiveMergeSort(vector<int> &arr, int low, int high)
{
    if (low >= high)
        return;

    int mid = (low + high) / 2;

    recursiveMergeSort(arr, low, mid);

    recursiveMergeSort(arr, mid + 1, high);

    merge(arr, low, mid, high);
}

vector<int> mergeSort(vector<int> &nums)
{
    recursiveMergeSort(nums, 0, nums.size() - 1);
    return nums;
}

int main()
{
    vector<int> nums = {13, 46, 24, 52, 8, 9};

    cout << "Before Merge Sort: ";
    for (auto it : nums)
        cout << it << " ";
    cout << endl;

    vector<int> sortedNums = mergeSort(nums);

    cout << "After Merge Sort: ";
    for (auto it : sortedNums)
        cout << it << " ";
    cout << endl;

    return 0;
}
