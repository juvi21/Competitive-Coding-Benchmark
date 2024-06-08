#include <iostream>
#include <vector>
#include <string>

const int MOD = 1000000007;

using namespace std;

// Function to check if the prefix is a valid bracket sequence
bool isValidPrefix(const string& prefix) {
    int balance = 0;
    for (char ch : prefix) {
        if (ch == '(') balance++;
        else balance--;
        if (balance < 0) return false;
    }
    return true;
}

int main() {
    int n;
    string prefix;
    cin >> n >> prefix;
    
    int k = prefix.length();
    
    // If prefix is invalid, return 0
    if (!isValidPrefix(prefix)) {
        cout << 0 << endl;
        return 0;
    }
    
    // Calculate the balance of the given prefix
    int balance = 0;
    for (char ch : prefix) {
        if (ch == '(') balance++;
        else balance--;
    }
    
    // DP table: dp[i][j] means number of valid sequences of length i with balance j
    vector<vector<int>> dp(n + 1, vector<int>(n + 1, 0));
    dp[k][balance] = 1;
    
    // Fill the DP table
    for (int i = k; i < n; ++i) {
        for (int j = 0; j <= n; ++j) {
            if (dp[i][j] > 0) {
                if (j + 1 <= n) {
                    dp[i + 1][j + 1] = (dp[i + 1][j + 1] + dp[i][j]) % MOD;
                }
                if (j - 1 >= 0) {
                    dp[i + 1][j - 1] = (dp[i + 1][j - 1] + dp[i][j]) % MOD;
                }
            }
        }
    }
    
    // The answer is dp[n][0] because we want a balance of 0 at length n
    cout << dp[n][0] << endl;
    
    return 0;
}
