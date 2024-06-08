#include <iostream>
#include <vector>
#include <set>
using namespace std;

void dfs(int node, int parent, const vector<vector<int>> &adj, const vector<int> &colors, vector<set<int>> &subtree_colors, vector<int> &result) {
    subtree_colors[node].insert(colors[node - 1]);
    
    for (int neighbor : adj[node]) {
        if (neighbor == parent) continue;
        dfs(neighbor, node, adj, colors, subtree_colors, result);
        // Merge the sets
        if (subtree_colors[neighbor].size() > subtree_colors[node].size()) {
            swap(subtree_colors[neighbor], subtree_colors[node]);
        }
        subtree_colors[node].insert(subtree_colors[neighbor].begin(), subtree_colors[neighbor].end());
    }
    
    result[node - 1] = subtree_colors[node].size();
}

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    
    int n;
    cin >> n;
    
    vector<int> colors(n);
    for (int i = 0; i < n; ++i) {
        cin >> colors[i];
    }
    
    vector<vector<int>> adj(n + 1);
    for (int i = 0; i < n - 1; ++i) {
        int a, b;
        cin >> a >> b;
        adj[a].push_back(b);
        adj[b].push_back(a);
    }
    
    vector<set<int>> subtree_colors(n + 1);
    vector<int> result(n);
    
    dfs(1, -1, adj, colors, subtree_colors, result);
    
    for (int i = 0; i < n; ++i) {
        cout << result[i] << " ";
    }
    
    return 0;
}
