#include <bits/stdc++.h>
using namespace std;

const int MAX_NODES = 100005;
const long long MOD = 1e9 + 7;

struct Edge {
    int destination;
    long long weight;
};

vector<Edge> graph[MAX_NODES];
long long distances[MAX_NODES];
long long ways[MAX_NODES];
int min_steps[MAX_NODES];
int max_steps[MAX_NODES];

void dijkstra(int start_node, int end_node) {
    priority_queue<pair<long long, int>, vector<pair<long long, int>>, greater<pair<long long, int>>> pq;
    pq.push({0, start_node});
    fill(distances, distances + MAX_NODES, LONG_LONG_MAX);
    distances[start_node] = 0;
    ways[start_node] = 1;
    min_steps[start_node] = 0;
    max_steps[start_node] = 0;

    while (!pq.empty()) {
        long long distance = pq.top().first;
        int node = pq.top().second;
        pq.pop();

        if (distance != distances[node]) continue;

        for (Edge edge : graph[node]) {
            if (distances[edge.destination] > distances[node] + edge.weight) {
                distances[edge.destination] = distances[node] + edge.weight;
                ways[edge.destination] = ways[node];
                min_steps[edge.destination] = min_steps[node] + 1;
                max_steps[edge.destination] = max_steps[node] + 1;
                pq.push({distances[edge.destination], edge.destination});
            } else if (distances[edge.destination] == distances[node] + edge.weight) {
                ways[edge.destination] = (ways[edge.destination] + ways[node]) % MOD;
                min_steps[edge.destination] = min(min_steps[edge.destination], min_steps[node] + 1);
                max_steps[edge.destination] = max(max_steps[edge.destination], max_steps[node] + 1);
            }
        }
    }
}

int main() {
    int num_nodes, num_edges;
    cin >> num_nodes >> num_edges;

    for (int i = 0; i < num_edges; i++) {
        int u, v, w;
        cin >> u >> v >> w;
        graph[u].push_back({v, w});
    }

    dijkstra(1, num_nodes);

    cout << distances[num_nodes] << " " << ways[num_nodes] << " " << min_steps[num_nodes] << " " << max_steps[num_nodes] << endl;

    return 0;
}