#include <iostream>
#include <vector>
#include <queue>
#include <unordered_map>
#include <algorithm>

using namespace std;

int main() {
    int n, m;
    cin >> n >> m;
    
    vector<pair<int, int>> edges(m);
    vector<vector<int>> adj(n + 1);
    vector<int> in_degree(n + 1, 0);
    
    for (int i = 0; i < m; ++i) {
        int a, b;
        cin >> a >> b;
        edges[i] = {a, b};
        adj[a].push_back(b);
        adj[b].push_back(a);
    }
    
    vector<int> topo_order;
    vector<bool> visited(n + 1, false);
    
    for (int i = 1; i <= n; ++i) {
        if (!visited[i]) {
            queue<int> q;
            q.push(i);
            visited[i] = true;
            while (!q.empty()) {
                int node = q.front();
                q.pop();
                topo_order.push_back(node);
                for (int neighbor : adj[node]) {
                    if (!visited[neighbor]) {
                        visited[neighbor] = true;
                        q.push(neighbor);
                    }
                }
            }
        }
    }

    unordered_map<int, int> position;
    for (int i = 0; i < n; ++i) {
        position[topo_order[i]] = i;
    }

    vector<pair<int, int>> result;
    for (auto &[a, b] : edges) {
        if (position[a] < position[b]) {
            result.push_back({a, b});
        } else {
            result.push_back({b, a});
        }
    }
    
    for (auto &[a, b] : result) {
        cout << a << " " << b << endl;
    }

    return 0;
}
