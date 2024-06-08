#include <iostream>
#include <vector>
#include <queue>

using namespace std;

int main() {
    int n, m;
    cin >> n >> m;

    vector<vector<int>> graph(n + 1);
    vector<int> in_degree(n + 1, 0);

    for (int i = 0; i < m; i++) {
        int a, b;
        cin >> a >> b;
        graph[a].push_back(b);
        in_degree[b]++;
    }

    queue<int> q;
    for (int i = 1; i <= n; i++) {
        if (in_degree[i] == 0) {
            q.push(i);
        }
    }

    vector<int> result;
    while (!q.empty()) {
        int course = q.front();
        q.pop();
        result.push_back(course);

        for (int adjacent_course : graph[course]) {
            in_degree[adjacent_course]--;
            if (in_degree[adjacent_course] == 0) {
                q.push(adjacent_course);
            }
        }
    }

    if (result.size() == n) {
        for (int course : result) {
            cout << course << " ";
        }
    } else {
        cout << "IMPOSSIBLE";
    }

    return 0;
}