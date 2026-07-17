// Given collection of candidate numbers (candidates) and a integer target.Find all unique combinations in candidates where the sum is equal to the target.There can only be one usage of each number in the candidates combination and return the answer in sorted order.

// e.g : The combination [1, 1, 2] and [1, 2, 1] are not unique.

#include <bits/stdc++.h>
using namespace std;

void helperFun(int index, vector<vector<int>> &result, vector<int> &candidates, vector<int> &tempList, int target, int n, int sum)
{
    if (sum == target)
    {
        result.push_back(tempList);
        return;
    }

    if (sum > target || index == n)
        return;

    for (int i = index; i < n; i++)
    {
        if (i > index && candidates[i] == candidates[i - 1])
            continue;

        if (sum + candidates[i] > target)
            break;

        tempList.push_back(candidates[i]);

        helperFun(i + 1, result, candidates, tempList, target, n, sum + candidates[i]);

        tempList.pop_back();
    }
}

vector<vector<int>> combinationSum2(vector<int> &candidates, int target)
{
    int n = candidates.size();

    vector<vector<int>> result;

    vector<int> tempList;

    sort(candidates.begin(), candidates.end());

    helperFun(0, result, candidates, tempList, target, n, 0);

    return result;
}

int main()
{
    vector<int> candidates = {10, 1, 2, 7, 6, 1, 5};
    int target = 8;

    vector<vector<int>> result = combinationSum2(candidates, target);

    cout << "Combinations are: " << endl;
    for (const auto &combination : result)
    {
        for (int num : combination)
        {
            cout << num << " ";
        }
        cout << endl;
    }
    return 0;
}