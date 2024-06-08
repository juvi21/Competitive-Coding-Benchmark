#include <iostream>
#include <vector>
#include <algorithm>

using namespace std;

struct Point {
    long long x, y;
    bool operator<(const Point& p) const {
        return x < p.x || (x == p.x && y < p.y);
    }
};

long long cross(const Point& O, const Point& A, const Point& B) {
    return (A.x - O.x) * (B.y - O.y) - (A.y - O.y) * (B.x - O.x);
}

vector<Point> convexHull(vector<Point>& points) {
    int n = points.size(), k = 0;
    if (n <= 3) return points;

    vector<Point> hull(2 * n);

    // Sort points lexicographically
    sort(points.begin(), points.end());

    // Build lower hull
    for (int i = 0; i < n; ++i) {
        while (k >= 2 && cross(hull[k - 2], hull[k - 1], points[i]) <= 0) k--;
        hull[k++] = points[i];
    }

    // Build upper hull
    for (int i = n - 1, t = k + 1; i >= 0; --i) {
        while (k >= t && cross(hull[k - 2], hull[k - 1], points[i]) <= 0) k--;
        hull[k++] = points[i];
    }

    hull.resize(k - 1);
    return hull;
}

int main() {
    int n;
    cin >> n;
    vector<Point> points(n);
    for (int i = 0; i < n; ++i) {
        cin >> points[i].x >> points[i].y;
    }

    vector<Point> hull = convexHull(points);
    cout << hull.size() << "\n";
    for (const Point& p : hull) {
        cout << p.x << " " << p.y << "\n";
    }

    return 0;
}
