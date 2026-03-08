// Given an N * N 2D integer matrix, rotate the matrix by 90 degrees clockwise.

// The rotation must be done in place, meaning the input 2D matrix must be modified directly.

#include <bits/stdc++.h>
using namespace std;

// ========= BRUTE FORCE (Place each element in its correct position) =========
// void rotateMatrix(vector<vector<int>> &matrix) // TC -> O(N^2), SC -> O(N^2)
// {
//     int n = matrix.size();

//     vector<vector<int>> ans(n, vector<int>(n));

//     for (int i = 0; i < n; i++) // O(N)
//         for (int j = 0; j < n; j++) // O(N)
//             ans[j][n - i - 1] = matrix[i][j];

//     for (int i = 0; i < n; i++) // O(N)
//         matrix[i] = ans[i];
// }

// ========= OPTIMAL (Transpose matrix and reverse each row) =========
void rotateMatrix(vector<vector<int>> &matrix)
{
    int n = matrix.size();

    for (int i = 0; i < n; i++)
        for (int j = i + 1; j < n; j++)
            swap(matrix[i][j], matrix[j][i]);

    for (auto &row : matrix)
        reverse(row.begin(), row.end());
}

int main()
{
    vector<vector<int>> input = {{1, 1, 2}, {5, 3, 1}, {5, 3, 5}};

    cout << "Before rotation: " << endl;
    for (auto lvl1Elem : input)
    {
        for (auto lvl2Elem : lvl1Elem)
            cout << lvl2Elem << " ";

        cout << endl;
    }

    rotateMatrix(input);

    cout << endl
         << "After rotation: " << endl;
    for (auto lvl1Elem : input)
    {
        for (auto lvl2Elem : lvl1Elem)
            cout << lvl2Elem << " ";

        cout << endl;
    }

    return 0;
}