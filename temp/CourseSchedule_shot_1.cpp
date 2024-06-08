#include <iostream>
#include <vector>
#include <queue>

using namespace std;

vector<int> findCourseOrder(int n, int m, vector<pair<int, int>>& prerequisites) {
    vector<vector<int>> adj(n + 1);
    vector<int> in_degree(n + 1, 0);
    vector<int> result;

    // Build the graph and in-degree array
    for (auto& pre : prerequisites) {
        int u = pre.first;
        int v = pre.second;
        adj[u].push_back(v);
        in_degree[v]++;
    }

    // Initialize the queue with nodes having in-degree 0
    queue<int> q;
    for (int i = 1; i <= n; ++i) {
        if (in_degree[i] == 0) {
            q.push(i);
        }
    }

    // Process the nodes
    while (!q.empty()) {
        int u = q.front();
        q.pop();
        result.push_back(u);

        for (int v : adj[u]) {
            in_degree[v]--;
            if (in_degree[v] == 0) {
                q.push(v);
            }
        }
    }

    // Check if we have a valid topological sort
    if (result.size() == n) {
        return result;
    } else {
        return {}; // Impossible case
    }
}

int main() {
    int n, m;
    cin >> n >> m;
    vector<pair<int, int>> prerequisites(m);
    for (int i = 0; i < m; ++i) {
        cin >> prerequisites[i].first >> prerequisites[i].second;
    }

    vector<int> order = findCourseOrder(n, m, prerequisites);

    if (order.empty()) {
        cout << "IMPOSSIBLE" << endl;
    } else {
        for (int course : order) {
            cout << course << " ";
        }
        cout << endl;
    }

    return 0;
}
