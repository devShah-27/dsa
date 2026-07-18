// Problem:
// Given two integers k and n, find all possible combinations of k unique numbers from 1 to 9 whose sum is equal to n.
// Each number can be selected only once, and duplicate combinations are not allowed.

#include <bits/stdc++.h>
using namespace std;

// ============================================================================
// BACKTRACKING APPROACH
//
// Idea:
// Generate combinations by deciding whether to pick or skip each number from 1 to 9.
// Picked numbers are moved forward using currNum + 1 to ensure every number is used at most once and combinations are generated without duplicates.
//
// Time Complexity: O(2^9)
// Space Complexity: O(k) due to recursion stack excluding output storage
// ============================================================================

void recursiveCombinationSum3(int currNum, vector<int> &tempList, vector<vector<int>> &result, int k, int n, int sum)
{
    // A valid combination is found when exactly k numbers form the target sum.
    if (sum == n && tempList.size() == k)
    {
        result.push_back(tempList);
        return;
    }

    // Stop exploring invalid paths.
    if (sum > n || currNum > 9)
        return;

    // Choice 1: Include the current number.
    tempList.push_back(currNum);
    sum += currNum;

    recursiveCombinationSum3(currNum + 1, tempList, result, k, n, sum);

    // Backtrack after exploring the include choice.
    tempList.pop_back();
    sum -= currNum;

    // Choice 2: Exclude the current number.
    recursiveCombinationSum3(currNum + 1, tempList, result, k, n, sum);
}

vector<vector<int>> combinationSum3(int k, int n)
{
    vector<vector<int>> result;
    vector<int> tempList;

    recursiveCombinationSum3(1, tempList, result, k, n, 0);

    return result;
}

int main()
{
    int k = 3; // Number of elements in the combination
    int n = 7; // Target sum

    vector<vector<int>> result = combinationSum3(k, n);

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