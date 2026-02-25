// You are given an integer n. You need to check whether it is an armstrong number or not. Return true if it is an armstrong number, otherwise return false.

// An armstrong number is a number which is equal to the sum of the digits of the number, raised to the power of the number of digits.

// You are given an integer n. Return the value of n! or n factorial.

// Factorial of a number is the product of all positive integers less than or equal to that number.

#include <bits/stdc++.h>
using namespace std;

bool checkArmstrong(int num)
{
    int count = log10(num) + 1;

    int sum = 0;

    int dupNum = num;

    while (num > 0)
    {
        int lastDigit = num % 10;

        sum = sum + pow(lastDigit, count);

        num = num / 10;
    }

    return (dupNum == sum);
}

int main()
{

    int input;
    cin >> input;

    bool isArmstrong = checkArmstrong(input);

    if (isArmstrong)
        cout << input << " is an Armstrong number" << endl;
    else
        cout << input << " is not an Armstrong number" << endl;

    return 0;
}