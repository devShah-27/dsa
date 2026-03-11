// Problem:
// Given an integer array nums, return the number of inversions in the array.
//
// An inversion is a pair (i, j) such that:
// i < j and nums[i] > nums[j].
//
// Observations:
// - A sorted array has 0 inversions.
// - A reverse sorted array has the maximum number of inversions.
// - Inversion count measures how far the array is from being sorted.

#include <bits/stdc++.h>
using namespace std;

// ================================================================
// BRUTE FORCE APPROACH
//
// Idea:
// For every element nums[i], check all elements to its right.
// If nums[i] > nums[j], then it forms an inversion.
//
// Count all such pairs.
//
// Time Complexity:  O(N²)
// Space Complexity: O(1)
// ================================================================

// long long int numberOfInversions(vector<int> nums)
// {
//     int n = nums.size();
//     int inversionCount = 0;
//
//     for (int i = 0; i < n; i++)
//     {
//         for (int j = i + 1; j < n; j++)
//         {
//             if (nums[i] > nums[j])
//                 inversionCount++;
//         }
//     }
//
//     return inversionCount;
// }

// ================================================================
// OPTIMAL APPROACH (MERGE SORT BASED)
//
// Idea:
// Use the merge sort technique to count inversions while merging.
//
// Key Observation:
// If nums[left] > nums[right], then all elements from nums[left] to nums[mid] will also form inversions with nums[right].
//
// Number of inversions added = (mid - left + 1)
//
// Time Complexity:  O(N log N)
// Space Complexity: O(N)
// ================================================================

long long int merge(vector<int> &nums, int low, int mid, int high)
{
    int left = low;
    int right = mid + 1;

    vector<int> temp;
    long long counter = 0;

    while (left <= mid && right <= high)
    {
        if (nums[left] <= nums[right])
        {
            temp.push_back(nums[left]);
            left++;
        }
        else
        {
            temp.push_back(nums[right]);
            right++;

            counter += mid - left + 1;
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

    return counter;
}

long long int mergeSort(vector<int> &nums, int low, int high)
{
    long long counter = 0;

    if (low >= high)
        return counter;

    int mid = (low + high) / 2;

    counter += mergeSort(nums, low, mid);
    counter += mergeSort(nums, mid + 1, high);

    counter += merge(nums, low, mid, high);

    return counter;
}

long long int numberOfInversions(vector<int> nums)
{
    return mergeSort(nums, 0, nums.size() - 1);
}

int main()
{
    vector<int> nums = {2, 3, 7, 1, 3, 5};

    cout << "Array: ";
    for (int it : nums)
        cout << it << " ";
    cout << endl;

    long long int inversionCount = numberOfInversions(nums);

    cout << "No. of inversions: " << inversionCount;

    return 0;
}