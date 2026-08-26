// Given an integer array nums and a non-negative integer k, rotate the array to the left by k steps.

#include <bits/stdc++.h>
using namespace std;

// ============ BRUTE FORCE (Use Temp Array) ============
// void rotateArray(vector<int> &nums, int k)
// {
//     int N = nums.size();

//     k = k % N;

//     vector<int> temp;

//     for (int i = 0; i < k; i++)
//         temp.emplace_back(nums[i]);

//     for (int i = k; i < N; i++)
//         nums[i - k] = nums[i];

//     for (int i = 0; i < k; i++)
//         nums[N - k + i] = temp[i];
// }

// ============ OPTIMAL (Reverse 3 times) ============
void reverse(vector<int> &nums, int start, int end)
{
    while (start < end)
    {
        swap(nums[start], nums[end]);
        start++, end--;
    }
}
void rotateArray(vector<int> &nums, int k)
{
    int N = nums.size();

    k = k % N;

    reverse(nums, 0, k - 1);
    reverse(nums, k, N - 1);
    reverse(nums, 0, N - 1);
}

int main()
{
    int size;
    cin >> size;

    vector<int> nums(size);

    for (int i = 0; i < size; i++)
        cin >> nums[i];

    int k;
    cin >> k;

    cout << "Before " << k << " rotation: ";
    for (int it : nums)
        cout << it << " ";
    cout << endl;

    rotateArray(nums, k);

    cout << "After " << k << " rotation: ";
    for (int it : nums)
        cout << it << " ";
    cout << endl;

    return 0;
}