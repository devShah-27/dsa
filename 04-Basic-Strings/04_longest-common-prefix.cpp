// Write a function to find the longest common prefix string amongst an array of strings.

// If there is no common prefix, return an empty string "".

#include <bits/stdc++.h>
using namespace std;

string getLongestCommonPrefix(vector<string> &strs)
{
    if (strs.empty())
        return "";

    sort(strs.begin(), strs.end());

    string prefix = "";

    string s1 = strs[0];
    string s2 = strs[strs.size() - 1];

    for (int i = 0; i < min(s1.size(), s2.size()); i++)
    {
        if (s1[i] != s2[i])
            break;

        prefix += s1[i];
    }

    return prefix;
}

int main()
{
    vector<string> str = {"dog", "racecar", "car"};

    cout << "Array before sorting: ";

    for (auto it : str)
        cout << it << " ";

    cout << endl;

    string longestCommonPrefix = getLongestCommonPrefix(str);

    cout << "Array after sorting: ";

    for (auto it : str)
        cout << it << " ";

    cout << endl;

    cout << "Longest common prefix: " << longestCommonPrefix << endl;

    return 0;
}