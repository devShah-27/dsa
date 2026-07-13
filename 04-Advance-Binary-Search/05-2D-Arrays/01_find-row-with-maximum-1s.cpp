// Problem:
// Given a non-empty binary matrix where every row is sorted in ascending order,
// return the index of the row containing the maximum number of 1s.
// If multiple rows have the same number of 1s, return the smallest index.
// If the matrix contains no 1s, return -1.

#include <bits/stdc++.h>
using namespace std;

// ============================================================================
// BRUTE FORCE APPROACH
//
// Idea:
// Traverse every element of each row and count the number of 1s.
// Keep track of the row having the maximum count of 1s.
// Since the answer should have the smallest index in case of a tie, update
// the answer only when a strictly larger count is found.
//
// Time Complexity: O(n * m)
// Space Complexity: O(1)
// ============================================================================
// int rowWithMax1s(vector<vector<int>> &mat)
// {
//     int n = mat.size(), m = mat[0].size();

//     int maximumOneCount = 0, minimizedMaxIndex = -1;

//     for (int i = 0; i < n; i++)
//     {
//         int currentOneCount = INT_MIN;

//         for (int j = 0; j < m; j++)
//         {
//             if (mat[i][j] == 1)
//                 currentOneCount++;
//         }

//         if (currentOneCount > maximumOneCount)
//         {
//             maximumOneCount = currentOneCount;
//             minimizedMaxIndex = i;
//         }
//     }

//     return minimizedMaxIndex;
// }

// ============================================================================
// OPTIMAL APPROACH
//
// Idea:
// Since every row is sorted, use Binary Search to locate the first occurrence
// of 1 in each row. The number of 1s equals:
//      total columns - first occurrence index.
// Track the row with the maximum count while preserving the smallest index.
//
// Time Complexity: O(n * log(m))
// Space Complexity: O(1)
// ============================================================================

// Returns the index of the first occurrence of 1 in a sorted binary row.
// Returns -1 if no 1 is present.
int firstOccuranceOf1(vector<int> &row, int m) // TC -> O(log(m))
{
    int low = 0, high = m - 1;

    int firstOccuranceIndex = -1;

    while (low <= high)
    {
        int mid = low + ((high - low) / 2);

        if (row[mid] == 1)
        {
            firstOccuranceIndex = mid;
            high = mid - 1;
        }
        else
        {
            low = mid + 1;
        }
    }

    return firstOccuranceIndex;
}

// Returns the total number of 1s present in a sorted binary row.
int countOf1s(vector<int> &row, int m)
{
    int firstOccuranceIndex = firstOccuranceOf1(row, m);

    if (firstOccuranceIndex < 0)
        return 0;

    return m - firstOccuranceIndex;
}

int rowWithMax1s(vector<vector<int>> &mat)
{
    int n = mat.size(), m = mat[0].size();

    int maximumOneCount = 0, minimizedMaxIndex = -1;

    for (int i = 0; i < n; i++)
    {
        int currentOneCount = countOf1s(mat[i], m);

        if (currentOneCount > maximumOneCount)
        {
            maximumOneCount = currentOneCount;
            minimizedMaxIndex = i;
        }
    }

    return minimizedMaxIndex;
}

int main()
{
    vector<vector<int>> matrix = {
        {0, 0, 1, 1}, // Row 0 -> 2 ones
        {0, 1, 1, 1}, // Row 1 -> 3 ones
        {0, 0, 1, 1}, // Row 2 -> 2 ones
        {0, 0, 0, 0}  // Row 3 -> 0 ones
    };

    cout << "The row with maximum number of 1's is: " << rowWithMax1s(matrix) << '\n';

    return 0;
}