#include <iostream>
#include <vector>

const int MOD = 1000000007;

using namespace std;

// Function to compute x^y % p using iterative method
long long power(long long x, long long y, long long p) {
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

// Function to compute nCr % p
long long nCrModP(long long n, long long r, long long p) {
    if (r == 0)
        return 1;
    vector<long long> fac(n + 1, 1);
    for (long long i = 2; i <= n; ++i)
        fac[i] = fac[i - 1] * i % p;
    return (fac[n] * power(fac[r], p - 2, p) % p * power(fac[n - r], p - 2, p) % p) % p;
}

int main() {
    long long n, k;
    cin >> n >> k;
    
    long long result = 0;
    for (long long i = 0; i <= k; ++i) {
        long long term = nCrModP(k, i, MOD) * power(k - i, n, MOD) % MOD;
        if (i % 2 == 0) {
            result = (result + term) % MOD;
        } else {
            result = (result - term + MOD) % MOD;
        }
    }
    
    cout << result << endl;
    return 0;
}
