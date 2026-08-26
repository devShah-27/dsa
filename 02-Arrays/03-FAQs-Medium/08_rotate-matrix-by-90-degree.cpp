// Problem:
// Given an N × N matrix, rotate the matrix by 90 degrees clockwise.
//
// Constraint:
// • The rotation must be done in-place (no extra matrix allowed).

#include <bits/stdc++.h>
using namespace std;

// ================================================================
// BRUTE FORCE APPROACH
//
// Idea:
// • Create a new matrix
// • Map each element (i, j) → (j, n - 1 - i)
// • Copy the result back into the original matrix
//
// Time Complexity:  O(N²)
// Space Complexity: O(N²)
// ================================================================

// void rotateMatrix(vector<vector<int>> &matrix)
// {
//     int n = matrix.size();
//     vector<vector<int>> ans(n, vector<int>(n));
//
//     for (int i = 0; i < n; i++)
//         for (int j = 0; j < n; j++)
//             ans[j][n - 1 - i] = matrix[i][j];
//
//     for (int i = 0; i < n; i++)
//         matrix[i] = ans[i];
// }

// ================================================================
// OPTIMAL APPROACH (IN-PLACE ROTATION)
//
// Key observation:
// A 90° clockwise rotation can be decomposed into two operations:
//
// 1. Transpose the matrix
//    Convert rows into columns: matrix[i][j] ↔ matrix[j][i]
//
// 2. Reverse each row
//    This shifts elements to their correct rotated position
//
// Example:
//
// Original        After Transpose       After Row Reverse
// 1 2 3           1 4 7                 7 4 1
// 4 5 6   →       2 5 8        →        8 5 2
// 7 8 9           3 6 9                 9 6 3
//
// Time Complexity:  O(N²)
// Space Complexity: O(1)
// ================================================================

void rotateMatrix(vector<vector<int>> &matrix)
{
    int n = matrix.size();

    // Step 1: Transpose matrix (swap across diagonal)
    for (int i = 0; i < n; i++)
        for (int j = i + 1; j < n; j++)
            swap(matrix[i][j], matrix[j][i]);

    // Step 2: Reverse each row
    for (auto &row : matrix)
        reverse(row.begin(), row.end());
}

int main()
{
    vector<vector<int>> input = {
        {1, 2, 3, 4, 5, 6, 7, 8, 9, 10},
        {11, 12, 13, 14, 15, 16, 17, 18, 19, 20},
        {21, 22, 23, 24, 25, 26, 27, 28, 29, 30},
        {31, 32, 33, 34, 35, 36, 37, 38, 39, 40},
        {41, 42, 43, 44, 45, 46, 47, 48, 49, 50},
        {51, 52, 53, 54, 55, 56, 57, 58, 59, 60},
        {61, 62, 63, 64, 65, 66, 67, 68, 69, 70},
        {71, 72, 73, 74, 75, 76, 77, 78, 79, 80},
        {81, 82, 83, 84, 85, 86, 87, 88, 89, 90},
        {91, 92, 93, 94, 95, 96, 97, 98, 99, 100}};

    cout << "Before rotation:\n";
    for (auto &row : input)
    {
        for (auto val : row)
            cout << val << " ";
        cout << endl;
    }

    rotateMatrix(input);

    cout << "\nAfter rotation:\n";
    for (auto &row : input)
    {
        for (auto val : row)
            cout << val << " ";
        cout << endl;
    }

    return 0;
}