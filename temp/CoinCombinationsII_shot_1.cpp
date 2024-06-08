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
    
    vector<int> dp(x + 1, 0);
    dp[0] = 1; // One way to make sum 0 (using no coins)
    
    for (int coin : coins) {
        for (int j = coin; j <= x; j++) {
            dp[j] = (dp[j] + dp[j - coin]) % MOD;
        }
    }
    
    cout << dp[x] << endl;
    return 0;
}
