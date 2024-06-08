#include <iostream>
#include <vector>
#include <stack>
#include <algorithm>

using namespace std;

const int MAXN = 100000;
vector<int> adj[MAXN];
vector<int> adjRev[MAXN];
bool visited[MAXN];
stack<int> finished;
vector<int> component;
int coins[MAXN];

void dfs1(int v) {
    visited[v] = true;
    for (int u : adj[v]) {
        if (!visited[u]) {
            dfs1(u);
        }
    }
    finished.push(v);
}

void dfs2(int v) {
    visited[v] = true;
    component.push_back(v);
    for (int u : adjRev[v]) {
        if (!visited[u]) {
            dfs2(u);
        }
    }
}

int main() {
    int n, m;
    cin >> n >> m;
    
    for (int i = 0; i < n; i++) {
        cin >> coins[i];
    }
    
    for (int i = 0; i < m; i++) {
        int a, b;
        cin >> a >> b;
        a--; b--;  // Convert to 0-based index
        adj[a].push_back(b);
        adjRev[b].push_back(a);
    }
    
    // Step 1: Perform DFS on the original graph to fill the finished stack
    fill(visited, visited + n, false);
    for (int i = 0; i < n; i++) {
        if (!visited[i]) {
            dfs1(i);
        }
    }
    
    // Step 2: Perform DFS on the reversed graph
    fill(visited, visited + n, false);
    int maxCoins = 0;
    
    while (!finished.empty()) {
        int v = finished.top();
        finished.pop();
        
        if (!visited[v]) {
            component.clear();
            dfs2(v);
            int sumCoins = 0;
            for (int u : component) {
                sumCoins += coins[u];
            }
            maxCoins = max(maxCoins, sumCoins);
        }
    }
    
    cout << maxCoins << endl;
    
    return 0;
}
