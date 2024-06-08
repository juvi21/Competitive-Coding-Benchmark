#include <iostream>
#include <vector>
#include <bitset>

using namespace std;

const int MAX_N = 3000;

int main() {
    int n;
    cin >> n;
    vector<bitset<MAX_N>> grid(n);

    for (int i = 0; i < n; ++i) {
        string row;
        cin >> row;
        for (int j = 0; j < n; ++j) {
            grid[i][j] = (row[j] == '1');
        }
    }

    long long beautifulSubgrids = 0;

    for (int i = 0; i < n; ++i) {
        for (int j = i + 1; j < n; ++j) {
            int commonBlackCells = (grid[i] & grid[j]).count();
            if (commonBlackCells >= 2) {
                // number of ways to choose 2 out of commonBlackCells
                beautifulSubgrids += (commonBlackCells * (commonBlackCells - 1)) / 2;
            }
        }
    }

    cout << beautifulSubgrids << endl;
    return 0;
}
