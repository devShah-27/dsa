// Problem:
// Given a 2D matrix where each row is sorted in non-decreasing order and the first element of every row is greater than the last element of the previous row, determine whether a given target value exists in the matrix.

#include <bits/stdc++.h>
using namespace std;

// ============================================================================
// BRUTE FORCE APPROACH
//
// Idea:
// Traverse every element of the matrix using nested loops.
// Return true immediately if the target is found; otherwise return false after scanning the entire matrix.
//
// Time Complexity: O(n * m)
// Space Complexity: O(1)
// ============================================================================

// bool searchMatrix(vector<vector<int>> &mat, int target)
// {
//     int n = mat.size(), m = mat[0].size();

//     for (int i = 0; i < n; i++)
//     {
//         for (int j = 0; j < m; j++)
//         {
//             if (mat[i][j] == target)
//                 return true;
//         }
//     }

//     return false;
// }

// ============================================================================
// BETTER APPROACH
//
// Idea:
// Since each row is individually sorted, first identify the only row that can possibly contain the target by checking its boundary values.
// Perform Binary Search on that row if the target lies within its range.
//
// Time Complexity: O(n * log(m))
// Space Complexity: O(1)
// ============================================================================

// Performs Binary Search on a single sorted row.
// bool binarySearch(vector<int> &row, int m, int target) // TC -> O(log(m)), SC -> O(1)
// {
//     int low = 0, high = m - 1;

//     while (low <= high)
//     {
//         int mid = low + ((high - low) / 2);

//         if (row[mid] == target)
//             return true;
//         else if (row[mid] < target)
//             low = mid + 1;
//         else
//             high = mid - 1;
//     }

//     return false;
// }

// bool searchMatrix(vector<vector<int>> &mat, int target)
// {
//     int n = mat.size(), m = mat[0].size();

//     for (int i = 0; i < n; i++)
//     {
//         if (mat[i][0] <= target && target <= mat[i][m - 1])
//             return binarySearch(mat[i], m, target);
//     }

//     return false;
// }

// ============================================================================
// OPTIMAL APPROACH
//
// Idea:
// The entire matrix is globally sorted because the first element of each row is greater than the last element of the previous row.
// Treat the matrix as a hypothetical 1D sorted array of size (n * m) and apply Binary Search. 
// Convert a 1D index back to 2D coordinates using:
//      row = index / m
//      col = index % m
//
// Time Complexity: O(log(n * m))
// Space Complexity: O(1)
// ============================================================================
bool searchMatrix(vector<vector<int>> &mat, int target)
{
    int n = mat.size(), m = mat[0].size();

    int low = 0, high = (n * m) - 1;

    while (low <= high)
    {
        int mid = low + ((high - low) / 2);

        int row = mid / m, col = mid % m;

        if (mat[row][col] == target)
            return true;
        else if (mat[row][col] < target)
            low = mid + 1;
        else
            high = mid - 1;
    }

    return false;
}

int main()
{
    vector<vector<int>> matrix = {
        {1, 2, 3, 4},
        {5, 6, 7, 8},
        {9, 10, 11, 12}};

    int target = 8;

    bool result = searchMatrix(matrix, target);

    result ? cout << "true\n" : cout << "false\n";

    return 0;
}