#include <iostream>
#include <vector>
#include <queue>

using namespace std;

vector<int> findCourseOrder(int n, vector<pair<int, int>>& prerequisites) {
    vector<vector<int>> adj(n + 1);
    vector<int> inDegree(n + 1, 0);
    for (const auto& pre : prerequisites) {
        adj[pre.first].push_back(pre.second);
        inDegree[pre.second]++;
    }

    priority_queue<int, vector<int>, greater<int>> zeroInDegreeQueue;
    for (int i = 1; i <= n; ++i) {
        if (inDegree[i] == 0) {
            zeroInDegreeQueue.push(i);
        }
    }

    vector<int> courseOrder;
    while (!zeroInDegreeQueue.empty()) {
        int course = zeroInDegreeQueue.top();
        zeroInDegreeQueue.pop();
        courseOrder.push_back(course);

        for (int nextCourse : adj[course]) {
            if (--inDegree[nextCourse] == 0) {
                zeroInDegreeQueue.push(nextCourse);
            }
        }
    }
    
    return courseOrder;
}

int main() {
    int n, m;
    cin >> n >> m;
    vector<pair<int, int>> prerequisites(m);
    for (int i = 0; i < m; ++i) {
        cin >> prerequisites[i].first >> prerequisites[i].second;
    }
    
    vector<int> courseOrder = findCourseOrder(n, prerequisites);
    for (int course : courseOrder) {
        cout << course << " ";
    }
    cout << endl;

    return 0;
}
