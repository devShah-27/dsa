// ==================================================
// PROBLEM
// - Given a text string and a pattern string, find the starting index
//   of every occurrence of pattern in text.
// - Use the Knuth-Morris-Pratt (KMP) algorithm and return 0-based indices.
// - Indices must be in ascending order. Return an empty list if there is no match.
// ==================================================

#include <bits/stdc++.h>
using namespace std;

// ==================================================
// BRUTE FORCE APPROACH
//
// Idea:
// - Join the strings as pattern + "$" + text, where "$" is a separator that appears in neither string.
// - For every index, test each prefix length by comparing the prefix with the substring ending at that index.
// - Keep the largest length that matches as the LPS value.
// - An LPS value equal to the pattern length marks a full pattern match ending at that index.
//
// Time Complexity: O((n + m)^3) - Two nested loops plus O(len) substring comparisons.
// Space Complexity: O(n + m) - Joined string and LPS array, plus temporary substrings.
// ==================================================

vector<int> computeLPS(string str) {
    int n = str.size();

    // LPS[i] = length of the longest proper prefix of str[0..i]
    // that is also a suffix of str[0..i]
    vector<int> LPS(n, 0);

    for (int i = 1; i < n; i++) {
        // Try every candidate length. Since len <= i, the prefix stays proper
        for (int len = 1; len <= i; len++) {
            // Compare the prefix of length len with the suffix of length len ending at i
            if (str.substr(0, len) == str.substr(i - len + 1, len))
                LPS[i] = len;
        }
    }

    // The optimal approach below avoids this entirely.
    return LPS;
}

vector<int> search(string pat, string txt) {
    // The separator stops any LPS value from exceeding the pattern length
    string s = pat + "$" + txt;

    vector<int> LPS = computeLPS(s);

    int m = pat.size();

    vector<int> res;

    // Scan only the text part of the joined string (starts after the separator)
    for (int i = m + 1; i < s.size(); i++) {
        // LPS equal to m means the whole pattern ends at index i
        if (LPS[i] == m)
            // The match starts at i - m + 1 in s. Subtracting the offset
            // m + 1 (pattern + separator) gives the 0-based index in text.
            res.push_back(i - 2 * m);
    }

    return res;
}

// ==================================================
// OPTIMAL APPROACH (KMP LPS ARRAY)
//
// Idea:
// - Build the same joined string, then compute the LPS array in a single pass using two pointers i and j.
// - Pointer j tracks the length of the current matching prefix.
// - On a mismatch, fall back to LPS[j - 1] instead of restarting, so no character is compared from scratch.
// - Each LPS value equal to the pattern length marks a match.
//
// Time Complexity: O(n + m) - Pointer j falls back at most as often as it advances.
// Space Complexity: O(n + m) - Joined string and LPS array.
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
            i++;
            j++;
        } else {
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
            i++;
        }
    }

    return LPS;
}

vector<int> search(string pattern, string text) {
    // The separator stops any LPS value from exceeding the pattern length
    string s = pattern + '$' + text;

    vector<int> LPS = computeLPS(s);

    int m = pattern.size();

    vector<int> ans;

    // Scan only the text part of the joined string (starts after the separator)
    for (int i = m + 1; i < s.size(); i++) {
        // LPS equal to m means the whole pattern ends at index i
        if (LPS[i] == m)
            // Convert the match end index in s to the 0-based start index in text
            ans.push_back(i - 2 * m);
    }

    return ans;
}

int main() {
    string text = "xyzabxyzabxyz";
    string pattern = "xyz";

    vector<int> ans = search(pattern, text);

    for (auto ind : ans)
        cout << ind << " ";
    return 0;
}
