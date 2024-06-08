#include <iostream>
#include <vector>
#include <limits>
#include <algorithm>

using namespace std;

struct Edge {
    int u, v;
    long long weight;
};

const long long INF = numeric_limits<long long>::max();

int main() {
    int n, m;
    cin >> n >> m;
    
    vector<Edge> edges(m);
    for (int i = 0; i < m; ++i) {
        cin >> edges[i].u >> edges[i].v >> edges[i].weight;
    }
    
    vector<long long> dist(n + 1, INF);
    vector<int> parent(n + 1, -1);
    dist[1] = 0;
    
    int x = -1;
    for (int i = 0; i < n; ++i) {
        x = -1;
        for (const auto& edge : edges) {
            if (dist[edge.u] < INF && dist[edge.u] + edge.weight < dist[edge.v]) {
                dist[edge.v] = dist[edge.u] + edge.weight;
                parent[edge.v] = edge.u;
                x = edge.v;
            }
        }
    }
    
    if (x == -1) {
        cout << "NO" << endl;
    } else {
        for (int i = 0; i < n; ++i) {
            x = parent[x];
        }
        
        vector<int> cycle;
        for (int v = x; ; v = parent[v]) {
            cycle.push_back(v);
            if (v == x && cycle.size() > 1) break;
        }
        reverse(cycle.begin(), cycle.end());
        
        cout << "YES" << endl;
        for (int v : cycle) {
            cout << v << " ";
        }
        cout << endl;
    }
    
    return 0;
}
