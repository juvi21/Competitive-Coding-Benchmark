#include <iostream>
#include <vector>
#include <algorithm>

using namespace std;

int main() {
    int n, m, k;
    cin >> n >> m >> k;
    
    vector<int> desiredSizes(n);
    vector<int> apartmentSizes(m);
    
    for (int i = 0; i < n; ++i) {
        cin >> desiredSizes[i];
    }
    
    for (int i = 0; i < m; ++i) {
        cin >> apartmentSizes[i];
    }
    
    sort(desiredSizes.begin(), desiredSizes.end());
    sort(apartmentSizes.begin(), apartmentSizes.end());
    
    int i = 0, j = 0;
    int matches = 0;
    
    while (i < n && j < m) {
        if (abs(desiredSizes[i] - apartmentSizes[j]) <= k) {
            ++matches;
            ++i;
            ++j;
        } else if (desiredSizes[i] < apartmentSizes[j]) {
            ++i;
        } else {
            ++j;
        }
    }
    
    cout << matches << endl;
    
    return 0;
}
