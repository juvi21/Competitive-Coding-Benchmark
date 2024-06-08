#include <iostream>
#include <vector>
using namespace std;

const int MOD = 1e9 + 7;

// Function to compute x^y % p using Iterative Function
long long power(long long x, unsigned int y, int p) {
    long long res = 1; // Initialize result
    x = x % p; // Update x if it is more than or equal to p
    while (y > 0) {
        // If y is odd, multiply x with result
        if (y & 1)
            res = (res * x) % p;
        // y must be even now
        y = y >> 1; // y = y/2
        x = (x * x) % p; // Change x to x^2
    }
    return res;
}

// Function to compute n! % p
void computeFactorials(int n, vector<long long>& fact, vector<long long>& invFact) {
    fact[0] = fact[1] = 1;
    for (int i = 2; i <= n; i++)
        fact[i] = fact[i - 1] * i % MOD;

    invFact[n] = power(fact[n], MOD - 2, MOD);
    for (int i = n - 1; i >= 0; i--)
        invFact[i] = invFact[i + 1] * (i + 1) % MOD;
}

// Function to compute nCr % p
long long nCr(int n, int r, const vector<long long>& fact, const vector<long long>& invFact) {
    if (r > n || r < 0) return 0;
    return fact[n] * invFact[r] % MOD * invFact[n - r] % MOD;
}

int main() {
    int n;
    cin >> n;

    if (n % 2 == 1) {
        cout << 0 << endl;
        return 0;
    }

    n /= 2; // We need Catalan number for n/2

    vector<long long> fact(2 * n + 1);
    vector<long long> invFact(2 * n + 1);

    computeFactorials(2 * n, fact, invFact);

    long long catalan = nCr(2 * n, n, fact, invFact) * power(n + 1, MOD - 2, MOD) % MOD;

    cout << catalan << endl;

    return 0;
}
