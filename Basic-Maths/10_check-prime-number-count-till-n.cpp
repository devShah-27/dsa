// You are given an integer n. You need to find out the number of prime numbers in the range [1, n] (inclusive). Return the number of prime numbers in the range.

// A prime number is a number which has no divisors except, 1 and itself.

#include <bits/stdc++.h>
using namespace std;

bool checkPrime(int n)
{
    if (n == 1)
        return false;

    for (int i = 2; i * i <= n; i++)
        if (n % i == 0)
            return false;

    return true;
}

int primeCount(int n)
{
    int count = 0;

    for (int i = 1; i <= n; i++)
        if (checkPrime(i))
            count++;

    return count;
}

int main()
{

    int input;
    cin >> input;

    int primes = primeCount(input);

    cout << "There are " << primes << " prime numbers between 1 and " << input << endl;

    return 0;
}