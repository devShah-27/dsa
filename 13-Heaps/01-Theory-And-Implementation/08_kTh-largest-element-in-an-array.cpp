// Problem:
// Given an array nums, return the kth largest element in the array.
// Multiple elements with the same value are treated as separate positions.

#include <bits/stdc++.h>
using namespace std;

// ==================================================
// BRUTE FORCE APPROACH
// Idea:
// - Sort the entire array in descending order.
// - The kth element (0-based index k - 1) is the kth largest element.
//
// Time Complexity: O(N log N)
// Space Complexity: O(log N) auxiliary space for std::sort's recursion stack
// ==================================================

// int kthLargestElement(vector<int> &nums, int k)
// {
//     int n = nums.size();

//     if (k > n)
//         return -1;

//     sort(nums.begin(), nums.end(), greater());

//     return nums[k - 1];
// }

// ==================================================
// BETTER APPROACH
// Idea:
// - Maintain a min-heap containing the k largest elements seen so far.
// - The smallest element among these k elements stays at the heap root.
// - After processing the entire array, the root is the kth largest element.
//
// Time Complexity: O(N log K)
// Space Complexity: O(K)
// ==================================================

// int kthLargestElement(vector<int> &nums, int k)
// {
//     int n = nums.size();

//     if (k > n)
//         return -1;

//     priority_queue<int, vector<int>, greater<int>> pq;

//     // Keep the first k elements in the heap.
//     // The heap will always contain at most k elements.
//     for (int i = 0; i < k; i++)
//     {
//         pq.push(nums[i]);
//     }

//     // Replace the smallest of the current k largest elements when a larger value is found.
//     for (int i = k; i < n; i++)
//     {
//         if (nums[i] > pq.top())
//         {
//             pq.pop();
//             pq.push(nums[i]);
//         }
//     }

//     return pq.top();
// }

// ==================================================
// OPTIMAL APPROACH
// Idea:
// - Use Quickselect to place the pivot at its correct position in descending order.
// - After partitioning:
//   - Elements to the left of the pivot are >= pivot.
//   - Elements to the right of the pivot are <= pivot.
//   - Therefore, if the pivot lands at index k - 1, it is the kth largest element.
// - We only continue Quickselect on the side containing index k - 1 instead of processing both sides.
//
// Average Time Complexity: O(N)
// Worst-Case Time Complexity: O(N^2)
// Space Complexity: O(1) auxiliary space
// ==================================================

int partition(vector<int> &nums, int L, int R)
{
    int P = nums[L];

    int i = L + 1;
    int j = R;

    while (i <= j)
    {
        // Move i while elements are already on the correct side.
        while (i <= R && nums[i] >= P)
        {
            i++;
        }

        // Move j while elements are already on the correct side.
        while (j >= L + 1 && nums[j] <= P)
        {
            j--;
        }

        // If both pointers found elements on the wrong sides,
        // swap them.
        if (i < j)
        {
            swap(nums[i], nums[j]);
        }
    }

    // Place the pivot between the two partitions.
    swap(nums[L], nums[j]);

    return j;
}

int kthLargestElement(vector<int> &nums, int k)
{
    int n = nums.size();

    if (k < 1 || k > n)
        return -1;

    int target = k - 1;

    int L = 0;
    int R = n - 1;

    while (L <= R)
    {
        int pivot_idx = partition(nums, L, R);

        if (pivot_idx == target)
        {
            return nums[pivot_idx];
        }
        else if (pivot_idx > target)
        {
            R = pivot_idx - 1;
        }
        else
        {
            L = pivot_idx + 1;
        }
    }

    return -1;
}

int main()
{
    vector<int> nums = {-5, 4, 1, 2, -3};
    int k = 3;

    int ans = kthLargestElement(nums, k);

    cout << "The Kth largest element in the array is: " << ans << endl;

    return 0;
}