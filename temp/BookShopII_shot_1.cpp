#include <iostream>
#include <vector>
#include <algorithm>

using namespace std;

int main() {
    int n, x;
    cin >> n >> x;

    vector<int> prices(n), pages(n), copies(n);
    for (int i = 0; i < n; ++i) {
        cin >> prices[i];
    }
    for (int i = 0; i < n; ++i) {
        cin >> pages[i];
    }
    for (int i = 0; i < n; ++i) {
        cin >> copies[i];
    }

    vector<int> dp(x + 1, 0);

    for (int i = 0; i < n; ++i) {
        for (int c = 1; c <= copies[i]; ++c) {
            for (int j = x; j >= prices[i]; --j) {
                dp[j] = max(dp[j], dp[j - prices[i]] + pages[i]);
            }
        }
    }

    cout << dp[x] << endl;

    return 0;
}
