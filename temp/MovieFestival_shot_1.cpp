#include <iostream>
#include <algorithm>
#include <vector>

using namespace std;

int main() {
    int n;
    cin >> n;

    vector<pair<int, int>> movies(n);
    for (int i = 0; i < n; i++) {
        cin >> movies[i].first >> movies[i].second;
    }

    sort(movies.begin(), movies.end(), [](const pair<int, int>& a, const pair<int, int>& b) {
        return a.second < b.second;
    });

    int count = 1;
    int lastEnd = movies[0].second;
    for (int i = 1; i < n; i++) {
        if (movies[i].first >= lastEnd) {
            count++;
            lastEnd = movies[i].second;
        }
    }

    cout << count << endl;

    return 0;
}