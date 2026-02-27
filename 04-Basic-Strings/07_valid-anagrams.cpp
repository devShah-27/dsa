// Given two strings s and t, return true if t is an anagram of s, and false otherwise.

// An Anagram is a word or phrase formed by rearranging the letters of a different word or phrase, typically using all the original letters exactly once.

#include <bits/stdc++.h>
using namespace std;

// ============ BRUTE FORCE (Sort both strings and compare) ============
// bool checkAnagram(string &s, string &t)
// {
//     if (s.size() != t.size())
//         return false;

//     string sCopy = s;
//     string tCopy = t;

//     sort(sCopy.begin(), sCopy.end());
//     sort(tCopy.begin(), tCopy.end());

//     return sCopy == tCopy;
// }

// ============ OPTIMAL (Use hashing) ============
bool checkAnagram(string &s, string &t)
{
    if (s.size() != t.size())
        return false;

    int freqS[26] = {0};
    int freqT[26] = {0};

    int n = s.size();

    for (int i = 0; i < n; i++)
    {
        freqS[s[i] - 'a']++;
        freqT[t[i] - 'a']++;
    }

    for (int i = 0; i < 26; i++)
    {
        if (freqS[i] != freqT[i])
            return false;
    }

    return true;
}

int main()
{

    string s = "eat";
    string t = "tea";

    bool isAnagram = checkAnagram(s, t);

    if (isAnagram)
        cout << t << " is an anagram of " << s << endl;
    else
        cout << t << " is not an anagram of " << s << endl;

    return 0;
}