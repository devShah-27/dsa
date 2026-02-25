// Given an array of n integers, find the second most frequent element in it.
// If there are multiple elements that appear second most frequent times, find the smallest of them.
// If second most frequent element does not exist return -1.

#include <bits/stdc++.h>
using namespace std;

// =================== BRUTE FORCE (Uses a visitor array) ===================
// int getSecondHighestFrequencyElement(vector<int> &inputArray)
// {
//     int size = inputArray.size();

//     vector<int> visitorArray(pow(10, 4) + 1, 0);

//     int maxElem = -1, secondMaxElem = -1;
//     int maxFreq, secondMaxFreq = 0;

//     for (int i = 0; i < size; i++)
//     {
//         if (visitorArray[inputArray[i]] == 0)
//         {
//             visitorArray[inputArray[i]] = 1;
//             int currentFrequency = 0;
//             for (int j = 0; j < size; j++)
//             {
//                 if (inputArray[i] == inputArray[j])
//                     currentFrequency++;
//             }

//             if (currentFrequency > maxFreq) // If current frequency is greater than max frequency, update max frequency, second max frequency, max element and second max element
//             {
//                 secondMaxFreq = maxFreq;
//                 secondMaxElem = maxElem;

//                 maxFreq = currentFrequency;
//                 maxElem = inputArray[i];
//             }
//             else if (currentFrequency == maxFreq) // If current frequency is equal to max frequency update max element
//             {
//                 maxElem = min(maxElem, inputArray[i]);
//             }
//             else if (currentFrequency > secondMaxFreq) // If current frequency is greater than second max frequency update second max frequency and second max element
//             {
//                 secondMaxFreq = currentFrequency;
//                 secondMaxElem = inputArray[i];
//             }
//             else if (currentFrequency == secondMaxFreq) // If current frequency is equal to second max frequency update second max element
//             {
//                 secondMaxElem = min(secondMaxElem, inputArray[i]);
//             }
//         }
//     }

//     return secondMaxElem;
// }

// =================== OPTIMAL (Uses a hash array) ===================
int getSecondHighestFrequencyElement(vector<int> &inputArray)
{
    int size = inputArray.size();

    unordered_map<int, int> frequencyMap;

    for (int i = 0; i < size; i++)
    {
        frequencyMap[inputArray[i]]++;
    }

    int maxFreq = 0, secondMaxFreq = 0;
    int maxElem = -1, secondMaxElem = -1;

    for (auto p : frequencyMap)
    {
        if (p.second == 0)
            continue;

        if (p.second > maxFreq) // If current frequency is greater than max frequency, update max frequency, second max frequency, max element and second max element
        {
            secondMaxFreq = maxFreq;
            secondMaxElem = maxElem;

            maxFreq = p.second;
            maxElem = p.first;
        }
        else if (p.second == maxFreq) // If current frequency is equal to max frequency update max element
        {
            maxElem = min(maxElem, p.first);
        }
        else if (p.second > secondMaxFreq) // If current frequency is greater than second max frequency update second max frequency and second max element
        {
            secondMaxFreq = p.second;
            secondMaxElem = p.first;
        }
        else if (p.second == secondMaxFreq) // If current frequency is equal to second max frequency update second max element
        {
            secondMaxElem = min(secondMaxElem, p.first);
        }
    }

    return secondMaxElem;
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

    int secondHighestFreqElem = getSecondHighestFrequencyElement(nums);

    cout << "Second Highest frequency element -> " << secondHighestFreqElem << endl;

    return 0;
}