// Given two sorted arrays nums1 and nums2, return an array that contains the union of these two arrays. The elements in the union must be in ascending order.

// The union of two arrays is an array where all values are distinct and are present in either the first array, the second array, or both.

#include <bits/stdc++.h>
using namespace std;

// ============== BRUTE FORCE (Use an ordered set like data structure for unique elements) ==============
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

// ============= OPTIMAL (2-pointer Approach) =============
vector<int> unionArray(vector<int> &nums1, vector<int> &nums2)
{
    int n1 = nums1.size(), n2 = nums2.size(), i = 0, j = 0;

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

    while (i < n1)
    {
        if (unionArr.size() == 0 || unionArr.back() != nums1[i])
            unionArr.emplace_back(nums1[i]);

        i++;
    }

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
