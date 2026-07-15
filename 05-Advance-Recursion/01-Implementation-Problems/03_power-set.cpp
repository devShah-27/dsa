// Given an array of integers nums of unique elements. Return all possible subsets (power set) of the array.

// Do not include the duplicates in the answer.

#include <bits/stdc++.h>
using namespace std;

// Recursion Solution
void generatePowerSet(vector<int> &nums, int index, vector<int> subsequence, vector<vector<int>> &ans, int n) // TC -> O(2ⁿ), SC -> O(n*2ⁿ)
{
    if (index == n)
    {
        ans.push_back(subsequence);
        return;
    }

    subsequence.push_back(nums[index]);
    generatePowerSet(nums, index + 1, subsequence, ans, n);
    subsequence.pop_back();

    generatePowerSet(nums, index + 1, subsequence, ans, n);
}

vector<vector<int>> powerSet(vector<int> &nums)
{
    vector<vector<int>> ans;

    int n = nums.size();

    generatePowerSet(nums, 0, {}, ans, n);

    return ans;
}

int main()
{
    vector<int> nums = {1, 2, 3};
    vector<vector<int>> result = powerSet(nums);

    for (const auto &subset : result)
    {
        cout << "[";
        for (int num : subset)
        {
            cout << num << " ";
        }
        cout << "]" << endl;
    }

    return 0;
}
