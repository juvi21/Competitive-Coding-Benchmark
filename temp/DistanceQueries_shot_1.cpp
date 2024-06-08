#include <iostream>
#include <vector>
#include <algorithm>

using namespace std;

const int MAXN = 200005;
const int LOG = 20;

vector<int> adj[MAXN];
int up[MAXN][LOG]; // up[i][j] is the 2^j-th ancestor of node i
int depth[MAXN];

// DFS function to set up depth and up table
void dfs(int v, int p) {
    up[v][0] = p;
    for (int i = 1; i < LOG; ++i) {
        if (up[v][i-1] != -1) {
            up[v][i] = up[up[v][i-1]][i-1];
        } else {
            up[v][i] = -1;
        }
    }
    for (int u : adj[v]) {
        if (u != p) {
            depth[u] = depth[v] + 1;
            dfs(u, v);
        }
    }
}

// Function to find the LCA of nodes a and b
int lca(int a, int b) {
    if (depth[a] < depth[b]) swap(a, b);
    int k = depth[a] - depth[b];
    for (int i = 0; i < LOG; ++i) {
        if (k & (1 << i)) {
            a = up[a][i];
        }
    }
    if (a == b) return a;
    for (int i = LOG-1; i >= 0; --i) {
        if (up[a][i] != up[b][i]) {
            a = up[a][i];
            b = up[b][i];
        }
    }
    return up[a][0];
}

// Function to calculate the distance between nodes a and b
int distance(int a, int b) {
    int l = lca(a, b);
    return depth[a] + depth[b] - 2 * depth[l];
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    
    int n, q;
    cin >> n >> q;
    
    for (int i = 0; i < n-1; ++i) {
        int a, b;
        cin >> a >> b;
        adj[a].push_back(b);
        adj[b].push_back(a);
    }
    
    depth[1] = 0;
    dfs(1, -1);
    
    while (q--) {
        int a, b;
        cin >> a >> b;
        cout << distance(a, b) << "\n";
    }
    
    return 0;
}
