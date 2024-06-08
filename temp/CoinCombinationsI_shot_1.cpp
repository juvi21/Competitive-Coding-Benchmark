#include <iostream>
#include <vector>
using namespace std;

const int MOD = 1e9 + 7;

int main() {
    int n, x;
    cin >> n >> x;
    vector<int> coins(n);
    for (int i = 0; i < n; i++) {
        cin >> coins[i];
    }

    // Create a DP array initialized to 0
    vector<int> dp(x + 1, 0);
    dp[0] = 1; // There's one way to make the sum 0, by using no coins

    // Iterate over all sums from 1 to x
    for (int sum = 1; sum <= x; sum++) {
        for (int j = 0; j < n; j++) {
            if (sum - coins[j] >= 0) {
                dp[sum] = (dp[sum] + dp[sum - coins[j]]) % MOD;
            }
        }
    }

    // Print the number of ways to form the sum x
    cout << dp[x] << endl;
    return 0;
}
