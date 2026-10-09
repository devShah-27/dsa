// ==================================================
// PROBLEM
// - Given a string of only '(' and ')'.
// - Find the minimum number of reversals ('(' <-> ')') needed to make the string a balanced expression.
// - Return -1 if it is impossible to balance the string.
// ==================================================

#include <bits/stdc++.h>
using namespace std;

// ==================================================
// OPTIMAL APPROACH
//
// Idea:
// - A balanced string needs an even length, so return -1 for odd lengths.
// - Scan the string and cancel every matched "()" pair.
// - An unmatched ')' with no open bracket before it is counted in 'close'.
// - Whatever remains is always of the form ")))...(((". 'close' holds the unmatched ')' and 'open' holds the unmatched '('.
// - Fix half of each group by reversing: ceil(close / 2) plus ceil(open / 2) reversals in total.
//
// Time Complexity: O(N) - Single pass over the string.
// Space Complexity: O(1) - Only a few integer counters are used.
// ==================================================

int countRev(string s) {
    int n = s.size();

    // An odd-length string can never be balanced
    if (n % 2)
        return -1;

    // 'open' = unmatched '(' so far, 'close' = unmatched ')' so far
    int open = 0, close = 0;

    for (char ch : s) {
        if (ch == '(') {
            // Push a potential match for a later ')'
            open++;
        } else {
            if (open > 0)
                // Match this ')' with the latest unmatched '('
                open--;
            else
                // No '(' available, so this ')' stays unmatched
                close++;
        }
    }

    // Reducing ceil(x / 2) per group: (x / 2) + (x % 2) equals ceil(x / 2).
    // Each reversal fixes two unmatched brackets of the same type.
    // An odd leftover needs one extra reversal to pair with the other group.
    int res = (open / 2) + (open % 2) + (close / 2) + (close % 2);

    return res;
}

int main() {
    string s = ")(())(((";

    // Compute the minimum reversals and print the result
    int ans = countRev(s);

    cout << "The minimum number of reversals required are: " << ans << endl;
}
