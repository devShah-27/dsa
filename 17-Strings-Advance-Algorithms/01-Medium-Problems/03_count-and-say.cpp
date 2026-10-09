// ==================================================
// PROBLEM
// - countAndSay(1) = "1". For n > 1, countAndSay(n) describes countAndSay(n - 1) as the count and value of each run of equal digits.
// - Example: "111221" is read as "three 1s, two 2s, one 1" -> "312211".
// - Given n, return the nth term of the sequence.
// ==================================================

#include <bits/stdc++.h>
using namespace std;

// ==================================================
// RECURSIVE APPROACH
//
// Idea:
// - Base case: the first term of the sequence is "1".
// - Recursively build the (n - 1)th term, then read it from left to right.
// - Track the length of each run of equal digits with a running 'count'.
// - When a run ends, append the count followed by the digit itself to the result.
//
// Time Complexity: O(N * L) - L is the length of the longest term, and each term is scanned once.
// Space Complexity: O(L) - Result string per call, plus O(N) for the recursion stack.
// ==================================================

string countAndSay(int n) {
    // Base case: the sequence starts with "1"
    if (n == 1)
        return "1";

    // Build the previous term, which we will describe in this call
    string prev = countAndSay(n - 1);

    // 'count' = length of the current run of equal digits
    int count = 1, prevSize = prev.size();

    string res = "";

    for (int i = 1; i < prevSize; i++) {
        if (prev[i] == prev[i - 1]) {
            // Same digit as before, so extend the current run
            count++;
        } else {
            // Run ended: append "<count><digit>" for the previous run
            // NOTE: '0' + count works because count is always a single digit (1 to 3).
            res += ('0' + count);
            res += prev[i - 1];

            // Start counting the new run
            count = 1;
        }
    }

    // Flush the final run, which the loop never closes
    res += ('0' + count);
    res += prev[prevSize - 1];

    return res;
}

int main() {
    int n = 20;

    // Compute the nth term and print it
    string ans = countAndSay(n);

    cout << "The nth term of the count-and-say sequence is: " << ans << endl;
}
