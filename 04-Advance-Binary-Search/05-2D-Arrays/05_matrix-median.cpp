// Problem:
// Given a row-wise sorted matrix, find the median element of the matrix.
// The matrix contains an odd number of elements, and the median is the middle
// element when all matrix elements are arranged in sorted order.

#include <bits/stdc++.h>
using namespace std;

// ============================================================================
// BRUTE FORCE APPROACH
//
// Idea:
// Store all elements of the matrix into a single 1D array.
// Sort the array and return the middle element as the median.
//
// Time Complexity: O(n * m * log(n * m))
// Space Complexity: O(n * m)
// ============================================================================

// int findMedian(vector<vector<int>> &matrix)
// {
//     int n = matrix.size(), m = matrix[0].size();

//     vector<int> ls;

//     for (int i = 0; i < n; i++)
//     {
//         for (int j = 0; j < m; j++)
//         {
//             ls.push_back(matrix[i][j]);
//         }
//     }

//     sort(ls.begin(), ls.end());

//     return ls[(n * m) / 2];
// }

// ============================================================================
// OPTIMAL APPROACH
//
// Idea:
// Apply Binary Search on the possible value range instead of matrix indices.
// For every middle value, count how many elements are less than or equal to it
// using Binary Search on each sorted row.
// Adjust the search range until the smallest value having more than half the
// elements smaller than or equal to it is found.
//
// Time Complexity: O(log(maxElement - minElement) * n * log(m))
// Space Complexity: O(1)
// ============================================================================

// Returns the index of the first element greater than x in a sorted row.
int upperBound(vector<int> row, int m, int x) // TC -> O(log(m)), SC -> O(1)
{
    int low = 0, high = m - 1;

    while (low <= high)
    {
        int mid = low + ((high - low) / 2);

        if (row[mid] <= x)
            low = mid + 1;
        else
            high = mid - 1;
    }

    return low;
}

// Counts the number of elements smaller than or equal to target in the matrix.
int getSmallEqualCount(vector<vector<int>> &matrix, int n, int m, int target) // TC -> O(n * log(m)), SC -> O(1)
{
    int count = 0;

    for (int i = 0; i < n; i++)
    {
        count += upperBound(matrix[i], m, target);
    }

    return count;
}

int findMedian(vector<vector<int>> &matrix)
{
    int n = matrix.size(), m = matrix[0].size();

    // Find the minimum and maximum possible values for Binary Search.
    int low = INT_MAX, high = INT_MIN;

    for (int i = 0; i < n; i++)
    {
        low = min(low, matrix[i][0]);
        high = max(high, matrix[i][m - 1]);
    }

    // Number of elements that should be smaller than or equal to the median.
    int required = (n * m) / 2;

    while (low <= high)
    {
        int mid = low + ((high - low) / 2);

        int smallEqualCount = getSmallEqualCount(matrix, n, m, mid);

        // If too few elements are <= mid, median lies on the right side.
        if (smallEqualCount <= required)
            low = mid + 1;
        else
            high = mid - 1;
    }

    return low;
}

int main()
{
    vector<vector<int>> matrix = {
        {1, 3, 5},
        {2, 6, 9},
        {3, 6, 9}};

    cout << findMedian(matrix) << endl; // Output: 5

    return 0;
}