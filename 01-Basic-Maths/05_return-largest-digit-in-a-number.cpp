// You are given an integer n. Return the largest digit present in the number.

#include <bits/stdc++.h>
using namespace std;

int getLargestDigit(int num)
{
    int largest = 0;

    while (num > 0)
    {
        int lastDigit = num % 10;

        if (lastDigit > largest)
            largest = lastDigit;

        num = num / 10;
    }

    return largest;
}

int main()
{

    int input;
    cin >> input;

    int largestDigit = getLargestDigit(input);

    cout << "Largest digit in " << input << " is " << largestDigit << endl;

    return 0;
}