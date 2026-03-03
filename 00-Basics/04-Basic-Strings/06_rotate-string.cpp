// Given two strings s and goal, return true if and only if s can become goal after some number of shifts on s.

// A shift on s consists of moving the leftmost character of s to the rightmost position.

// For example, if s = "abcde", then it will be "bcdea" after one shift.

#include <bits/stdc++.h>
using namespace std;

// ============== BRUTE FORCE (Compare all possible variations of s and goal) ==============
// bool checkRotation(string &s, string &goal)
// {
//     if (s.size() != goal.size())
//         return false;

//     int size = s.size();

//     string left = "";

//     for (int i = 0; i < size; i++)
//     {
//         string right = s.substr(i);

//         if ((right + left) == goal)
//             return true;

//         left += s[i];
//     }

//     return false;
// }

// ============== OPTIMAL ==============
bool checkRotation(string &s, string &goal)
{
    if (s.size() != goal.size())
        return false;

    string doubleS = s + s;

    return doubleS.find(goal) != string::npos;
}

int main()
{

    string s = "abcde";
    string goal = "cdeab";

    bool isRotationPossible = checkRotation(s, goal);

    if (isRotationPossible)
        cout << s << " and " << goal << " are rotatable" << endl;
    else
        cout << s << " and " << goal << " are not rotatable" << endl;

    return 0;
}