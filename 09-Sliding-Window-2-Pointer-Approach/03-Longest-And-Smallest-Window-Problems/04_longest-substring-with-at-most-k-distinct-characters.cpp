// Problem:
// Given a string s and an integer k, find the length of the longest substring that contains at most k distinct characters.
// Return the maximum length of such a substring.

#include <bits/stdc++.h>
using namespace std;

// ==================================================
// BRUTE FORCE APPROACH
//
// Idea:
// Generate all possible substrings and maintain a set of characters present in the current substring. Stop expanding once the number of distinct characters exceeds k and track the maximum valid substring length.
//
// Time Complexity: O(N^2)
// Space Complexity: O(K)
// ==================================================

// int kDistinctChar(string &s, int k)
// {
//     int n = s.size(), maxLength = 0;

//     for (int i = 0; i < n; i++)
//     {
//         unordered_set<char> st;

//         for (int j = i; j < n; j++)
//         {
//             st.emplace(s[j]);

//             if (st.size() > k)
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
// Maintain a window using two pointers and store the frequency of characters.
// Expand the window using the right pointer. If the number of distinct characters exceeds k, shrink the window from the left until the condition becomes valid.
//
// Time Complexity: O(2N)
// Space Complexity: O(K)
// ==================================================

// int kDistinctChar(string &s, int k)
// {
//     int n = s.size(), maxLength = 0;

//     int l = 0, r = 0;

//     unordered_map<char, int> mpp;

//     while (r < n)
//     {
//         mpp[s[r]]++;

//         while (mpp.size() > k)
//         {
//             mpp[s[l]]--;

//             if (mpp[s[l]] == 0)
//                 mpp.erase(s[l]);

//             l++;
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
// Maintain a window with at most k distinct characters using two pointers.
// Whenever the distinct character count exceeds k, remove the leftmost character and move the left pointer by one position. Each character is processed only once.
//
// Time Complexity: O(N)
// Space Complexity: O(K)
// ==================================================

int kDistinctChar(string &s, int k)
{
    int n = s.size(), maxLength = 0;

    int l = 0, r = 0;

    unordered_map<char, int> mpp;

    while (r < n)
    {
        mpp[s[r]]++;

        if (mpp.size() > k)
        {
            mpp[s[l]]--;

            if (mpp[s[l]] == 0)
                mpp.erase(s[l]);

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
    string s = "aaabbccd";
    int k = 2;

    int length = kDistinctChar(s, k);

    cout << "Maximum length of substring with at most " << k << " distinct characters: " << length << endl;

    return 0;
}