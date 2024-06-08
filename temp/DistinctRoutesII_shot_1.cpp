#include <bits/stdc++.h>
using namespace std;

const int INF = 1e9;

vector<int> adj[501];
vector<vector<int>> paths;
int n, m, k;
bool visited[501];
vector<int> path;

bool dfs(int u, int t) {
    if (u == t) {
        paths.push_back(path);
        return true;
    }
    visited[u] = true;
    for (int v : adj[u]) {
        if (!visited[v]) {
            path.push_back(v);
            if (dfs(v, t)) {
                if (paths.size() == k) return true;
            }
            path.pop_back();
        }
    }
    visited[u] = false;
    return false;
}

int main() {
    cin >> n >> m >> k;
    
    for (int i = 0; i < m; ++i) {
        int a, b;
        cin >> a >> b;
        adj[a].push_back(b);
    }
    
    path.push_back(1);
    memset(visited, false, sizeof(visited));
    
    if (!dfs(1, n) || paths.size() < k) {
        cout << -1 << endl;
        return 0;
    }
    
    int coins = 0;
    for (const auto& p : paths) {
        coins += p.size() - 1;
    }
    
    cout << coins << endl;
    for (const auto& p : paths) {
        cout << p.size() << endl;
        for (int room : p) {
            cout << room << " ";
        }
        cout << endl;
    }
    
    return 0;
}
