// ==================================================
// PROBLEM
// - Given a string containing letters, digits, and spaces.
// - A word is a maximal sequence of non-space characters.
// - Return the words in reverse order, joined by a single space.
// - Leading, trailing, and repeated spaces must be removed.
// ==================================================

#include <bits/stdc++.h>
using namespace std;

// ==================================================
// BRUTE FORCE APPROACH
//
// Idea:
// - Scan the string left to right, skipping all spaces.
// - Extract each word using start and end pointers, then store it in a vector of strings.
// - Traverse the vector from back to front, appending each word to the result.
// - Add a single space between words, but not after the last one.
//
// Time Complexity: O(N) - Each character is scanned and copied a constant number of times.
// Space Complexity: O(N) - The vector of words and the result string each hold up to N characters.
// ==================================================

string reverseWords(string s) {
    int n = s.size();

    string res = "";

    int i = 0;

    // Stores every word in its original left-to-right order
    vector<string> temp;

    while (i < n) {
        // Skip leading and repeated spaces between words
        while (i < n && s[i] == ' ')
            i++;

        // Only spaces remained, so there are no more words
        if (i == n)
            break;

        int start = i;

        // Move 'i' to the end of the current word
        while (i < n && s[i] != ' ')
            i++;

        int end = i - 1;

        // Extract the word s[start..end] and store it
        temp.push_back(s.substr(start, end - start + 1));
    }

    // Build the result by reading the words in reverse order
    for (int i = temp.size() - 1; i >= 0; i--) {
        res += temp[i];

        // Add a separator after every word except the last one appended
        if (i != 0)
            res += ' ';
    }

    return res;
}

// ==================================================
// OPTIMAL APPROACH
//
// Idea:
// - Reverse the entire string first, so the word order is flipped but each word appears backwards.
// - Use a read pointer 'j' and a write pointer 'i' to compact words in place, dropping extra spaces.
// - Reverse each compacted word back to its correct orientation as soon as it is written.
// - Insert one space between words, then trim the string to its final length.
//
// Time Complexity: O(N) - Each character is read, written, and reversed a constant number of times.
// Space Complexity: O(1) - Extra space is constant, since the string is modified in place.
// ==================================================

string reverseWords(string s) {
    int n = s.size();

    // Step 1: Reverse the whole string to flip the order of the words
    reverse(s.begin(), s.end());

    // 'j' reads from the original position, 'i' writes the compacted result
    int i = 0, j = 0, start = 0, end = 0;

    while (j < n) {
        // Skip leading and repeated spaces in the read region
        while (j < n && s[j] == ' ')
            j++;

        // No more words remain to process
        if (j == n)
            break;

        // Mark where the current word begins in the write region
        start = i;

        // Copy the current word forward to the write position
        while (j < n && s[j] != ' ') {
            s[i] = s[j];
            i++;
            j++;
        }

        end = i - 1;

        // Step 2: Reverse this single word to restore its correct orientation
        reverse(s.begin() + start, s.begin() + end + 1);

        // Add a single separator only if more input remains to be read
        if (j < n) {
            s[i] = ' ';
            i++;
        }
    }

    // Remove the trailing space left when the input ended with spaces
    if (i > 0 && s[i - 1] == ' ')
        i--;

    // Keep only the compacted portion of the string
    return s.substr(0, i);
}

int main() {
    string s = " amazing coding skills ";

    // Run the reversal and print the input and result for comparison
    string ans = reverseWords(s);

    cout << "Input string: " << s << endl;
    cout << "After reversing every word: " << ans << endl;
}
