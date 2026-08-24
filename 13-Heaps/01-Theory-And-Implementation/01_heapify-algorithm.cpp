// Problem:
// Given a min-heap array, update the value at a given index with a new value.
// Restore the min-heap property after modification by performing the required heapify operation.
// The modification should be done in-place without returning anything.

#include <bits/stdc++.h>
using namespace std;

// ==================================================
// OPTIMAL APPROACH
// Idea:
// Replace the value at the given index and determine the direction of heap violation.
// If the new value is greater than the previous value, the node may violate the heap property with its children,
// so perform heapify down. Otherwise, move the node upwards using heapify up.
//
// Time Complexity: O(log N)
// Space Complexity: O(log N) due to recursion stack
// ==================================================

void heapify_down(vector<int> &nums, int n, int ind)
{
    int lChild = (2 * ind) + 1, rChild = (2 * ind) + 2;
    int smallest = ind;

    if (lChild < n && nums[lChild] < nums[smallest])
        smallest = lChild;

    if (rChild < n && nums[rChild] < nums[smallest])
        smallest = rChild;

    if (smallest != ind)
    {
        swap(nums[ind], nums[smallest]);
        heapify_down(nums, n, smallest);
    }
}

void heapify_up(vector<int> &nums, int n, int ind)
{
    int parent = (ind - 1) / 2;

    if (ind != 0)
    {
        if (nums[ind] < nums[parent])
        {
            swap(nums[ind], nums[parent]);
            heapify_up(nums, n, parent);
        }
    }
}

void heapify(vector<int> &nums, int ind, int val)
{
    int n = nums.size();

    if (nums[ind] < val)
    {
        nums[ind] = val;
        heapify_down(nums, n, ind);
    }
    else
    {
        nums[ind] = val;
        heapify_up(nums, n, ind);
    }
}

int main()
{
    vector<int> nums = {1, 4, 5, 5, 7, 6};
    int ind = 5, val = 2;

    cout << "Input array: ";
    for (int it : nums)
        cout << it << " ";

    heapify(nums, ind, val);

    cout << "\nModified array after heapifying: ";
    for (int it : nums)
        cout << it << " ";

    return 0;
}