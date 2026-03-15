// Problem:
// Given an integer array nums, move all zeros to the end of the array while maintaining the relative order of all non-zero elements.
//
// The operation must be performed in-place without creating a copy of the array.

#include <bits/stdc++.h>
using namespace std;

// ===================================================
// BRUTE FORCE APPROACH
//
// Idea:
// Traverse the array and store all non-zero elements
// in a temporary array. After collecting them:
//
// 1. Copy the non-zero elements back into the
//    beginning of the original array.
// 2. Fill the remaining positions with zeros.
//
// This approach preserves order but uses extra space.
//
// Time Complexity: O(N)
// Space Complexity: O(N)
// ===================================================

// void moveZeroes(vector<int> &nums)
// {
//     int N = nums.size();

//     vector<int> temp;

//     for (int i = 0; i < N; i++)
//         if (nums[i] != 0)
//             temp.emplace_back(nums[i]);

//     int X = temp.size();

//     if (X == 0)
//         return;

//     for (int i = 0; i < X; i++)
//         nums[i] = temp[i];

//     for (int i = X; i < N; i++)
//         nums[i] = 0;
// }

// ===================================================
// OPTIMAL APPROACH (TWO POINTERS)
//
// Idea:
// Maintain a pointer `j` which represents the position
// where the next non-zero element should be placed.
//
// Traverse the array with pointer `i`:
//
// • If nums[i] is non-zero, swap nums[i] with nums[j].
// • Increment j so that it always points to the next
//   available position for a non-zero element.
//
// This ensures all non-zero elements move forward
// while zeros naturally shift to the end.
//
// Time Complexity: O(N)
// Space Complexity: O(1)
// ===================================================

void moveZeroes(vector<int> &nums)
{
    int j = 0;

    for (int i = 0; i < nums.size(); i++)
    {
        if (nums[i] != 0)
        {
            swap(nums[i], nums[j]);
            j++;
        }
    }
}

int main()
{
    int size;
    cin >> size;

    vector<int> nums(size);

    for (int i = 0; i < size; i++)
        cin >> nums[i];

    cout << "Before moving zeros: ";
    for (int it : nums)
        cout << it << " ";
    cout << endl;

    moveZeroes(nums);

    cout << "After moving zeros: ";
    for (int it : nums)
        cout << it << " ";
    cout << endl;

    return 0;
}