// ==================================================
// PROBLEM
// - Given a 2D array queries of size n * 2, where queries[i] is
//   an inclusive range [queries[i][0], queries[i][1]].
// - Return the count of prime numbers in each query range.
// ==================================================

#include <bits/stdc++.h>
using namespace std;

// ==================================================
// BRUTE FORCE APPROACH
//
// Idea:
// - Visit every number inside each query range one by one.
// - Test each number for primality using trial division up to its square root.
// - Count the numbers that pass the test and store the count as the answer for that query.
//
// Time Complexity: O(Q * (R - L + 1) * sqrt(R)) - Trial division for every number in every range.
// Space Complexity: O(1) - No extra space besides the output list.
// ==================================================

// Returns true if num is prime, using trial division up to sqrt(num)
bool isPrime(int num) {
    // 0, 1, and negatives are not prime
    if (num <= 1)
        return false;

    // A composite number always has a divisor at most its square root
    for (int i = 2; i * i <= num; i++) {
        if (num % i == 0)
            return false;
    }

    return true;
}

vector<int> primesInRange(vector<vector<int>> &queries) {
    vector<int> res;

    for (auto &query : queries) {
        int L = query[0], R = query[1];

        int counter = 0;

        // Test every number in the inclusive range [L, R]
        for (int num = L; num <= R; num++) {
            if (isPrime(num))
                counter++;
        }

        res.push_back(counter);
    }

    return res;
}

// ==================================================
// BETTER APPROACH (SIEVE + LINEAR SCAN)
//
// Idea:
// - Precompute primality for all numbers up to 1e5 with the Sieve of Eratosthenes.
// - Each primality check then becomes an O(1) array lookup.
// - For each query, scan the range and count the numbers marked prime in the sieve.
//
// Time Complexity: O(N log log N + Q * (R - L + 1)) - Sieve build plus one scan per query, N = 1e5.
// Space Complexity: O(N) - Sieve array of size N + 1.
// ==================================================

// Marks every composite number up to 1e5 as 0 in the isPrime array
void sieveOfEratosthenes(vector<int> &isPrime) {
    // Only primes up to sqrt(1e5) need to mark their multiples
    for (int num = 2; num * num <= 1e5; num++) {
        if (isPrime[num]) {
            // Start at num * num because smaller multiples were
            // already marked by smaller primes
            for (int multiple = num * num; multiple <= 1e5; multiple += num) {
                isPrime[multiple] = 0;
            }
        }
    }
}

vector<int> primesInRange(vector<vector<int>> &queries) {
    // Assume every number is prime until the sieve proves otherwise
    vector<int> isPrime(1e5 + 1, 1);

    sieveOfEratosthenes(isPrime);

    vector<int> res;

    for (auto &query : queries) {
        int L = query[0], R = query[1];

        int counter = 0;

        // Scan the range and count the sieve entries marked prime
        for (int num = L; num <= R; num++) {
            // 0, 1, and negatives are not prime, but the sieve marks 0 and 1 as 1
            if (num <= 1)
                continue;

            if (isPrime[num])
                counter++;
        }

        res.push_back(counter);
    }

    return res;
}

// ==================================================
// OPTIMAL APPROACH (SIEVE + PREFIX SUM)
//
// Idea:
// - Build the sieve once, then convert it into a prefix sum array of prime counts.
// - primeCount[i] stores how many primes exist in [0, i].
// - The answer for a range [L, R] is primeCount[R] minus primeCount[L - 1].
// - Handle L = 0 separately to avoid a negative index.
//
// Time Complexity: O(N log log N + Q) - Sieve and prefix build once, then O(1) per query, N = 1e5.
// Space Complexity: O(N) - Single array of size N + 1.
// ==================================================

// Marks every composite number up to 1e5 as 0 in the given array
void sieveOfEratosthenes(vector<int> &isPrime) {
    // Only primes up to sqrt(1e5) need to mark their multiples
    for (int num = 2; num * num <= 1e5; num++) {
        if (isPrime[num]) {
            // Start at num * num because smaller multiples were
            // already marked by smaller primes
            for (int multiple = num * num; multiple <= 1e5; multiple += num) {
                isPrime[multiple] = 0;
            }
        }
    }
}

vector<int> primesInRange(vector<vector<int>> &queries) {
    // The array first holds sieve flags, then is reused for prefix counts
    vector<int> primeCount(1e5 + 1, 1);

    // 0 and 1 are not prime. The sieve never touches them, so mark them here
    primeCount[0] = primeCount[1] = 0;

    sieveOfEratosthenes(primeCount);

    // Convert prime flags into a running total of primes
    int primeCnt = 0;

    // Indices 0 and 1 already hold 0, which is the correct prefix count for them
    for (int idx = 2; idx <= 1e5; idx++) {
        primeCnt += primeCount[idx];
        primeCount[idx] = primeCnt;
    }

    vector<int> res;

    for (auto &query : queries) {
        int L = query[0], R = query[1];

        // No prefix exists before index 0, so the answer is primeCount[R] alone
        if (L == 0) {
            res.push_back(primeCount[R]);
        }
        // Primes in [L, R] = primes up to R minus primes up to L - 1
        else {
            res.push_back(primeCount[R] - primeCount[L - 1]);
        }
    }

    return res;
}

int main() {
    vector<vector<int>> queries = {{3, 10}, {8, 20}, {1, 5}};

    vector<int> result = primesInRange(queries);

    for (int count : result) {
        cout << count << endl;
    }

    return 0;
}
