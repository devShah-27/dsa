// Given an array arr of n elements. The task is to reverse the given array. The reversal of array should be inplace.

#include <bits/stdc++.h>
using namespace std;

// ================= Brute Force ================
// Uses a temporary array to store reversed values.
// Space complexity -> O(N)
// void reverseArray(int arr[], int n)
// {
//     int temp[n];

//     for (int i = 0; i < n; i++)
//         temp[n - i - 1] = arr[i];

//     for (int i = 0; i < n; i++)
//         arr[i] = temp[i];
// }

// ================= Better (In-place sorting) ================
// Uses two-pointer approach

void swapElements(int arr[], int left, int right)
{
    int temp = arr[right];
    arr[right] = arr[left];
    arr[left] = temp;
}

void reverseArray(int arr[], int n)
{
    int left = 0, right = n - 1;

    while (left < right)
    {
        swapElements(arr, left, right);

        left++;
        right--;
    }
}

int main()
{

    int size;
    cin >> size;

    int arr[size];
    for (int i = 0; i < size; i++)
        cin >> arr[i];

    cout << "Array before reversing: ";

    for (int i = 0; i < size; i++)
    {
        cout << arr[i];
        if (i != size - 1)
            cout << ", ";
    }

    cout << endl;

    reverseArray(arr, size);

    cout << "Array after reversing: ";

    for (int i = 0; i < size; i++)
    {
        cout << arr[i];
        if (i != size - 1)
            cout << ", ";
    }

    cout << endl;

    return 0;
}