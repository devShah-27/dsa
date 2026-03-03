// Given an integer n, return the factorial of n.

// Factorial of a non-negative integer, is the multiplication of all integers smaller than or equal to n (use 64-bits to return answer).

#include <bits/stdc++.h>
using namespace std;

long long int getFactorialOf(int N)
{
    if (N == 0 || N == 1)
        return 1;

    return N * getFactorialOf(N - 1);
}

int main()
{
    int input;
    cin >> input;

    long long fact = getFactorialOf(input);

    cout << "Factorial of " << input << " is " << fact << endl;

    return 0;
}