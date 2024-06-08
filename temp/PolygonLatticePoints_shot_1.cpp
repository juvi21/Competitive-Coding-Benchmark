#include <iostream>
#include <vector>
#include <algorithm>
#include <cmath>

using namespace std;

typedef long long ll;
typedef pair<ll, ll> Point;

ll gcd(ll a, ll b) {
    return b == 0 ? a : gcd(b, a % b);
}

ll shoelaceFormula(vector<Point>& points) {
    ll area = 0;
    int n = points.size();
    for (int i = 0; i < n; i++) {
        area += points[i].first * points[(i + 1) % n].second - points[i].second * points[(i + 1) % n].first;
    }
    return abs(area) / 2;
}

ll boundaryPoints(vector<Point>& points) {
    ll count = 0;
    int n = points.size();
    for (int i = 0; i < n; i++) {
        count += gcd(abs(points[i].first - points[(i + 1) % n].first), abs(points[i].second - points[(i + 1) % n].second));
    }
    return count;
}

int main() {
    int n;
    cin >> n;
    vector<Point> points(n);
    for (int i = 0; i < n; i++) {
        cin >> points[i].first >> points[i].second;
    }
    ll area = shoelaceFormula(points);
    ll boundary = boundaryPoints(points);
    ll interior = area - boundary / 2 + 1;
    cout << interior << " " << boundary << endl;
    return 0;
}