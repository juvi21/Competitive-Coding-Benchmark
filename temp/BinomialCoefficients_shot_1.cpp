#include <iostream>
#include <vector>

const int MOD = 1e9 + 7;
const int MAX_A = 1e6;

std::vector<long long> fact(MAX_A + 1);
std::vector<long long> invFact(MAX_A + 1);

// Function to compute x^y % p using binary exponentiation
long long modExp(long long x, long long y, long long p) {
    long long res = 1;
    x = x % p;
    while (y > 0) {
        if (y & 1)
            res = (res * x) % p;
        y = y >> 1;
        x = (x * x) % p;
    }
    return res;
}

// Precompute factorials and their inverses
void precomputeFactorials() {
    fact[0] = 1;
    for (int i = 1; i <= MAX_A; ++i) {
        fact[i] = fact[i - 1] * i % MOD;
    }
    invFact[MAX_A] = modExp(fact[MAX_A], MOD - 2, MOD); // Fermat's little theorem
    for (int i = MAX_A - 1; i >= 0; --i) {
        invFact[i] = invFact[i + 1] * (i + 1) % MOD;
    }
}

// Function to compute binomial coefficient C(a, b) % MOD
long long binomialCoefficient(int a, int b) {
    if (b > a) return 0;
    return fact[a] * invFact[b] % MOD * invFact[a - b] % MOD;
}

int main() {
    precomputeFactorials();
    int n;
    std::cin >> n;
    while (n--) {
        int a, b;
        std::cin >> a >> b;
        std::cout << binomialCoefficient(a, b) << std::endl;
    }
    return 0;
}
