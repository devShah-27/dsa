// Problem:
// Design a stack that supports push, pop, top, and retrieving the minimum element in constant time.

#include <bits/stdc++.h>
using namespace std;

// =============================================================
// BRUTE FORCE APPROACH
//
// Idea:
// Store each element along with the minimum value present in the st up to that point. The minimum can be retrieved directly from the top.
//
// Time Complexity:
// push() -> O(1)
// pop() -> O(1)
// top() -> O(1)
// getMin() -> O(1)
//
// Space Complexity:
// O(2N), as each element stores its value and current minimum.
//
// =============================================================

// class MinStack
// {
//     stack<pair<int, int>> st;

// public:
//     void push(int x)
//     {
//         if (st.empty())
//             st.push({x, x});
//         else
//             st.push({x, min(st.top().second, x)});
//     }

//     void pop()
//     {
//         st.pop();
//     }

//     int top()
//     {
//         return st.top().first;
//     }

//     int getMin()
//     {
//         return st.top().second;
//     }
// };

// =============================================================
// OPTIMAL APPROACH
//
// Idea:
// Encode values when a new minimum is inserted to avoid storing an extra minimum value for every element. The encoded value helps restore the previous minimum during pop operations.
//
// Time Complexity:
// push() -> O(1)
// pop() -> O(1)
// top() -> O(1)
// getMin() -> O(1)
//
// Space Complexity:
// O(N), as the stack stores all elements.
//
// =============================================================

class MinStack
{
    stack<int> st;
    int mini = INT_MAX;

public:
    void push(int x)
    {
        if (st.empty())
        {
            st.push(x);
            mini = x;
        }
        else
        {
            if (x > mini)
            {
                st.push(x);
            }
            else
            {
                // Store encoded value to mark that a new minimum is inserted.
                st.push((2 * x) - mini);
                mini = x;
            }
        }
    }

    void pop()
    {
        if (st.empty())
            return;

        int n = st.top();
        st.pop();

        // Restore previous minimum from encoded value.
        if (n < mini)
            mini = (2 * n) - mini;
    }

    int top()
    {
        if (st.empty())
            return -1;

        int n = st.top();

        // Encoded values represent the current minimum.
        if (n < mini)
            return mini;

        return n;
    }

    int getMin()
    {
        return mini;
    }
};

int main()
{
    MinStack s;

    s.push(-2);
    s.push(0);
    s.push(-3);

    cout << s.getMin() << " ";

    s.pop();

    cout << s.top() << " ";

    s.pop();

    cout << s.getMin();

    return 0;
}