// Problem:
// A permutation of an array of integers is an arrangement of its
// elements in a particular order.
//
// Example:
// For arr = [1,2,3], the permutations are:
// [1,2,3], [1,3,2], [2,1,3], [2,3,1], [3,1,2], [3,2,1]
//
// The next permutation of an array is the next lexicographically
// greater arrangement of its elements.
//
// If the array is already the last permutation (sorted in descending
// order), then rearrange it to the first permutation (ascending order).
//
// The transformation must be done in-place and use only constant
// extra memory.

#include <bits/stdc++.h>
using namespace std;

// ================================================================
// BRUTE FORCE APPROACH
//
// Idea:
// Generate all permutations of the array, sort them lexicographically,
// and then locate the permutation that comes immediately after the
// current one.
//
// This approach is extremely expensive because the number of
// permutations of an array of size N is N!.
//
// Time Complexity:  O(N! * N)
// Space Complexity: O(N!)
// ================================================================

// void generatePermutations(int index, vector<int> &nums, vector<vector<int>> &ans)
// {
//     if (index == nums.size())
//     {
//         ans.push_back(nums);
//         return;
//     }
//
//     for (int i = index; i < nums.size(); i++)
//     {
//         swap(nums[i], nums[index]);
//         generatePermutations(index + 1, nums, ans);
//         swap(nums[i], nums[index]);
//     }
// }

// ================================================================
// BETTER APPROACH (USING STL)
//
// Idea:
// C++ provides a built-in function `next_permutation()` that
// transforms the array into the next lexicographical permutation.
//
// If the array is already the largest permutation,
// it automatically converts it to the smallest permutation.
//
// Time Complexity:  O(N)
// Space Complexity: O(1)
// ================================================================

// void getNextPermutationSTL(vector<int> &nums)
// {
//     next_permutation(nums.begin(), nums.end());
// }

// ================================================================
// OPTIMAL APPROACH (IMPLEMENT NEXT PERMUTATION)
//
// Key Observation:
// To generate the next permutation:
//
// 1. Traverse from right and find the first index where
//    nums[i] < nums[i+1]. This index is called the pivot.
// 2. If no such index exists, the array is in descending order.
//    Reverse the entire array to get the smallest permutation.
// 3. Otherwise, find the smallest element to the right of pivot
//    that is greater than nums[pivot] and swap them.
// 4. Reverse the elements to the right of the pivot to obtain
//    the next smallest lexicographic arrangement.
//
// Time Complexity:  O(N)
// Space Complexity: O(1)
// ================================================================

void nextPermutation(vector<int> &nums)
{
    int n = nums.size();

    if (n <= 1)
        return;

    int pivot = -1;

    // Step 1: Find pivot
    for (int i = n - 2; i >= 0; i--)
    {
        if (nums[i] < nums[i + 1])
        {
            pivot = i;
            break;
        }
    }

    // Step 2: If no pivot exists, reverse the entire array
    if (pivot == -1)
    {
        reverse(nums.begin(), nums.end());
        return;
    }

    // Step 3: Find the next greater element to swap
    for (int i = n - 1; i > pivot; i--)
    {
        if (nums[i] > nums[pivot])
        {
            swap(nums[i], nums[pivot]);
            break;
        }
    }

    // Step 4: Reverse the suffix
    reverse(nums.begin() + pivot + 1, nums.end());
}

int main()
{
    vector<int> nums = {3, 1, 2};

    // vector<vector<int>> permutations;
    // generatePermutations(0, nums, permutations);
    // sort(permutations.begin(), permutations.end());

    // getNextPermutationSTL(nums);

    nextPermutation(nums);

    cout << "NEXT PERMUTATION: ";

    for (int it : nums)
        cout << it << " ";

    return 0;
}