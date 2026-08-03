// Given an array of integers nums of unique elements. Return all possible subsets (power set) of the array.

// Do not include the duplicates in the answer.

#include <bits/stdc++.h>
using namespace std;

vector<vector<int>> powerSet(vector<int> &nums)
{
    int n = nums.size();

    if (n == 0)
        return {{}};

    int subsetCount = (1 << n); // 2^n

    vector<vector<int>> result;

    for (int i = 0; i < subsetCount; i++)
    {
        vector<int> tempList;

        for (int j = 0; j < n; j++)
        {
            if (i & (1 << j))
                tempList.emplace_back(nums[j]);
        }

        result.emplace_back(tempList);
    }

    return result;
}

int main()
{
    vector<int> nums = {1, 2, 3};

    vector<vector<int>> ans = powerSet(nums);

    sort(ans.begin(), ans.end());

    cout << "The power set for the given array is: " << endl;

    for (int i = 0; i < ans.size(); i++)
    {
        for (int j = 0; j < ans[i].size(); j++)
        {
            cout << ans[i][j] << " ";
        }
        cout << endl;
    }

    return 0;
}
