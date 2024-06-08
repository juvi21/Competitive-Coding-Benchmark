#include <iostream>
#include <vector>
#include <algorithm>

using namespace std;

const int MAXN = 100000;

vector<int> graph[MAXN];
bool visited[MAXN];
int discovery[MAXN], low[MAXN], parent[MAXN];
bool isCritical[MAXN];
int timeCounter;

void findArticulationPoints(int u) {
    visited[u] = true;
    discovery[u] = low[u] = ++timeCounter;
    int children = 0;

    for (int v : graph[u]) {
        if (!visited[v]) {
            children++;
            parent[v] = u;
            findArticulationPoints(v);

            low[u] = min(low[u], low[v]);

            if (parent[u] == -1 && children > 1) {
                isCritical[u] = true;
            }

            if (parent[u] != -1 && low[v] >= discovery[u]) {
                isCritical[u] = true;
            }
        } else if (v != parent[u]) {
            low[u] = min(low[u], discovery[v]);
        }
    }
}

int main() {
    int n, m;
    cin >> n >> m;

    for (int i = 0; i < m; i++) {
        int a, b;
        cin >> a >> b;
        graph[a].push_back(b);
        graph[b].push_back(a); // As it's a bidirectional graph
    }

    timeCounter = 0;
    fill(visited, visited + n + 1, false);
    fill(discovery, discovery + n + 1, -1);
    fill(low, low + n + 1, -1);
    fill(parent, parent + n + 1, -1);
    fill(isCritical, isCritical + n + 1, false);

    findArticulationPoints(1);

    vector<int> result;
    for (int i = 1; i <= n; i++) {
        if (isCritical[i]) {
            result.push_back(i);
        }
    }

    sort(result.begin(), result.end());

    cout << result.size() << "\n";
    for (int city : result) {
        cout << city << " ";
    }
    cout << "\n";

    return 0;
}
