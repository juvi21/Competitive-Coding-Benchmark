#include <iostream>
#include <vector>

const int MOD = 1e9 + 7;

// Function to perform modular exponentiation
long long modExp(long long base, long long exp, long long mod) {
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

    // Size of factorial array should be m + n - 1
    int maxFactorial = m + n - 1;
    
    // Precompute factorials and factorial inverses
    std::vector<long long> fact(maxFactorial + 1, 1);
    std::vector<long long> invFact(maxFactorial + 1, 1);

    for (int i = 2; i <= maxFactorial; ++i) {
        fact[i] = fact[i - 1] * i % MOD;
    }

    invFact[maxFactorial] = modExp(fact[maxFactorial], MOD - 2, MOD);
    for (int i = maxFactorial - 1; i >= 1; --i) {
        invFact[i] = invFact[i + 1] * (i + 1) % MOD;
    }

    // Calculate the binomial coefficient C(m + n - 1, n - 1)
    long long result = fact[m + n - 1] * invFact[n - 1] % MOD * invFact[m] % MOD;
    
    std::cout << result << std::endl;

    return 0;
}
