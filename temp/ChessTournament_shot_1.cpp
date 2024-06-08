#include <iostream>
#include <vector>
#include <queue>
#include <utility>

using namespace std;

int main() {
    int n;
    cin >> n;
    vector<int> x(n);
    int total_games = 0;

    for (int i = 0; i < n; ++i) {
        cin >> x[i];
        total_games += x[i];
    }

    if (total_games % 2 != 0) {
        cout << "IMPOSSIBLE" << endl;
        return 0;
    }

    priority_queue<pair<int, int>> pq;
    for (int i = 0; i < n; ++i) {
        if (x[i] > 0) {
            pq.push({x[i], i + 1});
        }
    }

    vector<pair<int, int>> games;
    while (pq.size() > 1) {
        auto top1 = pq.top(); pq.pop();
        auto top2 = pq.top(); pq.pop();

        games.push_back({top1.second, top2.second});
        
        top1.first--;
        top2.first--;

        if (top1.first > 0) pq.push(top1);
        if (top2.first > 0) pq.push(top2);
    }

    if (!pq.empty() && pq.top().first > 0) {
        cout << "IMPOSSIBLE" << endl;
    } else {
        cout << games.size() << endl;
        for (const auto& game : games) {
            cout << game.first << " " << game.second << endl;
        }
    }

    return 0;
}
