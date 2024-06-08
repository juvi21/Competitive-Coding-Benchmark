#include <iostream>
#include <vector>
#include <queue>

using namespace std;

const int MAX_N = 100000;
vector<int> adj[MAX_N + 1];
int color[MAX_N + 1];

bool bfs(int start) {
    queue<int> q;
    q.push(start);
    color[start] = 1;  // Start coloring with 1

    while (!q.empty()) {
        int node = q.front();
        q.pop();
        
        for (int neighbor : adj[node]) {
            if (color[neighbor] == 0) {
                // If neighbor is not colored, color it with a different color
                color[neighbor] = 3 - color[node];
                q.push(neighbor);
            } else if (color[neighbor] == color[node]) {
                // If neighbor is colored with the same color, we can't bipartite
                return false;
            }
        }
    }
    return true;
}

int main() {
    int n, m;
    cin >> n >> m;

    for (int i = 0; i < m; i++) {
        int a, b;
        cin >> a >> b;
        adj[a].push_back(b);
        adj[b].push_back(a);
    }

    // Initialize colors to 0 (uncolored)
    fill(color, color + n + 1, 0);

    for (int i = 1; i <= n; i++) {
        if (color[i] == 0) {
            if (!bfs(i)) {
                cout << "IMPOSSIBLE" << endl;
                return 0;
            }
        }
    }

    for (int i = 1; i <= n; i++) {
        cout << color[i] << " ";
    }
    cout << endl;

    return 0;
}
