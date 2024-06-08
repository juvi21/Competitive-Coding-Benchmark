#include <iostream>
#include <cmath>

const int MOD = 1e9 + 7;

// Function to calculate (base^exponent)%MOD
long long power(long long base, long long exponent) {
    long long result = 1;
    while (exponent > 0) {
        if (exponent % 2 == 1)
            result = (result * base) % MOD;
        base = (base * base) % MOD;
        exponent = exponent / 2;
    }
    return result;
}

// Function to calculate the inverse of a number
long long inverse(long long number) {
    return power(number, MOD - 2);
}

// Function to calculate the number of ways to distribute m apples to n children
long long countWays(int n, int m) {
    long long numerator = 1;
    long long denominator = 1;

    // Calculate the numerator (m+n-1)!
    for (int i = m + n - 1; i >= m + 1; i--) {
        numerator = (numerator * i) % MOD;
    }

    // Calculate the denominator (n-1)!
    for (int i = n - 1; i >= 2; i--) {
        denominator = (denominator * i) % MOD;
    }

    // Return the number of ways modulo MOD
    return (numerator * inverse(denominator)) % MOD;
}

int main() {
    int n, m;
    std::cin >> n >> m;

    // Print the number of ways to distribute the apples
    std::cout << countWays(n, m) << std::endl;
    return 0;
}