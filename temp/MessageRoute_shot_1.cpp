#include <iostream>
#include <vector>
#include <queue>
#include <algorithm>

using namespace std;

const int MAX_NODES = 100005;
vector<int> adj[MAX_NODES];
int parent[MAX_NODES];
bool visited[MAX_NODES];

void bfs(int start) {
    queue<int> q;
    q.push(start);
    visited[start] = true;
    parent[start] = -1;

    while (!q.empty()) {
        int u = q.front();
        q.pop();

        for (int v : adj[u]) {
            if (!visited[v]) {
                visited[v] = true;
                parent[v] = u;
                q.push(v);
            }
        }
    }
}

void print_path(int end) {
    vector<int> path;
    for (int at = end; at != -1; at = parent[at])
        path.push_back(at);
    reverse(path.begin(), path.end());

    cout << path.size() << "\n";
    for (int node : path)
        cout << node << " ";
    cout << "\n";
}

int main() {
    int n, m;
    cin >> n >> m;

    for (int i = 0; i < m; i++) {
        int u, v;
        cin >> u >> v;
        adj[u].push_back(v);
        adj[v].push_back(u);
    }

    bfs(1);

    if (!visited[n])
        cout << "IMPOSSIBLE\n";
    else
        print_path(n);

    return 0;
}