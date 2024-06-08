#include <iostream>
#include <vector>
#include <algorithm>

using namespace std;

int main() {
    int n;
    cin >> n;

    vector<pair<int, int>> events(2 * n);
    for (int i = 0; i < n; i++) {
        cin >> events[i].first >> events[i + n].first;
        events[i].second = 1;
        events[i + n].second = -1;
    }

    sort(events.begin(), events.end());

    int max_customers = 0, current_customers = 0;
    for (auto event : events) {
        current_customers += event.second;
        max_customers = max(max_customers, current_customers);
    }

    cout << max_customers << endl;

    return 0;
}