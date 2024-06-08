#include <iostream>
#include <vector>
#define MOD 1000000007

using namespace std;

int main() {
    int t;
    cin >> t;

    vector<int> queries(t);
    int max_n = 0;
    for (int i = 0; i < t; ++i) {
        cin >> queries[i];
        if (queries[i] > max_n) {
            max_n = queries[i];
        }
    }

    // Dynamic programming arrays
    vector<long long> dp1(max_n + 1, 0);
    vector<long long> dp2(max_n + 1, 0);

    // Initial conditions
    dp1[1] = 1;
    dp2[1] = 1;

    // Fill the dp arrays
    for (int i = 2; i <= max_n; ++i) {
        dp1[i] = (dp1[i-1] + dp2[i-1]) % MOD;
        dp2[i] = dp1[i-2] % MOD;
    }

    // Compute results for all test cases
    for (int i = 0; i < t; ++i) {
        int n = queries[i];
        long long result = (dp1[n] + dp2[n]) % MOD;
        cout << result << endl;
    }

    return 0;
}
