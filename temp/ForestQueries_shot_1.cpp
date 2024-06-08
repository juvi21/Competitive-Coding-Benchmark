#include <iostream>
#include <vector>

using namespace std;

int main() {
    int n, q;
    cin >> n >> q;

    vector<vector<int>> forest(n + 1, vector<int>(n + 1));
    vector<vector<int>> prefixSum(n + 1, vector<int>(n + 1));

    for (int i = 1; i <= n; i++) {
        for (int j = 1; j <= n; j++) {
            char c;
            cin >> c;
            forest[i][j] = (c == '*');
            prefixSum[i][j] = prefixSum[i - 1][j] + prefixSum[i][j - 1] - prefixSum[i - 1][j - 1] + forest[i][j];
        }
    }

    for (int i = 0; i < q; i++) {
        int y1, x1, y2, x2;
        cin >> y1 >> x1 >> y2 >> x2;
        cout << prefixSum[y2][x2] - prefixSum[y1 - 1][x2] - prefixSum[y2][x1 - 1] + prefixSum[y1 - 1][x1 - 1] << endl;
    }

    return 0;
}