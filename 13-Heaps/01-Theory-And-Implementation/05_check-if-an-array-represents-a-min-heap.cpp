// Problem:
// Given an array of integers, check whether it represents a binary min-heap.
// Return true if the array satisfies the min-heap property; otherwise, return false.

#include <bits/stdc++.h>
using namespace std;

// ==================================================
// OPTIMAL APPROACH
// Idea:
// - In an array representation of a complete binary tree, every non-leaf node has indices from 0 to (N / 2) - 1.
// - Check each non-leaf node and ensure its value is smaller than or equal to both of its children.
// - If any parent is greater than a child, the min-heap property is violated.
//
// Time Complexity: O(N)
// Space Complexity: O(1)
// ==================================================

bool isHeap(vector<int> &nums)
{
    int n = nums.size();

    // Only non-leaf nodes can violate the heap property.
    for (int i = (n / 2) - 1; i >= 0; i--)
    {
        int parent = i;

        int lChild = (2 * i) + 1;
        int rChild = (2 * i) + 2;

        if (lChild < n && nums[parent] > nums[lChild])
            return false;

        if (rChild < n && nums[parent] > nums[rChild])
            return false;
    }

    return true;
}

int main()
{
    vector<int> nums = {10, 20, 30, 21, 23};

    cout << "Given Array: ";
    for (int x : nums)
        cout << x << " ";

    bool ans = isHeap(nums);

    if (ans)
        cout << "\nThe given array is a min-heap.";
    else
        cout << "\nThe given array is not a min-heap.";

    return 0;
}