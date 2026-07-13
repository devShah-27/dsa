// Problem:
// Given a 0-indexed n x m matrix where no two adjacent cells are equal, find any peak element mat[i][j] and return its coordinates [i, j].
// A peak element is strictly greater than its adjacent elements (left, right, top, bottom).

#include <bits/stdc++.h>
using namespace std;

// ============================================================================
// BRUTE FORCE APPROACH
//
// Idea:
// Traverse every element of the matrix and identify the maximum element.
// Since no two adjacent elements are equal, the global maximum element will always be a peak element.
//
// Time Complexity: O(n * m)
// Space Complexity: O(1)
// ============================================================================

// vector<int> findPeakGrid(vector<vector<int>> &mat)
// {
//     int n = mat.size(), m = mat[0].size();

//     int maxElem = INT_MIN;
//     vector<int> maxElemCoords = {-1, -1};

//     for (int i = 0; i < n; i++)
//     {
//         for (int j = 0; j < m; j++)
//         {
//             if (mat[i][j] > maxElem)
//             {
//                 maxElem = mat[i][j];
//                 maxElemCoords = {i, j};
//             }
//         }
//     }

//     return maxElemCoords;
// }

// ============================================================================
// OPTIMAL APPROACH
//
// Idea:
// Apply Binary Search on columns instead of searching every cell.
// For the current middle column, find the row containing the maximum element.
// Compare this element with its left and right neighbours:
// - If it is greater than both, it is a peak.
// - If the left neighbour is greater, move towards the left half.
// - Otherwise, move towards the right half.
//
// Time Complexity: O(n * log(m))
// Space Complexity: O(1)
// ============================================================================

// Finds the row index containing the maximum element in the given column.
int findMaxElemRow(vector<vector<int>> &mat, int col)
{
    int n = mat.size();

    int maxElem = INT_MIN, maxElemRow = -1;

    for (int i = 0; i < n; i++)
    {
        if (mat[i][col] > maxElem)
        {
            maxElem = mat[i][col];
            maxElemRow = i;
        }
    }

    return maxElemRow;
}

vector<int> findPeakGrid(vector<vector<int>> &mat)
{
    int n = mat.size(), m = mat[0].size();

    int low = 0, high = m - 1;

    while (low <= high)
    {
        int mid = low + ((high - low) / 2);

        int maxElemRow = findMaxElemRow(mat, mid);

        int left = mid > 0 ? mat[maxElemRow][mid - 1] : -1;
        int right = mid < m - 1 ? mat[maxElemRow][mid + 1] : -1;

        if (left < mat[maxElemRow][mid] && right < mat[maxElemRow][mid])
        {
            return {maxElemRow, mid};
        }
        else if (left > mat[maxElemRow][mid])
        {
            high = mid - 1;
        }
        else
        {
            low = mid + 1;
        }
    }

    return {-1, -1};
}

int main()
{
    vector<vector<int>> mat = {
        {1, 2, 5, 1, 4, 5},
        {2, 9, 3, 2, 3, 2},
        {1, 7, 6, 0, 1, 3},
        {3, 6, 2, 3, 7, 2}};

    vector<int> peak = findPeakGrid(mat);

    cout << "The row of peak element is " << peak[0]
         << " and column of the peak element is " << peak[1] << endl;

    return 0;
}