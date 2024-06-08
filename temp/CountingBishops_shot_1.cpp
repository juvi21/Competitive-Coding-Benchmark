#include <iostream>
#include <vector>
#define MOD 1000000007

using namespace std;

int main() {
    int n, k;
    cin >> n >> k;

    if (k > 2 * n - 2) {
        cout << 0 << endl;
        return 0;
    }

    vector<vector<int>> dp(2 * n, vector<int>(k + 1, 0));

    dp[0][0] = 1;

    for (int d = 1; d <= 2 * n - 1; ++d) {
        int maxBishops = (d <= n) ? d : 2 * n - d;
        for (int m = 0; m <= k; ++m) {
            dp[d][m] = dp[d - 1][m];
            for (int b = 1; b <= maxBishops && b <= m; ++b) {
                dp[d][m] = (dp[d][m] + dp[d - 1][m - b]) % MOD;
            }
        }
    }

    cout << dp[2 * n - 1][k] << endl;

    return 0;
}
