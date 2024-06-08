#include <iostream>
#include <vector>
#include <algorithm>
using namespace std;

const int MOD = 1e9 + 7;

int main() {
    int n, x;
    cin >> n >> x;
    vector<int> t(n);
    for (int i = 0; i < n; ++i) {
        cin >> t[i];
    }
    
    sort(t.begin(), t.end());
    
    vector<vector<int>> dp(n + 1, vector<int>(x + 1, 0));
    dp[0][0] = 1;
    
    for (int i = 1; i <= n; ++i) {
        for (int j = 0; j <= x; ++j) {
            dp[i][j] = dp[i - 1][j]; // not including the current coder in a new team
            for (int k = 0; k < i; ++k) {
                int penalty = t[i - 1] - t[k];
                if (j >= penalty) {
                    dp[i][j] = (dp[i][j] + dp[k][j - penalty]) % MOD;
                }
            }
        }
    }
    
    int result = 0;
    for (int j = 0; j <= x; ++j) {
        result = (result + dp[n][j]) % MOD;
    }
    
    cout << result << endl;
    return 0;
}
