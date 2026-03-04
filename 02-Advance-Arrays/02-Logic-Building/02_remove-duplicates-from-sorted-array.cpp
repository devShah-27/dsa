// Given an integer array nums sorted in non-decreasing order, remove all duplicates in-place so that each unique element appears only once.

// Return the number of unique elements in the array.

// If the number of unique elements be k, then,
// - Change the array nums such that the first k elements of nums contain the unique values in the order that they were present originally.
// - The remaining elements, as well as the size of the array does not matter in terms of correctness.
// - The driver code will assess correctness by printing and checking only the first k elements of the modified array.

#include <bits/stdc++.h>
using namespace std;

// ============= BRUTE FORCE (Use a data structure like set to store unique elements) =============
// int removeDuplicates(vector<int> &nums)
// {
//     int N = nums.size();

//     set<int> st;

//     for (int i = 0; i < N; i++)
//         st.insert(nums[i]);

//     int index = 0;

//     for (auto it : st)
//     {
//         nums[index] = it;
//         index++;
//     }

//     for (int i = index; i < N; i++)
//         nums[i] = 0;

//     return index;
// }

// ============= OPTIMAL (2-pointer Approach) =============
int removeDuplicates(vector<int> &nums)
{
    int N = nums.size();

    int uniqueIndex = 0;

    for (int i = 0; i < N; i++)
    {
        if (nums[i] != nums[uniqueIndex])
        {
            nums[uniqueIndex + 1] = nums[i];
            uniqueIndex++;
        }
    }

    for (int i = uniqueIndex + 1; i < N; i++)
        nums[i] = 0;

    return (uniqueIndex + 1);
}

int main()
{
    int size;
    cin >> size;

    vector<int> nums(size);

    for (int i = 0; i < size; i++)
        cin >> nums[i];

    cout << "Input Array: ";
    for (int it : nums)
        cout << it << " ";
    cout << endl;

    int uniqueCount = removeDuplicates(nums);

    cout << "Number of unique elements: " << uniqueCount << endl;

    cout << "Array After Removing Duplicates: ";
    for (int it : nums)
        cout << it << " ";
    cout << endl;

    return 0;
}