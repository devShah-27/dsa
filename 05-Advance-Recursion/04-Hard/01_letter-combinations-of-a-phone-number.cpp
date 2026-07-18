// Given a string consisting of digits from 2 to 9 (inclusive). Return all possible letter combinations that the number can represent.

// Mapping of digits to letters is given in first example.

// Input : digits = "34"
// Output : [ "dg", "dh", "di", "eg", "eh", "ei", "fg", "fh", "fi" ]
// Explanation : The 3 is mapped with "def" and 4 is mapped with "ghi".
// So all possible combination by replacing the digits with characters are shown in output.

#include <bits/stdc++.h>
using namespace std;

void recursiveLetterCombinations(string digits, map<int, string> &mpp, vector<string> &result, int index, int n, string tempString)
{
    if (index == n)
    {
        result.emplace_back(tempString);
        return;
    }

    if (index > n)
        return;

    string mappedCharacters = mpp[digits[index] - '0'];

    for (int i = 0; i < mappedCharacters.size(); i++)
    {
        recursiveLetterCombinations(digits, mpp, result, index + 1, n, tempString + mappedCharacters[i]);
    }
}

vector<string> letterCombinations(string digits)
{
    int digitsSize = digits.size();

    map<int, string> mpp;

    mpp.emplace(2, "abc");
    mpp.emplace(3, "def");
    mpp.emplace(4, "ghi");
    mpp.emplace(5, "jkl");
    mpp.emplace(6, "mno");
    mpp.emplace(7, "pqrs");
    mpp.emplace(8, "tuv");
    mpp.emplace(9, "wxyz");

    vector<string> result;

    recursiveLetterCombinations(digits, mpp, result, 0, digitsSize, "");

    return result;
}

int main()
{
    string digits = "234";
    vector<string> result = letterCombinations(digits);

    for (const string &combination : result)
    {
        cout << combination << endl;
    }

    return 0;
}