// Given an array nums of n integers, find the most frequent element in it i.e., the element that occurs the maximum number of times. If there are multiple elements that appear a maximum number of times, find the smallest of them.

#include <bits/stdc++.h>
using namespace std;

// =================== BRUTE FORCE (Uses a visitor array) ===================
// int getHighestFrequencyElement(vector<int> &inputArray)
// {
//     int size = inputArray.size();

//     vector<int> visitorArray(pow(10, 4) + 1, 0);

//     int maxFrequency = 0;
//     int maxElement = -1;

//     for (int iteration = 0; iteration < size; iteration++)
//     {
//         if (visitorArray[inputArray[iteration]] == 0)
//         {
//             visitorArray[inputArray[iteration]] = 1;
//             int currentFrequency = 0;

//             for (int j = 0; j < size; j++)
//             {
//                 if (inputArray[iteration] == inputArray[j])
//                 {
//                     currentFrequency++;
//                 }
//             }

//             if (currentFrequency > maxFrequency)
//             {
//                 maxFrequency = currentFrequency;
//                 maxElement = inputArray[iteration];
//             }
//             else if (currentFrequency == maxFrequency)
//             {
//                 maxElement = min(maxElement, inputArray[iteration]);
//             }
//         }
//     }

//     return maxElement;
// }

// =================== OPTIMAL (Uses a hash array) ===================
int getHighestFrequencyElement(vector<int> &inputArray)
{
    int size = inputArray.size();

    unordered_map<int, int> frequencyMap;

    for (int iteration = 0; iteration < size; iteration++)
    {
        frequencyMap[inputArray[iteration]]++;
    }

    int maxElement = -1;
    int maxFrequency = 0;

    for (auto p : frequencyMap)
    {
        if (p.second > maxFrequency)
        {
            maxElement = p.first;
            maxFrequency = p.second;
        }
        else if (p.second == maxFrequency)
        {
            maxElement = min(maxElement, p.first);
        }
    }

    return maxElement;
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

    int highestFreqElem = getHighestFrequencyElement(nums);

    cout << "Highest frequency element -> " << highestFreqElem << endl;

    return 0;
}