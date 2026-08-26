// Problem:
// Given a 2D matrix where each row is sorted in ascending order (left to right) and each column is sorted in ascending order (top to bottom), determine whether a given target value exists in the matrix.

#include <bits/stdc++.h>
using namespace std;

// ============================================================================
// BRUTE FORCE APPROACH
//
// Idea:
// Traverse every element of the matrix using nested loops.
// Return true as soon as the target is found; otherwise return false after
// scanning the entire matrix.
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
// Since every row is individually sorted, check whether the target lies within
// the range of a row using its first and last elements.
// If it does, perform Binary Search on that row.
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
// Start from the top-right corner of the matrix.
// If the current element is smaller than the target, move down to increase
// the value. Otherwise, move left to decrease the value.
// Each move eliminates either one entire row or one entire column.
//
// Time Complexity: O(n + m)
// Space Complexity: O(1)
// ============================================================================
bool searchMatrix(vector<vector<int>> &mat, int target)
{
    int n = mat.size(), m = mat[0].size();

    int row = 0, col = m - 1;

    while (row < n && col >= 0)
    {
        if (mat[row][col] == target)
            return true;
        else if (mat[row][col] < target)
            row++;
        else
            col--;
    }

    return false;
}

int main()
{
    vector<vector<int>> matrix = {
        {1, 4, 7, 11, 15},
        {2, 5, 8, 12, 19},
        {3, 6, 9, 16, 22},
        {10, 13, 14, 17, 24},
        {18, 21, 23, 26, 30}};

    int target = 8;

    bool result = searchMatrix(matrix, target);

    result ? cout << "true\n" : cout << "false\n";

    return 0;
}