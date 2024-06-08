#include <iostream>
#include <vector>
using namespace std;

bool isPossible(vector<long long>& prefixSum, long long mid, int k) {
    int count = 1;
    long long currSum = 0;
    for (int i = 0; i < prefixSum.size(); i++) {
        if (prefixSum[i] - currSum > mid) {
            count++;
            currSum = prefixSum[i - 1];
        }
        if (count > k) {
            return false;
        }
    }
    return true;
}

int main() {
    int n, k;
    cin >> n >> k;
    vector<long long> arr(n);
    vector<long long> prefixSum(n);
    long long maxElement = 0;
    long long sum = 0;
    for (int i = 0; i < n; i++) {
        cin >> arr[i];
        maxElement = max(maxElement, arr[i]);
        sum += arr[i];
        prefixSum[i] = sum;
    }
    long long left = maxElement;
    long long right = sum;
    long long result = 0;
    while (left <= right) {
        long long mid = (left + right) / 2;
        if (isPossible(prefixSum, mid, k)) {
            result = mid;
            right = mid - 1;
        } else {
            left = mid + 1;
        }
    }
    cout << result << endl;
    return 0;
}