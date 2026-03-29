// ========================== PROBLEM ==========================
// Given an integer array, return the maximum (largest) element
// present in the array.
// ============================================================

#include <bits/stdc++.h>
using namespace std;

// ========================== BRUTE FORCE APPROACH (SORTING) ==========================
// Idea:
// Sort the array in ascending order and return the last element,
// which will be the largest after sorting.
//
// NOTE: This modifies the original array. If preserving input is required,
// consider using a copy.
//
// Time Complexity: O(N log N)
// Space Complexity: O(1) (ignoring sort recursion stack)
// ====================================================================================
// int largestElement(vector<int> &nums)
// {
//     sort(nums.begin(), nums.end());
//     return nums[nums.size() - 1];
// }

// ========================== OPTIMAL APPROACH ==========================
// Idea:
// Traverse the array once while maintaining a variable to track
// the maximum element seen so far. Update it whenever a larger
// element is found.
//
// Time Complexity: O(N)
// Space Complexity: O(1)
// =========================================================================
int largestElement(vector<int> &nums)
{
    int largestElem = nums[0]; // Assume first element as maximum

    for (int i = 0; i < nums.size(); i++)
    {
        if (nums[i] > largestElem)
            largestElem = nums[i];
    }

    return largestElem;
}

int main()
{
    int size;
    cin >> size;

    vector<int> nums(size);

    // Input array elements
    for (int i = 0; i < size; i++)
        cin >> nums[i];

    cout << "Input array: ";

    for (auto it : nums)
        cout << it << " ";

    cout << endl;

    int largestElem = largestElement(nums);

    cout << "Largest element in array: " << largestElem;

    return 0;
}