#include <iostream>
#include <vector>
using namespace std;

vector<vector<int>> tree;
vector<int> path_count;
vector<int> subtree_count;

void dfs(int node, int parent) {
    for(int neighbor : tree[node]) {
        if(neighbor == parent) continue;
        dfs(neighbor, node);
        subtree_count[node] += subtree_count[neighbor];
    }
    path_count[node] += subtree_count[node];
}

int main() {
    int n, m;
    cin >> n >> m;
    
    tree.resize(n + 1);
    path_count.resize(n + 1, 0);
    subtree_count.resize(n + 1, 0);
    
    for(int i = 0; i < n - 1; i++) {
        int a, b;
        cin >> a >> b;
        tree[a].push_back(b);
        tree[b].push_back(a);
    }
    
    for(int i = 0; i < m; i++) {
        int a, b;
        cin >> a >> b;
        subtree_count[a]++;
        subtree_count[b]++;
    }
    
    dfs(1, -1);
    
    for(int i = 1; i <= n; i++) {
        cout << path_count[i] << " ";
    }
    cout << endl;
    
    return 0;
}
