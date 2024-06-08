#include <iostream>
#include <cmath>
using namespace std;

const int MOD = 1000000007;

long long power(long long base, long long exp, long long mod) {
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
    long long n;
    cin >> n;

    long long total = power(2, n * n, MOD);

    long long fixed0 = total;
    long long fixed180 = (n % 2 == 0) ? power(2, (n * n) / 2, MOD) : power(2, (n * n + 1) / 2, MOD);
    long long fixed90 = (n % 4 == 0) ? power(2, (n * n + 3) / 4, MOD) : 0;
    long long fixed270 = fixed90;

    long long distinct_grids = (fixed0 + fixed90 + fixed180 + fixed270) % MOD;
    distinct_grids = (distinct_grids * power(4, MOD - 2, MOD)) % MOD;

    cout << distinct_grids << endl;

    return 0;
}
