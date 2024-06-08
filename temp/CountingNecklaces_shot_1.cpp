#include <iostream>
#include <vector>
#include <numeric>
#include <cmath>

const int MOD = 1000000007;

// Function to compute (base^exp) % mod
long long mod_pow(long long base, long long exp, long long mod) {
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
    int n, m;
    std::cin >> n >> m;

    long long result = 0;
    
    for (int k = 0; k < n; ++k) {
        // Compute gcd(n, k)
        int g = std::gcd(n, k);
        // Number of fixed necklaces for this rotation
        result = (result + mod_pow(m, g, MOD)) % MOD;
    }
    
    // Divide by n using modular multiplicative inverse of n % MOD
    long long n_inv = mod_pow(n, MOD - 2, MOD);
    result = (result * n_inv) % MOD;
    
    std::cout << result << std::endl;
    return 0;
}
