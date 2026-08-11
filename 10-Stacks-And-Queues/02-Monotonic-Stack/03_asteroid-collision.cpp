// Problem:
// Given an array of asteroids moving in a line, determine the final state after all collisions. Positive values move right and negative values move left.

#include <bits/stdc++.h>
using namespace std;

// =============================================================
// OPTIMAL APPROACH
//
// Idea:
// Use a stack to simulate asteroid collisions from left to right.
// Only a left-moving asteroid can collide with a previous right-moving asteroid. Resolve collisions until the current asteroid survives or is destroyed.
//
// Time Complexity:
// O(N), where each asteroid is pushed and popped from the stack at most once.
//
// Space Complexity:
// O(N), for storing the surviving asteroids.
//
// =============================================================

vector<int> asteroidCollision(vector<int> &asteroids)
{
    int n = asteroids.size();
    vector<int> st;

    for (int i = 0; i < n; i++)
    {
        if (asteroids[i] > 0)
        {
            st.emplace_back(asteroids[i]);
        }
        else
        {
            while (!st.empty() && st.back() > 0 && st.back() < abs(asteroids[i]))
            {
                st.pop_back();
            }

            if (!st.empty() && st.back() == abs(asteroids[i]))
            {
                st.pop_back();
            }
            else if (st.empty() || st.back() < 0)
            {
                st.emplace_back(asteroids[i]);
            }
        }
    }

    return st;
}

int main()
{
    vector<int> arr = {10, 20, -10};

    vector<int> ans = asteroidCollision(arr);

    cout << "The state of asteroids after collisions is: ";
    for (int i = 0; i < ans.size(); i++)
    {
        cout << ans[i] << " ";
    }

    return 0;
}