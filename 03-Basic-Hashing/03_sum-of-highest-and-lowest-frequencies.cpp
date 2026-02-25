// Given an array of n integers, find the second most frequent element in it.
// If there are multiple elements that appear second most frequent times, find the smallest of them.
// If second most frequent element does not exist return -1.

#include <bits/stdc++.h>
using namespace std;

// =================== BRUTE FORCE (Uses a visitor array) ===================
// int getSumOfHighestAndLowestFreq(vector<int> &inputArray)
// {
//     int size = inputArray.size();

//     vector<int> visited(pow(10, 4), 0);

//     int maxFreq = 0, minFreq = size;

//     for (int i = 0; i < size; i++)
//     {

//         if (visited[inputArray[i]] == 0)
//         {
//             visited[inputArray[i]] = 1;

//             int counter = 0;

//             for (int j = 0; j < size; j++)
//                 if (inputArray[j] == inputArray[i])
//                     counter++;

//             maxFreq = max(maxFreq, counter);
//             minFreq = min(minFreq, counter);
//         }
//     }

//     return (maxFreq + minFreq);
// }

// =================== OPTIMAL (Uses a hash array) ===================
int getSumOfHighestAndLowestFreq(vector<int> &inputArray)
{
    int size = inputArray.size();

    unordered_map<int, int> frequencyMap;

    int maxFreq = 0, minFreq = size;

    for (int i = 0; i < size; i++)
    {
        frequencyMap[inputArray[i]]++;
    }

    for (auto it : frequencyMap)
    {
        maxFreq = max(maxFreq, it.second);
        minFreq = min(minFreq, it.second);
    }

    return minFreq + maxFreq;
}

int main()
{
    int size;
    cin >> size;

    vector<int> nums(size);

    for (int i = 0; i < size; i++)
        cin >> nums[i];

    cout << "Input array: ";

    for (auto it : nums)
        cout << it << " ";

    cout << endl;

    int sum = getSumOfHighestAndLowestFreq(nums);

    cout << "Sum of Highest and Lowest Frequencies -> " << sum << endl;

    return 0;
}