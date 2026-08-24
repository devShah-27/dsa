// Problem:
// Given an array of integers, convert it in-place into a min-heap.
// A min-heap is a complete binary tree where each parent node contains a value smaller than or equal to its children.
// The heap property should be maintained recursively for all subtrees.

#include <bits/stdc++.h>
using namespace std;

// ==================================================
// OPTIMAL APPROACH
// Idea:
// - Build a min-heap using the bottom-up heap construction approach.
// - Start heapifying from the last non-leaf node and move towards the root.
// - Since leaf nodes are already valid heaps, only internal nodes need heapify down operations.
//
// Time Complexity: O(N)
// Space Complexity: O(log N) due to recursion stack
// ==================================================

void heapify_down(vector<int> &nums, int ind, int n)
{
    // Compare the current node with its children and find the smallest value.
    int lChild = (2 * ind) + 1, rChild = (2 * ind) + 2;

    int smallest = ind;

    if (lChild < n && nums[lChild] < nums[smallest])
        smallest = lChild;

    if (rChild < n && nums[rChild] < nums[smallest])
        smallest = rChild;

    // If the smallest value is not at the current node, swap and continue downwards.
    if (smallest != ind)
    {
        swap(nums[ind], nums[smallest]);
        heapify_down(nums, smallest, n);
    }
}

void buildMinHeap(vector<int> &nums)
{
    int n = nums.size();

    // Start from the last non-leaf node and heapify down each node.
    for (int i = (n / 2) - 1; i >= 0; i--)
    {
        heapify_down(nums, i, n);
    }
}

int main()
{
    vector<int> nums = {6, 5, 2, 7, 1, 7};

    cout << "Input array: ";

    for (int it : nums)
        cout << it << " ";

    buildMinHeap(nums);

    cout << "\nMin-heap array: ";

    for (int it : nums)
        cout << it << " ";

    return 0;
}