// ==================================================
// PROBLEM
// - Given an array of lowercase words, find the longest possible word chain.
// - wordA is a predecessor of wordB if inserting one character into wordA forms wordB.
// - Return the maximum length of a valid word chain chosen from the list.
// ==================================================

#include <bits/stdc++.h>
using namespace std;

// ==================================================
// SORTING + TABULATION (LIS VARIATION)
//
// Idea:
// - Sort words by length so potential predecessors always appear before their longer successors during sequential evaluation.
// - Verify valid predecessors using a linear two-pointer character comparison.
// - Apply Longest Increasing Subsequence (LIS) tabulation to dynamically track the maximum word chain length ending at each index.
//
// Time Complexity: O(n^2 * L) - Nested loops over n words with O(L) string comparison.
// Space Complexity: O(n) - Auxiliary array used to store dynamic programming states.
// ==================================================

bool comparator(const string &s1, const string &s2)
{
    return s1.size() < s2.size();
}

// Helper function to check if s2 is a valid predecessor of s1
bool canBeLISPart(string &s1, string &s2)
{
    // A valid predecessor must be exactly one character shorter than the current word
    if (s1.size() != s2.size() + 1)
        return false;

    int s1Ptr = 0, s2Ptr = 0;

    // Traverse the longer string s1 and match characters sequentially with s2
    while (s1Ptr < s1.size())
    {
        if (s2Ptr < s2.size() && s1[s1Ptr] == s2[s2Ptr])
        {
            // Characters match; advance both pointers
            s1Ptr++;
            s2Ptr++;
        }
        else
        {
            // Mismatch found; skip the extra character in the longer string s1
            s1Ptr++;
        }
    }

    // Both pointers must reach the end of their strings to confirm a single-character insertion
    if (s1Ptr == s1.size() && s2Ptr == s2.size())
        return true;

    return false;
}

int longestStringChain(vector<string> &words)
{
    // Sort words by length so chains can be built left-to-right like standard LIS
    sort(words.begin(), words.end(), comparator);

    int n = words.size();

    // dp[i] stores the length of the longest word chain ending at index i
    // Initialized to 1 because every single word is trivially a valid chain of length 1
    vector<int> dp(n, 1);

    int maxLen = INT_MIN;

    // Evaluate the longest chain ending at each word
    for (int i = 0; i < n; i++)
    {
        // Check all shorter or equal-length words appearing earlier in the sorted array
        for (int prevIdx = 0; prevIdx < i; prevIdx++)
        {
            // If words[prevIdx] is a valid predecessor, attempt to extend its chain
            if (canBeLISPart(words[i], words[prevIdx]) && dp[i] < dp[prevIdx] + 1)
                dp[i] = dp[prevIdx] + 1;
        }

        // Track the maximum chain length found across all words
        maxLen = max(maxLen, dp[i]);
    }

    return maxLen;
}

int main()
{
    vector<string> words = {"a", "ab", "abc", "abcd", "abcde"};

    // Compute the length of the longest valid string chain
    int lengthOfLongestStringChain = longestStringChain(words);

    cout << "The length of the Longest String Chain is: " << lengthOfLongestStringChain << endl;

    return 0;
}
