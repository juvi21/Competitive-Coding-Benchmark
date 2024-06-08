#include <iostream>
#include <vector>

using namespace std;

void dfs(int i, int j, int n, int m, vector<vector<char>>& map, vector<vector<bool>>& visited) {
    if (i < 0 || i >= n || j < 0 || j >= m || map[i][j] == '#' || visited[i][j])
        return;
    visited[i][j] = true;
    dfs(i + 1, j, n, m, map, visited); // down
    dfs(i - 1, j, n, m, map, visited); // up
    dfs(i, j + 1, n, m, map, visited); // right
    dfs(i, j - 1, n, m, map, visited); // left
}

int main() {
    int n, m;
    cin >> n >> m;
    
    vector<vector<char>> map(n, vector<char>(m));
    vector<vector<bool>> visited(n, vector<bool>(m, false));
    
    for (int i = 0; i < n; ++i) {
        for (int j = 0; j < m; ++j) {
            cin >> map[i][j];
        }
    }
    
    int roomCount = 0;
    for (int i = 0; i < n; ++i) {
        for (int j = 0; j < m; ++j) {
            if (map[i][j] == '.' && !visited[i][j]) {
                dfs(i, j, n, m, map, visited);
                roomCount++;
            }
        }
    }
    
    cout << roomCount << endl;
    
    return 0;
}
