// Given a string, the task is to reverse it. The string is represented by an array of characters s.

// Perform the reversal in place with O(1) extra memory.

#include <bits/stdc++.h>
using namespace std;

// =============== BRUTE FORCE (Use another string) ===============
// void reverseStr(vector<char> &str)
// {
//     int n = str.size();

//     char revStr[n] = {""};

//     for (int i = 0; i < n; i++)
//         revStr[n - i - 1] = str[i];

//     for (int i = 0; i < n; i++)
//         str[i] = revStr[i];
// }

// =============== OPTIMAL (Use 2 pointer approach) ===============
void reverseStr(vector<char> &str)
{
    int n = str.size();

    int left = 0, right = n - 1;

    while (left < right)
    {
        char temp = str[right];
        str[right] = str[left];
        str[left] = temp;

        left++, right--;
    }
}

int main()
{
    vector<char> str = {'s', 't', 'r', 'i', 'v', 'e', 'r'};

    cout
        << "String before reverse: ";

    for (auto it : str)
        cout << it;

    cout << endl;

    reverseStr(str);

    cout
        << "String after reverse: ";

    for (auto it : str)
        cout << it;

    return 0;
}