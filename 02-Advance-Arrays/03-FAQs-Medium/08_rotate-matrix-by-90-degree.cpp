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