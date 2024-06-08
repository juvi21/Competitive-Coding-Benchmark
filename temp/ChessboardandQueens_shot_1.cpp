#include <iostream>
#include <vector>
using namespace std;

int countWays = 0;
vector<string> board(8);
vector<bool> columns(8, false);
vector<bool> diag1(15, false); // for the diagonals from top-left to bottom-right
vector<bool> diag2(15, false); // for the diagonals from top-right to bottom-left

void solve(int row) {
    if (row == 8) {
        countWays++;
        return;
    }
    for (int col = 0; col < 8; col++) {
        if (board[row][col] == '.' && !columns[col] && !diag1[row - col + 7] && !diag2[row + col]) {
            columns[col] = diag1[row - col + 7] = diag2[row + col] = true;
            solve(row + 1);
            columns[col] = diag1[row - col + 7] = diag2[row + col] = false;
        }
    }
}

int main() {
    for (int i = 0; i < 8; i++) {
        cin >> board[i];
    }
    solve(0);
    cout << countWays << endl;
    return 0;
}
