// You are given two integers n1 and n2. You need find the Lowest Common Multiple (LCM) of the two given numbers. Return the LCM of the two numbers.

// The Lowest Common Multiple (LCM) of two integers is the lowest positive integer that is divisible by both the integers.

#include <bits/stdc++.h>
using namespace std;

// Using Euclidean Algorithm
int findGCD(int n1, int n2)
{
    while (n1 != 0 && n2 != 0)
    {
        if (n1 > n2)
            n1 = n1 % n2;
        else
            n2 = n2 % n1;
    }

    if (n2 == 0)
        return n1;
    else
        return n2;
}

int findLCM(int n1, int n2)
{
    int GCD = findGCD(n1, n2);

    return ((n1 * n2) / GCD);
}

int main()
{
    int n1, n2;

    cin >> n1 >> n2;

    int LCM = findLCM(n1, n2);

    cout << "LCM of " << n1 << " and " << n2 << " is " << LCM;
}