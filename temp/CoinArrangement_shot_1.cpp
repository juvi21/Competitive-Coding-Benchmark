#include <iostream>
#include <vector>
#include <cmath>
using namespace std;

int main() {
    int n;
    cin >> n;
    
    vector<int> grid[2];
    for (int i = 0; i < 2; ++i) {
        grid[i].resize(n);
        for (int j = 0; j < n; ++j) {
            cin >> grid[i][j];
        }
    }
    
    vector<int> excess;
    vector<int> deficit;
    
    for (int i = 0; i < 2; ++i) {
        for (int j = 0; j < n; ++j) {
            int coins = grid[i][j];
            if (coins > 1) {
                for (int k = 0; k < coins - 1; ++k) {
                    excess.push_back(i * n + j); // Flatten the 2D coordinates
                }
            } else if (coins == 0) {
                deficit.push_back(i * n + j); // Flatten the 2D coordinates
            }
        }
    }
    
    int moves = 0;
    for (int i = 0; i < excess.size(); ++i) {
        moves += abs(excess[i] / n - deficit[i] / n) + abs(excess[i] % n - deficit[i] % n);
    }
    
    cout << moves << endl;
    
    return 0;
}
