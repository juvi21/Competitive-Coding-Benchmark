#include <iostream>
#include <vector>
#include <cstring>

typedef long long ll;

ll dp[20][2][10];

std::vector<int> getDigits(ll x) {
    std::vector<int> digits;
    while (x > 0) {
        digits.push_back(x % 10);
        x /= 10;
    }
    reverse(digits.begin(), digits.end());
    return digits;
}

ll countNumbers(std::vector<int>& digits, int pos, bool tight, int prev) {
    if (pos == digits.size()) return 1;
    if (dp[pos][tight][prev] != -1) return dp[pos][tight][prev];
    
    int limit = tight ? digits[pos] : 9;
    ll res = 0;
    
    for (int d = 0; d <= limit; d++) {
        if (d != prev) {
            res += countNumbers(digits, pos + 1, tight && (d == limit), d);
        }
    }
    
    return dp[pos][tight][prev] = res;
}

ll countValidNumbers(ll x) {
    if (x < 0) return 0;
    if (x == 0) return 1;
    
    std::vector<int> digits = getDigits(x);
    memset(dp, -1, sizeof(dp));
    return countNumbers(digits, 0, true, 10);
}

int main() {
    ll a, b;
    std::cin >> a >> b;
    
    ll result = countValidNumbers(b) - countValidNumbers(a - 1);
    std::cout << result << std::endl;
    
    return 0;
}
