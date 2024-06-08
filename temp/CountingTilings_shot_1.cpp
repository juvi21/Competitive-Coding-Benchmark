#include <iostream>
#include <vector>
#include <cstring>
using namespace std;

const int MOD = 1000000007;

int n, m;
int dp[1001][1 << 10];

int solve(int col, int mask) {
    if (col == m) {
        return mask == 0;
    }
    if (dp[col][mask] != -1) {
        return dp[col][mask];
    }

    int &res = dp[col][mask];
    res = 0;
    vector<pair<int, int>> transitions;

    // Generate all transitions
    function<void(int, int)> genTransitions = [&](int pos, int curMask) {
        if (pos == n) {
            transitions.push_back({curMask, curMask ^ mask});
            return;
        }

        if ((curMask & (1 << pos)) == 0) {
            // Place vertical tile
            genTransitions(pos + 1, curMask | (1 << pos));
            // Place horizontal tiles if possible
            if (pos + 1 < n && (curMask & (1 << (pos + 1))) == 0) {
                genTransitions(pos + 2, curMask);
            }
        } else {
            genTransitions(pos + 1, curMask);
        }
    };

    genTransitions(0, 0);

    for (auto &t : transitions) {
        res = (res + solve(col + 1, t.second)) % MOD;
    }

    return res;
}

int main() {
    cin >> n >> m;
    memset(dp, -1, sizeof(dp));
    cout << solve(0, 0) << endl;
    return 0;
}
