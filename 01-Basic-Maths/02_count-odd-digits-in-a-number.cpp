// You are given an integer n. You need to return the number of odd digits present in the number.

// The number will have no leading zeroes, except when the number is 0 itself.

#include <bits/stdc++.h>
using namespace std;

int getOddDigitCount(int num)
{
    if (num == 0)
        return 0;

    int count = 0;

    while (num > 0)
    {
        int lastDigit = num % 10;

        if (lastDigit % 2 != 0)
            count++;

        num = num / 10;
    }

    return count;
}

int main()
{
    int input;
    cin >> input;

    int oddDigitCount = getOddDigitCount(input);

    cout << "Number of odd digits in " << input << " is " << oddDigitCount << endl;
    return 0;
}