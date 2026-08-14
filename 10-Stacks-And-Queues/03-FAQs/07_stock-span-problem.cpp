// Problem:
// Given stock prices for n days, find the stock span for every day.
// The span is the number of consecutive previous days, including the current day, whose prices are less than or equal to the current day's price.

#include <bits/stdc++.h>
using namespace std;

// =============================================================
// BRUTE FORCE APPROACH
//
// Idea:
// For every day, traverse backwards until a previous day with a greater price is found. The number of consecutive days traversed is the span.
//
// Time Complexity:
// O(N^2), where N is the number of days.
//
// Space Complexity:
// O(N), for storing the result array.
//
// =============================================================

// vector<int> stockSpan(vector<int> arr, int n)
// {
//     if (n == 0)
//         return {};

//     vector<int> result;

//     for (int i = 0; i < n; i++)
//     {
//         int count = 0;

//         for (int j = i; j >= 0; j--)
//         {
//             if (arr[j] <= arr[i])
//                 count++;
//             else
//                 break;
//         }

//         result.emplace_back(count);
//     }

//     return result;
// }

// =============================================================
// OPTIMAL APPROACH
//
// Idea:
// For every day, find the index of the nearest previous greater element using a monotonic decreasing stack. The span is the distance between the current index and that previous greater element.
//
// Time Complexity:
// O(N), where each element is pushed and popped from the stack once.
//
// Space Complexity:
// O(N), for the stack, PGE array, and result array.
//
// =============================================================

vector<int> findPGE(vector<int> arr, int n)
{
    stack<int> st;

    vector<int> result(n);

    for (int i = 0; i < n; i++)
    {
        // Remove previous elements that cannot be the nearest greater element.
        while (!st.empty() && arr[st.top()] <= arr[i])
        {
            st.pop();
        }

        // Store the nearest previous greater element index.
        result[i] = st.empty() ? -1 : st.top();

        st.push(i);
    }

    return result;
}

vector<int> stockSpan(vector<int> arr, int n)
{
    if (n == 0)
        return {};

    vector<int> PGE = findPGE(arr, n);

    vector<int> result(n);

    for (int i = 0; i < n; i++)
    {
        // If no previous greater element exists, PGE[i] = -1, so the span includes all days from index 0 to i.
        result[i] = i - PGE[i];
    }

    return result;
}

int main()
{
    int n = 8;
    vector<int> arr = {30, 20, 25, 28, 27, 29, 35, 40};

    vector<int> ans = stockSpan(arr, n);

    cout << "The span of stock prices is: ";
    for (int i = 0; i < n; i++)
    {
        cout << ans[i] << " ";
    }

    return 0;
}