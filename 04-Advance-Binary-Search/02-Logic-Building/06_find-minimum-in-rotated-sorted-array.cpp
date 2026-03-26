// ========================== PROBLEM ==========================
// Given a rotated sorted array with distinct elements, find the minimum element. The array was originally sorted in ascending order and then rotated unknown times.
// ============================================================

#include <bits/stdc++.h>
using namespace std;

// ========================== BRUTE FORCE APPROACH ==========================
// Idea:
// Traverse the entire array and track the minimum element.
// Since all elements are checked, this guarantees correctness.
//
// Time Complexity: O(N)
// Space Complexity: O(1)
// =========================================================================
// int findMin(vector<int> &arr)
// {
//     int mini = arr[0];
//
//     for (int it : arr)
//         mini = min(mini, it);
//
//     return mini;
// }

// ========================== OPTIMAL APPROACH (BINARY SEARCH) ==========================
// Idea:
// Use binary search by exploiting the rotated sorted structure.
// At any point, one half of the array will always be sorted.
// Compare mid with boundaries to decide which side contains the minimum.
// Keep updating the minimum while narrowing the search space.
//
// Time Complexity: O(log N)
// Space Complexity: O(1)
// ================================================================================
// int findMin(vector<int> &arr)
// {
//     int n = arr.size();
//
//     int mini = arr[0];
//
//     int low = 0, high = n - 1;
//
//     while (low <= high)
//     {
//         int mid = low + ((high - low) / 2);
//
//         // If left half is sorted
//         if (arr[low] <= arr[mid])
//         {
//             mini = min(mini, arr[low]);
//             low = mid + 1;
//         }
//         // Otherwise, right half is sorted
//         else
//         {
//             mini = min(mini, arr[mid]);
//             high = mid - 1;
//         }
//     }
//
//     return mini;
// }

// ========================== OPTIMAL APPROACH (EARLY EXIT OPTIMIZATION) ==========================
// Idea:
// Same binary search approach, but with an additional check:
// If the current search space is already sorted (arr[low] <= arr[high]), then arr[low] is the minimum, and we can stop early.
// This avoids unnecessary iterations in best-case scenarios.
//
// Time Complexity: O(log N)
// Space Complexity: O(1)
// ================================================================================================
int findMin(vector<int> &arr)
{
    int n = arr.size();

    int mini = arr[0];

    int low = 0, high = n - 1;

    while (low <= high)
    {
        int mid = low + ((high - low) / 2);

        // If the current segment is already sorted, the smallest element is at 'low'
        if (arr[low] <= arr[high])
        {
            mini = min(mini, arr[low]);
            break;
        }

        // Left half is sorted → minimum cannot be inside this sorted part
        if (arr[low] <= arr[mid])
        {
            mini = min(mini, arr[low]);
            low = mid + 1;
        }
        // Right half is sorted → minimum lies in left half including mid
        else
        {
            mini = min(mini, arr[mid]);
            high = mid - 1;
        }
    }

    return mini;
}

int main()
{
    vector<int> nums = {4, 5, 6, 7, -7, 1, 2, 3};

    cout << "Array: ";
    for (int it : nums)
        cout << it << " ";
    cout << endl;

    int mini = findMin(nums);

    cout << "\nMinimum element: " << mini;

    return 0;
}