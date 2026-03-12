// PROBLEM:
// Given an integer array nums of size n, return the length of the
// longest sequence of consecutive integers.
//
// The numbers forming the sequence do not need to appear in
// consecutive positions in the array.

#include <bits/stdc++.h>
using namespace std;

// ===================================================
// BRUTE FORCE APPROACH
//
// Idea:
// For every element X in the array, repeatedly check whether
// X + 1, X + 2, X + 3 ... exist in the array using linear search.
//
// If the next consecutive number is found, extend the sequence
// length. Track the maximum length across all starting elements.
//
// The heavy cost comes from repeatedly performing linear searches
// inside the loop.
//
// Time Complexity: O(N^3)
// Space Complexity: O(1)
// ===================================================

// bool linearSearch(vector<int> &nums, int target)
// {
//     int n = nums.size();

//     for (int it : nums)
//         if (it == target)
//             return true;

//     return false;
// }

// int longestConsecutive(vector<int> &nums)
// {
//     int n = nums.size(), longest = 1;

//     for (int i = 0; i < n; i++)
//     {
//         int count = 1;
//         int x = nums[i];

//         while (linearSearch(nums, x + 1))
//             count++, x++;

//         longest = max(longest, count);
//     }

//     return longest;
// }

// ===================================================
// BETTER APPROACH
//
// Idea:
// First sort the array so that consecutive numbers become adjacent.
// Then iterate through the sorted array and maintain:
//
// • currentCount → length of current consecutive sequence
// • longestCount → maximum sequence length seen so far
//
// Handle duplicate values by skipping them during iteration.
//
// Time Complexity: O(N log N) for sorting + O(N) traversal
// Space Complexity: O(1)
// ===================================================

// int longestConsecutive(vector<int> &nums)
// {
//     sort(nums.begin(), nums.end());

//     int longestCount = 1;
//     int currentCount = 1;

//     for (int i = 1; i < nums.size(); i++)
//     {
//         if (nums[i] == nums[i - 1])
//             continue;

//         if (nums[i] == nums[i - 1] + 1)
//         {
//             currentCount++;
//         }
//         else
//         {
//             currentCount = 1;
//         }

//         longestCount = max(longestCount, currentCount);
//     }

//     return longestCount;
// }

// ===================================================
// OPTIMAL APPROACH — HASH SET
//
// Key Observation:
// A number X can only be the *start* of a sequence if (X - 1) does NOT exist in the set.
//
// Example:
// nums = [100,4,200,1,3,2]
//
// set = {1,2,3,4,100,200}
//
// 1 -> start (0 not present) -> sequence: 1,2,3,4
// 2 -> skipped (1 exists)
// 3 -> skipped (2 exists)
// 4 -> skipped (3 exists)
//
// This ensures every consecutive sequence is processed
// exactly once.
//
// Algorithm:
// 1. Insert all numbers into an unordered_set for O(1)
//    average-time existence checks.
// 2. Iterate through the set.
// 3. For each number:
//      • If (num - 1) exists → skip (not sequence start)
//      • Otherwise → expand forward num+1, num+2 ...
// 4. Track the maximum sequence length.
//
// Time Complexity:
// Average Case  : O(N)
//   - Each element is visited at most once while expanding.
//
// Worst Case    : O(N^2)
//   - Only if unordered_set suffers extreme hash collisions (very rare in practice with modern implementations).
//
// Space Complexity:
// O(N) for the hash set.
//
// Practical Note:
// In real-world scenarios and coding interviews, this is considered the optimal solution. If strict worst-case
// guarantees are required, the sorting solution (O(N log N)) is safer.
// ===================================================

int longestConsecutive(vector<int> &nums)
{
    // Edge case: empty input
    if (nums.empty())
        return 0;

    unordered_set<int> st;
    st.reserve(nums.size()); // Prevent multiple rehashes

    // Insert all numbers into the set
    for (int num : nums)
        st.insert(num);

    int longestCount = 0;

    // Iterate through unique elements in the set
    for (int num : st)
    {
        // If predecessor exists, this number cannot be the start of a consecutive sequence.
        if (st.find(num - 1) != st.end())
            continue;

        // num is the start of a sequence
        int current = num;
        int currentCount = 1;

        // Expand the sequence forward
        while (st.find(current + 1) != st.end())
        {
            current++;
            currentCount++;
        }

        // Update global maximum
        longestCount = max(longestCount, currentCount);
    }

    return longestCount;
}

int main()
{
    vector<int> nums = {0, 3, 7, 2, 5, 8, 4, 6, 0, 1};

    cout << "Array: ";
    for (int it : nums)
        cout << it << " ";
    cout << endl;

    int maxConsecutiveSequenceCount = longestConsecutive(nums);

    cout << "Longest sequence count: " << maxConsecutiveSequenceCount;

    return 0;
}