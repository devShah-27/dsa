// Given an M * N matrix, print the elements in a clockwise spiral manner.

// Return an array with the elements in the order of their appearance when printed in a spiral manner.

#include <bits/stdc++.h>
using namespace std;

vector<int> spiralOrder(vector<vector<int>> &matrix)
{
    int m = matrix.size();
    int n = matrix[0].size();

    int top = 0, bottom = m - 1;
    int left = 0, right = n - 1;

    vector<int> ans;

    while (left <= right && top <= bottom)
    {
        // Left --> Right
        for (int i = left; i <= right; i++)
            ans.emplace_back(matrix[top][i]);
        top++;

        // Top --> Bottom
        for (int i = top; i <= bottom; i++)
            ans.emplace_back(matrix[i][right]);
        right--;

        // Right --> Left
        if (top <= bottom)
        {
            for (int i = right; i >= left; i--)
                ans.emplace_back(matrix[bottom][i]);
            bottom--;
        }

        // Bottom --> Top
        if (left <= right)
        {
            for (int i = bottom; i >= top; i--)
                ans.emplace_back(matrix[i][left]);
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
    for (int it : spiral)
        cout << it << " ";

    return 0;
}