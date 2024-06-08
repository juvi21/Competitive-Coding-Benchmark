#include <iostream>
#include <vector>
#include <string>
#include <algorithm>

const int MOD = 1e9 + 7;

int main() {
    std::string s;
    std::cin >> s;
    int n = s.size();

    // Step 1: Calculate frequency of each character
    std::vector<int> freq(26, 0);
    for (char c : s) {
        freq[c - 'a']++;
    }

    // Step 2: Dynamic Programming
    std::vector<int> dp(n + 1, 0);
    dp[0] = 1; // There is one way to arrange 0 characters
    
    for (int i = 0; i < n; ++i) {
        std::vector<int> new_dp(n + 1, 0);
        for (int j = 0; j < 26; ++j) {
            if (freq[j] > 0) {
                for (int k = 0; k < 26; ++k) {
                    if (j != k && freq[k] > 0) {
                        new_dp[j] = (new_dp[j] + dp[k]) % MOD;
                    }
                }
            }
        }
        dp = new_dp;
    }

    // Step 3: Sum up all valid permutations of length n
    int result = 0;
    for (int i = 0; i < 26; ++i) {
        result = (result + dp[i]) % MOD;
    }

    std::cout << result << std::endl;

    return 0;
}
