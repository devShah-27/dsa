// Given two sorted arrays, nums1 and nums2, return an array containing the intersection of these two arrays. Each element in the result must appear as many times as it appears in both arrays; that is, if an element appears x times in nums1 and y times in nums2, it should appear min(x, y) times in the result.

// The intersection of two arrays is an array where all values are present in both arrays.

#include <bits/stdc++.h>
using namespace std;

// ============== BRUTE FORCE (For every element of nums1, check nums2) ==============
vector<int> intersectionArray(vector<int> &nums1, vector<int> &nums2)
{
    int n1 = nums1.size(), n2 = nums2.size();

    vector<int> intersectionArr;

    vector<int> visited(n2, 0);

    for (int i = 0; i < n1; i++)
    {
        for (int j = 0; j < n2; j++)
        {
            if (nums1[i] == nums2[j] && visited[j] == 0)
            {
                visited[j] = 1;
                intersectionArr.emplace_back(nums1[i]);
                break;
            }
            else if (nums2[j] > nums1[i])
                break;
        }
    }

    return intersectionArr;
}

// ============= OPTIMAL (2-pointer Approach) =============
// vector<int> intersectionArray(vector<int> &nums1, vector<int> &nums2)
// {
//     int n1 = nums1.size(), n2 = nums2.size(), i = 0, j = 0;

//     vector<int> intersectionArr;

//     while (i < n1 && j < n2)
//     {
//         if (nums1[i] < nums2[j])
//             i++;
//         else if (nums2[j] < nums1[i])
//             j++;
//         else
//         {
//             intersectionArr.emplace_back(nums1[i]);
//             i++, j++;
//         }
//     }

//     return intersectionArr;
// }

int main()
{
    // vector<int> nums1 = {1, 2, 2, 3, 3, 3}, nums2 = {2, 3, 3, 4, 5, 7};
    vector<int> nums1 = {1, 2, 5}, nums2 = {2};

    vector<int> intersectionArr = intersectionArray(nums1, nums2);

    cout << "Array 1: ";
    for (auto it : nums1)
        cout << it << " ";
    cout << endl;

    cout << "Array 2: ";
    for (auto it : nums2)
        cout << it << " ";
    cout << endl;

    cout << "Intersection of Array 1 and Array 2: ";
    for (auto it : intersectionArr)
        cout << it << " ";
    cout << endl;

    return 0;
}