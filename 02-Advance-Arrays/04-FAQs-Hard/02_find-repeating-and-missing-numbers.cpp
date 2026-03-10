// Problem:
// Given an integer array nums of size n containing numbers from 1 to n,
// exactly one number appears twice (repeating) and one number is missing.
// Return {repeating, missing} without modifying the original array.

#include <bits/stdc++.h>
using namespace std;

// ================================================================
// BRUTE FORCE APPROACH
//
// Idea:
// For every number from 1 to n, iterate through the entire array
// and count its occurrences. If a number appears twice, it is the
// repeating number. If it never appears, it is the missing number.
//
// Time Complexity:  O(N^2)
// Space Complexity: O(1)
// ================================================================

// vector<int> findMissingRepeatingNumbers(vector<int> nums)
// {
//     int n = nums.size();

//     int repeating = -1, missing = -1;

//     for (int i = 1; i <= n; i++) // O(N)
//     {
//         int count = 0;

//         for (int j = 0; j < n; j++) // O(N)
//         {
//             if (nums[j] == i)
//                 count++;
//         }

//         if (count == 2)
//             repeating = i;

//         if (count == 0)
//             missing = i;

//         if (repeating != -1 && missing != -1)
//             break;
//     }

//     return {repeating, missing};
// }

// ================================================================
// BETTER APPROACH (HASHING / FREQUENCY ARRAY)
//
// Idea:
// Use an auxiliary array to store the frequency of each number.
// Traverse nums to build frequencies, then scan from 1..n to
// identify which number is missing (freq = 0) and repeating (freq = 2).
//
// Time Complexity:  O(N)
// Space Complexity: O(N)
// ================================================================

// vector<int> findMissingRepeatingNumbers(vector<int> nums)
// {
//     int n = nums.size();

//     int repeating = -1, missing = -1;

//     int hash[n + 1] = {0};

//     for (int it : nums)
//         hash[it]++;

//     for (int i = 1; i <= n; i++) // O(N)
//     {
//         if (hash[i] == 0)
//             missing = i;

//         else if (hash[i] == 2)
//             repeating = i;

//         if (missing != -1 && repeating != -1)
//             break;
//     }

//     return {repeating, missing};
// }

// ================================================================
// OPTIMAL APPROACH 1 (MATH / EQUATION METHOD)
//
// Idea:
// Use formulas for the sum and square sum of the first n natural numbers.
// Compare them with the actual array sum and square sum to form equations:
//     X - Y  and  X + Y
// Solve the two equations to compute the repeating (X) and missing (Y) values.
//
// Time Complexity:  O(N)
// Space Complexity: O(1)
// ================================================================

// vector<int> findMissingRepeatingNumbers(vector<int> nums)
// {
//     long long n = nums.size();

//     /*
//     ---------------------------------------------------------
//     Step 1: Compute the expected sum and expected square sum
//             of numbers from 1..n using formulas
//     ---------------------------------------------------------
//     */

//     // Expected sum of first n natural numbers
//     // Sn = 1 + 2 + 3 + ... + n
//     long long Sn = (n * (n + 1)) / 2;

//     // Expected sum of squares
//     // S2n = 1^2 + 2^2 + 3^2 + ... + n^2
//     long long S2n = (n * (n + 1) * (2 * n + 1)) / 6;

//     /*
//     ---------------------------------------------------------
//     Step 2: Compute the actual sum and actual square sum
//             from the given array
//     ---------------------------------------------------------
//     */

//     long long S = 0;  // actual sum of elements in array
//     long long S2 = 0; // actual sum of squares

//     for (int i = 0; i < n; i++)
//     {
//         S += nums[i];
//         S2 += (long long)nums[i] * nums[i];
//     }

//     /*
//     ---------------------------------------------------------
//     Step 3: Build equations using the difference
//     ---------------------------------------------------------

//     Let:
//     X = repeating number
//     Y = missing number

//     Because X appears twice and Y is missing:

//     Actual Sum = Expected Sum + X - Y

//     Therefore:
//     S - Sn = X - Y  ---- (Equation 1)
//     */

//     long long equation1 = S - Sn; // (X - Y)

//     /*
//     For squares:

//     Actual Square Sum = Expected Square Sum + X^2 - Y^2

//     Therefore:
//     S2 - S2n = X^2 - Y^2

//     Using identity:
//     X^2 - Y^2 = (X - Y)(X + Y)

//     So:
//     S2 - S2n = (X - Y)(X + Y)

//     Divide by (X - Y):

//     X + Y = (S2 - S2n) / (X - Y)
//     */

//     long long equation2 = S2 - S2n;
//     equation2 = equation2 / equation1; // (X + Y)

//     /*
//     ---------------------------------------------------------
//     Step 4: Solve the system of equations
//     ---------------------------------------------------------

//     We now know:

//     X - Y = equation1
//     X + Y = equation2

//     Add both equations:

//     (X - Y) + (X + Y) = 2X

//     So:
//     X = (equation1 + equation2) / 2
//     */

//     long long X = (equation1 + equation2) / 2; // repeating number

//     /*
//     Substitute X back into:

//     X - Y = equation1

//     Y = X - equation1
//     */

//     long long Y = X - equation1; // missing number

//     /*
//     Return:
//     X = repeating
//     Y = missing
//     */

//     return {(int)X, (int)Y};
// }

// ================================================================
// OPTIMAL APPROACH 2 (XOR METHOD)
//
// Idea:
// XOR all array elements with numbers from 1..n.
// The result becomes (X ^ Y) where X = repeating, Y = missing.
// Use the rightmost set bit to divide numbers into two groups and XOR again to isolate the two numbers.
// Finally determine which one is repeating by counting occurrences.
//
// Time Complexity:  O(N)
// Space Complexity: O(1)
// ================================================================

vector<int> findMissingRepeatingNumbers(vector<int> nums)
{
    long long n = nums.size();

    int xr = 0;

    for (int i = 0; i < n; i++) // O(N)
    {
        xr = xr ^ nums[i];
        xr = xr ^ (i + 1);
    }

    int differentiatingBitNo = xr & ~(xr - 1);

    int zeroClub = 0;
    int oneClub = 0;

    for (int i = 0; i < n; i++) // O(N)
    {
        if ((nums[i] & differentiatingBitNo) != 0)
            oneClub = oneClub ^ nums[i];
        else
            zeroClub = zeroClub ^ nums[i];
    }

    for (int i = 0; i <= n; i++) // O(N)
    {
        if ((i & differentiatingBitNo) != 0)
            oneClub = oneClub ^ i;
        else
            zeroClub = zeroClub ^ i;
    }

    int counter = 0;

    for (int i = 0; i < n; i++) // O(N)
    {
        if (nums[i] == zeroClub)
            counter++;
    }

    if (counter == 0)
        return {oneClub, zeroClub};

    return {zeroClub, oneClub};
}

int main()
{
    vector<int> nums = {6, 5, 7, 1, 8, 6, 4, 3, 2};

    vector<int> ans = findMissingRepeatingNumbers(nums);

    cout << "Repeating Number: " << ans[0] << "\n";
    cout << "Missing Number: " << ans[1];

    return 0;
}