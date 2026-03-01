// Given an array nums of n integers, return reverse of the array.

#include <bits/stdc++.h>
using namespace std;

void recursiveReverseArray(vector<int> &arr, int N, int i)
{
    if (i >= (N / 2))
        return;

    int temp = arr[i];
    arr[i] = arr[N - i - 1];
    arr[N - i - 1] = temp;

    recursiveReverseArray(arr, N, i + 1);
}

vector<int> reverseArray(vector<int> &nums)
{
    recursiveReverseArray(nums, nums.size(), 0);

    return nums;
}

int main()
{
    vector<int> arr = {1, 2, 3, 4};

    cout << "Before reverse: ";
    for (auto it : arr)
        cout << it << " ";

    cout << endl;

    vector<int> revArr = reverseArray(arr);

    cout << "After reverse: ";
    for (auto it : revArr)
        cout << it << " ";

    cout << endl;
}
