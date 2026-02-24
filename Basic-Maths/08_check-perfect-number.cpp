// You are given an integer n. You need to check if the number is a perfect number or not. Return true if it is a perfect number, otherwise, return false.

// A perfect number is a number whose proper divisors (excluding the number itself) add up to the number itself.

#include <bits/stdc++.h>
using namespace std;

//=============== BRUTE FORCE ===============
// bool checkPerfect(int n)
// {
//     if (n == 1)
//         return false;

//     int sum = 0;

//     for (int i = 1; i <= n - 1; i++)
//     {
//         if (n % i == 0)
//             sum = sum + i;
//     }

//     return (sum == n);
// }

//=============== OPTIMAL ===============
bool checkPerfect(int n)
{
    if (n == 1)
        return false;

    int sum = 1;

    for (int i = 2; i * i <= n; i++)
    {
        if (n % i == 0)
        {
            sum = sum + i;

            if (i != (n / i))
                sum = sum + (n / i);
        }
    }

    return (sum == n);
}

int main()
{

    int input;
    cin >> input;

    bool isPerfect = checkPerfect(input);

    if (isPerfect)
        cout << input << " is a perfect number" << endl;
    else
        cout << input << " is not a perfect number" << endl;

    return 0;
}