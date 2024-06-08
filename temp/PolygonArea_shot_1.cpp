#include <iostream>
#include <vector>
using namespace std;

int main() {
    int n;
    cin >> n;

    vector<pair<int, int>> vertices(n);
    for (int i = 0; i < n; i++) {
        cin >> vertices[i].first >> vertices[i].second;
    }

    long long area = 0;
    for (int i = 0; i < n; i++) {
        int j = (i + 1) % n;
        area += (long long)vertices[i].first * vertices[j].second;
        area -= (long long)vertices[j].first * vertices[i].second;
    }

    cout << abs(area) << endl;
    return 0;
}