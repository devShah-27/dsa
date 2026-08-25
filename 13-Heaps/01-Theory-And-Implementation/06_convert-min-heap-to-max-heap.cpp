// Problem:
// Given a min-heap in array representation, convert it into a max-heap.
// Return the resulting array. Since multiple valid max-heaps may exist, any correct max-heap is accepted.

#include <bits/stdc++.h>
using namespace std;

// ==================================================
// OPTIMAL APPROACH
// Idea:
// - The array already represents a complete binary tree, so only the heap property needs to be changed.
// - Starting from the last non-leaf node, perform max-heapify down towards the root.
// - Leaf nodes already satisfy the max-heap property and therefore do not need processing.
//
// Time Complexity: O(N)
// Space Complexity: O(log N) due to recursion stack
// ==================================================

void heapify_down(vector<int> &nums, int n, int ind)
{
    int lChild = (2 * ind) + 1, rChild = (2 * ind) + 2, largest = ind;

    if (lChild < n && nums[lChild] > nums[largest])
        largest = lChild;

    if (rChild < n && nums[rChild] > nums[largest])
        largest = rChild;

    if (largest != ind)
    {
        swap(nums[largest], nums[ind]);
        heapify_down(nums, n, largest);
    }
}

vector<int> minToMaxHeap(vector<int> nums)
{
    int n = nums.size();

    for (int i = (n / 2) - 1; i >= 0; i--)
    {
        heapify_down(nums, n, i);
    }

    return nums;
}

int main()
{
    vector<int> nums = {2, 6, 3, 100, 120, 4, 5};

    vector<int> res = minToMaxHeap(nums);

    cout << "Max Heap: ";
    for (int x : res)
        cout << x << " ";
    cout << endl;

    return 0;
}