#include <iostream>
#include <vector>
using namespace std;

const int MOD = 1e9 + 7;

int countWays(int n) {
    vector<int> dp(n + 1, 0);
    dp[0] = 1;
    for (int i = 1; i <= n; i++) {
        for (int j = 1; j <= 6 && j <= i; j++) {
            dp[i] = (dp[i] + dp[i - j]) % MOD;
        }
    }
    return dp[n];
}

int main() {
    int n;
    cin >> n;
    cout << countWays(n) << endl;
    return 0;
}