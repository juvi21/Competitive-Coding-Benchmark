#include <bits/stdc++.h>
using namespace std;

const int MAXN = 200000;
vector<int> adj[MAXN + 1];
vector<int> depth(MAXN + 1, -1);
vector<int> offices;

void dfs(int node, int parent, int d) {
    bool canPlaceOffice = true;
    for (int neighbor : adj[node]) {
        if (neighbor == parent) continue;
        depth[neighbor] = depth[node] + 1;
        dfs(neighbor, node, d);
        if (depth[neighbor] - depth[node] < d) {
            canPlaceOffice = false;
        }
    }
    if (canPlaceOffice) {
        offices.push_back(node);
        depth[node] = 0; // Reset the depth for subtree to prevent placing nearby offices
    }
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    int n, d;
    cin >> n >> d;
    
    for (int i = 0; i < n - 1; ++i) {
        int a, b;
        cin >> a >> b;
        adj[a].push_back(b);
        adj[b].push_back(a);
    }
    
    // Start DFS from node 1 (or any arbitrary node)
    depth[1] = 0;
    dfs(1, -1, d);
    
    cout << offices.size() << "\n";
    for (int city : offices) {
        cout << city << " ";
    }
    cout << "\n";
    
    return 0;
}
