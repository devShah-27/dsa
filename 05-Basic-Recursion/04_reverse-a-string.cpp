// Given an input string as an array of characters, write a function that reverses the string.

#include <bits/stdc++.h>
using namespace std;

void revStrRecursive(vector<char> &input, int left, int right)
{
    if (left >= right)
        return;

    int temp = input[left];
    input[left] = input[right];
    input[right] = temp;

    revStrRecursive(input, left + 1, right - 1);
}

vector<char> reverseString(vector<char> &s)
{
    revStrRecursive(s, 0, s.size() - 1);
    return s;
}

int main()
{
    string longText = "TheQuickBrownFoxJumpsOverTheLazyDog1234567890!@#"
                      "ABCDEFGHIJKLMNOPQRSTUVWXYZ"
                      "abcdefghijklmnopqrstuvwxyz"
                      "CplusplusRecursionTestCaseWithLargeInputData";

    vector<char> input(longText.begin(), longText.end());

    cout << "Input before reverse: ";
    for (auto it : input)
        cout << it;

    cout << "\n\n";

    vector<char> reversedInput = reverseString(input);

    cout << "Input after reverse: ";
    for (auto it : reversedInput)
        cout << it;

    cout << endl;

    return 0;
}