// There is only one row of fruit trees on the farm, oriented left to right. An integer array called fruits represents the trees, where fruits[i] denotes the kind of fruit produced by the ith tree.

// The goal is to gather as much fruit as possible, adhering to the owner's stringent rules:

// 1) There are two baskets available, and each basket can only contain one kind of fruit. The quantity of fruit each basket can contain is unlimited.
// 2) Start at any tree, but as you proceed to the right, select exactly one fruit from each tree, including the starting tree. One of the baskets must hold the harvested fruits.
// 3) Once reaching a tree with fruit that cannot fit into any basket, stop.

// Return the maximum number of fruits that can be picked.

#include <bits/stdc++.h>
using namespace std;

// BRUTE FORCE
// int totalFruits(vector<int> &fruits) // TC -> O(N^2), SC -> O(1)
// {
//     int n = fruits.size(), maxLength = 0;

//     for (int i = 0; i < n; i++)
//     {
//         unordered_set<int> st;

//         for (int j = i; j < n; j++)
//         {
//             st.emplace(fruits[j]);

//             if (st.size() > 2)
//                 break;

//             maxLength = max(maxLength, j - i + 1);
//         }
//     }

//     return maxLength;
// }

// BETTER
// int totalFruits(vector<int> &fruits) // TC -> O(2N), SC -> O(1)
// {
//     int n = fruits.size(), maxLength = 0;

//     int l = 0, r = 0;

//     unordered_map<int, int> mpp;

//     while (r < n)
//     {
//         mpp[fruits[r]]++;

//         if (mpp.size() > 2)
//         {
//             while (mpp.size() > 2)
//             {
//                 mpp[fruits[l]]--;

//                 if (mpp[fruits[l]] == 0)
//                     mpp.erase(fruits[l]);

//                 l++;
//             }
//         }
//         if (mpp.size() <= 2)
//         {
//             maxLength = max(maxLength, r - l + 1);
//         }

//         r++;
//     }

//     return maxLength;
// }

// OPTIMAL
int totalFruits(vector<int> &fruits) // TC -> O(N), SC -> O(1)
{
    int n = fruits.size(), maxLength = 0;

    int l = 0, r = 0;

    unordered_map<int, int> mpp;

    while (r < n)
    {
        mpp[fruits[r]]++;

        if (mpp.size() > 2)
        {
            mpp[fruits[l]]--;

            if (mpp[fruits[l]] == 0)
                mpp.erase(fruits[l]);

            l++;
        }
        if (mpp.size() <= 2)
        {
            maxLength = max(maxLength, r - l + 1);
        }

        r++;
    }

    return maxLength;
}

int main()
{
    vector<int> input = {3, 3, 3, 1, 2, 1, 1, 2, 3, 3, 4};

    int length = totalFruits(input);

    cout << "Maximum fruits in the basket is: " << length << endl;

    return 0;
}