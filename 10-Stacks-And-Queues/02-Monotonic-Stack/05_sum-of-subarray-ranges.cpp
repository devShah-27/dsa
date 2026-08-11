// Problem:
// Given an integer array, find the sum of ranges of all contiguous subarrays.
// The range of a subarray is the difference between its maximum and minimum elements.

#include <bits/stdc++.h>
using namespace std;

// =============================================================
// BRUTE FORCE APPROACH
//
// Idea:
// Generate every possible subarray while maintaining the minimum and
// maximum element. Add the difference between maximum and minimum
// for each subarray.
//
// Time Complexity:
// O(N^2), where N is the size of the array.
//
// Space Complexity:
// O(1), excluding the input array.
//
// =============================================================

// long long subArrayRanges(vector<int> &nums)
// {
//     int n = nums.size();

//     long long sum = 0;

//     for (int i = 0; i < n; i++)
//     {
//         long long mini = INT_MAX, maxi = INT_MIN;

//         for (int j = i; j < n; j++)
//         {
//             mini = min(mini, (nums[j] * 1LL));
//             maxi = max(maxi, (nums[j] * 1LL));

//             sum += (maxi - mini);
//         }
//     }

//     return sum;
// }

// =============================================================
// OPTIMAL APPROACH
//
// Idea:
// The range of every subarray can be represented as:
// Sum of all subarray maximums - Sum of all subarray minimums.
//
// Use monotonic stacks to find how many subarrays each element contributes
// as the maximum and minimum element.
//
// Time Complexity:
// O(N), where each element is pushed and popped from the stacks once.
//
// Space Complexity:
// O(N), for storing boundary indices and stack space.
//
// =============================================================

// Finds the next greater element index for every element.
vector<int> findNextGreaterIndex(vector<int> &nums, int n)
{
    vector<int> result(n);
    stack<int> st;

    for (int i = n - 1; i >= 0; i--)
    {
        while (!st.empty() && nums[st.top()] <= nums[i])
        {
            st.pop();
        }

        result[i] = st.empty() ? n : st.top();

        st.push(i);
    }

    return result;
}

// Finds the previous greater or equal element index for every element.
vector<int> findPreviousGreaterEqualIndex(vector<int> &nums, int n)
{
    vector<int> result(n);
    stack<int> st;

    for (int i = 0; i < n; i++)
    {
        while (!st.empty() && nums[st.top()] < nums[i])
        {
            st.pop();
        }

        result[i] = st.empty() ? -1 : st.top();

        st.push(i);
    }

    return result;
}

// Calculates the contribution of every element as the maximum element.
long long sumOfSubarrayMax(vector<int> &nums, int n)
{
    long long sum = 0;

    vector<int> nge = findNextGreaterIndex(nums, n);
    vector<int> pgee = findPreviousGreaterEqualIndex(nums, n);

    for (int i = 0; i < n; i++)
    {
        int left = i - pgee[i];
        int right = nge[i] - i;

        sum += 1LL * left * right * nums[i];
    }

    return sum;
}

// Finds the next smaller element index for every element.
vector<int> findNextSmallerIndex(vector<int> &nums, int n)
{
    vector<int> result(n);
    stack<int> st;

    for (int i = n - 1; i >= 0; i--)
    {
        while (!st.empty() && nums[st.top()] >= nums[i])
        {
            st.pop();
        }

        result[i] = st.empty() ? n : st.top();

        st.push(i);
    }

    return result;
}

// Finds the previous smaller or equal element index for every element.
vector<int> findPreviousSmallerEqualIndex(vector<int> &nums, int n)
{
    vector<int> result(n);
    stack<int> st;

    for (int i = 0; i < n; i++)
    {
        while (!st.empty() && nums[st.top()] > nums[i])
        {
            st.pop();
        }

        result[i] = st.empty() ? -1 : st.top();

        st.push(i);
    }

    return result;
}

// Calculates the contribution of every element as the minimum element.
long long sumOfSubarrayMin(vector<int> &nums, int n)
{
    long long sum = 0;

    vector<int> nse = findNextSmallerIndex(nums, n);
    vector<int> psee = findPreviousSmallerEqualIndex(nums, n);

    for (int i = 0; i < n; i++)
    {
        int left = i - psee[i];
        int right = nse[i] - i;

        sum += 1LL * left * right * nums[i];
    }

    return sum;
}

long long subArrayRanges(vector<int> &nums)
{
    int n = nums.size();

    return sumOfSubarrayMax(nums, n) - sumOfSubarrayMin(nums, n);
}

int main()
{
    vector<int> arr = {1, 2, 3};

    long long ans = subArrayRanges(arr);

    cout << "The sum of subarray ranges is: " << ans;

    return 0;
}