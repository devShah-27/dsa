// You are given two integers n1 and n2. You need find the Greatest Common Divisor (GCD) of the two given numbers. Return the GCD of the two numbers.

// The Greatest Common Divisor (GCD) of two integers is the largest positive integer that divides both of the integers.

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

int main()
{
    int n1, n2;

    cin >> n1 >> n2;

    int gcd = findGCD(n1, n2);

    cout << "GCD of " << n1 << " and " << n2 << " is " << gcd;
}