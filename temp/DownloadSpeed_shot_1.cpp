#include <iostream>
#include <vector>
#include <queue>
#include <climits>
#include <cstring>

using namespace std;

const int MAXN = 500;

// Function to perform BFS and find if there is a path from source to sink
bool bfs(int rGraph[MAXN][MAXN], int s, int t, int parent[]) {
    bool visited[MAXN];
    memset(visited, 0, sizeof(visited));
    queue<int> q;
    q.push(s);
    visited[s] = true;
    parent[s] = -1;

    while (!q.empty()) {
        int u = q.front();
        q.pop();

        for (int v = 0; v < MAXN; v++) {
            if (!visited[v] && rGraph[u][v] > 0) {
                if (v == t) {
                    parent[v] = u;
                    return true;
                }
                q.push(v);
                parent[v] = u;
                visited[v] = true;
            }
        }
    }
    return false;
}

// Function to implement the Edmonds-Karp algorithm
int edmondsKarp(int graph[MAXN][MAXN], int s, int t) {
    int u, v;
    int rGraph[MAXN][MAXN]; // Residual graph
    for (u = 0; u < MAXN; u++)
        for (v = 0; v < MAXN; v++)
            rGraph[u][v] = graph[u][v];

    int parent[MAXN]; // Array to store the path
    int max_flow = 0; // Initial flow is 0

    // Augment the flow while there is a path from source to sink
    while (bfs(rGraph, s, t, parent)) {
        int path_flow = INT_MAX;

        for (v = t; v != s; v = parent[v]) {
            u = parent[v];
            path_flow = min(path_flow, rGraph[u][v]);
        }

        for (v = t; v != s; v = parent[v]) {
            u = parent[v];
            rGraph[u][v] -= path_flow;
            rGraph[v][u] += path_flow;
        }

        max_flow += path_flow;
    }

    return max_flow;
}

int main() {
    int n, m;
    cin >> n >> m;

    int graph[MAXN][MAXN] = {0};

    for (int i = 0; i < m; i++) {
        int a, b, c;
        cin >> a >> b >> c;
        graph[a-1][b-1] += c;
    }

    cout << edmondsKarp(graph, 0, n-1) << endl;

    return 0;
}
