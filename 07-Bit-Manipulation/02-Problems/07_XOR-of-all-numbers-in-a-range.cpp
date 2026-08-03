// Given two integers L and R. Find the XOR of the elements in the range [L , R].

#include <bits/stdc++.h>
using namespace std;

// BRUTE FORCE
// int findRangeXOR(int l, int r) // TC -> O(R-L+1), SC ->O(1)
// {
//     int ans = 0;

//     for (int i = l; i <= r; i++)
//     {
//         ans ^= i;
//     }

//     return ans;
// }

// OPTIMAL
int XORTillN(int N)
{
    if (N % 4 == 1)
        return 1;
    else if (N % 4 == 2)
        return N + 1;
    else if (N % 4 == 3)
        return 0;
    else
        return N;
}

int findRangeXOR(int l, int r) // TC -> O(1), SC ->O(1)
{
    return XORTillN(l - 1) ^ XORTillN(r);
}

int main()
{
    int l = 4, r = 10000;

    int ans = findRangeXOR(l, r);

    cout << "The XOR of numbers from " << l << " to " << r << " is: " << ans;

    return 0;
}
