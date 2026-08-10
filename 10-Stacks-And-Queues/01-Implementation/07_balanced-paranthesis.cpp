// Problem:
// Given a string containing only '(', ')', '{', '}', '[' and ']', determine whether the brackets are balanced and properly nested.

#include <bits/stdc++.h>
using namespace std;

// =============================================================
// OPTIMAL APPROACH
//
// Idea:
// Use a stack to store all opening brackets encountered while traversing the string. 
// For every closing bracket, check whether it matches the most recent opening bracket.
//
// Time Complexity:
// O(N), where N is the length of the string.
//
// Space Complexity:
// O(N), in the worst case when all characters are opening brackets.
//
// =============================================================

bool isValid(string str)
{
    int n = str.size();
    stack<char> st;

    for (char c : str)
    {
        if (c == '(' || c == '[' || c == '{')
        {
            st.push(c);
        }
        else
        {
            if (st.empty())
                return false;

            char topChar = st.top();
            st.pop();

            if (c == ')' && topChar != '(' ||
                c == ']' && topChar != '[' ||
                c == '}' && topChar != '{')
                return false;
        }
    }

    return st.empty();
}

int main()
{
    string str = "()[{}()]";

    bool ans = isValid(str);

    if (ans)
        cout << "The given string is valid.";
    else
        cout << "The given string is invalid.";

    return 0;
}