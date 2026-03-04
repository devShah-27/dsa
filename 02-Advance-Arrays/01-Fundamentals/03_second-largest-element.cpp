// Given an array of integers nums, return the second-largest element in the array. If the second-largest element does not exist, return -1.

#include <bits/stdc++.h>
using namespace std;

// ================ BRUTE FORCE (Sort array and return second largest element) ================
// int secondLargestElement(vector<int> &nums)
// {
//     int n = nums.size();

//     if (n < 2)
//         return -1;

//     sort(nums.begin(), nums.end());

//     int largest = nums[n - 1];

//     for (int i = n - 2; i >= 0; i--)
//     {
//         if (nums[i] < largest)
//             return nums[i];
//     }

//     return -1;
// }

// ================ BETTER (2 passes of array) ================
// int secondLargestElement(vector<int> &nums)
// {
//     int n = nums.size();

//     if (n < 2)
//         return -1;

//     int largest = INT_MIN, secondLargest = INT_MIN;

//     for (int i = 0; i < n; i++)
//     {
//         if (nums[i] > largest)
//             largest = nums[i];
//     }

//     for (int i = 0; i < n; i++)
//     {
//         if (nums[i] > secondLargest && nums[i] != largest)
//             secondLargest = nums[i];
//     }

//     if (secondLargest == INT_MIN)
//         return -1;

//     return secondLargest;
// }

// ================ OPTIMAL (Single pass of array) ================
int secondLargestElement(vector<int> &nums)
{
    int n = nums.size();

    if (n < 2)
        return -1;

    int largest = INT_MIN, secondLargest = INT_MIN;

    for (int i = 0; i < n; i++)
    {
        if (nums[i] > largest)
        {
            secondLargest = largest;
            largest = nums[i];
        }
        else if (nums[i] > secondLargest && nums[i] != largest)
            secondLargest = nums[i];
    }

    if (secondLargest == INT_MIN)
        return -1;

    return secondLargest;
}

int main()
{
    int size;
    cin >> size;

    vector<int> nums(size);

    for (int i = 0; i < size; i++)
        cin >> nums[i];

    int secondLargestElem = secondLargestElement(nums);

    cout << "Second Largest Element in given array: " << secondLargestElem;

    return 0;
}