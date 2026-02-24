// You are given an integer n. You need to check if the number is prime or not. Return true if it is a prime number, otherwise return false.

// A prime number is a number which has no divisors except 1 and itself.

#include <bits/stdc++.h>
using namespace std;

//=============== BRUTE FORCE ===============
// bool checkPrime(int n)
// {
//     if (n == 1)
//         return false;

//     for (int i = 2; i < n; i++)
//         if (n % i == 0)
//             return false;

//     return true;
// }

//=============== OPTIMAL ===============
bool checkPrime(int n)
{
    if (n == 1)
        return false;

    for (int i = 2; i * i <= n; i++)
        if (n % i == 0)
            return false;

    return true;
}

int main()
{

    int input;
    cin >> input;

    bool isPrime = checkPrime(input);

    if (isPrime)
        cout << input << " is a prime number" << endl;
    else
        cout << input << " is not a prime number" << endl;

    return 0;
}