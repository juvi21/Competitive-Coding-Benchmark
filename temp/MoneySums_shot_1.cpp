#include <iostream>
#include <vector>
#include <algorithm>

using namespace std;

int main() {
    int n;
    cin >> n;

    vector<int> coins(n);
    int sum = 0;
    for (int i = 0; i < n; i++) {
        cin >> coins[i];
        sum += coins[i];
    }

    vector<bool> dp(sum + 1, false);
    dp[0] = true;

    for (int i = 0; i < n; i++) {
        for (int j = sum; j >= coins[i]; j--) {
            dp[j] = dp[j] || dp[j - coins[i]];
        }
    }

    int count = 0;
    for (int i = 1; i <= sum; i++) {
        if (dp[i]) {
            count++;
        }
    }

    cout << count << endl;

    for (int i = 1; i <= sum; i++) {
        if (dp[i]) {
            cout << i << " ";
        }
    }

    return 0;
}