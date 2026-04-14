// ========================== PROBLEM ==========================
// Given a positive integer n, compute and return the floor value
// of its square root. If n is a perfect square, return exact sqrt,
// otherwise return the greatest integer less than sqrt(n).
// ============================================================

#include <bits/stdc++.h>
using namespace std;

// ========================== BRUTE FORCE APPROACH (LINEAR SEARCH) ==========================
// Idea:
// Iterate from 0 to n and check i*i <= n. Keep updating the answer
// until the condition fails. The last valid i is the floor sqrt.
//
// NOTE: Inefficient for large n due to linear traversal.
//
// Time Complexity: O(N)
// Space Complexity: O(1)
// ==========================================================================================
// int floorSqrt(int n)
// {
//     int ans = 1;
//
//     for (int i = 0; i <= n; i++)
//     {
//         if ((i * i) <= n)
//             ans = i;
//         else
//             break;
//     }
//
//     return ans;
// }

// ========================== OPTIMAL APPROACH (BINARY SEARCH) ==========================
// Idea:
// Use binary search on the range [1, n] to find the largest value
// whose square is <= n. If mid*mid <= n, move right; otherwise move left.
// The final 'high' pointer will store the floor sqrt.
//
// Time Complexity: O(log N)
// Space Complexity: O(1)
// =====================================================================================
int floorSqrt(int n)
{
    int low = 1, high = n;

    while (low <= high)
    {
        long long mid = low + ((high - low) / 2);

        // Prevent overflow by using long long for multiplication
        if ((mid * mid) <= n)
            low = mid + 1;
        else
            high = mid - 1;
    }

    return high; // 'high' holds the floor sqrt
}

int main()
{
    int input;
    cin >> input;

    int squareRoot = floorSqrt(input);

    cout << "Floor sqrt of " << input << " = " << squareRoot;

    return 0;
}