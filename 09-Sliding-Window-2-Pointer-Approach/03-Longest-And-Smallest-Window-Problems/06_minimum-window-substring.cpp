// Problem:
// Given two strings s and t, find the smallest substring of s that contains all characters of t, including duplicate occurrences.
// Return an empty string if no such substring exists.

#include <bits/stdc++.h>
using namespace std;

// ==================================================
// BRUTE FORCE APPROACH
//
// Idea:
// Generate all possible substrings of s and check whether each substring contains all required characters from t with the correct frequencies. Track the smallest valid window found.
//
// Time Complexity: O(N^2)
// Space Complexity: O(1)
// ==================================================

// string minWindow(string s, string t)
// {
//     int n = s.size(), minLength = INT_MAX, sIdx = -1;

//     for (int i = 0; i < n; i++)
//     {
//         unordered_map<char, int> hash;

//         int count = 0;

//         for (char it : t)
//         {
//             hash[it]++;
//         }

//         for (int j = i; j < n; j++)
//         {
//             if (hash[s[j]] > 0)
//                 count++;

//             hash[s[j]]--;

//             if (count == t.size())
//             {
//                 if (j - i + 1 < minLength)
//                 {
//                     minLength = j - i + 1;
//                     sIdx = i;
//                 }

//                 break;
//             }
//         }
//     }

//     return (sIdx == -1) ? "" : s.substr(sIdx, minLength);
// }

// ==================================================
// OPTIMAL APPROACH (SLIDING WINDOW)
//
// Idea:
// Use a sliding window with two pointers and maintain the frequency of required characters. 
// Expand the window using the right pointer until all characters of t are included, then shrink from the left to find the smallest valid window.
//
// Time Complexity: O(2N)
// Space Complexity: O(1)
// ==================================================

string minWindow(string s, string t)
{
    int n = s.size(), minLength = INT_MAX, sIdx = -1;

    unordered_map<char, int> hash;

    // Store the frequency of required characters.
    for (char c : t)
        hash[c]++;

    int r = 0, l = 0, count = 0;

    while (r < n)
    {
        // Count only characters that are still required.
        if (hash[s[r]] > 0)
            count++;

        hash[s[r]]--;

        // When all required characters are present, minimize the window.
        while (count == t.size())
        {
            if (r - l + 1 < minLength)
            {
                minLength = r - l + 1;
                sIdx = l;
            }

            hash[s[l]]++;

            // If a required character is removed, the window becomes invalid.
            if (hash[s[l]] > 0)
                count--;

            l++;
        }

        r++;
    }

    return (sIdx == -1) ? "" : s.substr(sIdx, minLength);
}

int main()
{
    string s = "ddaaabbcccccccca";
    string t = "abc";

    string ans = minWindow(s, t);

    cout << "Minimum length substring containing all characters from \"" << t << "\" is: " << ans << endl;

    return 0;
}