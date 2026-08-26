// Problem:
// Given an integer n, generate all possible combinations of well-formed parentheses.
// Each combination should contain exactly n opening and n closing parentheses.

#include <bits/stdc++.h>
using namespace std;

// ============================================================================
// BACKTRACKING APPROACH
//
// Idea:
// Build the parentheses string character by character using recursion.
// An opening bracket can be added until we have placed n opening brackets.
// A closing bracket can be added only when it does not exceed the number of opening brackets already placed, ensuring the string remains valid.
//
// Time Complexity: O((4^n) / sqrt(n)) - Catalan number of valid combinations
// Space Complexity: O(n) excluding output storage due to recursion stack
// ============================================================================

void recursiveGeneratePrentheses(int index, string paraStr, int open, int close, vector<string> &ansList, int n)
{
    // Stop recursion if invalid state is reached.
    if (open > n)
        return;

    // A valid combination is formed when n pairs of parentheses are placed.
    if (open + close == 2 * n && open == close)
    {
        ansList.push_back(paraStr);
        return;
    }

    // Choice 1: Add an opening bracket if available.
    recursiveGeneratePrentheses(index + 1, paraStr + '(', open + 1, close, ansList, n);

    // Choice 2: Add a closing bracket only when there are unmatched opening brackets.
    if (open > close)
        recursiveGeneratePrentheses(index + 1, paraStr + ')', open, close + 1, ansList, n);
}

vector<string> generateParenthesis(int n)
{
    vector<string> ansList;

    recursiveGeneratePrentheses(1, "", 0, 0, ansList, n);

    return ansList;
}

int main()
{
    int n = 10;

    vector<string> result = generateParenthesis(n);

    cout << "All combinations of balanced parentheses for n = " << n << " are:" << endl;

    for (const string &combination : result)
    {
        cout << combination << endl;
    }

    return 0;
}