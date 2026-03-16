// Problem:
// Given a sorted integer array nums (non-decreasing order),
// remove duplicates in-place such that each unique element
// appears only once.
//
// Return k = number of unique elements. The first k positions
// of nums must contain the unique values in their original order.

#include <bits/stdc++.h>
using namespace std;

// ===================================================
// BRUTE FORCE APPROACH
//
// Idea:
// Insert all elements into a set. Since a set stores only
// unique values in sorted order, duplicates are automatically
// removed.
//
// After building the set:
// 1. Copy its elements back into the original array.
// 2. Fill the remaining positions with any values (here 0).
//
// NOTE: This approach does not strictly preserve the in-place
// constraint since it uses an additional data structure.
//
// Time Complexity: O(N log N)
// Space Complexity: O(N)
// ===================================================

// int removeDuplicates(vector<int> &nums)
// {
//     int N = nums.size();

//     set<int> st;

//     for (int i = 0; i < N; i++)
//         st.insert(nums[i]);

//     int index = 0;

//     for (auto it : st)
//     {
//         nums[index] = it;
//         index++;
//     }

//     for (int i = index; i < N; i++)
//         nums[i] = 0;

//     return index;
// }

// ===================================================
// OPTIMAL APPROACH (TWO POINTERS)
//
// Idea:
// Since the array is already sorted, duplicates appear
// next to each other.
//
// Maintain:
// • uniqueIndex → position of last unique element
//
// Traverse the array with index i. Whenever a new element
// different from nums[uniqueIndex] is found:
//
// 1. Move it to position (uniqueIndex + 1)
// 2. Increment uniqueIndex
//
// At the end, the first (uniqueIndex + 1) elements represent
// all unique values.
//
// Time Complexity: O(N)
// Space Complexity: O(1)
// ===================================================

int removeDuplicates(vector<int> &nums)
{
    int N = nums.size();

    int uniqueIndex = 0;

    for (int i = 0; i < N; i++)
    {
        if (nums[i] != nums[uniqueIndex])
        {
            nums[uniqueIndex + 1] = nums[i];
            uniqueIndex++;
        }
    }

    // Remaining elements beyond the unique region are irrelevant
    // for correctness, but here they are explicitly set to 0.
    for (int i = uniqueIndex + 1; i < N; i++)
        nums[i] = 0;

    return (uniqueIndex + 1);
}

int main()
{
    int size;
    cin >> size;

    vector<int> nums(size);

    for (int i = 0; i < size; i++)
        cin >> nums[i];

    cout << "Input Array: ";
    for (int it : nums)
        cout << it << " ";
    cout << endl;

    int uniqueCount = removeDuplicates(nums);

    cout << "Number of unique elements: " << uniqueCount << endl;

    cout << "Array After Removing Duplicates: ";
    for (int it : nums)
        cout << it << " ";
    cout << endl;

    return 0;
}