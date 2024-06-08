#include <bits/stdc++.h>
using namespace std;

const int MAX_NODES = 100005;
const long long INF = 1e18;

int numNodes, numEdges;
vector<pair<int, int>> graph[MAX_NODES];
long long dist[MAX_NODES][2];

void dijkstra() {
    priority_queue<pair<long long, pair<int, int>>, vector<pair<long long, pair<int, int>>>, greater<pair<long long, pair<int, int>>>> pq;
    pq.push({0, {1, 0}});

    while (!pq.empty()) {
        long long cost = pq.top().first;
        int node = pq.top().second.first;
        int usedCoupon = pq.top().second.second;
        pq.pop();

        if (dist[node][usedCoupon] < cost) continue;

        for (auto &edge : graph[node]) {
            int nextNode = edge.first;
            int edgeCost = edge.second;

            if (dist[nextNode][usedCoupon] > dist[node][usedCoupon] + edgeCost) {
                dist[nextNode][usedCoupon] = dist[node][usedCoupon] + edgeCost;
                pq.push({dist[nextNode][usedCoupon], {nextNode, usedCoupon}});
            }

            if (usedCoupon == 0 && dist[nextNode][1] > dist[node][0] + edgeCost / 2) {
                dist[nextNode][1] = dist[node][0] + edgeCost / 2;
                pq.push({dist[nextNode][1], {nextNode, 1}});
            }
        }
    }
}

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    cout.tie(NULL);

    cin >> numNodes >> numEdges;

    for (int i = 1; i <= numEdges; i++) {
        int u, v, w;
        cin >> u >> v >> w;
        graph[u].push_back({v, w});
    }

    for (int i = 1; i <= numNodes; i++) {
        dist[i][0] = dist[i][1] = INF;
    }

    dist[1][0] = dist[1][1] = 0;
    dijkstra();

    cout << min(dist[numNodes][0], dist[numNodes][1]);

    return 0;
}