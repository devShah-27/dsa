// Given an array arr of size n, the task is to find the sum of all the elements in the array.

#include <bits/stdc++.h>
using namespace std;

int getSum(int arr[], int n)
{
    int sum = 0;

    for (int i = 0; i < n; i++)
        sum = sum + arr[i];

    return sum;
}

int main()
{

    int size;

    cin >> size;

    int arr[size];

    for (int i = 0; i < size; i++)
    {
        cin >> arr[i];
    }

    int sum = getSum(arr, size);

    cout << "Sum of elements of given array is " << sum << endl;

    return 0;
}