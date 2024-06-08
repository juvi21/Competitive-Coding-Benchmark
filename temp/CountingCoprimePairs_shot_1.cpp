#include <iostream>
#include <vector>
#include <algorithm>
#include <numeric>
using namespace std;

const int MAXN = 1000000;

vector<int> calculateTotient(int n) {
    vector<int> phi(n + 1);
    iota(phi.begin(), phi.end(), 0); // phi[i] = i
    
    for (int i = 2; i <= n; i++) {
        if (phi[i] == i) { // i is prime
            for (int j = i; j <= n; j += i) {
                phi[j] = phi[j] * (i - 1) / i;
            }
        }
    }
    return phi;
}

int main() {
    int n;
    cin >> n;
    vector<int> arr(n);
    vector<int> freq(MAXN + 1, 0);
    
    for (int i = 0; i < n; i++) {
        cin >> arr[i];
        freq[arr[i]]++;
    }
    
    vector<int> phi = calculateTotient(MAXN);
    vector<long long> prefixSum(MAXN + 1, 0);
    
    // Calculate prefix sums of frequencies
    for (int i = 1; i <= MAXN; i++) {
        prefixSum[i] = prefixSum[i - 1] + freq[i];
    }
    
    long long coprimePairs = 0;
    
    // Calculate coprime pairs
    for (int i = 1; i <= MAXN; i++) {
        if (freq[i] > 0) {
            for (int j = 1; j <= MAXN / i; j++) {
                if (__gcd(i, j) == 1) {
                    coprimePairs += freq[i] * (prefixSum[min(MAXN, (j + 1) * i - 1)] - prefixSum[j * i - 1]);
                }
            }
        }
    }
    
    cout << coprimePairs / 2 << endl; // Each pair is counted twice
    return 0;
}
