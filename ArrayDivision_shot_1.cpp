#include <iostream>
#include <vector>
#include <algorithm>
#include <numeric>

using namespace std;

bool canDivide(const vector<int>& arr, int n, int k, long long maxSum) {
    long long currentSum = 0;
    int subarrays = 1;
    
    for (int i = 0; i < n; ++i) {
        if (currentSum + arr[i] > maxSum) {
            currentSum = arr[i];
            ++subarrays;
            if (subarrays > k) {
                return false;
            }
        } else {
            currentSum += arr[i];
        }
    }
    
    return true;
}

int main() {
    int n, k;
    cin >> n >> k;
    vector<int> arr(n);
    
    for (int i = 0; i < n; ++i) {
        cin >> arr[i];
    }
    
    long long left = *max_element(arr.begin(), arr.end());
    long long right = accumulate(arr.begin(), arr.end(), 0LL);
    long long result = right;
    
    while (left <= right) {
        long long mid = left + (right - left) / 2;
        
        if (canDivide(arr, n, k, mid)) {
            result = mid;
            right = mid - 1;
        } else {
            left = mid + 1;
        }
    }
    
    cout << result << endl;
    
    return 0;
}