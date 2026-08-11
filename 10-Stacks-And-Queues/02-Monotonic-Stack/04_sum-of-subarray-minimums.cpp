// Problem:
// Given an integer array, find the sum of the minimum element of every contiguous subarray. Return the answer modulo 10^9 + 7.

#include <bits/stdc++.h>
using namespace std;

// =============================================================
// BRUTE FORCE APPROACH
//
// Idea:
// Generate every possible subarray and keep track of the minimum element while expanding the subarray. Add each minimum to the answer.
//
// Time Complexity:
// O(N^2), where N is the size of the array.
//
// Space Complexity:
// O(1), excluding the input array.
//
// =============================================================

// int sumSubarrayMins(vector<int> &arr)
// {
//     int n = arr.size(), sum = 0, mod = 1e9 + 7;

//     for (int i = 0; i < n; i++)
//     {
//         int mini = arr[i];

//         for (int j = i; j < n; j++)
//         {
//             mini = min(mini, arr[j]);
//             sum = (sum + mini) % mod;
//         }
//     }

//     return sum;
// }

// =============================================================
// OPTIMAL APPROACH
//
// Idea:
// For every element, calculate the number of subarrays where it acts as the minimum element. Use monotonic stacks to find the nearest smaller element on the left and right boundaries.
//
// Time Complexity:
// O(N), where each element is pushed and popped from the stack once.
//
// Space Complexity:
// O(N), for storing NSE, PSEE arrays, and stack space.
//
// =============================================================

// Finds the Next Smaller Element index for every element.
vector<int> findNSE(vector<int> &arr, int n)
{
    vector<int> result(n);
    stack<int> st;

    for (int i = n - 1; i >= 0; i--)
    {
        while (!st.empty() && arr[st.top()] >= arr[i])
        {
            st.pop();
        }

        result[i] = st.empty() ? n : st.top();

        st.push(i);
    }

    return result;
}

// Finds the Previous Smaller or Equal Element index for every element.
vector<int> findPSEE(vector<int> &arr, int n)
{
    vector<int> result(n);
    stack<int> st;

    for (int i = 0; i < n; i++)
    {
        while (!st.empty() && arr[st.top()] > arr[i])
        {
            st.pop();
        }

        result[i] = st.empty() ? -1 : st.top();

        st.push(i);
    }

    return result;
}

int sumSubarrayMins(vector<int> &arr)
{
    int n = arr.size();

    vector<int> nse = findNSE(arr, n);
    vector<int> psee = findPSEE(arr, n);

    int total = 0, mod = 1e9 + 7;

    for (int i = 0; i < n; i++)
    {
        // Number of choices for left and right boundaries where arr[i] remains the minimum element.
        int left = i - psee[i];
        int right = nse[i] - i;

        total = (total + (left * right * 1LL * arr[i]) % mod) % mod;
    }

    return total;
}

int main()
{
    vector<int> arr = {11, 81, 94, 43, 3};

    int ans = sumSubarrayMins(arr);

    cout << "The sum of minimum value in each subarray is: " << ans;

    return 0;
}