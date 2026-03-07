// Given an integer r, return all the values in the rth row (1-indexed) in Pascal's Triangle in correct order.

// In Pascal's triangle:

// - The first row has one element with a value of 1.

// - Each row has one more element in it than its previous row.

// - The value of each element is equal to the sum of the elements directly above it when arranged in a triangle format.

#include <bits/stdc++.h>
using namespace std;

vector<int> pascalTriangleII(int r)
{
    vector<int> pascalRow;

    int element = 1;

    pascalRow.emplace_back(element);

    for (int i = 1; i < r; i++)
    {
        element = element * (r - i);
        element = element / i;
        pascalRow.emplace_back(element);
    }

    return pascalRow;
}

int main()
{
    int row;
    cin >> row;

    vector<int> pascalRow = pascalTriangleII(row);

    cout << "Pascal row at " << row << ": ";
    for (int it : pascalRow)
        cout << it << " ";

    return 0;
}