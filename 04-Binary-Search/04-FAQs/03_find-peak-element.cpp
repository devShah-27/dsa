#include <bits/stdc++.h>
using namespace std;

// Linear Search
// int findPeakElement(vector<int> &arr) // TC -> O(N), SC -> O(1)
// {
//     int n = arr.size();

//     for (int i = 0; i < n; i++)
//     {
//         if ((i == 0 || arr[i - 1] < arr[i]) && (i == n - 1 || arr[i + 1] < arr[i]))
//             return i;
//     }

//     return -1;
// }

// Binary Search
int findPeakElement(vector<int> &arr) // TC -> O(log(N)), SC -> O(1)
{
    int n = arr.size();

    if (n == 1)
        return 0;

    if (arr[0] > arr[1])
        return 0;

    if (arr[n - 1] > arr[n - 2])
        return n - 1;

    int low = 1, high = n - 2;

    while (low <= high)
    {
        int mid = low + ((high - low) / 2);

        if (arr[mid - 1] < arr[mid] && arr[mid] > arr[mid + 1])
            return mid;

        else if (arr[mid - 1] > arr[mid])
            high = mid - 1;

        else
            low = mid + 1;
    }

    return -1;
}

int main()
{
    vector<int> nums = {1, 2, 3, 4, 5, 6, 8, 7, 5, 1};

    int ans = findPeakElement(nums);

    cout << ans;

    return 0;
}