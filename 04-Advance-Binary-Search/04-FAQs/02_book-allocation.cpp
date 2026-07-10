// ========================== PROBLEM ==========================
// Given an array where each element represents the pages in a book,
// allocate all books to m students such that each student gets
// contiguous books and the maximum pages assigned is minimized.
// Return -1 if allocation is not possible.
// ============================================================

#include <bits/stdc++.h>
using namespace std;

// ========================== HELPER FUNCTION ==========================
// Idea:
// Traverse the array and return the maximum element.
// Every student must receive at least one book, so the minimum
// possible answer cannot be smaller than the largest book.
//
// Time Complexity: O(N)
// Space Complexity: O(1)
// =====================================================================
int maximumElement(vector<int> &nums)
{
    int maxElem = INT_MIN;

    for (int it : nums)
        maxElem = max(maxElem, it);

    return maxElem;
}

// ========================== HELPER FUNCTION ==========================
// Idea:
// Compute the total number of pages across all books.
// This represents the upper bound of the search space since
// one student can be assigned all books.
//
// Time Complexity: O(N)
// Space Complexity: O(1)
// =====================================================================
long long sumOfAllElements(vector<int> nums)
{
    long long sum = 0;

    for (int it : nums)
        sum += it;

    return sum;
}

// ========================== HELPER FUNCTION ==========================
// Idea:
// Determine the minimum number of students required if no student
// is allowed to read more than 'allowedPageCount' pages.
// Books must be allocated contiguously.
//
// Time Complexity: O(N)
// Space Complexity: O(1)
// =====================================================================
int countPossibleStudents(vector<int> &nums, int allowedPageCount)
{
    int studentCount = 1, currentStudentPageCount = 0;

    for (int i = 0; i < nums.size(); i++)
    {
        if (currentStudentPageCount + nums[i] <= allowedPageCount)
        {
            currentStudentPageCount += nums[i];
        }
        else
        {
            studentCount++;
            currentStudentPageCount = nums[i];
        }
    }

    return studentCount;
}

// ========================== BRUTE FORCE APPROACH (LINEAR SEARCH) ==========================
// Idea:
// Try every possible maximum page limit from the largest book
// to the total pages. Return the first page limit that can
// allocate books to at most m students.
//
// Time Complexity: O((Sum of pages - Maximum pages + 1) * N)
// Space Complexity: O(1)
// ==========================================================================================
// int findPages(vector<int> &nums, int m)
// {
//     int n = nums.size();
//
//     if (m > n)
//         return -1;
//
//     int low = maximumElement(nums);
//
//     long long high = sumOfAllElements(nums);
//
//     for (int pageCount = low; pageCount <= high; pageCount++)
//     {
//         int studentCount = countPossibleStudents(nums, pageCount);
//
//         if (studentCount <= m)
//             return pageCount;
//     }
//
//     return -1;
// }

// ========================== OPTIMAL APPROACH (BINARY SEARCH) ==========================
// Idea:
// The answer lies between the largest book and the total pages.
// Use binary search on this range.
// - If current page limit can allocate books to at most m students,
//   try reducing the limit.
// - Otherwise, increase the page limit.
//
// Time Complexity: O(N * log(Sum of pages - Maximum pages + 1))
// Space Complexity: O(1)
// ======================================================================================
int findPages(vector<int> &nums, int m)
{
    int n = nums.size();

    // Impossible if students exceed the number of books
    if (m > n)
        return -1;

    int low = maximumElement(nums);
    long long high = sumOfAllElements(nums);

    while (low <= high)
    {
        int mid = low + ((high - low) / 2);

        int studentCount = countPossibleStudents(nums, mid);

        // Current page limit is feasible; try a smaller one
        if (studentCount <= m)
            high = mid - 1;
        // Too many students required; increase page limit
        else
            low = mid + 1;
    }

    // 'low' stores the minimum feasible maximum page allocation
    return low;
}

int main()
{
    vector<int> nums = {12, 34, 67, 90};

    int m = 2;

    int ans = findPages(nums, m);

    cout << ans;

    return 0;
}