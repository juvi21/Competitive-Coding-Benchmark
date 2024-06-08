#include <iostream>
#include <vector>
#include <stack>

using namespace std;

void dfs(int node, vector<vector<int>>& adj, vector<bool>& visited) {
    stack<int> s;
    s.push(node);
    while (!s.empty()) {
        int v = s.top();
        s.pop();
        for (auto u : adj[v]) {
            if (!visited[u]) {
                visited[u] = true;
                s.push(u);
            }
        }
    }
}

int main() {
    int n, m;
    cin >> n >> m;
    
    vector<vector<int>> adj(n + 1);
    for (int i = 0; i < m; ++i) {
        int a, b;
        cin >> a >> b;
        adj[a].push_back(b);
        adj[b].push_back(a);
    }
    
    vector<bool> visited(n + 1, false);
    vector<int> representatives;
    
    for (int i = 1; i <= n; ++i) {
        if (!visited[i]) {
            representatives.push_back(i);
            visited[i] = true;
            dfs(i, adj, visited);
        }
    }
    
    int k = representatives.size() - 1;
    cout << k << "\n";
    for (int i = 1; i < representatives.size(); ++i) {
        cout << representatives[i - 1] << " " << representatives[i] << "\n";
    }
    
    return 0;
}
