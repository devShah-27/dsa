// Problem:
// Given an M × N matrix, return the elements in clockwise spiral order.
//
// Idea:
// Maintain four boundaries representing the current unvisited layer:
// • top    → first unvisited row
// • bottom → last unvisited row
// • left   → first unvisited column
// • right  → last unvisited column
//
// Traverse the outer layer in four steps:
// 1. Left → Right across the top row
// 2. Top → Bottom down the right column
// 3. Right → Left across the bottom row
// 4. Bottom → Top up the left column
//
// After completing each side, shrink the corresponding boundary.
// Continue until all layers are processed.
//
// Time Complexity:  O(M × N)
// Space Complexity: O(1) extra (excluding output)

#include <bits/stdc++.h>
using namespace std;

vector<int> spiralOrder(vector<vector<int>> &matrix)
{
    int m = matrix.size();
    int n = matrix[0].size();

    int top = 0;
    int bottom = m - 1;
    int left = 0;
    int right = n - 1;

    vector<int> ans;

    while (left <= right && top <= bottom)
    {
        // Traverse the top row
        for (int i = left; i <= right; i++)
            ans.push_back(matrix[top][i]);
        top++;

        // Traverse the right column
        for (int i = top; i <= bottom; i++)
            ans.push_back(matrix[i][right]);
        right--;

        // Traverse the bottom row (if remaining)
        if (top <= bottom)
        {
            for (int i = right; i >= left; i--)
                ans.push_back(matrix[bottom][i]);
            bottom--;
        }

        // Traverse the left column (if remaining)
        if (left <= right)
        {
            for (int i = bottom; i >= top; i--)
                ans.push_back(matrix[i][left]);
            left++;
        }
    }

    return ans;
}

int main()
{
    vector<vector<int>> nums = {{1, 2, 3},
                                {4, 5, 6},
                                {7, 8, 9}};

    vector<int> spiral = spiralOrder(nums);

    cout << "Spiral order of given matrix: ";
    for (int val : spiral)
        cout << val << " ";

    return 0;
}