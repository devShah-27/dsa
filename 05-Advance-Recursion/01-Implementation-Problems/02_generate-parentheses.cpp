// Given an integer n.Generate all possible combinations of well-formed parentheses of length 2 x N.

#include <bits/stdc++.h>
using namespace std;

void recursiveGeneratePrentheses(int index, string paraStr, int open, int close, vector<string> &ansList, int n)
{
    if (open > n)
        return;

    if (open + close == 2 * n && open == close)
    {
        ansList.push_back(paraStr);
        return;
    }

    // Explore the opening bracket path
    recursiveGeneratePrentheses(index + 1, paraStr + '(', open + 1, close, ansList, n);

    // If after exploring opening bracket paths we still have space, explore the closing bracket path
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