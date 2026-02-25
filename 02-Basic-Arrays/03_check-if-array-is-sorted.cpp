// Given an array arr of size n, the task is to check if the given array is sorted in (ascending / Increasing / Non-decreasing) order. If the array is sorted then return True, else return False.

#include <bits/stdc++.h>
using namespace std;

// ============== BRUTE FORCE O(N^2) Complexity =================
// bool isSorted(int arr[], int n)
// {
//     for (int i = 0; i < n; i++)
//         for (int j = i + 1; j < n; j++)
//             if (arr[j] < arr[i])
//                 return false;

//     return true;
// }

// ============== OPTIMAL O(N) Complexity =================
bool isSorted(int arr[], int n)
{
    for (int i = 1; i < n; i++)
        if (arr[i] < arr[i - 1])
            return false;

    return true;
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

    bool sorted = isSorted(arr, size);

    if (sorted)
        cout << "Given array is sorted!" << endl;
    else
        cout << "Given array not is sorted!" << endl;

    return 0;
}