// Problem:
// Given the ratings of N children standing in a line, distribute candies such that every child gets at least one candy, and any child with a higher rating than an adjacent child receives more candies. Return the minimum candies required.

#include <bits/stdc++.h>
using namespace std;

// ==================================================
// BRUTE FORCE APPROACH
//
// Idea:
// Perform two passes:
// 1. Left to right: ensure every child with a higher rating than the left neighbor
//    gets more candies.
// 2. Right to left: ensure every child with a higher rating than the right neighbor
//    gets more candies.
// The final candy count for each child is the maximum value assigned by the two passes.
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
// During the right-to-left pass, compute the required candies on the fly instead of storing another array, and immediately add the maximum of both requirements to the final answer.
//
// Time Complexity: O(2N)
// Space Complexity: O(N)
// ==================================================

int candy(vector<int> &ratings)
{
    int n = ratings.size();

    vector<int> left(n);

    left[0] = 1;

    for (int i = 1; i < n; i++)
    {
        if (ratings[i] > ratings[i - 1])
            left[i] = left[i - 1] + 1;
        else
            left[i] = 1;
    }

    int current = 1, right = 1;

    int sum = max(left[n - 1], right);

    for (int i = n - 2; i >= 0; i--)
    {
        if (ratings[i] > ratings[i + 1])
        {
            current = right + 1;
            right = current;
        }
        else
        {
            current = 1;
            right = 1;
        }

        sum += max(left[i], current);
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