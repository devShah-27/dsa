// ==================================================
// PROBLEM
// - Given a string text and a string pattern, find the starting index of every occurrence of pattern in text.
// - Implement this using the Rabin-Karp algorithm.
// - If pattern is not found, return an empty list.
// ==================================================

#include <bits/stdc++.h>
using namespace std;

// ==================================================
// BRUTE FORCE APPROACH
//
// Idea:
// - Slide the pattern across every valid starting position in the text.
// - At each position, compare characters one by one until a mismatch is found.
// - Record the starting index if all pattern characters match the current text window.
//
// Time Complexity: O(n * m) - Each of the n - m + 1 windows may compare m characters.
// Space Complexity: O(1) - No extra space besides the output list.
// ==================================================

vector<int> search(const string &pat, const string &txt) {
    // Stores the starting index of every match
    vector<int> res;

    int n = txt.size(), m = pat.size();

    // Try every possible starting position of the pattern in the text
    for (int i = 0; i <= n - m; i++) {
        bool isMatching = true;

        // Compare the pattern with the current text window character by character
        for (int j = 0; j < m; j++) {
            if (pat[j] != txt[i + j]) {
                isMatching = false;
                break; // Stop at the first mismatch
            }
        }

        // All m characters matched, so record this starting index
        if (isMatching)
            res.push_back(i);
    }

    return res;
}

// ==================================================
// RABIN-KARP APPROACH (ROLLING HASH)
//
// Idea:
// - Compute a polynomial hash for the pattern and for the first text window of length m.
// - Compare hashes at each window position, and run a direct string comparison only when hashes are equal.
// - Slide the window by removing the leftmost character and adding the next character in O(1).
// - Multiply the pattern hash by p each step so its powers stay aligned with the shifted window.
//
// Time Complexity: O(n + m) average, O(n * m) worst case when many hash collisions occur.
// Space Complexity: O(1) - Only a few integer variables besides the output list.
// ==================================================

vector<int> search(const string &pat, const string &txt) {
    int n = txt.size(), m = pat.size();

    if (m > n)
        return {};

    // p = base of the polynomial hash, mod = modulus that keeps hash values small
    int p = 7, mod = 101;

    int patHash = 0, txtHash = 0;

    // primeRight = p^k for the next character to be added to the window
    // primeLeft = p^i for the leftmost character to be removed from the window
    int primeRight = 1, primeLeft = 1;

    // Build the initial hash of the pattern and of the first text window
    // Each character maps to 1..26 and is weighted by an increasing power of p
    for (int i = 0; i < m; i++) {
        patHash = (patHash + ((pat[i] - 'a' + 1) * primeRight) % mod) % mod;
        txtHash = (txtHash + ((txt[i] - 'a' + 1) * primeRight) % mod) % mod;

        primeRight = (primeRight * p) % mod;
    }

    vector<int> ans;

    // Slide the window across all valid starting positions
    for (int i = 0; i <= n - m; i++) {
        // Equal hashes can be a collision, so verify with a direct comparison
        if (patHash == txtHash) {
            if (txt.substr(i, m) == pat)
                ans.push_back(i);
        }

        // Remove the contribution of the leftmost character (txt[i])
        txtHash =
            (txtHash - ((txt[i] - 'a' + 1) * primeLeft) % mod + mod) % mod;

        // Add the contribution of the next character (txt[i + m]) to the window
        txtHash = (txtHash + ((txt[i + m] - 'a' + 1) * primeRight) % mod) % mod;

        // Shift the pattern hash by one power of p to stay aligned with the window
        patHash = (patHash * p) % mod;

        // Advance both power multipliers for the next window
        primeLeft = (primeLeft * p) % mod;
        primeRight = (primeRight * p) % mod;
    }

    return ans;
}

int main() {
    string txt = "ababcabcababc";
    string pat = "abc";

    vector<int> ans = search(pat, txt);

    cout << "The starting indices of all occurrences of " << pat << " in "
         << txt << " are: ";
    for (auto it : ans)
        cout << it << " ";

    return 0;
}
