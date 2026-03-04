// Given an integer array nums, move all the 0's to the end of the array. The relative order of the other elements must remain the same.

// This must be done in place, without making a copy of the array.

#include <bits/stdc++.h>
using namespace std;

// ============== BRUTE FORCE (Store non-zero elements in temp and place them back) ==============
// void moveZeroes(vector<int> &nums)
// {
//     int N = nums.size();

//     vector<int> temp;

//     for (int i = 0; i < N; i++)
//         if (nums[i] != 0)
//             temp.emplace_back(nums[i]);

//     int X = temp.size();

//     if (X == 0)
//         return;

//     for (int i = 0; i < X; i++)
//         nums[i] = temp[i];

//     for (int i = X; i < N; i++)
//         nums[i] = 0;
// }

// ============== OPTIMAL (2-pointer approach) ==============
void moveZeroes(vector<int> &nums)
{
    int j = 0;

    for (int i = 0; i < nums.size(); i++)
    {
        if (nums[i] != 0)
        {
            swap(nums[i], nums[j]);
            j++;
        }
    }
}

int main()
{
    int size;
    cin >> size;

    vector<int> nums(size);

    for (int i = 0; i < size; i++)
        cin >> nums[i];

    cout << "Before moving zeros: ";
    for (int it : nums)
        cout << it << " ";
    cout << endl;

    moveZeroes(nums);

    cout << "After moving zeros: ";
    for (int it : nums)
        cout << it << " ";
    cout << endl;

    return 0;
}