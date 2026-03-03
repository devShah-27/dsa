// Given an array of integers nums, return the value of the largest element in the array

#include <bits/stdc++.h>
using namespace std;

// =============== BRUTE FORCE (Sort) ===============
// int largestElement(vector<int> &nums)
// {
//     sort(nums.begin(), nums.end());
//     return nums[nums.size() - 1];
// }

// =============== OPTIMAL ===============
int largestElement(vector<int> &nums)
{
    int largestElem = nums[0];

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

    for (int i = 0; i < size; i++)
        cin >> nums[i];

    int query;
    cin >> query;

    cout << "Input array: ";

    for (auto it : nums)
        cout << it << " ";

    cout << endl;

    int largestElem = largestElement(nums);

    cout << "Largest element in array: " << largestElem;

    return 0;
}
