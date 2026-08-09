// Problem:
// Given a string s containing only characters 'a', 'b', and 'c',
// find the number of substrings that contain at least one occurrence of all
// three characters 'a', 'b', and 'c'.

#include <bits/stdc++.h>
using namespace std;

// ==================================================
// BRUTE FORCE APPROACH
//
// Idea:
// Generate all possible substrings and store the characters present in each substring using a set. If all three characters are found, count the substring.
//
// Time Complexity: O(N^2)
// Space Complexity: O(3)
// ==================================================

// int numberOfSubstrings(string s)
// {
//     int n = s.size(), count = 0;

//     for (int i = 0; i < n; i++)
//     {
//         unordered_set<int> st;

//         for (int j = i; j < n; j++)
//         {
//             st.emplace(s[j]);

//             if (st.size() == 3)
//                 count++;
//         }
//     }

//     return count;
// }

// ==================================================
// BETTER APPROACH
//
// Idea:
// Generate substrings while maintaining the set of characters present.
// Once a valid substring containing all three characters is found, all extensions of this substring will also be valid, so add the remaining possible endings directly.
//
// Time Complexity: O(N^2)
// Space Complexity: O(3)
// ==================================================

// int numberOfSubstrings(string s)
// {
//     int n = s.size(), count = 0;

//     for (int i = 0; i < n; i++)
//     {
//         unordered_set<int> st;

//         for (int j = i; j < n; j++)
//         {
//             st.emplace(s[j]);

//             if (st.size() == 3)
//             {
//                 count += n - j;
//                 break;
//             }
//         }
//     }

//     return count;
// }

// ==================================================
// OPTIMAL APPROACH (SLIDING WINDOW)
//
// Idea:
// Store the last seen index of each character.
// At every position, if all three characters have appeared, the earliest last occurrence determines the number of valid starting positions for substrings ending at the current index.
//
// Time Complexity: O(N)
// Space Complexity: O(1)
// ==================================================

int numberOfSubstrings(string s)
{
    int n = s.size(), count = 0;

    vector<int> lastSeen = {-1, -1, -1};

    for (int i = 0; i < n; i++)
    {
        lastSeen[s[i] - 'a'] = i;

        if (lastSeen[0] != -1 && lastSeen[1] != -1 && lastSeen[2] != -1)
        {
            count += min({lastSeen[0], lastSeen[1], lastSeen[2]}) + 1;
        }
    }

    return count;
}

int main()
{
    string s = "bbacba";

    int ans = numberOfSubstrings(s);

    cout << "Number of substrings containing 'a', 'b', 'c' in \"" << s << "\" is: " << ans << endl;

    return 0;
}