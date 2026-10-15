// ==================================================
// PROBLEM
// - Given an integer array queries of length n.
// - Return the prime factorization of each number in queries.
// - Each factorization must be in sorted (non-decreasing) order.
// ==================================================

#include <bits/stdc++.h>
using namespace std;

// ==================================================
// BRUTE FORCE APPROACH (TRIAL DIVISION)
//
// Idea:
// - Start with the smallest prime candidate, 2.
// - If it divides the number, record it and divide the number by it.
// - Otherwise, move to the next candidate.
// - Factors come out in sorted order since candidates only increase.
//
// Time Complexity: O(Q * N) - Worst case is a prime N, where the candidate runs up to N.
// Space Complexity: O(log N) - Factors stored per query (excluding the output).
// ==================================================

vector<int> getPrimeFactorisation(int n) {
    vector<int> res;

    // Candidate divisor, starts at the smallest prime
    int prime = 2;

    while (n > 1) {
        if (n % prime == 0) {
            // Prime divides n, so record it and reduce n
            // The candidate stays the same to catch repeated factors
            res.push_back(prime);
            n = n / prime;
        } else {
            // Non-divisor, so try the next candidate
            prime++;
        }
    }

    return res;
}

vector<vector<int>> primeFactors(vector<int> &queries) {
    vector<vector<int>> res;

    // Factorize each query independently
    for (int query : queries) {
        res.push_back(getPrimeFactorisation(query));
    }

    return res;
}

// ==================================================
// OPTIMAL APPROACH (SMALLEST PRIME FACTOR SIEVE)
//
// Idea:
// - Precompute the smallest prime factor (spf) of every number up to the maximum limit using a sieve.
// - To factorize a number, repeatedly read its spf and divide the number by it.
// - Each query then takes only as many steps as it has prime factors.
// - Factors come out in sorted order since spf is the smallest each time.
//
// Time Complexity: O(M log log M + Q log N) - Sieve build plus per-query factorization.
// Space Complexity: O(M) - spf array of size M + 1, where M = 1e5.
// ==================================================

vector<vector<int>> primeFactors(vector<int> &queries) {
    // spf[i] holds the smallest prime factor of i
    vector<int> spf(1e5 + 1);

    // Initially, every number is its own smallest prime factor
    for (int i = 0; i <= 1e5; i++)
        spf[i] = i;

    // Sieve: only primes up to sqrt(limit) are needed to update composites
    for (int num = 2; num * num <= 1e5; num++) {
        if (spf[num] == num) {
            // Start at num * num: smaller multiples have a smaller prime factor
            for (int multiple = num * num; multiple <= 1e5; multiple += num) {
                // Update only if no smaller prime has claimed this number yet
                if (spf[multiple] == multiple) {
                    spf[multiple] = num;
                }
            }
        }
    }

    vector<vector<int>> res;

    for (int query : queries) {
        vector<int> temp;

        // Peel off the smallest prime factor until the number becomes 1
        while (query > 1) {
            temp.push_back(spf[query]);
            query = query / spf[query];
        }

        res.push_back(temp);
    }

    return res;
}

int main() {
    vector<int> queries = {2, 3, 4, 5, 6};

    vector<vector<int>> ans = primeFactors(queries);

    cout << "The prime factorization of all the numbers is: " << endl;

    for (int i = 0; i < ans.size(); i++) {
        cout << "For " << queries[i] << ": ";

        for (int j = 0; j < ans[i].size(); j++) {
            cout << ans[i][j] << " ";
        }
        cout << endl;
    }

    return 0;
}
