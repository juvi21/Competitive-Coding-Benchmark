#include <iostream>
#include <vector>
#include <iomanip>

using namespace std;

int main() {
    int n, a, b;
    cin >> n >> a >> b;

    // DP table where dp[i][j] is the number of ways to get sum j with i dice
    vector<vector<long long>> dp(n + 1, vector<long long>(6 * n + 1, 0));
    
    // Base case: 1 way to get sum 0 with 0 dice
    dp[0][0] = 1;

    // Fill the DP table
    for (int dice = 1; dice <= n; ++dice) {
        for (int sum = dice; sum <= 6 * dice; ++sum) {
            for (int face = 1; face <= 6; ++face) {
                if (sum - face >= 0) {
                    dp[dice][sum] += dp[dice - 1][sum - face];
                }
            }
        }
    }

    // Calculate the total number of valid outcomes
    long long valid_outcomes = 0;
    for (int sum = a; sum <= b; ++sum) {
        valid_outcomes += dp[n][sum];
    }

    // Total number of possible outcomes
    long long total_outcomes = 1;
    for (int i = 0; i < n; ++i) {
        total_outcomes *= 6;
    }

    // Calculate the probability
    double probability = (double)valid_outcomes / total_outcomes;

    // Print the result rounded to six decimal places
    cout << fixed << setprecision(6) << probability << endl;

    return 0;
}
