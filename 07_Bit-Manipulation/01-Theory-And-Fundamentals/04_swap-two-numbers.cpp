// Problem:
// Swap two integers without using an additional variable.
// The swap operation should be performed using bitwise XOR operations.

#include <bits/stdc++.h>
using namespace std;

// ==================================================
// OPTIMAL APPROACH
// Idea:
// Use XOR properties to swap values without requiring a temporary variable.
// XOR operation allows storing and retrieving values through reversible transformations.
//
// Time Complexity: O(1)
// Space Complexity: O(1)
// ==================================================

int main()
{
    int a, b;
    cin >> a >> b;

    cout << "Before swap -> A: " << a << ", B: " << b << endl;

    a = a ^ b;
    b = a ^ b;
    a = a ^ b;

    cout << "After swap -> A: " << a << ", B: " << b << endl;

    return 0;
}