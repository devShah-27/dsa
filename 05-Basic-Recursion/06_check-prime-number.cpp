// Given an integer num, return true if it is prime otherwise false.

// A prime number is a number that is divisible only by 1 and itself.

#include <bits/stdc++.h>
using namespace std;

bool checkPrime(int i, int N)
{
    if (N <= 1)
        return false;

    if (i * i > N)
        return true;

    if (N % i == 0)
        return false;

    return checkPrime(i + 1, N);
}

int main()
{
    int input;
    cin >> input;

    bool isPrime = checkPrime(2, input);

    if (isPrime)
        cout << input << " is a prime number";
    else
        cout << input << " is not a prime number";

    return 0;
}