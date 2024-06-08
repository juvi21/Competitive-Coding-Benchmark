#include <iostream>
#include <vector>

using namespace std;

const int MAXN = 200000;
const int LOG = 18; // log2(200000) is approximately 17.6, so we use 18

int up[MAXN + 1][LOG]; // up[i][j] is the 2^j-th ancestor of node i

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    int n, q;
    cin >> n >> q;

    // Read the direct bosses for employees 2 to n
    for (int i = 2; i <= n; ++i) {
        cin >> up[i][0]; // up[i][0] is the 1st ancestor (direct boss) of employee i
    }

    // Employee 1 is the general director and has no boss
    for (int j = 0; j < LOG; ++j) {
        up[1][j] = -1; // No ancestor exists for the general director
    }

    // Preprocess the up table for all powers of 2
    for (int j = 1; j < LOG; ++j) {
        for (int i = 2; i <= n; ++i) {
            if (up[i][j-1] != -1) {
                up[i][j] = up[up[i][j-1]][j-1];
            } else {
                up[i][j] = -1;
            }
        }
    }

    // Process each query
    while (q--) {
        int x, k;
        cin >> x >> k;

        for (int j = 0; j < LOG; ++j) {
            if (k & (1 << j)) {
                x = up[x][j];
                if (x == -1) break;
            }
        }

        cout << x << "\n";
    }

    return 0;
}
