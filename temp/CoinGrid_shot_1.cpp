#include <iostream>
#include <vector>
using namespace std;

int main() {
    int n;
    cin >> n;
    vector<string> grid(n);
    for (int i = 0; i < n; ++i) {
        cin >> grid[i];
    }
    
    vector<bool> row_has_coin(n, false);
    vector<bool> col_has_coin(n, false);
    
    // Mark the rows and columns that contain coins
    for (int i = 0; i < n; ++i) {
        for (int j = 0; j < n; ++j) {
            if (grid[i][j] == 'o') {
                row_has_coin[i] = true;
                col_has_coin[j] = true;
            }
        }
    }
    
    vector<pair<int, int>> moves;
    
    // First, remove all rows that contain coins
    for (int i = 0; i < n; ++i) {
        if (row_has_coin[i]) {
            moves.push_back({1, i + 1});
        }
    }
    
    // Then, remove all columns that contain coins
    for (int j = 0; j < n; ++j) {
        if (col_has_coin[j]) {
            moves.push_back({2, j + 1});
        }
    }
    
    // Output the result
    cout << moves.size() << endl;
    for (auto move : moves) {
        cout << move.first << " " << move.second << endl;
    }
    
    return 0;
}
