// ==================================================
// PROBLEM
// - Given an array representing daily stock prices, find the maximum achievable profit.
// - You can buy and sell at most once, and buying must happen before selling.
// ==================================================

#include <bits/stdc++.h>
using namespace std;

// ==================================================
// OPTIMAL APPROACH (One Pass)
//
// Idea:
// - Track the minimum stock price seen so far while iterating.
// - Calculate potential profit for each day using this minimum.
// - Update maximum profit if the current potential profit is higher.
// - This ensures the buy day always precedes the sell day.
//
// Time Complexity: O(n) - A single traversal of the stock prices array.
// Space Complexity: O(1) - Only constant extra space is used for tracking variables.
// ==================================================

int stockBuySell(const vector<int> &arr, int n)
{
    // Initialize the minimum price to the first day's price and max profit to 0
    int mini = arr[0], maxProfit = 0;

    // Iterate through the stock prices starting from the second day
    for (int i = 1; i < n; i++)
    {
        // Calculate profit if we sold the stock on the current day
        int currProfit = arr[i] - mini;

        // Update the maximum profit achieved so far
        maxProfit = max(maxProfit, currProfit);

        // Update the minimum price seen so far to use for future days
        mini = min(mini, arr[i]);
    }

    return maxProfit;
}

int main()
{
    vector<int> Arr = {7, 1, 5, 3, 6, 4};

    int n = 6;

    cout << "The maximum profit by selling the stock is " << stockBuySell(Arr, n) << endl;

    return 0;
}
