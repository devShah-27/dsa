// Problem:
// Given an integer n, return the first n rows of Pascal's Triangle.
//
// Properties of Pascal's Triangle:
// • The first and last element of every row is 1
// • Each element is the sum of the two elements above it
// • Row r contains the binomial coefficients: C(r-1, 0) ... C(r-1, r-1)

#include <bits/stdc++.h>
using namespace std;

// ================================================================
// BRUTE FORCE APPROACH
//
// Idea:
// Each element of Pascal's Triangle is a binomial coefficient:
//
// element(row, col) = C(row-1, col-1)
//
// So we compute each value using the nCr formula.
//
// Time Complexity:  O(N³)
// Space Complexity: O(N²)
// ================================================================

// int NcR(int n, int r)
// {
//     int ans = 1;
//
//     // Compute nCr using iterative formula
//     for (int col = 0; col < r; col++)
//     {
//         ans = ans * (n - col);
//         ans = ans / (col + 1);
//     }
//
//     return ans;
// }
//
// vector<vector<int>> pascalTriangleIII(int n)
// {
//     vector<vector<int>> ans;
//
//     for (int row = 1; row <= n; row++)
//     {
//         vector<int> temp;
//
//         for (int col = 1; col <= row; col++)
//         {
//             temp.push_back(NcR(row - 1, col - 1));
//         }
//
//         ans.push_back(temp);
//     }
//
//     return ans;
// }

// ================================================================
// OPTIMAL APPROACH
//
// Key Observation:
// Consecutive elements in a row follow the relation:
//
// C(n, r) = C(n, r-1) * (n - r + 1) / r
//
// This allows generating a full row in O(row) time without
// recomputing factorials or calling nCr repeatedly.
//
// Time Complexity:  O(N²)
// Space Complexity: O(N²)
// ================================================================

// Generates a single row of Pascal's Triangle
vector<int> generateRow(int row)
{
    vector<int> pascalRow;

    int val = 1;
    pascalRow.push_back(val); // First element is always 1

    for (int i = 1; i < row; i++)
    {
        val = val * (row - i);
        val = val / i;

        pascalRow.push_back(val);
    }

    return pascalRow;
}

// Generates the first n rows of Pascal's Triangle
vector<vector<int>> pascalTriangleIII(int n)
{
    vector<vector<int>> ans;

    for (int row = 1; row <= n; row++)
        ans.push_back(generateRow(row));

    return ans;
}

int main()
{
    int input;
    cin >> input;

    vector<vector<int>> ans = pascalTriangleIII(input);

    for (auto &row : ans)
    {
        for (auto val : row)
            cout << val << " ";

        cout << endl;
    }

    return 0;
}