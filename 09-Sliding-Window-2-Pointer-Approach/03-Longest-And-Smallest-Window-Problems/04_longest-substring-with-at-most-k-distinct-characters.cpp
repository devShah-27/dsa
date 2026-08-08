// Given a string s and an integer k.Find the length of the longest substring with at most k distinct characters.

#include <bits/stdc++.h>
using namespace std;

// BRUTE FORCE
// int kDistinctChar(string &s, int k) // TC -> O(N^2), SC -> O(k)
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

// BETTER
// int kDistinctChar(string &s, int k) // TC -> O(2N), SC -> O(K)
// {
//     int n = s.size(), maxLength = 0;

//     int l = 0, r = 0;

//     unordered_map<char, int> mpp;

//     while (r < n)
//     {
//         mpp[s[r]]++;

//         if (mpp.size() > k)
//         {
//             while (mpp.size() > k)
//             {
//                 mpp[s[l]]--;

//                 if (mpp[s[l]] == 0)
//                     mpp.erase(s[l]);

//                 l++;
//             }
//         }
//         else
//         {
//             maxLength = max(maxLength, r - l + 1);
//         }

//         r++;
//     }

//     return maxLength;
// }

// OPTIMAL
int kDistinctChar(string &s, int k) // TC -> O(N), SC -> O(K)
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
