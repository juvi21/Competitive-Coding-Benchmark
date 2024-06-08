#include <iostream>
#include <vector>
#include <algorithm>

const int INF = 1e9;

int main() {
    int n, x;
    std::cin >> n >> x;

    std::vector<int> coins(n);
    for (int i = 0; i < n; i++) {
        std::cin >> coins[i];
    }

    std::vector<int> dp(x + 1, INF);
    dp[0] = 0;

    for (int i = 0; i < n; i++) {
        for (int j = coins[i]; j <= x; j++) {
            dp[j] = std::min(dp[j], dp[j - coins[i]] + 1);
        }
    }

    if (dp[x] == INF) {
        std::cout << -1 << std::endl;
    } else {
        std::cout << dp[x] << std::endl;
    }

    return 0;
}