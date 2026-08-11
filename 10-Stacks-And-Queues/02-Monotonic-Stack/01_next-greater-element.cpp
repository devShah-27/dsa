// Problem:
// Given an array, find the next greater element for every element.
// The next greater element is the nearest element on the right that is greater than the current element. Return -1 if no such element exists.

#include <bits/stdc++.h>
using namespace std;

// =============================================================
// BRUTE FORCE APPROACH
//
// Idea:
// For every element, traverse all elements to its right until a greater element is found. If no greater element exists, store -1.
//
// Time Complexity:
// O(N^2), where N is the size of the array.
//
// Space Complexity:
// O(N), for storing the result array.
//
// =============================================================

// vector<int> nextLargerElement(vector<int> arr)
// {
//     int n = arr.size();
//     vector<int> result;

//     for (int i = 0; i < n; i++)
//     {
//         int greaterElem = -1;

//         for (int j = i + 1; j < n; j++)
//         {
//             if (arr[j] > arr[i])
//             {
//                 greaterElem = arr[j];
//                 break;
//             }
//         }

//         result.emplace_back(greaterElem);
//     }

//     return result;
// }

// =============================================================
// OPTIMAL APPROACH
//
// Idea:
// Traverse the array from right to left and maintain a monotonic stack containing possible next greater elements. Remove all elements from the stack that cannot be the answer for the current element.
//
// Time Complexity:
// O(N), where each element is pushed and popped from the stack once.
//
// Space Complexity:
// O(N), for the stack and result array.
//
// =============================================================

vector<int> nextLargerElement(vector<int> arr)
{
    int n = arr.size();
    vector<int> result(n);

    stack<int> st;

    for (int i = n - 1; i >= 0; i--)
    {
        while (!st.empty() && st.top() <= arr[i])
        {
            st.pop();
        }

        if (st.empty())
            result[i] = -1;
        else
            result[i] = st.top();

        st.push(arr[i]);
    }

    return result;
}

int main()
{
    int n = 4;
    vector<int> arr = {1, 3, 2, 4};

    vector<int> ans = nextLargerElement(arr);

    cout << "The next greater elements are: ";
    for (int i = 0; i < n; i++)
    {
        cout << ans[i] << " ";
    }

    return 0;
}