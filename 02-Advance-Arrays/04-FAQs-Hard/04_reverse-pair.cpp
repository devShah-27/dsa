// Problem:
// Given an integer array nums, return the number of reverse pairs in the array.
//
// A reverse pair is defined as a pair (i, j) such that:
// 0 ≤ i < j < n and nums[i] > 2 * nums[j].

#include <bits/stdc++.h>
using namespace std;

// ================================================================
// BRUTE FORCE APPROACH
//
// Idea:
// For every element nums[i], check all elements to its right.
// If nums[i] > 2 * nums[j], then it forms a reverse pair.
//
// Count all such pairs.
//
// Time Complexity:  O(N²)
// Space Complexity: O(1)
// ================================================================

// int reversePairs(vector<int> &nums)
// {
//     int count = 0, n = nums.size();
//
//     for (int i = 0; i < n; i++)
//     {
//         for (int j = i + 1; j < n; j++)
//         {
//             if (nums[i] > (2 * nums[j]))
//                 count++;
//         }
//     }
//
//     return count;
// }

// ================================================================
// OPTIMAL APPROACH (MERGE SORT BASED)
//
// Idea:
// Use merge sort to divide the array into sorted halves.
// Before merging the halves, count reverse pairs across them.
//
// Key Observation:
// If nums[i] > 2 * nums[j] for a given j, then all further valid elements can be counted using a two-pointer approach.
//
// Time Complexity:  O(N log N)
// Space Complexity: O(N)
// ================================================================

void merge(vector<int> &nums, int low, int mid, int high)
{
    int left = low, right = mid + 1;

    vector<int> temp;

    while (left <= mid && right <= high)
    {
        if (nums[left] < nums[right])
        {
            temp.push_back(nums[left]);
            left++;
        }
        else
        {
            temp.push_back(nums[right]);
            right++;
        }
    }

    while (left <= mid)
    {
        temp.push_back(nums[left]);
        left++;
    }

    while (right <= high)
    {
        temp.push_back(nums[right]);
        right++;
    }

    for (int i = 0; i < temp.size(); i++)
    {
        nums[low + i] = temp[i];
    }
}

int countPairs(vector<int> &nums, int low, int mid, int high)
{
    int right = mid + 1;
    int counter = 0;

    for (int i = low; i <= mid; i++)
    {
        // Written 2LL to avoid integer overflow.
        while (right <= high && nums[i] > (2LL * nums[right]))
            right++;

        counter += right - (mid + 1);
    }

    return counter;
}

int mergeSort(vector<int> &nums, int low, int high)
{
    int count = 0;

    if (low >= high)
        return count;

    int mid = low + (high - low) / 2; // For overflow safety

    count += mergeSort(nums, low, mid);

    count += mergeSort(nums, mid + 1, high);

    count += countPairs(nums, low, mid, high);

    merge(nums, low, mid, high);

    return count;
}

int reversePairs(vector<int> &nums)
{
    return mergeSort(nums, 0, nums.size() - 1);
}

int main()
{
    vector<int> nums = {6, 4, 4, 2, 2};

    cout << "Array: ";
    for (int it : nums)
        cout << it << " ";
    cout << endl;

    int reversePairsCount = reversePairs(nums);

    cout << "No. of reverse pairs: " << reversePairsCount;

    return 0;
}