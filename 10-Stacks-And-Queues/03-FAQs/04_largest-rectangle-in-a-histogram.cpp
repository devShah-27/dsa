// Problem:
// Given histogram bar heights where each bar has width 1, find the area of the largest rectangle that can be formed within the histogram.

#include <bits/stdc++.h>
using namespace std;

// =============================================================
// BRUTE FORCE APPROACH
//
// Idea:
// For every bar, find the nearest smaller element on the left and right.
// These boundaries determine the maximum width for which the current bar can act as the minimum height of the rectangle.
//
// Time Complexity:
// O(5N) -> O(N), where N is the number of bars.
//
// Space Complexity:
// O(4N) -> O(N), for storing NSE, PSE arrays and stack space.
//
// =============================================================

// void findNextSmallestElement(vector<int> &heights, int n, vector<int> &nse)
// {
//     stack<int> st;

//     for (int i = n - 1; i >= 0; i--)
//     {
//         while (!st.empty() && heights[st.top()] >= heights[i])
//             st.pop();

//         nse[i] = st.empty() ? n : st.top();

//         st.push(i);
//     }
// }

// void findPreviousSmallestElement(vector<int> &heights, int n, vector<int> &pse)
// {
//     stack<int> st;

//     for (int i = 0; i < n; i++)
//     {
//         while (!st.empty() && heights[st.top()] >= heights[i])
//             st.pop();

//         pse[i] = st.empty() ? -1 : st.top();

//         st.push(i);
//     }
// }

// int largestRectangleArea(vector<int> &heights)
// {
//     int n = heights.size();

//     if (n == 0)
//         return 0;

//     vector<int> nse(n), pse(n);

//     findNextSmallestElement(heights, n, nse);
//     findPreviousSmallestElement(heights, n, pse);

//     int maxArea = INT_MIN;

//     for (int i = 0; i < n; i++)
//     {
//         // Rectangle area = height of current bar * maximum possible width
//         int area = heights[i] * (nse[i] - pse[i] - 1);

//         maxArea = max(maxArea, area);
//     }

//     return maxArea;
// }

// =============================================================
// OPTIMAL APPROACH
//
// Idea:
// Use a monotonic increasing stack to store indices of bars in increasing height order. When a smaller height is encountered, calculate the maximum rectangle area possible using the bars removed from the stack.
//
// Time Complexity:
// O(N), where every bar is pushed and popped from the stack once.
//
// Space Complexity:
// O(N), for storing indices in the stack.
//
// =============================================================

int largestRectangleArea(vector<int> &heights)
{
    int n = heights.size();

    if (n == 0)
        return 0;

    stack<int> st;

    int maxArea = INT_MIN;

    for (int i = 0; i < n; i++)
    {
        while (!st.empty() && heights[st.top()] > heights[i])
        {
            int element = st.top();
            st.pop();

            int nse = i;
            int pse = st.empty() ? -1 : st.top();

            maxArea = max(maxArea, heights[element] * (nse - pse - 1));
        }

        st.push(i);
    }

    while (!st.empty())
    {
        int nse = n;

        int element = st.top();
        st.pop();

        int pse = st.empty() ? -1 : st.top();

        maxArea = max(maxArea, heights[element] * (nse - pse - 1));
    }

    return maxArea;
}

int main()
{
    vector<int> heights = {2, 1, 5, 6, 2, 3};

    int ans = largestRectangleArea(heights);

    cout << "The largest rectangle area is: " << ans;

    return 0;
}