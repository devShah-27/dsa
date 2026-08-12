// Problem:
// Given an array and a sliding window of size k, find the maximum element in every window as it moves from left to right across the array.

#include <bits/stdc++.h>
using namespace std;

// =============================================================
// BRUTE FORCE APPROACH
//
// Idea:
// For every possible window of size k, traverse all elements inside the window and calculate the maximum element.
//
// Time Complexity:
// O((N-K+1)*K), where N is the size of the array.
//
// Space Complexity:
// O(N-K+1), for storing the result array.
//
// =============================================================

// vector<int> maxSlidingWindow(vector<int> &arr, int k)
// {
//     int n = arr.size();
//     vector<int> res;

//     for (int i = 0; i <= n - k; i++)
//     {
//         int maxi = INT_MIN;

//         for (int j = i; j < i + k; j++)
//         {
//             maxi = max(maxi, arr[j]);
//         }

//         res.emplace_back(maxi);
//     }

//     return res;
// }

// =============================================================
// OPTIMAL APPROACH
//
// Idea:
// Use a monotonic decreasing deque to store indices of useful elements.
// The front of the deque always contains the index of the maximum element in the current window. Remove smaller elements from the back because they can never become the maximum for future windows.
//
// Time Complexity:
// O(N), where each element is added and removed from the deque once.
//
// Space Complexity:
// O(K), for storing indices in the deque.
//
// =============================================================

vector<int> maxSlidingWindow(vector<int> &arr, int k)
{
    int n = arr.size();
    vector<int> res;

    deque<int> dQ;

    for (int i = 0; i < n; i++)
    {
        // Remove elements that are outside the current window.
        if (!dQ.empty() && dQ.front() <= i - k)
        {
            dQ.pop_front();
        }

        // Maintain decreasing order in deque.
        while (!dQ.empty() && arr[dQ.back()] <= arr[i])
        {
            dQ.pop_back();
        }

        dQ.push_back(i);

        // Start recording answers once the first complete window is formed.
        if (i >= k - 1)
            res.emplace_back(arr[dQ.front()]);
    }

    return res;
}

int main()
{
    vector<int> arr = {4, 0, -1, 3, 5, 3, 6, 8};
    int k = 3;

    vector<int> ans = maxSlidingWindow(arr, k);

    cout << "The maximum elements in the sliding window are: ";
    for (int i = 0; i < ans.size(); i++)
    {
        cout << ans[i] << " ";
    }

    return 0;
}