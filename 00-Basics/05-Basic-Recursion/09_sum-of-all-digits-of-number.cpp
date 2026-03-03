// Given an integer num, repeatedly add all its digits until the result has only one digit, and return it.

#include <bits/stdc++.h>
using namespace std;

long long int addDigits(int num)
{
    if (num == 0)
        return 0;

    int sum = (num % 10) + addDigits(num / 10);

    if (sum >= 10)
        sum = addDigits(sum);

    return sum;
}

int main()
{
    long long int input;
    cin >> input;

    long long int sum = addDigits(input);

    cout << "Sum of all digits of " << input << " is " << sum;

    return 0;
}