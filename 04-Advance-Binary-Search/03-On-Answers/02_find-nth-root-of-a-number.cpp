// ========================== PROBLEM ==========================
// Given two positive integers N and M, find the Nth root of M.
// If there exists an integer x such that x^N = M, return x.
// Otherwise, return -1.
// ============================================================

#include <bits/stdc++.h>
using namespace std;

// ========================== BRUTE FORCE APPROACH (LINEAR SEARCH) ==========================
// Idea:
// Check every possible value from 1 to M and determine whether
// its Nth power is equal to M.
//
// NOTE: Inefficient for large values of M.
// The power calculation should ideally be optimized to avoid overflow.
//
// Time Complexity: O(M * log N) with built-in power function
// Space Complexity: O(1)
// ==========================================================================================
// int NthRoot(int N, int M)
// {
//     for (int i = 1; i <= M; i++)
//     {
//         if (pow(i, N) == M)
//             return i;
//     }
//
//     return -1;
// }

// ========================== HELPER FUNCTION (POWER CHECK) ==========================
// Idea:
// Calculate mid^N while avoiding unnecessary computations.
// Return:
// 1 -> if mid^N equals M
// 0 -> if mid^N is less than M
// 2 -> if mid^N exceeds M
//
// Time Complexity: O(N)
// Space Complexity: O(1)
// ====================================================================================
int powCheck(int mid, int N, int M)
{
    long long ans = 1;

    for (int i = 1; i <= N; i++)
    {
        ans = ans * mid;

        // Early termination to prevent overflow and unnecessary calculations
        if (ans > M)
            return 2;
    }

    if (ans == M)
        return 1;

    return 0;
}

// ========================== OPTIMAL APPROACH (BINARY SEARCH) ==========================
// Idea:
// Since x^N is an increasing function, apply binary search on the
// possible range of answers from 1 to M.
// Use powCheck() to determine whether to search left or right.
//
// Time Complexity: O(log M * N)
// Space Complexity: O(1)
// =====================================================================================
int NthRoot(int N, int M)
{
    int low = 1, high = M;

    while (low <= high)
    {
        int mid = low + ((high - low) / 2);

        int result = powCheck(mid, N, M);

        if (result == 1)
            return mid;
        else if (result == 0)
            low = mid + 1;
        else
            high = mid - 1;
    }

    return -1;
}

int main()
{
    int M, N;

    cin >> N;
    cin >> M;

    int ans = NthRoot(N, M);

    cout << ans;

    return 0;
}