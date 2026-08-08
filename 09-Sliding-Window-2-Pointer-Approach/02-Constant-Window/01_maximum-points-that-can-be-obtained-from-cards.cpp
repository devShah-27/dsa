// Problem:
// Given N cards arranged in a row, select exactly k cards from either the beginning
// or the end of the row. Return the maximum possible score obtained by summing
// the selected card values.

#include <bits/stdc++.h>
using namespace std;

// ==================================================
// OPTIMAL APPROACH
//
// Idea:
// Initially take all k cards from the left side and calculate their sum.
// Gradually remove cards from the left selection and replace them with cards
// from the right end, checking the maximum score after each possible split.
//
// Time Complexity: O(2K)
// Space Complexity: O(1)
// ==================================================

int maxScore(vector<int> &cardScore, int k)
{
    int n = cardScore.size(), lSum = 0, rSum = 0;

    // Calculate the initial score by taking all k cards from the left.
    for (int i = 0; i < k; i++)
    {
        lSum += cardScore[i];
    }

    if (k == n)
        return lSum;

    int maxSum = lSum, rightPtr = n - 1;

    // Replace left cards one by one with cards from the right.
    for (int i = k - 1; i >= 0; i--)
    {
        lSum -= cardScore[i];

        rSum += cardScore[rightPtr];
        rightPtr--;

        maxSum = max(maxSum, lSum + rSum);
    }

    return maxSum;
}

int main()
{
    vector<int> nums = {1, 2, 3, 4, 5, 6};

    int result = maxScore(nums, 3);

    cout << "The maximum score is:\n";
    cout << result << endl;

    return 0;
}