// Given a non-empty grid mat consisting of only 0s and 1s, where all the rows are sorted in ascending order, find the index of the row with the maximum number of ones.
// If two rows have the same number of ones, consider the one with a smaller index. If no 1 exists in the matrix, return -1.

#include <bits/stdc++.h>
using namespace std;

// Linear Search
int rowWithMax1s(vector<vector<int>> &mat) // TC -> O(m * n), SC -> O(1)
{
    int n = mat.size(), m = mat[1].size();

    int maximumOneCount = INT_MIN, minimizedMaxIndex = -1;

    for (int i = 0; i < n; i++)
    {
        int currentOneCount = INT_MIN;

        for (int j = 0; j < m; j++)
        {
            if (mat[i][j] == 1)
                currentOneCount++;
        }

        if (currentOneCount > maximumOneCount)
        {
            maximumOneCount = currentOneCount;
            minimizedMaxIndex = i;
        }
    }

    return minimizedMaxIndex;
}

// Binary Search (lower_bound(1) / upper_bound(0) / first_occurance(1))
int firstOccuranceOf1(vector<int> row, int m) // TC -> O(log(m))
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

int countOf1s(vector<int> row, int m)
{
    int firstOccuranceIndex = firstOccuranceOf1(row, m);

    if (firstOccuranceIndex < 0)
        return 0;

    return m - firstOccuranceIndex;
}

int rowWithMax1s(vector<vector<int>> &mat) // TC -> O(log(m) * n), SC -> O(1)
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
    // vector<vector<int>> matrix = {
    //     {0, 0, 1, 1}, // Row 0 → 1 one
    //     {0, 1, 1, 1}, // Row 1 → 3 ones
    //     {0, 0, 1, 1}, // Row 2 → 2 ones
    //     {0, 0, 0, 0}  // Row 3 → 0 ones
    // };

    vector<vector<int>> matrix = {
        {0, 0}, {0, 0}};

    cout << "The row with maximum number of 1's is: " << rowWithMax1s(matrix) << '\n';

    return 0;
}
