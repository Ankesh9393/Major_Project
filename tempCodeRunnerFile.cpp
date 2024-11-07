#include <iostream>
#include <vector>
using namespace std;

const int MAX_N = 10000000;
vector<bool> is_prime(MAX_N + 1, true);
vector<int> prime_count(MAX_N + 1, 0);
vector<int> subtractorizations(MAX_N + 1, 0);

// Sieve of Eratosthenes to find all primes up to MAX_N
void sieve() {
    is_prime[0] = is_prime[1] = false;  // 0 and 1 are not primes
    for (int i = 2; i * i <= MAX_N; ++i) {
        if (is_prime[i]) {
            for (int j = i * i; j <= MAX_N; j += i) {
                is_prime[j] = false;
            }
        }
    }

    // Populate prime_count: number of primes <= i for each i
    for (int i = 2; i <= MAX_N; ++i) {
        prime_count[i] = prime_count[i - 1] + is_prime[i];
    }
}

// Precompute the number of subtractorizations for every N
void precompute_subtractorizations() {
    for (int p = 2; p <= MAX_N; ++p) {
        if (is_prime[p]) {
            // For each prime p, check if it can be written as p1 - p2
            for (int p1 = p; p1 <= MAX_N; ++p1) {
                if (is_prime[p1] && p1 - p >= 2 && is_prime[p1 - p]) {
                    subtractorizations[p]++;
                }
            }
        }
    }

    // Accumulate the results for fast query responses
    for (int i = 1; i <= MAX_N; ++i) {
        subtractorizations[i] += subtractorizations[i - 1];
    }
}

int main() {
    sieve();  // Step 1: Generate all primes up to MAX_N
    precompute_subtractorizations();  // Step 2: Precompute all subtractorizations

    // Input handling
    int T;
    cin >> T;
    for (int t = 1; t <= T; ++t) {
        int N;
        cin >> N;
        // Output the precomputed result for this N
        cout << "Case #" << t << ": " << subtractorizations[N] << endl;
    }

    return 0;
}
