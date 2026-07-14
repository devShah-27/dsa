// Problem:
// Implement the power function pow(x, n) that calculates x raised to the power n.
// The function should handle both positive and negative powers.
// Print the result with exactly 4 digits after the decimal point.

#include <bits/stdc++.h>
using namespace std;

// ============================================================================
// BRUTE FORCE APPROACH
//
// Idea:
// Multiply x repeatedly n times to calculate x^n.
// For negative powers, convert x into its reciprocal and make n positive.
//
// Time Complexity: O(n)
// Space Complexity: O(1)
// ============================================================================

// double myPow(double x, int n)
// {
//     double ans = 1.0000;

//     if (n < 0)
//     {
//         x = 1 / x;
//         n = -1 * n;
//     }

//     for (int i = 0; i < n; i++)
//     {
//         ans = ans * x;
//     }

//     return ans;
// }

// ============================================================================
// BETTER APPROACH
//
// Idea:
// Use Binary Exponentiation to reduce the number of multiplications.
// If n is even, square x and reduce n by half.
// If n is odd, multiply the answer by x and reduce n by one.
//
// Time Complexity: O(log(n))
// Space Complexity: O(1)
// ============================================================================

// double myPow(double x, int n)
// {
//     double ans = 1.0000;
//     long num = n;

//     if (num < 0)
//     {
//         x = 1 / x;
//         num = -1 * num;
//     }

//     while (num > 0)
//     {
//         if (num % 2 == 1)
//         {
//             ans = ans * x;
//             num = num - 1;
//         }
//         else
//         {
//             x = x * x;
//             num = num / 2;
//         }
//     }

//     return ans;
// }

// ============================================================================
// OPTIMAL APPROACH (Recursive Binary Exponentiation)
//
// Idea:
// Use divide and conquer to calculate powers efficiently.
// For even powers: x^n = (x^(n/2)) * (x^(n/2)).
// For odd powers: x^n = x * x^(n-1).
// Convert negative powers using the reciprocal of x.
//
// Time Complexity: O(log(n))
// Space Complexity: O(log(n)) due to recursive call stack
// ============================================================================
double myPow(double x, int n)
{
    if (n == 0)
        return 1;

    long num = n;

    if (n < 0)
    {
        x = 1 / x;
        num = -1 * num;
    }

    if (n % 2 == 1)
        return x * myPow(x, num - 1);

    return myPow(x * x, num / 2);
}

int main()
{
    printf("%.4f\n", myPow(2.0000, 10));

    printf("%.4f\n", myPow(2.0000, -2));

    return 0;
}