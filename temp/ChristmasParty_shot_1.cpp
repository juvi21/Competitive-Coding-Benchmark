#include <iostream>
#include <vector>
#define MOD 1000000007

using namespace std;

int main() {
    int n;
    cin >> n;

    if (n == 0) {
        cout << 1 << endl;
        return 0;
    } else if (n == 1) {
        cout << 0 << endl;
        return 0;
    }

    vector<long long> dp(n + 1);

    dp[0] = 1; // By convention
    dp[1] = 0; // No way to derange 1 item
    dp[2] = 1; // Only one way to derange 2 items

    for (int i = 3; i <= n; ++i) {
        dp[i] = (i - 1) * (dp[i - 1] + dp[i - 2]) % MOD;
    }

    cout << dp[n] << endl;

    return 0;
}
