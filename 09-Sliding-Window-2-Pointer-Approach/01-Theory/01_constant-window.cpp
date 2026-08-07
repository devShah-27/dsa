// Problem:
// Given an array and a fixed window size k, calculate the sum of elements for every contiguous window of size k as the window moves across the array.

#include <bits/stdc++.h>
using namespace std;

// ==================================================
// BRUTE FORCE APPROACH
//
// Idea:
// For every possible window of size k, iterate through all elements inside that window and calculate its sum independently.
// This repeats calculations for overlapping windows.
//
// Time Complexity: O(N*K)
// Space Complexity: O(1)
// ==================================================

// void sumOfElements(vector<int> &arr, int k)
// {
//     int n = arr.size();

//     for (int i = 0; i < n; i++)
//     {
//         int sum = 0;

//         for (int j = i; j < i + k; j++)
//         {
//             sum += arr[j];
//         }

//         cout << "Sum of window " << i + 1 << ": " << sum << endl;
//     }
// }

// ==================================================
// OPTIMAL APPROACH
//
// Idea:
// Use the sliding window technique to avoid recalculating the entire window sum.
// Calculate the first window sum, then remove the outgoing element and add the incoming element while shifting the window one position at a time.
//
// Time Complexity: O(N)
// Space Complexity: O(1)
// ==================================================

void sumOfElements(vector<int> &arr, int k)
{
    int n = arr.size();

    if (n < k)
    {
        cout << "Size of array < " << k << endl;
        return;
    }

    int l = 0, r = k - 1;

    int sum = 0;

    // Calculate sum of the first window.
    for (int i = 0; i < k; i++)
    {
        sum += arr[i];
    }

    int windowCount = 1;

    cout << "Sum of window " << windowCount << ": " << sum << endl;

    while (r < n)
    {
        sum -= arr[l];
        l++;

        r++;
        sum += arr[r];

        windowCount++;

        cout << "Sum of window " << windowCount << ": " << sum << endl;
    }
}

int main()
{
    vector<int> arr = {1, 3, 2, 6, 4, 8, 5};
    int k = 3;

    sumOfElements(arr, k);

    return 0;
}