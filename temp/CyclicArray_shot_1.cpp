#include <iostream>
#include <vector>
using namespace std;

int minSubarrays(const vector<int>& arr, int n, long long k) {
    int subarrayCount = 0;
    long long currentSum = 0;

    for (int i = 0; i < 2 * n; ++i) {
        // Get the current element in the cyclic manner
        int val = arr[i % n];
        
        // If adding this value exceeds k, start a new subarray
        if (currentSum + val > k) {
            subarrayCount++;
            currentSum = val; // start new subarray with the current element
        } else {
            currentSum += val;
        }

        // If we have iterated over n elements, break
        if (i >= n - 1 && subarrayCount > 0) {
            break;
        }
    }
    
    // Account for the last subarray
    if (currentSum > 0) {
        subarrayCount++;
    }

    return subarrayCount;
}

int main() {
    int n;
    long long k;
    cin >> n >> k;
    vector<int> arr(n);
    for (int i = 0; i < n; ++i) {
        cin >> arr[i];
    }

    cout << minSubarrays(arr, n, k) << endl;

    return 0;
}
