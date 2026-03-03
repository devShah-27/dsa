// Given an array of n elements. The task is to return the count of the number of odd numbers in the array.

#include <bits/stdc++.h>
using namespace std;

int getOddCount(int arr[], int n)
{
    int count = 0;

    for (int i = 0; i < n; i++)
        if (arr[i] % 2 == 1)
            count++;

    return count;
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

    int oddCount = getOddCount(arr, size);

    cout << "Number of odd elements of given array is " << oddCount << endl;

    return 0;
}