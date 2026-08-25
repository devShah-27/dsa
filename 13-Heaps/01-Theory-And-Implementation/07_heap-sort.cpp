// Problem:
// Given an array of integers, sort the array in non-decreasing order using Heap Sort.
// The sorting should be performed in-place without returning a new array.

#include <bits/stdc++.h>
using namespace std;

// ==================================================
// OPTIMAL APPROACH
// Idea:
// - First, build a max-heap from the entire array so the largest element is at index 0.
// - Repeatedly move the maximum element to the end of the unsorted portion and restore the max-heap property.
// - The sorted portion grows from right to left, resulting in ascending order.
//
// Time Complexity: O(N log N)
// Space Complexity: O(1)
// ==================================================

void heapify_down(vector<int> &nums, int n, int ind)
{
    int lChild = (2 * ind) + 1, rChild = (2 * ind) + 2, largest = ind;

    if (lChild <= n && nums[lChild] > nums[largest])
        largest = lChild;

    if (rChild <= n && nums[rChild] > nums[largest])
        largest = rChild;

    if (largest != ind)
    {
        swap(nums[ind], nums[largest]);
        heapify_down(nums, n, largest);
    }
}

void max_heapify(vector<int> &nums, int n)
{
    // Build the max-heap bottom-up; leaf nodes already satisfy the heap property.
    for (int i = (n / 2) - 1; i >= 0; i--)
    {
        heapify_down(nums, n - 1, i);
    }
}

void heapSort(vector<int> &nums)
{
    int n = nums.size();

    max_heapify(nums, n);

    int last = n - 1;

    while (last > 0)
    {
        // Move the current maximum to its final sorted position.
        swap(nums[0], nums[last]);

        last--;

        // Restore the max-heap property only within the remaining unsorted portion.
        if (last > 0)
            heapify_down(nums, last, 0);
    }
}

int main()
{
    vector<int> nums = {60, 30, 40, 20, 10, 50};

    cout << "Input Array: ";
    for (int x : nums)
        cout << x << " ";

    heapSort(nums);

    cout << "\nSorted Array: ";
    for (int x : nums)
        cout << x << " ";

    return 0;
}