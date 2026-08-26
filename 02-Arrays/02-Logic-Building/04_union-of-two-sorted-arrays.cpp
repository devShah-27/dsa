// Problem:
// Given two sorted arrays nums1 and nums2, return their union.
//
// The union should contain all distinct elements present
// in either array, and the result must be sorted in ascending order.

#include <bits/stdc++.h>
using namespace std;

// ===================================================
// BRUTE FORCE APPROACH
//
// Idea:
// Insert all elements from both arrays into a set.
// Since a set stores only unique elements in sorted
// order, duplicates are automatically removed.
//
// Finally, copy elements from the set into a result array.
//
// Time Complexity: O((N + M) log(N + M))
// Space Complexity: O(N + M)
// ===================================================

// vector<int> unionArray(vector<int> &nums1, vector<int> &nums2)
// {
//     set<int> st;

//     vector<int> unionArr;

//     for (auto it : nums1)
//         st.insert(it);

//     for (auto it : nums2)
//         st.insert(it);

//     for (auto it : st)
//         unionArr.emplace_back(it);

//     return unionArr;
// }

// ===================================================
// OPTIMAL APPROACH (TWO POINTERS)
//
// Idea:
// Since both arrays are already sorted, use two pointers
// to traverse them simultaneously.
//
// At each step:
// • Compare current elements of both arrays
// • Insert the smaller element into the result (if not duplicate)
// • Move the corresponding pointer
//
// To maintain uniqueness, only insert an element if it is
// different from the last inserted element.
//
// After one array is exhausted, process the remaining elements
// of the other array similarly.
//
// Time Complexity: O(N + M)
// Space Complexity: O(N + M) (for output array)
// ===================================================

vector<int> unionArray(vector<int> &nums1, vector<int> &nums2)
{
    int n1 = nums1.size(), n2 = nums2.size();
    int i = 0, j = 0;

    vector<int> unionArr;

    while (i < n1 && j < n2)
    {
        if (nums1[i] <= nums2[j])
        {
            if (unionArr.size() == 0 || unionArr.back() != nums1[i])
                unionArr.emplace_back(nums1[i]);

            i++;
        }
        else
        {
            if (unionArr.size() == 0 || unionArr.back() != nums2[j])
                unionArr.emplace_back(nums2[j]);

            j++;
        }
    }

    // Process remaining elements of nums1
    while (i < n1)
    {
        if (unionArr.size() == 0 || unionArr.back() != nums1[i])
            unionArr.emplace_back(nums1[i]);

        i++;
    }

    // Process remaining elements of nums2
    while (j < n2)
    {
        if (unionArr.size() == 0 || unionArr.back() != nums2[j])
            unionArr.emplace_back(nums2[j]);

        j++;
    }

    return unionArr;
}

int main()
{
    vector<int> nums1 = {3, 4, 6, 7, 9, 9}, nums2 = {1, 5, 7, 8, 8};

    vector<int> unionArr = unionArray(nums1, nums2);

    cout << "Array 1: ";
    for (auto it : nums1)
        cout << it << " ";
    cout << endl;

    cout << "Array 2: ";
    for (auto it : nums2)
        cout << it << " ";
    cout << endl;

    cout << "Union of Array 1 and Array 2: ";
    for (auto it : unionArr)
        cout << it << " ";
    cout << endl;

    return 0;
}