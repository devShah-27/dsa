// You are given an integer n. You need to return the number of digits in the number.
// The number will have no leading zeroes, except when the number is 0 itself.

#include <bits/stdc++.h>
using namespace std;

int countDigits(int input)
{
    if (input == 0)
        return 1;

    int count = 0;

    while (input > 0)
    {
        input = input / 10;
        count++;
    }

    return count;
}

int main()
{
    int input;
    cin >> input;

    int digitCount = countDigits(input);

    cout << "Number of digits in " << input << " is " << digitCount << endl;
}