#include <iostream>
#include <string>
#include <vector>
#include <cmath>

const int MOD = 1e9 + 7;
const int MAX_N = 1e6 + 5;

std::vector<long long> fact(MAX_N);
std::vector<long long> inv(MAX_N);
std::vector<int> cnt(26);

long long power(long long a, long long b) {
    long long res = 1;
    while (b > 0) {
        if (b & 1) res = (res * a) % MOD;
        a = (a * a) % MOD;
        b >>= 1;
    }
    return res;
}

void precompute() {
    fact[0] = 1;
    for (int i = 1; i < MAX_N; i++) {
        fact[i] = (fact[i - 1] * i) % MOD;
    }
    inv[MAX_N - 1] = power(fact[MAX_N - 1], MOD - 2);
    for (int i = MAX_N - 2; i >= 0; i--) {
        inv[i] = (inv[i + 1] * (i + 1)) % MOD;
    }
}

int main() {
    std::ios_base::sync_with_stdio(false);
    std::cin.tie(NULL);

    precompute();

    std::string s;
    std::cin >> s;

    int n = s.length();
    for (char c : s) {
        cnt[c - 'a']++;
    }

    long long ans = fact[n];
    for (int i = 0; i < 26; i++) {
        ans = (ans * inv[cnt[i]]) % MOD;
    }

    std::cout << ans << std::endl;

    return 0;
}