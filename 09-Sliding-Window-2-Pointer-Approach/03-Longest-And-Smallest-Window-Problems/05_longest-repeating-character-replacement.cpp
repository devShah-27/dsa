// Problem:
// Given a string s and an integer k, replace at most k characters in the string with any uppercase English character. Return the length of the longest substring that can be transformed into a string containing the same character.

#include <bits/stdc++.h>
using namespace std;

// ==================================================
// BRUTE FORCE APPROACH
//
// Idea:
// Generate all possible substrings and maintain the frequency of each character.
// The number of replacements required for a substring is its length minus the frequency of the most common character. If replacements are within k, update the maximum valid substring length.
//
// Time Complexity: O(N^2)
// Space Complexity: O(26)
// ==================================================

// int characterReplacement(string s, int k)
// {
//     int n = s.size(), maxLength = 0;

//     for (int i = 0; i < n; i++)
//     {
//         vector<int> hash(26, 0);

//         int maxFreq = 0;

//         for (int j = i; j < n; j++)
//         {
//             hash[s[j] - 'A']++;

//             maxFreq = max(maxFreq, hash[s[j] - 'A']);

//             int changes = (j - i + 1) - maxFreq;

//             if (changes > k)
//                 break;

//             maxLength = max(maxLength, j - i + 1);
//         }
//     }

//     return maxLength;
// }

// ==================================================
// BETTER APPROACH (SLIDING WINDOW)
//
// Idea:
// Maintain a sliding window and store character frequencies inside it.
// Track the frequency of the most common character. If the number of replacements needed exceeds k, shrink the window from the left until it becomes valid.
//
// Time Complexity: O(2N)
// Space Complexity: O(26)
// ==================================================

// int characterReplacement(string s, int k)
// {
//     int n = s.size(), maxLength = 0;

//     unordered_map<char, int> hash;

//     int r = 0, l = 0, maxFreq = 0;

//     while (r < n)
//     {
//         hash[s[r]]++;

//         maxFreq = max(maxFreq, hash[s[r]]);

//         int changes = (r - l + 1) - maxFreq;

//         while (changes > k)
//         {
//             hash[s[l]]--;

//             if (hash[s[l]] == 0)
//                 hash.erase(s[l]);

//             l++;

//             changes = (r - l + 1) - maxFreq;
//         }

//         maxLength = max(maxLength, r - l + 1);

//         r++;
//     }

//     return maxLength;
// }

// ==================================================
// OPTIMAL APPROACH (SLIDING WINDOW)
//
// Idea:
// Maintain a window where the number of replacements required is at most k.
// The most frequent character in the window does not need replacement, so the remaining characters determine the number of changes needed. Shrink the window only when it becomes invalid, while keeping track of the maximum valid length.
//
// Time Complexity: O(N)
// Space Complexity: O(26)
// ==================================================

int characterReplacement(string s, int k)
{
    int n = s.size(), maxLength = 0;

    unordered_map<char, int> hash;

    int r = 0, l = 0, maxFreq = 0;

    while (r < n)
    {
        hash[s[r]]++;

        maxFreq = max(maxFreq, hash[s[r]]);

        if ((r - l + 1) - maxFreq > k)
        {
            hash[s[l]]--;

            l++;
        }
        else
        {
            maxLength = max(maxLength, r - l + 1);
        }

        r++;
    }

    return maxLength;
}

int main()
{
    string s = "AABABBA";
    int k = 3;

    int length = characterReplacement(s, k);

    cout << "Maximum length of substring with at most " << k << " characters replaced: " << length << endl;

    return 0;
}