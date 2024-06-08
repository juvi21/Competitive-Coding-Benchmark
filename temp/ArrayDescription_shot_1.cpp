#include <iostream>
#include <vector>
using namespace std;

const int MOD = 1e9 + 7;

int main() {
    int n, m;
    cin >> n >> m;
    vector<int> x(n);
    for (int i = 0; i < n; i++) {
        cin >> x[i];
    }

    vector<vector<int>> dp(n + 1, vector<int>(m + 1, 0));

    // Initialize the base case
    if (x[0] == 0) {
        for (int j = 1; j <= m; j++) {
            dp[1][j] = 1;
        }
    } else {
        dp[1][x[0]] = 1;
    }

    // Fill the dp table
    for (int i = 2; i <= n; i++) {
        if (x[i - 1] == 0) {
            for (int k = 1; k <= m; k++) {
                dp[i][k] = ((k > 1 ? dp[i - 1][k - 1] : 0) + dp[i - 1][k] + (k < m ? dp[i - 1][k + 1] : 0)) % MOD;
            }
        } else {
            int k = x[i - 1];
            dp[i][k] = ((k > 1 ? dp[i - 1][k - 1] : 0) + dp[i - 1][k] + (k < m ? dp[i - 1][k + 1] : 0)) % MOD;
        }
    }

    // Calculate the result
    int result = 0;
    for (int j = 1; j <= m; j++) {
        result = (result + dp[n][j]) % MOD;
    }

    cout << result << endl;

    return 0;
}
