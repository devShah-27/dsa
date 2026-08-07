// Problem:
// Given the ratings of N children standing in a line, distribute candies such that every child gets at least one candy, and children with higher ratings than their neighbours receive more candies. Return the minimum number of candies required.

#include <bits/stdc++.h>
using namespace std;

// ==================================================
// BRUTE FORCE APPROACH
//
// Idea:
// Perform two passes to calculate candy requirements from both directions:
// 1. Left to right: handle children with higher ratings than their left neighbour.
// 2. Right to left: handle children with higher ratings than their right neighbour.
// Assign each child the maximum candy requirement from both directions.
//
// Time Complexity: O(3N)
// Space Complexity: O(2N)
// ==================================================

// int candy(vector<int> &ratings)
// {
//     int n = ratings.size();

//     vector<int> left(n), right(n);

//     left[0] = 1;
//     right[n - 1] = 1;

//     for (int i = 1; i < n; i++)
//     {
//         if (ratings[i] > ratings[i - 1])
//             left[i] = left[i - 1] + 1;
//         else
//             left[i] = 1;
//     }

//     for (int i = n - 2; i >= 0; i--)
//     {
//         if (ratings[i] > ratings[i + 1])
//             right[i] = right[i + 1] + 1;
//         else
//             right[i] = 1;
//     }

//     int sum = 0;

//     for (int i = 0; i < n; i++)
//     {
//         sum += max(left[i], right[i]);
//     }

//     return sum;
// }

// ==================================================
// BETTER APPROACH
//
// Idea:
// Store the left-to-right candy requirements in an auxiliary array.
// While traversing from right to left, calculate the right-side requirement using a variable instead of another array and add the maximum of both requirements.
//
// Time Complexity: O(2N)
// Space Complexity: O(N)
// ==================================================

// int candy(vector<int> &ratings)
// {
//     int n = ratings.size();

//     vector<int> left(n);

//     left[0] = 1;

//     for (int i = 1; i < n; i++)
//     {
//         if (ratings[i] > ratings[i - 1])
//             left[i] = left[i - 1] + 1;
//         else
//             left[i] = 1;
//     }

//     int current = 1, right = 1;

//     int sum = max(left[n - 1], right);

//     for (int i = n - 2; i >= 0; i--)
//     {
//         if (ratings[i] > ratings[i + 1])
//         {
//             current = right + 1;
//             right = current;
//         }
//         else
//         {
//             current = 1;
//             right = 1;
//         }

//         sum += max(left[i], current);
//     }

//     return sum;
// }

// ==================================================
// OPTIMAL APPROACH
//
// Idea:
// Treat the ratings array as increasing and decreasing slopes.
// Count candies required for increasing and decreasing sequences separately.
// For a decreasing slope after a higher peak, adjust the peak candy count to satisfy both increasing and decreasing constraints.
//
// Time Complexity: O(N)
// Space Complexity: O(1)
// ==================================================

int candy(vector<int> &ratings)
{
    int n = ratings.size();

    int sum = 1;

    int i = 1;

    while (i < n)
    {
        // Handle equal ratings (plateau).
        if (ratings[i] == ratings[i - 1])
        {
            sum += 1;
            i++;
            continue;
        }

        // Count increasing slope.
        int peak = 1;
        while (i < n && ratings[i] > ratings[i - 1])
        {
            peak++;
            sum += peak;
            i++;
        }

        // Count decreasing slope.
        int trough = 1;
        while (i < n && ratings[i] < ratings[i - 1])
        {
            sum += trough;
            trough++;
            i++;
        }

        // Adjust the peak if the decreasing slope is longer.
        if (trough > peak)
            sum += trough - peak;
    }

    return sum;
}

int main()
{
    vector<int> ratings = {1, 0, 2};

    int result = candy(ratings);

    cout << "Minimum candies required: " << result << endl;

    return 0;
}