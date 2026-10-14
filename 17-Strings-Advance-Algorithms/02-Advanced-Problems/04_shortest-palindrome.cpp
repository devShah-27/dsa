// ==================================================
// PROBLEM
// - Given a string s, add characters only at the front of s.
// - Return the shortest palindrome that can be formed this way.
// ==================================================

#include <bits/stdc++.h>
using namespace std;

// ==================================================
// OPTIMAL APPROACH (KMP LPS ARRAY)
//
// Idea:
// - The answer needs the longest palindromic prefix of s.
// - Only the remaining suffix must be mirrored to the front.
// - Build s + "$" + reverse(s) and compute its LPS array.
// - The last LPS value is the longest prefix of s that matches a suffix of reverse(s).
// - That prefix is a palindrome, so its length is the longest palindromic prefix.
// - Reverse the unmatched suffix of s and prepend it.
//
// Time Complexity: O(n) - One KMP pass over a string of length 2n + 1.
// Space Complexity: O(n) - Joined string, LPS array, and the reversed copy.
// ==================================================

vector<int> computeLPS(string s) {
    int n = s.size();

    // LPS[i] = length of the longest proper prefix of s[0..i] that is also a suffix of s[0..i]
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

            // Mismatch: fall back through shorter borders until a match is found or j reaches 0
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

string shortestPalindrome(string s) {

    // Reverse a copy of s so its prefixes line up with suffixes of the reversal
    string revs = s;
    reverse(revs.begin(), revs.end());

    // The separator stops any LPS value from exceeding s.size()
    string str = s + '$' + revs;

    vector<int> lps = computeLPS(str);

    // lps.back() = length of the longest palindromic prefix of s
    // The remaining characters (s.size() - lps.back()) must be mirrored to the front
    int ans = s.size() - lps.back();

    // The first 'ans' characters of revs are the reversed unmatched suffix of s
    string to_add = revs.substr(0, ans);

    return to_add + s;
}

int main() {
    string s = "aacecaaa";

    string ans = shortestPalindrome(s);

    cout << ans << endl;
    return 0;
}
