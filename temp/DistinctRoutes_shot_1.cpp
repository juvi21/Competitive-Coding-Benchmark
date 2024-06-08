#include <iostream>
#include <vector>
#include <queue>
#include <algorithm>
#include <cstring>

using namespace std;

const int MAXN = 500;
const int INF = 1e9;

int n, m;
vector<int> adj[MAXN + 1];
int capacity[MAXN + 1][MAXN + 1];
int parent[MAXN + 1];

bool bfs(int s, int t) {
    memset(parent, -1, sizeof(parent));
    queue<pair<int, int>> q;
    q.push({s, INF});

    while (!q.empty()) {
        int cur = q.front().first;
        int flow = q.front().second;
        q.pop();

        for (int next : adj[cur]) {
            if (parent[next] == -1 && capacity[cur][next]) {
                parent[next] = cur;
                int new_flow = min(flow, capacity[cur][next]);
                if (next == t) {
                    return true;
                }
                q.push({next, new_flow});
            }
        }
    }

    return false;
}

int edmonds_karp(int s, int t) {
    int flow = 0;

    while (bfs(s, t)) {
        int cur = t;
        int cur_flow = INF;

        while (cur != s) {
            int prev = parent[cur];
            cur_flow = min(cur_flow, capacity[prev][cur]);
            cur = prev;
        }

        cur = t;
        while (cur != s) {
            int prev = parent[cur];
            capacity[prev][cur] -= cur_flow;
            capacity[cur][prev] += cur_flow;
            cur = prev;
        }

        flow += cur_flow;
    }

    return flow;
}

void find_paths(int s, int t, vector<vector<int>>& paths) {
    bool visited[MAXN + 1];
    while (true) {
        memset(visited, false, sizeof(visited));
        vector<int> path;
        queue<int> q;
        q.push(s);
        visited[s] = true;
        bool found = false;

        while (!q.empty() && !found) {
            int cur = q.front();
            q.pop();
            path.push_back(cur);

            for (int next : adj[cur]) {
                if (!visited[next] && capacity[cur][next] == 0 && capacity[next][cur] == 1) {
                    visited[next] = true;
                    q.push(next);
                    if (next == t) {
                        found = true;
                        break;
                    }
                }
            }

            if (found) {
                path.push_back(t);
                break;
            }
        }

        if (!found) break;

        paths.push_back(path);

        for (size_t i = 0; i < path.size() - 1; ++i) {
            int u = path[i];
            int v = path[i + 1];
            capacity[v][u] -= 1;
        }
    }
}

int main() {
    cin >> n >> m;

    for (int i = 0; i < m; ++i) {
        int a, b;
        cin >> a >> b;
        adj[a].push_back(b);
        adj[b].push_back(a);
        capacity[a][b] = 1;
    }

    int max_flow = edmonds_karp(1, n);

    vector<vector<int>> paths;
    find_paths(1, n, paths);

    cout << max_flow << endl;
    for (const auto& path : paths) {
        cout << path.size() << endl;
        for (int room : path) {
            cout << room << " ";
        }
        cout << endl;
    }

    return 0;
}
