#include <iostream>
#include <vector>
#include <cmath>
#include <algorithm>

using namespace std;

void findMinDifference(const vector<int>& weights, int n, int index, long long currentSum, long long totalSum, long long& minDiff) {
    if (index == n) {
        long long otherGroupSum = totalSum - currentSum;
        minDiff = min(minDiff, abs(currentSum - otherGroupSum));
        return;
    }
    // Include the current apple in the current subset
    findMinDifference(weights, n, index + 1, currentSum + weights[index], totalSum, minDiff);
    // Exclude the current apple from the current subset
    findMinDifference(weights, n, index + 1, currentSum, totalSum, minDiff);
}

int main() {
    int n;
    cin >> n;
    vector<int> weights(n);
    long long totalSum = 0;
    
    for (int i = 0; i < n; ++i) {
        cin >> weights[i];
        totalSum += weights[i];
    }
    
    long long minDiff = LLONG_MAX;
    findMinDifference(weights, n, 0, 0, totalSum, minDiff);
    
    cout << minDiff << endl;
    return 0;
}
