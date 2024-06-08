#include <iostream>
#include <vector>
#include <cmath>

using namespace std;

const int MOD = 1000000007;

long long mod_exp(long long base, long long exp, long long mod) {
    long long result = 1;
    while (exp > 0) {
        if (exp % 2 == 1) {
            result = (result * base) % mod;
        }
        base = (base * base) % mod;
        exp /= 2;
    }
    return result;
}

int main() {
    int n;
    cin >> n;
    vector<pair<long long, long long>> factors(n);
    for (int i = 0; i < n; ++i) {
        cin >> factors[i].first >> factors[i].second;
    }

    long long num_divisors = 1;
    long long sum_divisors = 1;
    long long product_divisors = 1;
    long long total_divisors = 1;

    for (const auto& factor : factors) {
        long long p = factor.first;
        long long k = factor.second;

        num_divisors = (num_divisors * (k + 1)) % MOD;

        // Calculate sum of divisors for this prime factor
        long long term = mod_exp(p, k + 1, MOD) - 1;
        if (term < 0) term += MOD;
        long long inv = mod_exp(p - 1, MOD - 2, MOD);
        long long sum_term = (term * inv) % MOD;
        sum_divisors = (sum_divisors * sum_term) % MOD;

        total_divisors = (total_divisors * (k + 1)) % (MOD - 1);
        product_divisors = (product_divisors * mod_exp(mod_exp(p, k * (k + 1) / 2, MOD), num_divisors / (k + 1), MOD)) % MOD;
    }

    cout << num_divisors << " " << sum_divisors << " " << product_divisors << endl;
    return 0;
}
