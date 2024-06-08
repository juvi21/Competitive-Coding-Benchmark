#include <iostream>
#include <vector>
#include <string>
#define MOD 1000000007
using namespace std;

// Function to compute factorial % MOD
vector<long long> compute_factorials(int max_n) {
    vector<long long> fact(max_n + 1, 1);
    for (int i = 2; i <= max_n; ++i) {
        fact[i] = fact[i-1] * i % MOD;
    }
    return fact;
}

// Function to compute modular inverses using Fermat's Little Theorem
vector<long long> compute_inverses(const vector<long long>& fact) {
    int max_n = fact.size() - 1;
    vector<long long> inv(max_n + 1, 1);
    inv[max_n] = 1;  // fact[max_n]^(MOD-2) % MOD
    for (int i = max_n - 1; i >= 0; --i) {
        inv[i] = inv[i + 1] * (i + 1) % MOD;
    }
    return inv;
}

int main() {
    string s;
    cin >> s;

    int n = s.size();
    vector<long long> fact = compute_factorials(n);
    vector<long long> inv = compute_inverses(fact);

    // Count frequencies of each character
    vector<int> freq(26, 0);
    for (char c : s) {
        freq[c - 'a']++;
    }

    // Calculate the number of distinct permutations
    long long result = fact[n];
    for (int count : freq) {
        if (count > 0) {
            result = result * inv[count] % MOD;
        }
    }

    cout << result << endl;
    return 0;
}
