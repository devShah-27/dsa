// ==================================================
// PROBLEM
// - Given a string s, return its longest happy prefix.
// - A happy prefix is both a proper prefix and a proper suffix of s.
// - If no such prefix exists, return an empty string "".
// ==================================================

#include <bits/stdc++.h>
using namespace std;

// ==================================================
// OPTIMAL APPROACH (KMP LPS ARRAY)
//
// Idea:
// - The LPS array stores, for each index, the longest proper prefix that is also a suffix of that substring.
// - The last LPS value describes the whole string s.
// - That value is the length of the longest happy prefix.
// - Slice that many characters from the start of s.
//
// Time Complexity: O(n) - Pointer j falls back at most as often as it advances.
// Space Complexity: O(n) - LPS array plus the returned substring.
// ==================================================

vector<int> computeLPS(string s) {
    int n = s.size();

    // LPS[i] = length of the longest proper prefix of s[0..i]
    // that is also a suffix of s[0..i]
    vector<int> LPS(n, 0);

    // i scans the string, j is the length of the current matching prefix
    int i = 1, j = 0;

    while (i < n) {

        // Characters match, so extend the current prefix match
        if (s[i] == s[j]) {
            LPS[i] = j + 1;
            i++, j++;
        }

        else {

            // Mismatch: fall back through shorter borders until a match
            // is found or j reaches 0
            while (j > 0 && s[i] != s[j]) {
                j = LPS[j - 1];
            }

            // After falling back, a shorter prefix may match the current character
            if (s[i] == s[j]) {
                LPS[i] = j + 1;
                j++;
            }

            // If j is 0 and there is still no match, LPS[i] stays 0
            i += 1;
        }
    }

    return LPS;
}

string lps(string s) {
    vector<int> LPS = computeLPS(s);

    // LPS.back() is the length of the longest proper prefix of s that is also a suffix
    // It is 0 when no happy prefix exists, so substr returns ""
    return s.substr(0, LPS[s.size() - 1]);
}

int main() {
    string s = "ababab";

    string ans = lps(s);

    cout << "The longest happy prefix of the given string is: " << ans << endl;
    return 0;
}
