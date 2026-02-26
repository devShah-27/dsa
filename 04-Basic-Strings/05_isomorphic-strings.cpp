// Given two strings s and t, determine if they are isomorphic. Two strings s and t are isomorphic if the characters in s can be replaced to get t.

// All occurrences of a character must be replaced with another character while preserving the order of characters. No two characters may map to the same character, but a character may map to itself.

#include <bits/stdc++.h>
using namespace std;

bool isIsomorphic(string s, string t)
{
    if (s.size() != t.size())
        return false;

    unordered_map<char, char> mapST;
    unordered_map<char, char> mapTS;

    for (int i = 0; i < s.size(); i++)
    {
        char c1 = s[i];
        char c2 = t[i];

        // If mapping exists, check consistency
        if (mapST.count(c1))
        {
            if (mapST[c1] != c2)
                return false;
        }
        else
        {
            mapST[c1] = c2;
        }

        // Check reverse mapping to ensure no two chars map to same char
        if (mapTS.count(c2))
        {
            if (mapTS[c2] != c1)
                return false;
        }
        else
        {
            mapTS[c2] = c1;
        }
    }

    return true;
}

int main()
{
    string s1 = "paper";
    string s2 = "title";

    bool checkIsomorphic = isIsomorphic(s1, s2);

    if (checkIsomorphic)
        cout << s1 << " and " << s2 << " are isomorphic" << endl;
    else
        cout << s1 << " and " << s2 << " are not isomorphic" << endl;

    return 0;
}
