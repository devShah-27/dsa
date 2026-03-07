// Given an integer array nums, return a list of all the leaders in the array.

// A leader in an array is an element whose value is strictly greater than all elements to its right in the given array. The rightmost element is always a leader. The elements in the leader array must appear in the order they appear in the nums array.

#include <bits/stdc++.h>
using namespace std;

// =========== BRUTE FORCE (Use 2 loops) ===========
// vector<int> leaders(vector<int> &nums) // TC -> O(N^2), SC -> O(1)
// {
//     int n = nums.size();

//     vector<int> ans; // SC -> O(No. of leaders) only used to return the answer.

//     for (int i = 0; i < n; i++) // O(N)
//     {
//         bool leader = true;

//         for (int j = i + 1; j < n; j++) // O(N)
//         {
//             if (nums[j] > nums[i])
//             {
//                 leader = false;
//                 break;
//             }
//         }

//         if (leader)
//             ans.emplace_back(nums[i]);
//     }

//     return ans;
// }

// =========== OPTIMAL (Back Iteration) ===========
vector<int> leaders(vector<int> &nums) // TC -> O(N), SC -> O(1)
{
    int n = nums.size();

    vector<int> ans; // SC -> O(No. of leaders) only used to return the answer.

    int max = INT_MIN;

    for (int i = n - 1; i >= 0; i--) // O(N)
    {
        if (nums[i] > max)
        {
            max = nums[i];
            ans.emplace_back(nums[i]);
        }
    }

    // Perform the following only if order has to be maintained as in given array.
    int left = 0, right = ans.size() - 1;

    while (left < right) // O(N)
    {
        swap(ans[left], ans[right]);
        left++, right--;
    }

    return ans;
}

int main()
{
    vector<int> nums = {10, 22, 12, 3, 0, 6};

    vector<int> ans = leaders(nums);

    cout << "Leaders in given array: ";
    for (int it : ans)
        cout << it << " ";

    return 0;
}