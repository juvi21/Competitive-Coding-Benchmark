#include <iostream>
#include <vector>

using namespace std;

const int N = 8;
vector<vector<bool>> board(N, vector<bool>(N));
vector<bool> col(N, false);
vector<bool> diag1(2 * N - 1, false);
vector<bool> diag2(2 * N - 1, false);
int count = 0;

bool is_safe(int row, int col) {
    return !diag1[row + col] && !diag2[row - col + N - 1];
}

void place_queens(int row) {
    if (row == N) {
        count++;
        return;
    }
    for (int i = 0; i < N; i++) {
        if (board[row][i] && !col[i] && is_safe(row, i)) {
            col[i] = true;
            diag1[row + i] = true;
            diag2[row - i + N - 1] = true;
            place_queens(row + 1);
            col[i] = false;
            diag1[row + i] = false;
            diag2[row - i + N - 1] = false;
        }
    }
}

int main() {
    char c;
    for (int i = 0; i < N; i++) {
        for (int j = 0; j < N; j++) {
            cin >> c;
            board[i][j] = (c == '.');
        }
    }
    place_queens(0);
    cout << count << endl;
    return 0;
}