// ==================================================
// PROBLEM
// - Given an integer N.
// - Print all prime numbers from 2 up to N (inclusive).
// - A prime has exactly two divisors: 1 and itself.
// ==================================================

#include <bits/stdc++.h>
using namespace std;

// ==================================================
// BRUTE FORCE APPROACH (SIEVE OF ERATOSTHENES, UNOPTIMIZED)
//
// Idea:
// - Assume every number from 2 to N is prime initially.
// - For each number still marked prime, mark all of its multiples as composite.
// - Marking starts at 2 * num and runs through N, so some multiples get marked redundantly.
// - Collect every index still marked prime into the result.
//
// Time Complexity: O(N log log N) - Harmonic sum of N / p over all primes p.
// Space Complexity: O(N) - Sieve array of size N + 1 (excluding the output vector).
// ==================================================

vector<int> primeTillN(int n) {
    // isPrime[i] == 1 means i is assumed prime until proven composite
    vector<int> isPrime(n + 1, 1);

    for (int num = 2; num <= n; num++) {
        if (isPrime[num]) {
            // Mark all multiples of num as composite, starting from 2 * num
            for (int multiple = 2 * num; multiple <= n; multiple += num) {
                isPrime[multiple] = 0;
            }
        }
    }

    vector<int> res;

    // Collect all numbers that survived the sieve
    for (int i = 2; i <= n; i++) {
        if (isPrime[i]) {
            res.push_back(i);
        }
    }

    return res;
}

// ==================================================
// OPTIMAL APPROACH (SIEVE OF ERATOSTHENES)
//
// Idea:
// - Any composite number up to N has a prime factor less than or equal to sqrt(N).
// - So the outer loop only needs to run while num * num <= N.
// - For each prime num, start marking multiples from num * num.
// - Smaller multiples were already marked by smaller primes.
// - Collect every index still marked prime into the result.
//
// Time Complexity: O(N log log N) - Fewer redundant markings than brute force.
// Space Complexity: O(N) - Sieve array of size N + 1 (excluding the output vector).
// ==================================================

vector<int> primeTillN(int n) {
    // isPrime[i] == 1 means i is assumed prime until proven composite
    vector<int> isPrime(n + 1, 1);

    // Only primes up to sqrt(n) are needed to eliminate all composites
    for (int num = 2; num * num <= n; num++) {
        if (isPrime[num]) {
            // Start at num * num: smaller multiples (2*num, 3*num, ...)
            // have a smaller prime factor and are already marked
            for (int multiple = num * num; multiple <= n; multiple += num) {
                isPrime[multiple] = 0;
            }
        }
    }

    vector<int> res;

    // Collect all numbers that survived the sieve
    for (int i = 2; i <= n; i++) {
        if (isPrime[i]) {
            res.push_back(i);
        }
    }

    return res;
}

int main() {
    int n = 7;

    vector<int> ans = primeTillN(n);

    cout << "All primes till N are: " << endl;
    for (int i = 0; i < ans.size(); i++) {
        cout << ans[i] << " ";
    }

    return 0;
}
