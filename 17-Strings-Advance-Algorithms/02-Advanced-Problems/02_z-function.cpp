// ==================================================
// PROBLEM
// - Given a text string and a pattern string, find the starting index of every occurrence of pattern in text.
// - Use the Z function algorithm and return 0-based indices.
// ==================================================

#include <bits/stdc++.h>
using namespace std;

// ==================================================
// BRUTE FORCE APPROACH
//
// Idea:
// - Join the strings as pattern + "$" + text, where "$" is a separator that appears in neither string.
// - Compute the Z value of every index by comparing characters directly against the start of the joined string.
// - A Z value equal to the pattern length marks a full pattern match starting at that index.
// - Subtract m + 1 from the index to get the text index.
//
// Time Complexity: O((n + m)^2) - Every index may re-compare up to n + m characters.
// Space Complexity: O(n + m) - Joined string and Z array.
// ==================================================

vector<int> getZValues(string str) {
    int n = str.size();

    // zValue[i] = length of the longest prefix of str that starts at index i
    vector<int> zValue(n, 0);

    for (int i = 0; i < n; i++) {
        // Extend the match while characters agree with the prefix
        while ((i + zValue[i] < n) && (str[i + zValue[i]] == str[zValue[i]]))
            zValue[i]++;
    }

    // NOTE: zValue[0] ends up as n here (the whole string matches itself).
    // It is never read by search() because the scan starts at m + 1.
    return zValue;
}

vector<int> search(string text, string pattern) {
    int m = pattern.size();

    // The separator stops any Z value from extending past the pattern length
    string superStr = pattern + "$" + text;

    vector<int> zValue = getZValues(superStr);

    vector<int> res;

    // Scan only the text part of the joined string (starts after the separator)
    for (int idx = m + 1; idx < superStr.size(); idx++) {
        // Z value equal to m means the whole pattern matches at this index
        if (zValue[idx] == m)
            // Convert the joined-string index to a 0-based text index
            res.push_back(idx - (m + 1));
    }

    return res;
}

// ==================================================
// OPTIMAL APPROACH (Z ALGORITHM)
//
// Idea:
// - Build the same joined string, then compute Z values using a Z-box [left, right] of the rightmost match.
// - If index i lies inside the Z-box, reuse the earlier value Z[i - left] instead of comparing again.
// - Compare characters directly only when i is outside the box or the reused value reaches the box boundary.
// - The right boundary only moves forward, so total work stays linear.
//
// Time Complexity: O(n + m) - Each character is compared beyond 'right' at most once.
// Space Complexity: O(n + m) - Joined string and Z array.
// ==================================================

vector<int> computeZarray(string s) {
    int n = s.size();

    // Z[i] = length of the longest prefix of s that starts at index i
    vector<int> Z(n, 0);

    // [left, right] is the Z-box: the rightmost segment that matches a prefix
    int left = 0, right = 0;

    for (int i = 1; i < n; i++) {

        // Case 1: i is outside the Z-box, so compute Z[i] from scratch
        if (i > right) {
            while (i + Z[i] < n && s[i + Z[i]] == s[Z[i]])
                Z[i]++;
        }

        // Case 2: i is inside the Z-box, so reuse the mirrored value Z[i - left]
        else {

            // The mirrored match fits strictly inside the box, so copy it
            if (i + Z[i - left] <= right)
                Z[i] = Z[i - left];

            // The mirrored match touches or crosses the box boundary,
            // so keep the known part and extend by direct comparison
            else {
                Z[i] = right - i + 1;

                while (i + Z[i] < n && s[i + Z[i]] == s[Z[i]])
                    Z[i]++;
            }
        }

        // Move the Z-box forward if the match at i reaches further right
        if (i + Z[i] - 1 > right) {
            left = i;
            right = i + Z[i] - 1;
        }
    }

    return Z;
}

vector<int> search(string text, string pattern) {
    // The separator stops any Z value from extending past the pattern length
    string s = pattern + '$' + text;

    vector<int> Z = computeZarray(s);

    int m = pattern.size();

    vector<int> ans;

    // Scan only the text part of the joined string (starts after the separator)
    for (int i = m + 1; i < s.size(); i++) {
        // Z value equal to m means the whole pattern matches at this index
        if (Z[i] == m)
            // Convert the joined-string index to a 0-based text index
            ans.push_back(i - (m + 1));
    }

    return ans;
}

int main() {
    string text = "xyzabxyzabxyz";
    string pattern = "xyz";

    // Find all starting indices of pattern in text
    vector<int> ans = search(text, pattern);

    for (auto ind : ans)
        cout << ind << " ";
    return 0;
}
