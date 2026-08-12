// Problem:
// Given a non-negative integer represented as a string, remove exactly k digits to obtain the smallest possible integer. Return "0" if all digits are removed.

#include <bits/stdc++.h>
using namespace std;

// =============================================================
// OPTIMAL APPROACH
//
// Idea:
// Maintain a monotonic increasing stack of digits. For each digit, remove larger preceding digits while removals are available, since placing a smaller digit earlier produces the smallest possible number.
// After the traversal, remove any remaining digits from the end and strip leading zeros from the final result.
//
// Time Complexity:
// O(N), where N is the number of digits. Each digit is pushed and popped once.
//
// Space Complexity:
// O(N), for storing the digits in the stack.
//
// =============================================================

string removeKdigits(string nums, int k)
{
    int n = nums.size();

    if (k == n)
        return "0";

    stack<int> st;

    for (char c : nums)
    {
        while (!st.empty() && k && st.top() > c)
        {
            st.pop();
            k--;
        }

        st.push(c);
    }

    while (k)
    {
        st.pop();
        k--;
    }

    if (st.empty())
        return "0";

    string res = "";

    while (!st.empty())
    {
        res += st.top();
        st.pop();
    }

    while (res.size() != 0 && res.back() == '0')
    {
        res.pop_back();
    }

    if (res.size() == 0)
        return "0";

    reverse(res.begin(), res.end());

    return res;
}

int main()
{
    string nums = "541892";
    int k = 2;

    string ans = removeKdigits(nums, k);

    cout << "The smallest possible integer after removing k digits is: " << ans;

    return 0;
}