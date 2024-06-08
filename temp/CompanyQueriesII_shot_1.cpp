#include <iostream>
#include <vector>
#include <cmath>
using namespace std;

const int MAXN = 200001;
const int LOG = 19; // because 2^19 > 200000

vector<int> adj[MAXN];
int up[MAXN][LOG]; // up[v][j] is 2^j-th ancestor of node v
int depth[MAXN];

void dfs(int v, int p) {
    // Set the 2^0-th ancestor (parent)
    up[v][0] = p;
    // Set depths
    if (p != -1) depth[v] = depth[p] + 1;

    // Set all 2^j-th ancestors using dynamic programming
    for (int j = 1; j < LOG; j++) {
        if (up[v][j-1] != -1)
            up[v][j] = up[up[v][j-1]][j-1];
        else
            up[v][j] = -1;
    }

    for (int u : adj[v]) {
        if (u != p) {
            dfs(u, v);
        }
    }
}

int lca(int a, int b) {
    if (depth[a] < depth[b]) swap(a, b);

    // Lift node a up until both nodes are at the same depth
    int diff = depth[a] - depth[b];
    for (int j = LOG - 1; j >= 0; j--) {
        if ((diff >> j) & 1) {
            a = up[a][j];
        }
    }

    if (a == b) return a;

    // Lift both a and b up until their LCA is found
    for (int j = LOG - 1; j >= 0; j--) {
        if (up[a][j] != up[b][j]) {
            a = up[a][j];
            b = up[b][j];
        }
    }

    return up[a][0];
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    int n, q;
    cin >> n >> q;

    for (int i = 2; i <= n; i++) {
        int e_i;
        cin >> e_i;
        adj[e_i].push_back(i);
        adj[i].push_back(e_i); // Since it's an undirected tree
    }

    // Initialize the depth array
    depth[1] = 0;
    // Run DFS from the root (employee 1)
    dfs(1, -1);

    while (q--) {
        int a, b;
        cin >> a >> b;
        cout << lca(a, b) << '\n';
    }

    return 0;
}
