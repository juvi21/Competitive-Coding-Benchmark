#include <iostream>
#include <vector>
using namespace std;

const int MOD = 1000000007;

int main() {
    int n;
    cin >> n;
    
    vector<int> dp(n + 1, 0);
    dp[0] = 1; // Base case: There's one way to get a sum of 0 (no dice thrown)
    
    for (int i = 1; i <= n; ++i) {
        for (int j = 1; j <= 6; ++j) {
            if (i - j >= 0) {
                dp[i] = (dp[i] + dp[i - j]) % MOD;
            }
        }
    }
    
    cout << dp[n] << endl;
    return 0;
}
