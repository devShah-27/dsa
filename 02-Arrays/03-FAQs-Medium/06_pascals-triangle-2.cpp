// Problem:
// Given an integer r, return the r-th row (1-indexed) of Pascal's Triangle.
//
// Key observation:
// The r-th row contains the binomial coefficients:
//
// C(r-1,0), C(r-1,1), C(r-1,2) ... C(r-1,r-1)
//
// Instead of computing factorials, we generate each element using
// the recurrence relation:
//
// C(n, k) = C(n, k-1) * (n - k + 1) / k
//
// Time Complexity:  O(r)
// Space Complexity: O(r)

#include <bits/stdc++.h>
using namespace std;

vector<int> pascalTriangleII(int r)
{
    vector<int> pascalRow;

    long long element = 1; // First element is always 1
    pascalRow.push_back(element);

    // Generate remaining elements using binomial recurrence
    for (int i = 1; i < r; i++)
    {
        element = element * (r - i);
        element = element / i;

        pascalRow.push_back(element);
    }

    return pascalRow;
}

int main()
{
    int row;
    cin >> row;

    vector<int> pascalRow = pascalTriangleII(row);

    cout << "Pascal row at " << row << ": ";
    for (int val : pascalRow)
        cout << val << " ";

    return 0;
}