// Given an integer n, return the first n (1-Indexed) rows of Pascal's triangle.

// In Pascal's triangle:
// - The first row has one element with a value of 1.
// - Each row has one more element in it than its previous row.
// - The value of each element is equal to the sum of the elements directly above it when arranged in a triangle format.
#include <bits/stdc++.h>
using namespace std;

// ======== BRUTE FORCE (Use Pascal's Triangle 1 method) ========
// int NcR(int n, int r) // TC -> O(r)  (or O(N) upper bound), SC -> O(1)
// {
//     int ans = 1;

//     for (int col = 0; col < r; col++) // O(N)
//     {
//         ans = ans * (n - col);
//         ans = ans / (col + 1);
//     }

//     return ans;
// }

// vector<vector<int>> pascalTriangleIII(int n) // TC -> O(N^3), SC -> O(N^2)
// {
//     vector<vector<int>> ans;

//     for (int row = 1; row <= n; row++) // O(N)
//     {
//         vector<int> tempList;

//         for (int col = 1; col <= row; col++) // O(N)
//         {
//             int element = NcR(row - 1, col - 1); // O(N)
//             tempList.emplace_back(element);
//         }

//         ans.emplace_back(tempList);
//     }

//     return ans;
// }

// ======== OPTIMAL (Use Pascal's Triangle 2 method) ========
vector<int> generateRow(int row) // TC -> O(row), SC -> O(row)
{
    vector<int> pascalRow;

    int ans = 1;

    pascalRow.emplace_back(ans);

    for (int i = 1; i < row; i++) // O(row)
    {
        ans = ans * (row - i);
        ans = ans / i;
        pascalRow.emplace_back(ans);
    }

    return pascalRow;
}

vector<vector<int>> pascalTriangleIII(int n) // TC -> O(N^2), SC -> O(N^2)
{
    vector<vector<int>> ans;

    for (int row = 1; row <= n; row++) // O(N)
        ans.emplace_back(generateRow(row)); // O(N)

    return ans;
}

int main()
{
    int input;
    cin >> input;

    vector<vector<int>> ans = pascalTriangleIII(input);

    for (auto lvl1Elem : ans)
    {
        for (auto lvl2Elem : lvl1Elem)
            cout << lvl2Elem << " ";

        cout << endl;
    }

    return 0;
}