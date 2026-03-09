// Problem:
// Given integers r and c (1-indexed), return the element located at
// row r and column c in Pascal's Triangle.
//
// Key observation:
// Each value in Pascal's Triangle corresponds to a binomial coefficient:
//
// Pascal[r][c] = C(r-1, c-1)
//
// Instead of computing factorials, we calculate nCr iteratively
// using the relation:
//
// C(n, r) = C(n, r-1) * (n - r + 1) / r
//
// Time Complexity:  O(c)
// Space Complexity: O(1)

#include <bits/stdc++.h>
using namespace std;

// Computes nCr using iterative multiplication to avoid factorial overflow
long long NcR(int n, int r)
{
    long long res = 1;

    for (int i = 0; i < r; i++)
    {
        res = res * (n - i);
        res = res / (i + 1);
    }

    return res;
}

// Returns the value at position (r, c) in Pascal's Triangle
long long pascalTriangleI(int r, int c)
{
    return NcR(r - 1, c - 1);
}

int main()
{
    int r, c;
    cin >> r >> c;

    long long ans = pascalTriangleI(r, c);

    cout << "Element at R -> " << r << " and C -> " << c << " is " << ans;

    return 0;
}