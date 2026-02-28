// Given an integer N, return the sum of first N natural numbers. Solve this using recursion.

#include <bits/stdc++.h>
using namespace std;

int getSumTill(int N)
{
    if (N == 0)
        return 0;
        
    if (N == 1)
        return 1;

    return N + getSumTill(N - 1);
}

int main()
{
    int input;
    cin >> input;

    int sum = getSumTill(input);

    cout << "Sum of first " << input << " numbers is " << sum << endl;

    return 0;
}
