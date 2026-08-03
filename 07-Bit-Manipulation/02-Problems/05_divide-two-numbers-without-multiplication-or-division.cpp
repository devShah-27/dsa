// Problem:
// Divide two integers without using multiplication, division, or modulo operators.
// Return the quotient truncated toward zero while handling 32-bit signed integer overflow.

#include <bits/stdc++.h>
using namespace std;

// ==================================================
// BRUTE FORCE APPROACH
// Idea:
// Repeatedly subtract the absolute value of the divisor from the absolute value of the dividend until the remaining value becomes smaller than the divisor. The number of successful subtractions gives the quotient.
// Apply the correct sign and handle overflow cases separately.
//
// Time Complexity: O(|dividend / divisor|)
// Space Complexity: O(1)
// ==================================================

// int divide(int dividend, int divisor)
// {
//     if (dividend == divisor)
//         return 1;

//     if (dividend == INT_MIN && divisor == -1)
//         return INT_MAX;

//     if (divisor == 1)
//         return dividend;

//     bool isPositive = !((dividend >= 0 && divisor < 0) || (dividend < 0 && divisor > 0));

//     long long n = abs((long long)dividend);
//     long long d = abs((long long)divisor);

//     long long ans = 0;

//     while (n >= d)
//     {
//         n -= d;
//         ans++;
//     }

//     if (ans > INT_MAX)
//         return isPositive ? INT_MAX : INT_MIN;

//     return isPositive ? ans : -ans;
// }

// ==================================================
// OPTIMAL APPROACH
// Idea:
// Instead of subtracting the divisor one time at a time, use bit shifting to subtract the largest possible multiples of the divisor.
// Since multiplying by powers of two can be done using left shifts, we build the quotient by adding corresponding powers of two.
//
// Time Complexity: O(log^2(N))
// Space Complexity: O(1)
// ==================================================

int divide(int dividend, int divisor)
{
    if (dividend == divisor)
        return 1;

    bool sign = true; // true means positive quotient

    if ((dividend >= 0 && divisor < 0) || (dividend < 0 && divisor > 0))
        sign = false;

    long long numerator = abs((long long)dividend);
    long long denominator = abs((long long)divisor);

    int ans = 0;

    while (numerator >= denominator)
    {
        int shiftCount = 0;

        // Find the largest power of two such that:
        // denominator * 2^shiftCount <= numerator
        while (numerator >= (denominator << (shiftCount + 1)))
        {
            shiftCount++;
        }

        // Add the corresponding power of two to the quotient.
        ans += 1 << shiftCount;

        // Subtract the calculated multiple from the numerator.
        numerator -= denominator * (1 << shiftCount);
    }

    if (ans == INT_MAX)
        return sign ? INT_MAX : INT_MIN;

    return sign ? ans : (-1) * ans;
}

int main()
{
    cout << divide(10, 3) << endl;  // Expected 3
    cout << divide(7, -3) << endl;  // Expected -2
    cout << divide(-15, 2) << endl; // Expected -7

    return 0;
}