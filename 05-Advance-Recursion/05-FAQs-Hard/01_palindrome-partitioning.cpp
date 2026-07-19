// Problem:
// Given a string s, partition it into substrings such that every substring in the partition is a palindrome. Return all possible palindrome partitions of s.

#include <bits/stdc++.h>
using namespace std;

// ============================================================================
// BACKTRACKING APPROACH
//
// Idea:
// Try every possible partition starting from the current index.
// Only choose a substring if it is a palindrome, then recursively partition the remaining suffix.
// Backtrack after exploring each possible partition choice.
//
// Time Complexity: O(n * 2^n) in the worst case
// Space Complexity: O(n) due to recursion stack excluding output storage
// ============================================================================

// Checks whether the substring from left to right is a palindrome.
bool checkPalindrome(string s, int left, int right)
{
    while (left <= right)
    {
        if (s[left] != s[right])
            return false;

        left++;
        right--;
    }

    return true;
}

void recursivePalindromePartition(int idx, string s, int n, vector<vector<string>> &result, vector<string> &tempList)
{
    // All characters are partitioned successfully.
    if (idx == n)
    {
        result.emplace_back(tempList);
        return;
    }

    // Try every possible substring starting from the current index.
    for (int j = idx; j < n; j++)
    {
        // Only continue with palindrome substrings.
        if (checkPalindrome(s, idx, j))
        {
            // Choose the current palindrome substring.
            tempList.emplace_back(s.substr(idx, j - idx + 1));

            // Recursively partition the remaining string.
            recursivePalindromePartition(j + 1, s, n, result, tempList);

            // Backtrack and try the next possible partition.
            tempList.pop_back();
        }
    }
}

vector<vector<string>> partition(string s)
{
    int n = s.size();

    vector<vector<string>> result;
    vector<string> tempList;

    recursivePalindromePartition(0, s, n, result, tempList);

    return result;
}

int main()
{
    string s = "aabaabaabbbaaababaaa";

    vector<vector<string>> result = partition(s);

    for (const auto &partition : result)
    {
        for (const auto &str : partition)
        {
            cout << str << " ";
        }

        cout << endl;
    }

    return 0;
}