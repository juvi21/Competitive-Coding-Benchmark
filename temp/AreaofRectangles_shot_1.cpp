#include <iostream>
#include <vector>
#include <algorithm>
#include <map>

using namespace std;

struct Event {
    int x, y1, y2, type;
    Event(int x, int y1, int y2, int type) : x(x), y1(y1), y2(y2), type(type) {}
    bool operator<(const Event &e) const {
        return x < e.x;
    }
};

struct SegmentTree {
    vector<int> count, length;
    vector<int> y_coords;
    SegmentTree(int n) : count(4 * n), length(4 * n) {}

    void build(const vector<int> &ys) {
        y_coords = ys;
    }

    void update(int node, int start, int end, int l, int r, int value) {
        if (start >= r || end <= l) return;
        if (start >= l && end <= r) {
            count[node] += value;
        } else {
            int mid = (start + end) / 2;
            update(2 * node + 1, start, mid, l, r, value);
            update(2 * node + 2, mid, end, l, r, value);
        }
        if (count[node] > 0) {
            length[node] = y_coords[end] - y_coords[start];
        } else if (start + 1 == end) {
            length[node] = 0;
        } else {
            length[node] = length[2 * node + 1] + length[2 * node + 2];
        }
    }

    int query() {
        return length[0];
    }
};

int main() {
    int n;
    cin >> n;
    vector<Event> events;
    vector<int> y_coords;

    for (int i = 0; i < n; ++i) {
        int x1, y1, x2, y2;
        cin >> x1 >> y1 >> x2 >> y2;
        events.emplace_back(x1, y1, y2, 1);
        events.emplace_back(x2, y1, y2, -1);
        y_coords.push_back(y1);
        y_coords.push_back(y2);
    }

    sort(events.begin(), events.end());
    sort(y_coords.begin(), y_coords.end());
    y_coords.erase(unique(y_coords.begin(), y_coords.end()), y_coords.end());

    SegmentTree segTree(y_coords.size());
    segTree.build(y_coords);

    long long result = 0;
    int prev_x = events[0].x;

    for (const auto &event : events) {
        int x = event.x;
        int y1 = lower_bound(y_coords.begin(), y_coords.end(), event.y1) - y_coords.begin();
        int y2 = lower_bound(y_coords.begin(), y_coords.end(), event.y2) - y_coords.begin();

        result += (x - prev_x) * segTree.query();
        segTree.update(0, 0, y_coords.size(), y1, y2, event.type);
        prev_x = x;
    }

    cout << result << endl;
    return 0;
}
