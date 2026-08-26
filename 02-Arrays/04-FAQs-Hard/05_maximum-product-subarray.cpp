// Problem:
// Given an integer array nums, find the contiguous subarray that has the
// largest product and return that product.
//
// A subarray is defined as a non-empty contiguous sequence of elements
// within the array.

#include <bits/stdc++.h>
using namespace std;

// ===================================================
// BRUTE FORCE APPROACH
//
// Idea:
// Generate every possible subarray and compute the product of elements
// inside each subarray. Track the maximum product encountered during
// the process.
//
// This method explicitly evaluates all subarrays using three nested loops.
// The innermost loop recomputes the product for each subarray.
//
// Time Complexity: O(N^3)
// Space Complexity: O(1)
// ===================================================

// int maxProduct(vector<int> &nums)
// {
//     int n = nums.size();

//     long long maxProduct = LLONG_MIN;

//     for (int i = 0; i < n; i++) // Start index of subarray
//     {
//         for (int j = i; j < n; j++) // End index of subarray
//         {
//             long long product = 1;

//             for (int k = i; k <= j; k++) // Compute product of subarray [i..j]
//                 product *= nums[k];

//             maxProduct = max(maxProduct, product);
//         }
//     }

//     return maxProduct;
// }

// ===================================================
// BETTER APPROACH
//
// Idea:
// Instead of recomputing the product of a subarray from scratch, maintain a running product while expanding the subarray.
//
// For a fixed starting index i, progressively multiply elements as j moves forward. This eliminates the innermost loop and avoids repeated multiplications.
//
// Time Complexity: O(N^2)
// Space Complexity: O(1)
// ===================================================

// int maxProduct(vector<int> &nums)
// {
//     int n = nums.size();

//     long long maxProduct = LLONG_MIN;

//     for (int i = 0; i < n; i++) // Start index of subarray
//     {
//         long long product = 1;

//         for (int j = i; j < n; j++) // Extend subarray to the right
//         {
//             product *= nums[j];
//             maxProduct = max(maxProduct, product);
//         }
//     }

//     return maxProduct;
// }

// ===================================================
// OPTIMAL APPROACH
//
// Idea:
// The presence of negative numbers complicates product tracking
// because two negatives can produce a positive product.
//
// To handle this, compute running products from both directions:
// 1) Prefix product (left → right)
// 2) Suffix product (right → left)
//
// If a zero appears, reset the running product to 1 because any
// subarray product crossing zero becomes zero. The maximum value
// seen across prefix and suffix products is the answer.
//
// Time Complexity: O(N)
// Space Complexity: O(1)
// ===================================================

int maxProduct(vector<int> &nums)
{
    int n = nums.size();

    long long maxProduct = LLONG_MIN;

    long long prefix = 1, suffix = 1;

    for (int i = 0; i < n; i++)
    {
        // Reset running products if a zero was encountered earlier
        if (prefix == 0)
            prefix = 1;

        if (suffix == 0)
            suffix = 1;

        // Prefix product (left → right)
        prefix = prefix * nums[i];

        // Suffix product (right → left)
        suffix = suffix * nums[n - i - 1];

        // Update global maximum
        maxProduct = max(maxProduct, max(prefix, suffix));
    }

    return maxProduct;
}

int main()
{
    vector<int> nums = {1, -2, 3, 4, -4, -3};

    cout << "Array: ";
    for (int it : nums)
        cout << it << " ";
    cout << endl;

    int maxProductSubarray = maxProduct(nums);

    cout << "Maximum Product Subarray: " << maxProductSubarray;

    return 0;
}