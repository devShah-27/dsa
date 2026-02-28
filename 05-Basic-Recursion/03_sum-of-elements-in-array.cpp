// Given an array nums, find the sum of elements of array using recursion.

#include <bits/stdc++.h>
using namespace std;

int getSum(const vector<int> &arr, int index = 0)
{
    if (index == arr.size())
        return 0;

    return arr[index] + getSum(arr, index + 1);
}

int main()
{
    vector<int> arr = {12, 9, 17};

    int sum = getSum(arr);

    cout << "Sum of all elements: " << sum;
}