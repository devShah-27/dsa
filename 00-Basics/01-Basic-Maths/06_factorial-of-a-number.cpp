//You are given an integer n. Return the value of n! or n factorial.

// Factorial of a number is the product of all positive integers less than or equal to that number.

#include <bits/stdc++.h>
using namespace std;

int getFactorial(int num)
{
    if (num == 0)
        return 1;

    long long ans = 1;

    for (int i = 1; i <= num; i++)
    {
        ans = ans * i;
    }

    return ans;
}

int main()
{

    int input;
    cin >> input;

    int factorial = getFactorial(input);

    cout << "Factorial of " << input << " is " << factorial << endl;

    return 0;
}