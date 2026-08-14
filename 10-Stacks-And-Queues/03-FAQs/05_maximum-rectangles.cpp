// Problem:
// Given a binary matrix containing only 0s and 1s, find the largest rectangle consisting only of 1s and return its area.

#include <bits/stdc++.h>
using namespace std;

// =============================================================
// OPTIMAL APPROACH
//
// Idea:
// Convert each row of the matrix into a histogram by maintaining the height of consecutive 1s in every column. For each row, calculate the largest rectangle area in the histogram using a monotonic stack.
//
// Time Complexity:
// O(N * M), where N is the number of rows and M is the number of columns.
//
// Space Complexity:
// O(M), for storing histogram heights and stack space.
//
// =============================================================

// Finds the largest rectangle area in a histogram using a monotonic stack.
int getMaxHistogramRectangleArea(vector<int> &heights, int m)
{
    stack<int> st;

    int maxArea = 0;

    for (int i = 0; i < m; i++)
    {
        while (!st.empty() && heights[st.top()] > heights[i])
        {
            int elem = st.top();
            st.pop();

            int nse = i;
            int pse = st.empty() ? -1 : st.top();

            maxArea = max(maxArea, (nse - pse - 1) * heights[elem]);
        }

        st.push(i);
    }

    while (!st.empty())
    {
        int elem = st.top();
        st.pop();

        int nse = m;
        int pse = st.empty() ? -1 : st.top();

        maxArea = max(maxArea, (nse - pse - 1) * heights[elem]);
    }

    return maxArea;
}

int maximalAreaOfSubMatrixOfAll1(vector<vector<int>> &matrix)
{
    int n = matrix.size(), m = matrix[0].size();

    vector<int> currentHistogram(m, 0);

    int maxArea = 0;

    for (int row = 0; row < n; row++)
    {
        // Build histogram heights for the current row.
        for (int col = 0; col < m; col++)
        {
            if (matrix[row][col] == 0)
                currentHistogram[col] = 0;
            else
                currentHistogram[col]++;
        }

        // Calculate the maximum rectangle area for the current histogram.
        maxArea = max(maxArea, getMaxHistogramRectangleArea(currentHistogram, m));
    }

    return maxArea;
}

int main()
{
    vector<vector<int>> matrix = {{1, 0, 1, 0, 0},
                                  {1, 0, 1, 1, 1},
                                  {1, 1, 1, 1, 1},
                                  {1, 0, 0, 1, 0}};

    int maxArea = maximalAreaOfSubMatrixOfAll1(matrix);

    cout << "Maximum possible area for given matrix is: " << maxArea << endl;

    return 0;
}