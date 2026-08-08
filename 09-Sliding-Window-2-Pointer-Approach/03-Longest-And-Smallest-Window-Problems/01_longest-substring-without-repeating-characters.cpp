// Problem:
// Given a string S, find the length of the longest substring that contains no repeating characters.
// Return the maximum length of such a substring.

#include <bits/stdc++.h>
using namespace std;

// ==================================================
// BRUTE FORCE APPROACH
//
// Idea:
// Generate every possible substring and maintain a set of characters seen so far.
// If a duplicate character is found, stop extending the current substring.
// Track the maximum valid substring length found.
//
// Time Complexity: O(N^2)
// Space Complexity: O(256)
// ==================================================

// int longestNonRepeatingSubstring(string &s)
// {
//     int n = s.size(), maxLen = 0;

//     for (int i = 0; i < n; i++)
//     {
//         vector<int> seen(256, 0);

//         for (int j = i; j < n; j++)
//         {
//             if (seen[s[j]] == 1)
//                 break;

//             int length = j - i + 1;

//             maxLen = max(maxLen, length);

//             seen[s[j]] = 1;
//         }
//     }

//     return maxLen;
// }

// ==================================================
// OPTIMAL APPROACH (SLIDING WINDOW)
//
// Idea:
// Maintain a window containing only unique characters using two pointers.
// Store the last seen index of every character. When a duplicate character appears, move the left pointer to the position after its previous occurrence.
//
// Time Complexity: O(N)
// Space Complexity: O(256)
// ==================================================

int longestNonRepeatingSubstring(string &s)
{
    int n = s.size();

    vector<int> seen(256, -1);

    int left = 0, right = 0, maxLength = 0;

    while (right < n)
    {
        // If the character exists inside the current window, shrink the window.
        if (seen[s[right]] != -1 && seen[s[right]] >= left)
            left = seen[s[right]] + 1;

        // Update the latest occurrence of the current character.
        seen[s[right]] = right;

        int length = right - left + 1;
        maxLength = max(maxLength, length);

        right++;
    }

    return maxLength;
}

int main()
{
    string input = "cadbzabcd";

    int length = longestNonRepeatingSubstring(input);

    cout << "Length of longest substring without repeating characters: " << length << endl;

    return 0;
}