// Problem:
// Given a circular array, find the next greater element for every element.
// The next greater element is the first greater element encountered while traversing the array in a clockwise direction. Return -1 if none exists.

#include <bits/stdc++.h>
using namespace std;

// =============================================================
// BRUTE FORCE APPROACH
//
// Idea:
// For every element, traverse the next N-1 elements using circular indexing. Stop when a greater element is found, otherwise store -1.
//
// Time Complexity:
// O(N^2), where N is the size of the array.
//
// Space Complexity:
// O(N), for storing the result array.
//
// =============================================================

// vector<int> nextGreaterElements(vector<int> &arr)
// {
//     int n = arr.size();
//     vector<int> result(n, -1);

//     for (int i = 0; i < n; i++)
//     {
//         for (int j = i + 1; j < i + n; j++)
//         {
//             int idx = j % n;

//             if (arr[idx] > arr[i])
//             {
//                 result[i] = arr[idx];
//                 break;
//             }
//         }
//     }

//     return result;
// }

// =============================================================
// OPTIMAL APPROACH
//
// Idea:
// Treat the circular array as a duplicated array by traversing it twice.
// Use a monotonic stack to store potential next greater elements while traversing from right to left. Use modulo to simulate circular traversal.
//
// Time Complexity:
// O(2N), where each element is pushed and popped from the stack once.
//
// Space Complexity:
// O(N), for the stack and result array.
//
// =============================================================

vector<int> nextGreaterElements(vector<int> &arr)
{
    int n = arr.size();
    vector<int> result(n, -1);

    stack<int> st;

    for (int i = (2 * n) - 1; i >= 0; i--)
    {
        while (!st.empty() && st.top() <= arr[i % n])
        {
            st.pop();
        }

        if (i < n)
        {
            result[i] = st.empty() ? -1 : st.top();
        }

        st.emplace(arr[i % n]);
    }

    return result;
}

int main()
{
    int n = 6;
    vector<int> arr = {5, 7, 1, 7, 6, 0};

    vector<int> ans = nextGreaterElements(arr);

    cout << "The next greater elements are: ";
    for (int i = 0; i < n; i++)
    {
        cout << ans[i] << " ";
    }

    return 0;
}