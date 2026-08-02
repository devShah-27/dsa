// Problem:
// Divide two integers without using multiplication, division, or modulo operators.
// Return the quotient truncated toward zero while handling 32-bit signed integer overflow.

#include <bits/stdc++.h>
using namespace std;

// ==================================================
// BRUTE FORCE APPROACH
// Idea:
// Repeatedly subtract the absolute value of the divisor from the absolute
// value of the dividend until the remaining value becomes smaller than the
// divisor. The number of successful subtractions is the quotient.
// Apply the correct sign at the end and handle overflow separately.
//
// Time Complexity: O(|dividend / divisor|)
// Space Complexity: O(1)
// ==================================================

int divide(int dividend, int divisor)
{
    // Handle simple edge cases.
    if (dividend == divisor)
        return 1;

    if (dividend == INT_MIN && divisor == -1)
        return INT_MAX;

    if (divisor == 1)
        return dividend;

    // Determine whether the final quotient should be positive.
    bool isPositive = !((dividend >= 0 && divisor < 0) || (dividend < 0 && divisor > 0));

    // Work with absolute values to simplify subtraction.
    long long n = abs((long long)dividend);
    long long d = abs((long long)divisor);

    long long ans = 0;

    while (n >= d)
    {
        n -= d;
        ans++;
    }

    if (ans > INT_MAX)
        return isPositive ? INT_MAX : INT_MIN;

    return isPositive ? ans : -ans;
}

int main()
{
    cout << divide(10, 3) << endl;  // Expected 3
    cout << divide(7, -3) << endl;  // Expected -2
    cout << divide(-15, 2) << endl; // Expected -7

    return 0;
}